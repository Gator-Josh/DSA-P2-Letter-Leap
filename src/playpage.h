#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>
#include <QString>
#include <QVector>

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

    void setMode(SearchMode mode);

signals:
    void backRequested();
    void wordSubmitted(const QString &word);
    void solutionRequested();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void refreshTiles();
    void styleTile(QLabel *tile, const QString &bg, const QString &border);

    Ui::PlayPage *ui;
    QGridLayout *m_grid = nullptr;
    SearchMode m_mode = SearchMode::Trie;

    QString m_typed;
    int m_currentRow = 0;
    QVector<QVector<QLabel *>> m_tiles;

    static constexpr int kTileCount = 4;
    static constexpr int kRowCount  = 2000; // This is the secret... its not actually infinite attempts... :3
};

#endif