QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../AlgorithmModule/ScoreCalculator.cpp \
    ../AlgorithmModule/ScoreCalculatorQuery.cpp \
    ../AlgorithmModule/ScoreCalculatorResult.cpp \
    ../AlgorithmModule/ScrabbleSearchEngine.cpp \
    ../AlgorithmModule/ScrabbleSearchEngineQuery.cpp \
    ../AlgorithmModule/ScrabbleSearchEngineResult.cpp \
    ../AlgorithmModule/SearchAlgorithmQuery.cpp \
    ../AlgorithmModule/SearchAlgorithmResult.cpp \
    ../AlgorithmModule/Trie.cpp \
    ../AlgorithmModule/TrieSearchAlgorithm.cpp \
    ../AlgorithmModule/log.cpp \
    ../FilesystemModule/FileReader.cpp \
    ../FilesystemModule/LanguageHandeler.cpp \
    ../Program.cpp \
    ../UIModule/GameBoard/GameBoardDelegate.cpp \
    ../UIModule/GameBoard/GameBoardModel.cpp \
    ../UIModule/GameBoard/TableViewBasedGameBoard.cpp \
    ../UIModule/ResultsList/ListItemDelegate.cpp \
    ../UIModule/ResultsList/ScrabbleWordsList.cpp \
    ../UIModule/UiController.cpp \
    ../UIModule/UiStateChangers/GameBoardTilesEraser/EraseFromGameBoardCommand.cpp \
    ../UIModule/UiStateChangers/GameBoardTilesEraser/GameBoardTilesEraser.cpp \
    ../UIModule/UiStateChangers/NewWordAdder/Commands/PutAndSaveWordOnGameBoardCommand.cpp \
    ../UIModule/UiStateChangers/NewWordAdder/Commands/PutWordOnGameBoardCommand.cpp \
    ../UIModule/UiStateChangers/NewWordAdder/NewWordAdder.cpp \
    ../UIModule/UiStateChangers/TimeTraveler/TimeTraveler.cpp \
    ../UIModule/UiStateChangers/UserLettersAdder/Commands/SetUserLettersCommand.cpp \
    ../UIModule/UiStateChangers/UserLettersAdder/Commands/ShowUserLettersCommand.cpp \
    ../UIModule/UiStateChangers/UserLettersAdder/UserLettersAdder.cpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/Commands/SelectWordFromListCommand.cpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/Commands/ShowWordFromListCommand.cpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/SearchListController.cpp \
    ../UIModule/UserLetters/ListViewBasedUserLetters.cpp \
    ../UIModule/UserLetters/UserLettersDelegate.cpp \
    ../UIModule/UserLetters/UserLettersModel.cpp \
    ../UIModule/Utils/Commands/CommandListManager.cpp \
    ../UIModule/Utils/Controls/LineTextScrabbleTextEdit.cpp \
    ../UIModule/Utils/Controls/RadioButtonSwitch.cpp \
    ../UIModule/Utils/SlotsBlocker.cpp \
    ../UIModule/Utils/TextureHandeler.cpp \
    ../Uils/FileReadHelpers.cpp \
    ../Uils/GameBoard.cpp \
    ../Uils/LettersInfo.cpp \
    ../Uils/LettersRenumberer.cpp \
    ../Uils/PolishDebugRenumberer.cpp \
    ../Uils/ScrabbleString.cpp \
    ../Uils/ThreadInformer.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    ../AlgorithmModule/IScoreCalculator.hpp \
    ../AlgorithmModule/ISearchAlgorithm.hpp \
    ../AlgorithmModule/ScoreCalculator.hpp \
    ../AlgorithmModule/ScoreCalculatorQuery.hpp \
    ../AlgorithmModule/ScoreCalculatorResult.hpp \
    ../AlgorithmModule/ScrabbleSearchEngine.hpp \
    ../AlgorithmModule/ScrabbleSearchEngineQuery.hpp \
    ../AlgorithmModule/ScrabbleSearchEngineResult.hpp \
    ../AlgorithmModule/SearchAlgorithmQuery.hpp \
    ../AlgorithmModule/SearchAlgorithmResult.hpp \
    ../AlgorithmModule/Trie.hpp \
    ../AlgorithmModule/TrieSearchAlgorithm.hpp \
    ../AlgorithmModule/log.hpp \
    ../FilesystemModule/FileReader.hpp \
    ../FilesystemModule/IFileReader.hpp \
    ../FilesystemModule/ILanguagesHandeler.hpp \
    ../FilesystemModule/LanguageHandeler.hpp \
    ../Program.hpp \
    ../UIModule/GameBoard/GameBoardDelegate.hpp \
    ../UIModule/GameBoard/GameBoardModel.hpp \
    ../UIModule/GameBoard/IGameBoardDisplay.hpp \
    ../UIModule/GameBoard/TableViewBasedGameBoard.hpp \
    ../UIModule/IUiController.hpp \
    ../UIModule/ResultsList/IList.hpp \
    ../UIModule/ResultsList/ListItemDelegate.hpp \
    ../UIModule/ResultsList/ScrabbleWordsList.hpp \
    ../UIModule/UiController.hpp \
    ../UIModule/UiStateChangers/GameBoardTilesEraser/EraseFromGameBoardCommand.hpp \
    ../UIModule/UiStateChangers/GameBoardTilesEraser/GameBoardTilesEraser.hpp \
    ../UIModule/UiStateChangers/IUiStateChanger.hpp \
    ../UIModule/UiStateChangers/NewWordAdder/Commands/PutAndSaveWordOnGameBoardCommand.hpp \
    ../UIModule/UiStateChangers/NewWordAdder/Commands/PutWordOnGameBoardCommand.hpp \
    ../UIModule/UiStateChangers/NewWordAdder/NewWordAdder.hpp \
    ../UIModule/UiStateChangers/TimeTraveler/TimeTraveler.hpp \
    ../UIModule/UiStateChangers/UserLettersAdder/Commands/SetUserLettersCommand.hpp \
    ../UIModule/UiStateChangers/UserLettersAdder/Commands/ShowUserLettersCommand.hpp \
    ../UIModule/UiStateChangers/UserLettersAdder/UserLettersAdder.hpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/Commands/SelectWordFromListCommand.hpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/Commands/ShowWordFromListCommand.hpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/SearchListController.hpp \
    ../UIModule/UserLetters/IUserLettersDisplay.hpp \
    ../UIModule/UserLetters/ListViewBasedUserLetters.hpp \
    ../UIModule/UserLetters/UserLettersDelegate.hpp \
    ../UIModule/UserLetters/UserLettersModel.hpp \
    ../UIModule/Utils/Commands/CommandListManager.hpp \
    ../UIModule/Utils/Commands/ICommand.hpp \
    ../UIModule/Utils/Commands/ICommandListManager.hpp \
    ../UIModule/Utils/Commands/IReversableCommand.hpp \
    ../UIModule/Utils/Controls/IScrabbleTextEdit.hpp \
    ../UIModule/Utils/Controls/ISwitch.hpp \
    ../UIModule/Utils/Controls/LineTextScrabbleTextEdit.hpp \
    ../UIModule/Utils/Controls/RadioButtonSwitch.hpp \
    ../UIModule/Utils/ITextureHandeler.hpp \
    ../UIModule/Utils/SlotsBlocker.hpp \
    ../UIModule/Utils/TextureHandeler.hpp \
    ../Uils/FileReadHelpers.hpp \
    ../Uils/GameBoard.hpp \
    ../Uils/ILettersRenumberer.hpp \
    ../Uils/LettersInfo.hpp \
    ../Uils/LettersRenumberer.hpp \
    ../Uils/PolishDebugRenumberer.hpp \
    ../Uils/ScrabbleString.hpp \
    ../Uils/ThreadInformer.hpp \
    MainWindow.hpp

FORMS += \
    MainWindow.ui \
    language_window.ui

INCLUDEPATH += \
    $$PWD/../ \
    $$PWD/../AlgorithmModule \
    $$PWD/../Desktop \
    $$PWD/../FilesystemModule \
    $$PWD/../UIModule \
    $$PWD/../UIModule/ResultsList \
    $$PWD/../UIModule/UiStateChangers \
    $$PWD/../UIModule/UiStateChangers/GameBoardTilesEraser \
    $$PWD/../UIModule/UiStateChangers/NewWordAdder \
    $$PWD/../UIModule/UiStateChangers/NewWordAdder/Commands \
    $$PWD/../UIModule/UiStateChangers/WordsFromListAdder \
    $$PWD/../UIModule/UiStateChangers/WordsFromListAdder/Commands \
    $$PWD/../UIModule/UiStateChangers/TimeTraveler \
    $$PWD/../UIModule/UiStateChangers/UserLettersAdder \
    $$PWD/../UIModule/UiStateChangers/UserLettersAdder/Commands \
    $$PWD/../UIModule/GameBoard \
    $$PWD/../UIModule/Utils \
    $$PWD/../UIModule/Utils/Commands \
    $$PWD/../UIModule/Utils/Controls \
    $$PWD/../UIModule/UserLetters \
    $$PWD/../Uils \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Src/Languages/English/letters_info.txt \
    ../Src/Languages/English/words.txt \
    ../Src/Languages/Polski/letters_info.txt \
    ../Src/Languages/Polski/words.txt \
    ../Src/Tiles/empty_tile.png \
    ../Src/Tiles/letterx2_tile.png \
    ../Src/Tiles/letterx3_tile.png \
    ../Src/Tiles/normal_tile (kopia).png \
    ../Src/Tiles/normal_tile.png \
    ../Src/Tiles/transparent_tile.png \
    ../Src/Tiles/wordx2_tile.png \
    ../Src/Tiles/wordx3_tile.png \
    ../Uils/letters_info.txt
