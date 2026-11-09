#include "BK_Tree.cpp"

#include "playpage.h"
#include "ui_playpage.h"

#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QScrollBar>

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
    // Tiles are created later, in startGame, once the letter count is known
}

PlayPage::~PlayPage()
{
    delete ui;
}

bool PlayPage::startGame(SearchMode mode, int letters)
{
    m_mode = mode;
    m_tileCount = letters;
    m_typed.clear();
    m_won = false;
    m_solutionShown = false;

    if (mode == SearchMode::BkTree) {
        if (!m_bk.generateLastWord(letters)) {
            return false;   // word list missing or no valid chain found
        }
        // The ladder needs at least `complexity` moves; leave some spare rows.
        // +1 for the pre-filled first word row.
        m_rowCount = m_bk.complexity + 5 + 1;
    } else {
        m_rowCount = 8;     // placeholder until the Trie mode is hooked up
    }

    ui->playLabel->setText(mode == SearchMode::Trie ? "Mode: Trie"
                                                    : "Mode: BK-Tree");

    buildGrid();

    if (mode == SearchMode::BkTree) {
        // Row 0 is the starting word, already locked in
        const QString first = QString::fromStdString(m_bk.getFirstWord()).toUpper();
        for (int c = 0; c < m_tileCount; ++c)
            m_tiles[0][c]->setText(QString(first[c]));
        m_currentRow = 1;
        ui->targetLabel->setText("Target: " +
                                 QString::fromStdString(m_bk.getLastWord()).toUpper());
    } else {
        m_currentRow = 0;
        ui->statusLabel->clear();
    }

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
    const bool boardFull = (m_currentRow >= m_rowCount) || m_won || m_solutionShown;

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

            // Trie mode will get its own validation later
            const std::string result = (m_mode == SearchMode::BkTree)
                                           ? m_bk.insertWord(word)
                                           : std::string("valid");

            if (result == "valid") {
                emit wordSubmitted(m_typed);
                m_typed.clear();
                ++m_currentRow;
                ui->targetLabel->setText("Target: " +
                                         QString::fromStdString(m_bk.getLastWord()).toUpper());

                if (m_mode == SearchMode::BkTree && word == m_bk.getLastWord()) {
                    m_won = true;
                    ui->statusLabel->setText("You win!");
                }
                else {
                    ui->tileScroll->ensureWidgetVisible(m_tiles[m_currentRow][0]);
                }
            } else {
                // Invalid: keep the row active so the player can fix it
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
    if (m_mode != SearchMode::BkTree) {
        ui->statusLabel->setText("No solution available in this mode");
        return;
    }

    const auto &solution = m_bk.getSolution();
    if (solution.empty() || static_cast<int>(solution.size()) > m_tiles.size())
        return;

    // Write each word of the path into its own row, first word on top
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

    // Color the solution rows green so they stand out from normal play
    for (int r = 0; r < row; ++r)
        for (int c = 0; c < m_tileCount; ++c)
            styleTile(m_tiles[r][c], "#2e7d32", "#66bb6a");

    ui->statusLabel->setText("Solution shown");
    ui->tileScroll->verticalScrollBar()->setValue(0);
}

void PlayPage::resetGame()
{
    if (m_tiles.isEmpty())
        return;

    m_typed.clear();
    m_won = false;
    m_solutionShown = false;

    // Clear every tile's text (solution or guesses may have filled them)
    for (auto &row : m_tiles)
        for (QLabel *t : row)
            t->setText(QString());

    if (m_mode == SearchMode::BkTree) {
        m_bk.resetProgress();

        // Row 0 is the starting word again
        const QString first = QString::fromStdString(m_bk.getFirstWord()).toUpper();
        for (int c = 0; c < m_tileCount; ++c)
            m_tiles[0][c]->setText(QString(first[c]));
        m_currentRow = 1;
    } else {
        m_currentRow = 0;
    }

    ui->statusLabel->clear();
    refreshTiles();
    ui->tileScroll->verticalScrollBar()->setValue(0);
    setFocus();
}