#include "playpage.h"
#include "ui_playpage.h"

PlayPage::PlayPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlayPage)
{
    ui->setupUi(this);
}

PlayPage::~PlayPage()
{
    delete ui;
}

void PlayPage::setMode(SearchMode mode)
{
    m_mode = mode;
    ui->playLabel->setText(mode == SearchMode::Trie ? "Mode: Trie"
                                                    : "Mode: BK-Tree");
    // Later: this is where you'd decide whether lookups go to your
    // Trie or your BK_Tree.
}