#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>

namespace Ui { class HomePage; }

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

signals:
    void playTrieRequested();
    void playBkTreeRequested();
    void quitRequested();

private:
    Ui::HomePage *ui;
};

#endif