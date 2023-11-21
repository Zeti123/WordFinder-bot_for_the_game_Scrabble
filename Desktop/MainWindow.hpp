#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Program.hpp"

#include "AlgorithmModule/log.hpp"

#include <memory>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class language_window;}
QT_END_NAMESPACE
class ILanguagesHandler;

class GameBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //void resizeEvent(QResizeEvent* re) override;
    void resizeWindow();
    void showGameBoard(const GameBoard& gameBoard);
    void setUpMainWindow(std::shared_ptr<ILanguagesHandler> languageHandeler, const QString& str);
    Ui::MainWindow* ui;
    Ui::language_window* uiMenu;
    std::unique_ptr<Program> program_;
    //LoggerHandeler lh;
};
#endif // MAINWINDOW_HPP
