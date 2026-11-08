#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent), ui(new Ui::HomePage)
{
    ui->setupUi(this);

    connect(ui->trieButton,   &QPushButton::clicked, this, &HomePage::playTrieRequested);
    connect(ui->bkButton, &QPushButton::clicked, this, &HomePage::playBkTreeRequested);
    connect(ui->quitButton,   &QPushButton::clicked, this, &HomePage::quitRequested);
}

HomePage::~HomePage()
{
    delete ui;
}