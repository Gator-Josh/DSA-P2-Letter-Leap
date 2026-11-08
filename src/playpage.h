#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>

namespace Ui { class PlayPage; }

enum class SearchMode { Trie, BkTree };

class PlayPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayPage(QWidget *parent = nullptr);
    ~PlayPage();

    void setMode(SearchMode mode);

private:
    Ui::PlayPage *ui;
    SearchMode m_mode = SearchMode::Trie;
};

#endif