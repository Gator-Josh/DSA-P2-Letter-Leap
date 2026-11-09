#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BK_Tree.cpp"

class QStackedWidget;
class HomePage;
class PlayPage;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QStackedWidget *m_stack;
    HomePage *m_home;
    PlayPage *m_play;
    Ui::MainWindow *ui;
    BK_Tree bk_tree;

};

#endif // MAINWINDOW_H