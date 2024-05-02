#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "Program.hpp"

#include "AlgorithmModule/log.hpp"

#include <memory>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class language_window;}
QT_END_NAMESPACE
class IFilesystemHandler;

class GameBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void resizeWindow();
    void resizeEvent(QResizeEvent* event);
    void showGameBoard(const GameBoard& gameBoard);
    void setUpMainWindow(const std::unique_ptr<IFilesystemHandler>& languageHandeler, const QString& str);

    Ui::MainWindow* ui;
    Ui::language_window* uiMenu;
    std::unique_ptr<Program> program_;
};
#endif // MAINWINDOW_HPP
