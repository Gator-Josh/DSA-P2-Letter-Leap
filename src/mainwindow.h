#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};

#endif // MAINWINDOW_H