#include "playpage.h"
#include "ui_playpage.h"

#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QScrollBar>

PlayPage::PlayPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlayPage)
{
    ui->setupUi(this);

    connect(ui->backButton,   &QPushButton::clicked, this, &PlayPage::backRequested);
    connect(ui->solutionButton,   &QPushButton::clicked, this, &PlayPage::solutionRequested);

    // Focus: the page receives keys; nothing else steals them
    setFocusPolicy(Qt::StrongFocus);
    ui->tileScroll->setFocusPolicy(Qt::NoFocus);
    ui->scrollAreaWidgetContents->setFocusPolicy(Qt::NoFocus);


    // Grid layout on the scroll area's content widget (created in code)
    m_grid = new QGridLayout(ui->scrollAreaWidgetContents);
    m_grid->setSpacing(8);
    m_grid->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    // Build the tiles
    m_tiles.resize(kRowCount);
    for (int r = 0; r < kRowCount; ++r) {
        for (int c = 0; c < kTileCount; ++c) {
            auto *tile = new QLabel(ui->scrollAreaWidgetContents);
            tile->setAlignment(Qt::AlignCenter);
            tile->setFixedSize(56, 56);
            m_grid->addWidget(tile, r, c);
            m_tiles[r].append(tile);
        }
    }

    refreshTiles();
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
    m_typed.clear();
    m_currentRow = 0;
    refreshTiles();
    ui->tileScroll->verticalScrollBar()->setValue(0);
    setFocus();
}

void PlayPage::keyPressEvent(QKeyEvent *event)
{
    const bool boardFull = (m_currentRow >= kRowCount);

    switch (event->key()) {
    case Qt::Key_Escape:
        emit backRequested();
        return;

    case Qt::Key_Backspace:
        if (!boardFull)
            m_typed.chop(1);
        break;

    case Qt::Key_Return:
    case Qt::Key_Enter:
        if (!boardFull && m_typed.size() == kTileCount) {
            emit wordSubmitted(m_typed);
            m_typed.clear();
            ++m_currentRow;
        }
        break;

    default: {
        const QString t = event->text();
        if (!t.isEmpty() && t[0].isLetter()) {
            if (!boardFull && m_typed.size() < kTileCount)
                m_typed += t.toUpper();
        } else {
            QWidget::keyPressEvent(event);
            return;
        }
    }
    }

    refreshTiles();
    ui->tileScroll->ensureWidgetVisible(m_tiles[m_currentRow][0]);
}

void PlayPage::styleTile(QLabel *tile, const QString &bg, const QString &border)
{
    tile->setStyleSheet(QString(
                            "QLabel {"
                            "  background-color: %1;"
                            "  color: white;"
                            "  border: 2px solid %2;"
                            "  border-radius: 0px;"
                            "  font-size: 28px;"
                            "  font-weight: bold;"
                            "}").arg(bg, border));
}

void PlayPage::refreshTiles()
{
    for (int r = 0; r < kRowCount; ++r) {
        for (int c = 0; c < kTileCount; ++c) {
            QLabel *tile = m_tiles[r][c];

            if (r < m_currentRow) {
                tile->setVisible(true);
                styleTile(tile, "#4a4a4a", "#4a4a4a");          // past rows
            } else if (r == m_currentRow) {
                tile->setVisible(true);
                const bool filled = c < m_typed.size();         // active row
                tile->setText(filled ? QString(m_typed[c]) : QString());
                styleTile(tile,
                          filled ? "#555555" : "#2b2b2b",
                          filled ? "#aaaaaa" : "#555555");
                ui->tileScroll->verticalScrollBar()->setValue(ui->tileScroll->verticalScrollBar()->maximum());
            }
            else
            {
                tile->setVisible(false); //Future rows exist we just dont render them :3
            }
        }
    }
}