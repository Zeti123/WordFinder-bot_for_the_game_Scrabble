#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "ui_language_window.h"

#include "UiControllerFactory.hpp"
#include "Program.hpp"
#include "SearchEngineFactory.hpp"
#include "LettersRenumberer.hpp"
#include "TextureHandler.hpp"
#include "PolishDebugRenumberer.hpp"
#include "FileReadHelpers.hpp"
#include "FilesystemHandlerFactory.hpp"
#include "UiStateChangersFactory.hpp"

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
    auto uiController = UiControllerFactory().create(*this, *ui, lettersRenumberer, textureHandler);
    program_ = std::make_unique<Program>(std::move(uiController), std::move(searchEngine), threadInformer);
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



