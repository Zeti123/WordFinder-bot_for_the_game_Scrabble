#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "ui_language_window.h"

#include "UiController.hpp"
#include "Program.hpp"
#include "LineTextScrabbleTextEdit.hpp"
#include "RadioButtonSwitch.hpp"
#include "NewWordAdder.hpp"
#include "IUserLettersDisplay.hpp"
#include "ListViewBasedUserLetters.hpp"
#include "UserLettersAdder.hpp"
#include "SearchEngineFactory.hpp"
#include "LettersRenumberer.hpp"
#include "TextureHandler.hpp"
#include "UserLettersModel.hpp"
#include "UserLettersDelegate.hpp"
#include "PolishDebugRenumberer.hpp"
#include "PutWordOnGameBoardCommand.hpp"
#include "EraseFromGameBoardCommand.hpp"
#include "SelectWordFromListCommand.hpp"
#include "PutAndSaveWordOnGameBoardCommand.hpp"
#include "CommandListManager.hpp"
#include "GameBoardTilesEraser.hpp"
#include "SetUserLettersCommand.hpp"
#include "ShowUserLettersCommand.hpp"
#include "SearchListController.hpp"
#include "TimeTraveler.hpp"
#include "ShowWordFromListCommand.hpp"
#include "FileReadHelpers.hpp"
#include "FilesystemHandlerFactory.hpp"

#include "GameBoardDisplayFactory.hpp"
#include "ResultsListsFactory.hpp"

#include "AlgorithmModule/log.hpp"

#include <cmath>

#include <QScrollBar>
#include <QScreen>
#include <QMessageBox>


void MainWindow::resizeWindow()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  rec = screen->geometry();
    auto height = rec.height();
    auto width = rec.width();

    QSize windowSize = QSize(1239, 966);
    std::size_t tileSize = 59;

    if (width <= windowSize.width() || height <= windowSize.height())
    {
        windowSize = QSize(969, 696);
        tileSize = 41;
    }
    resize(windowSize);
    qApp->processEvents();

    tileSize = std::ceil((std::max(ui->game_board->width(), ui->game_board->height())-2) / 15.0);
    ui->game_board->horizontalHeader()->setDefaultSectionSize(tileSize);
    ui->game_board->verticalHeader()->setDefaultSectionSize(tileSize);
}

void MainWindow::setUpMainWindow(const std::unique_ptr<IFilesystemHandler>& filesystemHandler, const QString& language)
{
    uiMenu->stackedWidget->setCurrentIndex(1);
    uiMenu->loading_bar->setValue(1);

    LanguageInfo languageInfo = filesystemHandler->getLanguageInfo(language);
    auto allLetters = getAllLetters(languageInfo);
#ifndef DEBUG
    auto lettersRenumberer = std::make_shared<LettersRenumberer>(allLetters);
#else
    auto lettersRenumberer = std::make_shared<PolishDebugRenumberer>();
#endif
    auto lettersInfo = std::make_shared<LettersInfo>(getLettersInfo(languageInfo, lettersRenumberer));
    auto textureHandler = std::make_shared<TextureHandler>(L"Resources/Tiles/", lettersRenumberer, lettersInfo);
    uiMenu->loading_bar->setValue(33);
    auto listOfWords = convertFromQStringVector(languageInfo.listOfWords, lettersRenumberer);
    uiMenu->loading_bar->setValue(66);
    auto threadInformer = ThreadInformer();
    auto searchEngine = SearchEngineFactory::create(listOfWords, *lettersInfo, threadInformer);
    uiMenu->loading_bar->setValue(100);
    ui->setupUi(this);


    ui->user_letters->setItemDelegate(new UserLettersDelegate(textureHandler));
    ui->user_letters->setModel(new UserLettersModel());

    auto searchBar = std::make_shared<LineTextScrabbleTextEdit>(*ui->search_bar, lettersRenumberer);

    auto wordsList = ResultsListsFactory().create(*ui->list_of_words, lettersRenumberer);

    auto board = GameBoardDisplayFactory().create(*ui->game_board, textureHandler);
    auto newWordLineEdit = std::make_shared<LineTextScrabbleTextEdit>(*ui->word_adder, lettersRenumberer);
    auto orientationSwitch = std::make_shared<RadioButtonSwitch>(*ui->orientation_vertical, *ui->orientation_horizontal, false);
    auto userLettersDisplay = std::make_shared<ListViewBasedUserLetters>(*ui->user_letters);
    auto scrabbleTextEdit = std::make_shared<LineTextScrabbleTextEdit>(*ui->user_letters_line_edit, lettersRenumberer, true);

    auto commandList = std::make_shared<CommandListManager>();
    auto eraseFromGameBoardCommand = std::make_shared<EraseFromGameBoardCommand>(board);
    auto putWordOnGameBoardCommand = std::make_shared<PutWordOnGameBoardCommand>(board, newWordLineEdit, orientationSwitch);
    auto putAndSaveWordOnGameBoardCommand = std::make_shared<PutAndSaveWordOnGameBoardCommand>(board, newWordLineEdit, orientationSwitch);
    auto showWordFromListCommand = std::make_shared<ShowWordFromListCommand>(board, wordsList);
    auto selectWordFromListCommand = std::make_shared<SelectWordFromListCommand>(board, wordsList);
    auto setUserLettersCommand = std::make_shared<SetUserLettersCommand>(userLettersDisplay, scrabbleTextEdit);
    auto showUserLettersCommand = std::make_shared<ShowUserLettersCommand>(userLettersDisplay, scrabbleTextEdit);

    auto eraseSwitch = std::make_shared<RadioButtonSwitch>(*ui->erase_on, *ui->erase_of, false);
    auto gameBoardTilesEraser = std::make_shared<GameBoardTilesEraser>(eraseSwitch, eraseFromGameBoardCommand, commandList);
    connect(board.get(), &IGameBoardDisplay::selectionChanged, gameBoardTilesEraser.get(), &GameBoardTilesEraser::receiveGameBoardSelectionChange);

    auto newWordAdder = std::make_shared<NewWordAdder>(orientationSwitch, newWordLineEdit, putWordOnGameBoardCommand, putAndSaveWordOnGameBoardCommand, commandList);
    connect(ui->new_word_apply, &QPushButton::clicked, newWordAdder.get(), &NewWordAdder::receiveApplyClick);
    connect(board.get(), &IGameBoardDisplay::selectionChanged, newWordAdder.get(), &NewWordAdder::receiveGameBoardSelectionChange);

    auto userLettersAdder = std::make_shared<UserLettersAdder>(scrabbleTextEdit, showUserLettersCommand, setUserLettersCommand, commandList);
    connect(ui->user_letters_apply, &QPushButton::clicked, userLettersAdder.get(), &UserLettersAdder::receiveApplyClick);

    auto searchListController = std::make_shared<SearchListController>(searchBar, wordsList, showWordFromListCommand, selectWordFromListCommand, commandList);
    connect(ui->search_apply, &QPushButton::clicked, searchListController.get(), &SearchListController::receiveApply);

    auto undoShortcut = std::make_unique<QShortcut>(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
    auto redoShortcut = std::make_unique<QShortcut>(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Z), this);
    auto timeTraveler = std::make_shared<TimeTraveler>(*ui->undo, *ui->redo, commandList, std::move(undoShortcut), std::move(redoShortcut));

    std::vector<std::shared_ptr<IUiStateChanger>> stateChangers = {newWordAdder, gameBoardTilesEraser, userLettersAdder, searchListController, timeTraveler};
    auto gameBoardController = std::make_unique<UiController>(board, userLettersDisplay, wordsList, stateChangers);
    program_ = std::make_unique<Program>(std::move(gameBoardController), std::move(searchEngine), threadInformer);
    resizeWindow();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , uiMenu(new Ui::language_window)
{
    uiMenu->setupUi(this);
    try
    {
        auto filesystemHandler = FilesystemHandlerFactory().create();

        for (auto language: filesystemHandler->getAvailableLanguages())
            uiMenu->languages_list->addItem(language);

        connect(uiMenu->ok_button, &QPushButton::clicked, this, [this, filesystemHandler = std::move(filesystemHandler)]()
        {
            try
            {
                setUpMainWindow(filesystemHandler, uiMenu->languages_list->currentItem()->text());
            }
            catch (std::runtime_error& e)
            {
                QMessageBox messageBox;
                messageBox.critical(0, "Error", e.what());
                messageBox.setFixedSize(500,200);
                exit(1);
            }
        });
    }
    catch (std::runtime_error& e)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", e.what());
        messageBox.setFixedSize(500,200);
        exit(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



