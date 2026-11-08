#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>
#include "homepage.h"
#include "playpage.h"
#include "Trie.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Build the stack and add both screens
    m_stack = new QStackedWidget(this);
    m_home  = new HomePage;
    m_play  = new PlayPage;
    m_stack->addWidget(m_home);
    m_stack->addWidget(m_play);
    setCentralWidget(m_stack);
    m_stack->setCurrentWidget(m_home);

    // Home -> Play (both buttons, different modes)
    connect(m_home, &HomePage::playTrieRequested, this, [this]() {
        m_play->setMode(SearchMode::Trie);
        m_stack->setCurrentWidget(m_play);
    });
    connect(m_home, &HomePage::playBkTreeRequested, this, [this]() {
        m_play->setMode(SearchMode::BkTree);
        m_stack->setCurrentWidget(m_play);
    });
    connect(m_home, &HomePage::quitRequested, this, &QMainWindow::close);

    //Play Buttons
    connect(m_play, &PlayPage::backRequested, this, [this]() {
        m_stack->setCurrentWidget(m_home);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
