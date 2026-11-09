#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>
#include <QString>
#include <QVector>
#include "BK_Tree.cpp"

class QKeyEvent;
class QLabel;
class QGridLayout;

namespace Ui { class PlayPage; }

enum class SearchMode { Trie, BkTree };

class PlayPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayPage(QWidget *parent = nullptr);
    ~PlayPage();

    bool startGame(SearchMode mode, int letters);

signals:
    void backRequested();
    void wordSubmitted(const QString &word);
    void solutionRequested();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void buildGrid();
    void refreshTiles();
    void styleTile(QLabel *tile, const QString &bg, const QString &border);
    void showSolution();
    bool m_solutionShown = false;
    void resetGame();

    Ui::PlayPage *ui;
    QGridLayout *m_grid = nullptr;
    SearchMode m_mode = SearchMode::Trie;
    BK_Tree m_bk;

    QString m_typed;
    int m_currentRow = 0;
    int m_tileCount = 5;     // set by startGame
    int m_rowCount = 8;      // set by startGame
    bool m_won = false;
    QVector<QVector<QLabel *>> m_tiles;
};

#endif