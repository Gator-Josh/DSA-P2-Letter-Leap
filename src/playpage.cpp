#include "playpage.h"
#include "ui_playpage.h"

#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QScrollBar>
#include <QTimer>

static QString messageFor(const std::string &result)
{
    if (result == "invalid length") return "Wrong length";
    if (result == "redundant")      return "Word already used";
    if (result == "invalid word")   return "Not in the word list";
    if (result == "invalid swap")   return "Change exactly one letter";
    return QString::fromStdString(result);
}

PlayPage::PlayPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlayPage)
{
    ui->setupUi(this);

    setFocusPolicy(Qt::StrongFocus);
    ui->backButton->setFocusPolicy(Qt::NoFocus);
    ui->tileScroll->setFocusPolicy(Qt::NoFocus);
    ui->scrollAreaWidgetContents->setFocusPolicy(Qt::NoFocus);
    ui->solutionButton->setFocusPolicy(Qt::NoFocus);
    ui->resetButton->setFocusPolicy(Qt::NoFocus);

    connect(ui->resetButton, &QPushButton::clicked, this, &PlayPage::resetGame);
    connect(ui->solutionButton, &QPushButton::clicked, this, &PlayPage::showSolution);
    connect(ui->backButton, &QPushButton::clicked, this, &PlayPage::backRequested);

    m_grid = new QGridLayout(ui->scrollAreaWidgetContents);
    m_grid->setSpacing(8);
    m_grid->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    // Tiles are created in startGame, once the letter count is known
}

PlayPage::~PlayPage()
{
    delete ui;
}

bool PlayPage::startGame(SearchMode mode, int letters)
{
    // Pick the data structure for this game
    GameLogic *game = (mode == SearchMode::Trie)
                          ? static_cast<GameLogic *>(&m_trie)
                          : static_cast<GameLogic *>(&m_bk);

    if (!game->generateLastWord(letters))
        return false;   // word list missing or no valid chain found

    m_game = game;
    m_mode = mode;
    m_tileCount = letters;
    m_typed.clear();
    m_won = false;
    m_solutionShown = false;

    // Fake having infinite rows by just making 2000 of them... :3
    m_rowCount = 2000;

    ui->playLabel->setText(mode == SearchMode::Trie ? "Mode: Trie" : "Mode: BK-Tree");
    ui->statusLabel->clear();

    buildGrid();

    // Firs row is the starting word
    const QString first = QString::fromStdString(m_game->getFirstWord()).toUpper();
    for (int c = 0; c < m_tileCount; ++c)
        m_tiles[0][c]->setText(QString(first[c]));
    m_currentRow = 1;
    ui->targetLabel->setText("Target: " +
                             QString::fromStdString(m_game->getLastWord()).toUpper());

    refreshTiles();
    ui->tileScroll->verticalScrollBar()->setValue(0);
    setFocus();
    return true;
}

void PlayPage::buildGrid()
{
    // Remove the previous game's tiles
    for (auto &row : m_tiles) {
        for (QLabel *t : row) {
            m_grid->removeWidget(t);
            t->deleteLater();
        }
    }
    m_tiles.clear();

    // Shrink tiles for long words so the grid still fits the width
    // UI IS SUCH A PAIN
    const int size = (m_tileCount > 9) ? 44 : 56;

    m_tiles.resize(m_rowCount);
    for (int r = 0; r < m_rowCount; ++r) {
        for (int c = 0; c < m_tileCount; ++c) {
            auto *tile = new QLabel(ui->scrollAreaWidgetContents);
            tile->setAlignment(Qt::AlignCenter);
            tile->setFixedSize(size, size);
            m_grid->addWidget(tile, r, c);
            m_tiles[r].append(tile);
        }
    }
}

void PlayPage::keyPressEvent(QKeyEvent *event)
{
    const bool boardFull = !m_game || (m_currentRow >= m_rowCount) || m_won || m_solutionShown;
    bool scrollToActive = false;

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
        if (!boardFull && m_typed.size() == m_tileCount) {
            const std::string word = m_typed.toLower().toStdString();
            const std::string result = m_game->insertWord(word);

            if (result == "valid") {
                emit wordSubmitted(m_typed);
                m_typed.clear();
                ++m_currentRow;
                ui->statusLabel->clear();

                if (word == m_game->getLastWord()) {
                    m_won = true;
                    ui->statusLabel->setText("You win!");
                } else if (m_currentRow >= m_rowCount) {
                    //Only here as a backup since the way the "infinite" guesses works is that there's 2000 rows
                    ui->statusLabel->setText("Out of rows!");
                } else {
                    scrollToActive = true;
                }
            } else {
                // Keeps the row active so the player can keep guessing
                ui->statusLabel->setText(messageFor(result));
            }
        }
        break;

    default: {
        const QString t = event->text();
        if (!t.isEmpty() && t[0].isLetter()) {
            if (!boardFull && m_typed.size() < m_tileCount)
                m_typed += t.toUpper();
        } else {
            QWidget::keyPressEvent(event);
            return;
        }
    }
    }

    refreshTiles();

    if (scrollToActive) {
        // Waits for the layout to update, then brings the new active row into view
        QTimer::singleShot(0, this, [this]() {
            if (m_currentRow < m_tiles.size())
                ui->tileScroll->ensureWidgetVisible(m_tiles[m_currentRow][0]);
        });
    }
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
    for (int r = 0; r < m_tiles.size(); ++r) {
        for (int c = 0; c < m_tiles[r].size(); ++c) {
            QLabel *tile = m_tiles[r][c];

            if (r < m_currentRow) {
                tile->setVisible(true);
                styleTile(tile, "#4a4a4a", "#4a4a4a");           // past rows
            } else if (r == m_currentRow && !m_won && !m_solutionShown) {
                tile->setVisible(true);
                const bool filled = c < m_typed.size();          // active row
                tile->setText(filled ? QString(m_typed[c]) : QString());
                styleTile(tile,
                          filled ? "#555555" : "#2b2b2b",
                          filled ? "#aaaaaa" : "#555555");
            } else {
                tile->setText(QString());                        // future rows
                tile->setVisible(false);
            }
        }
    }
}

void PlayPage::showSolution()
{
    if (!m_game)
        return;

    const auto &solution = m_game->getSolution();
    if (solution.empty() || static_cast<int>(solution.size()) > static_cast<int>(m_tiles.size()))
        return;

    // Write each word of the path into its own row
    int row = 0;
    for (const std::string &w : solution) {
        const QString word = QString::fromStdString(w).toUpper();
        for (int c = 0; c < m_tileCount; ++c)
            m_tiles[row][c]->setText(QString(word[c]));
        ++row;
    }

    m_typed.clear();
    m_solutionShown = true;
    m_currentRow = row;          // every solution row counts as "past"
    refreshTiles();

    // Color the solution rows green
    // I like green
    // its one of my two favorite colors
    // my other favorite color is orange btw
    // my favorite types of these colors are pastel variants
    // i really like pastel orange i think its pretty <3
    for (int r = 0; r < row; ++r)
        for (int c = 0; c < m_tileCount; ++c)
            styleTile(m_tiles[r][c], "#2e7d32", "#66bb6a");

    ui->statusLabel->setText("Solution shown");
    ui->tileScroll->verticalScrollBar()->setValue(0);
}

void PlayPage::resetGame()
{
    if (!m_game || m_tiles.isEmpty())
        return;

    m_typed.clear();
    m_won = false;
    m_solutionShown = false;

    // Clear every tile's text
    for (auto &row : m_tiles)
        for (QLabel *t : row)
            t->setText(QString());

    // Rewind the game to the first word of the SAME puzzle
    m_game->resetProgress();

    // First word is the same starting word again
    const QString first = QString::fromStdString(m_game->getFirstWord()).toUpper();
    for (int c = 0; c < m_tileCount; ++c)
        m_tiles[0][c]->setText(QString(first[c]));
    m_currentRow = 1;

    ui->statusLabel->clear();
    refreshTiles();
    ui->tileScroll->verticalScrollBar()->setValue(0);
    setFocus();
}