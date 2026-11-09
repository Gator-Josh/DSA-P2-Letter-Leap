#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent), ui(new Ui::HomePage)
{
    ui->setupUi(this);

    connect(ui->trieButton, &QPushButton::clicked, this, [this]() {
        emit playTrieRequested(ui->lengthSpin->value());
    });
    connect(ui->bkButton, &QPushButton::clicked, this, [this]() {
        emit playBkTreeRequested(ui->lengthSpin->value());
    });
    connect(ui->quitButton,   &QPushButton::clicked, this, &HomePage::quitRequested);
}

HomePage::~HomePage()
{
    delete ui;
}