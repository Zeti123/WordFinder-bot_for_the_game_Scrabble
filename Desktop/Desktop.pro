QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../AlgorithmModule/ScoreCalculator/ScoreCalculator.cpp \
    ../AlgorithmModule/ScoreCalculator/ScoreCalculatorFactory.cpp \
    ../AlgorithmModule/ScoreCalculator/ScoreCalculatorQuery.cpp \
    ../AlgorithmModule/ScoreCalculator/ScoreCalculatorResult.cpp \
    ../AlgorithmModule/ScrabbleSearchEngine.cpp \
    ../AlgorithmModule/ScrabbleSearchEngineQuery.cpp \
    ../AlgorithmModule/ScrabbleSearchEngineResult.cpp \
    ../AlgorithmModule/SearchAlgorithm/SearchAlgorithmFactory.cpp \
    ../AlgorithmModule/SearchAlgorithm/Trie.cpp \
    ../AlgorithmModule/SearchAlgorithm/TrieSearchAlgorithm.cpp \
    ../AlgorithmModule/SearchEngineFactory.cpp \
    ../AlgorithmModule/log.cpp \
    ../FilesystemModule/FileReader/FileReader.cpp \
    ../FilesystemModule/FilesystemHandler.cpp \
    ../FilesystemModule/FilesystemHandlerFactory.cpp \
    ../FilesystemModule/LanguageHandler/LanguageHandler.cpp \
    ../Program.cpp \
    ../UIModule/GameBoard/GameBoardDelegate.cpp \
    ../UIModule/GameBoard/GameBoardDisplayFactory.cpp \
    ../UIModule/GameBoard/GameBoardModel.cpp \
    ../UIModule/GameBoard/TableViewBasedGameBoard.cpp \
    ../UIModule/ResultsList/ListItemDelegate.cpp \
    ../UIModule/ResultsList/ListModel.cpp \
    ../UIModule/ResultsList/ResultsListsFactory.cpp \
    ../UIModule/ResultsList/ScrabbleWordsList.cpp \
    ../UIModule/UiController.cpp \
    ../UIModule/UiControllerFactory.cpp \
    ../UIModule/UiStateChangers/GameBoardTilesEraser/EraseFromGameBoardCommand.cpp \
    ../UIModule/UiStateChangers/GameBoardTilesEraser/GameBoardTilesEraser.cpp \
    ../UIModule/UiStateChangers/GameBoardTilesEraser/GameBoardTilesEraserFactory.cpp \
    ../UIModule/UiStateChangers/NewWordAdder/Commands/PutAndSaveWordOnGameBoardCommand.cpp \
    ../UIModule/UiStateChangers/NewWordAdder/Commands/PutWordOnGameBoardCommand.cpp \
    ../UIModule/UiStateChangers/NewWordAdder/NewWordAdder.cpp \
    ../UIModule/UiStateChangers/NewWordAdder/NewWordAdderFactory.cpp \
    ../UIModule/UiStateChangers/TimeTraveler/TimeTraveler.cpp \
    ../UIModule/UiStateChangers/UiStateChangersFactory.cpp \
    ../UIModule/UiStateChangers/UserLettersAdder/Commands/SetUserLettersCommand.cpp \
    ../UIModule/UiStateChangers/UserLettersAdder/Commands/ShowUserLettersCommand.cpp \
    ../UIModule/UiStateChangers/UserLettersAdder/UserLettersAdder.cpp \
    ../UIModule/UiStateChangers/UserLettersAdder/UserLettersAdderFactory.cpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/Commands/SelectWordFromListCommand.cpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/Commands/ShowWordFromListCommand.cpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/SearchListController.cpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/WordsFromListAdderFactory.cpp \
    ../UIModule/UserLetters/ListViewBasedUserLetters.cpp \
    ../UIModule/UserLetters/UserLettersDelegate.cpp \
    ../UIModule/UserLetters/UserLettersFactory.cpp \
    ../UIModule/UserLetters/UserLettersModel.cpp \
    ../UIModule/Utils/Commands/CommandListManager.cpp \
    ../UIModule/Utils/Controls/LineTextScrabbleTextEdit.cpp \
    ../UIModule/Utils/Controls/RadioButtonSwitch.cpp \
    ../UIModule/Utils/SlotsBlocker.cpp \
    ../UIModule/Utils/TextureHandler.cpp \
    ../Uils/CommonDataStructures/GameBoard.cpp \
    ../Uils/CommonDataStructures/ScrabbleString.cpp \
    ../Uils/CommonDataStructures/WordPlacement.cpp \
    ../Uils/FileReadHelpers.cpp \
    ../Uils/GameBoardHelpers.cpp \
    ../Uils/LettersInfo.cpp \
    ../Uils/LettersRenumberer.cpp \
    ../Uils/PolishDebugRenumberer.cpp \
    ../Uils/ThreadInformer.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    ../AlgorithmModule/IScrabbleSearchEngine.hpp \
    ../AlgorithmModule/ScoreCalculator/IScoreCalculator.hpp \
    ../AlgorithmModule/ScoreCalculator/ScoreCalculator.hpp \
    ../AlgorithmModule/ScoreCalculator/ScoreCalculatorFactory.hpp \
    ../AlgorithmModule/ScoreCalculator/ScoreCalculatorQuery.hpp \
    ../AlgorithmModule/ScoreCalculator/ScoreCalculatorResult.hpp \
    ../AlgorithmModule/ScrabbleSearchEngine.hpp \
    ../AlgorithmModule/ScrabbleSearchEngineQuery.hpp \
    ../AlgorithmModule/ScrabbleSearchEngineResult.hpp \
    ../AlgorithmModule/SearchAlgorithm/ISearchAlgorithm.hpp \
    ../AlgorithmModule/SearchAlgorithm/SearchAlgorithmFactory.hpp \
    ../AlgorithmModule/SearchAlgorithm/SearchAlgorithmQuery.hpp \
    ../AlgorithmModule/SearchAlgorithm/SearchAlgorithmResult.hpp \
    ../AlgorithmModule/SearchAlgorithm/Trie.hpp \
    ../AlgorithmModule/SearchAlgorithm/TrieSearchAlgorithm.hpp \
    ../AlgorithmModule/SearchEngineFactory.hpp \
    ../AlgorithmModule/log.hpp \
    ../FilesystemModule/FileReader.hpp \
    ../FilesystemModule/FileReader/FileReader.hpp \
    ../FilesystemModule/FileReader/IFileReader.hpp \
    ../FilesystemModule/FilesystemHandler.hpp \
    ../FilesystemModule/FilesystemHandlerFactory.hpp \
    ../FilesystemModule/IFileReader.hpp \
    ../FilesystemModule/IFilesystemHandler.hpp \
    ../FilesystemModule/ILanguagesHandler.hpp \
    ../FilesystemModule/LanguageHandler.hpp \
    ../FilesystemModule/LanguageHandler/ILanguagesHandler.hpp \
    ../FilesystemModule/LanguageHandler/LanguageHandler.hpp \
    ../FilesystemModule/LanguageInfo.hpp \
    ../Program.hpp \
    ../UIModule/GameBoard/GameBoardDelegate.hpp \
    ../UIModule/GameBoard/GameBoardDisplayFactory.hpp \
    ../UIModule/GameBoard/GameBoardModel.hpp \
    ../UIModule/GameBoard/IGameBoardDisplay.hpp \
    ../UIModule/GameBoard/TableViewBasedGameBoard.hpp \
    ../UIModule/IUiController.hpp \
    ../UIModule/ResultsList/IList.hpp \
    ../UIModule/ResultsList/ListItemDelegate.hpp \
    ../UIModule/ResultsList/ListModel.hpp \
    ../UIModule/ResultsList/ResultsListsFactory.hpp \
    ../UIModule/ResultsList/ScrabbleWordsList.hpp \
    ../UIModule/UiController.hpp \
    ../UIModule/UiControllerFactory.hpp \
    ../UIModule/UiStateChangers/GameBoardTilesEraser/EraseFromGameBoardCommand.hpp \
    ../UIModule/UiStateChangers/GameBoardTilesEraser/GameBoardTilesEraser.hpp \
    ../UIModule/UiStateChangers/GameBoardTilesEraser/GameBoardTilesEraserFactory.hpp \
    ../UIModule/UiStateChangers/IUiStateChanger.hpp \
    ../UIModule/UiStateChangers/NewWordAdder/Commands/PutAndSaveWordOnGameBoardCommand.hpp \
    ../UIModule/UiStateChangers/NewWordAdder/Commands/PutWordOnGameBoardCommand.hpp \
    ../UIModule/UiStateChangers/NewWordAdder/NewWordAdder.hpp \
    ../UIModule/UiStateChangers/NewWordAdder/NewWordAdderFactory.hpp \
    ../UIModule/UiStateChangers/TimeTraveler/TimeTraveler.hpp \
    ../UIModule/UiStateChangers/UiStateChangersFactory.hpp \
    ../UIModule/UiStateChangers/UserLettersAdder/Commands/SetUserLettersCommand.hpp \
    ../UIModule/UiStateChangers/UserLettersAdder/Commands/ShowUserLettersCommand.hpp \
    ../UIModule/UiStateChangers/UserLettersAdder/UserLettersAdder.hpp \
    ../UIModule/UiStateChangers/UserLettersAdder/UserLettersAdderFactory.hpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/Commands/SelectWordFromListCommand.hpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/Commands/ShowWordFromListCommand.hpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/SearchListController.hpp \
    ../UIModule/UiStateChangers/WordsFromListAdder/WordsFromListAdderFactory.hpp \
    ../UIModule/UserLetters/IUserLettersDisplay.hpp \
    ../UIModule/UserLetters/ListViewBasedUserLetters.hpp \
    ../UIModule/UserLetters/UserLettersDelegate.hpp \
    ../UIModule/UserLetters/UserLettersFactory.hpp \
    ../UIModule/UserLetters/UserLettersModel.hpp \
    ../UIModule/Utils/Commands/CommandListManager.hpp \
    ../UIModule/Utils/Commands/ICommand.hpp \
    ../UIModule/Utils/Commands/ICommandListManager.hpp \
    ../UIModule/Utils/Commands/IReversableCommand.hpp \
    ../UIModule/Utils/Controls/IScrabbleTextEdit.hpp \
    ../UIModule/Utils/Controls/ISwitch.hpp \
    ../UIModule/Utils/Controls/LineTextScrabbleTextEdit.hpp \
    ../UIModule/Utils/Controls/RadioButtonSwitch.hpp \
    ../UIModule/Utils/ITextureHandler.hpp \
    ../UIModule/Utils/SlotsBlocker.hpp \
    ../UIModule/Utils/TextureHandler.hpp \
    ../Uils/CommonDataStructures/GameBoard.hpp \
    ../Uils/CommonDataStructures/ScrabbleString.hpp \
    ../Uils/CommonDataStructures/WordPlacement.hpp \
    ../Uils/FileReadHelpers.hpp \
    ../Uils/GameBoardHelpers.hpp \
    ../Uils/ILettersRenumberer.hpp \
    ../Uils/LettersInfo.hpp \
    ../Uils/LettersRenumberer.hpp \
    ../Uils/PolishDebugRenumberer.hpp \
    ../Uils/ThreadInformer.hpp \
    MainWindow.hpp

FORMS += \
    MainWindow.ui \
    language_window.ui

INCLUDEPATH += \
    $$PWD/../ \
    $$PWD/../AlgorithmModule \
    $$PWD/../AlgorithmModule/ScoreCalculator \
    $$PWD/../AlgorithmModule/SearchAlgorithm \
    $$PWD/../Desktop \
    $$PWD/../FilesystemModule \
    $$PWD/../FilesystemModule/FileReader \
    $$PWD/../FilesystemModule/LanguageHandler \
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
    $$PWD/../Uils/CommonDataStructures \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Resources/Languages/English/letters_info.txt \
    ../Resources/Languages/English/words.txt \
    ../Resources/Languages/Polski/letters_info.txt \
    ../Resources/Languages/Polski/words.txt \
    ../Resources/Tiles/empty_tile.png \
    ../Resources/Tiles/letterx2_tile.png \
    ../Resources/Tiles/letterx3_tile.png \
    ../Resources/Tiles/normal_tile (kopia).png \
    ../Resources/Tiles/normal_tile.png \
    ../Resources/Tiles/transparent_tile.png \
    ../Resources/Tiles/wordx2_tile.png \
    ../Resources/Tiles/wordx3_tile.png \
    ../Uils/letters_info.txt
