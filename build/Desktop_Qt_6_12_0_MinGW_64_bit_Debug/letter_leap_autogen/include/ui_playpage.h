/********************************************************************************
** Form generated from reading UI file 'playpage.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYPAGE_H
#define UI_PLAYPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayPage
{
public:
    QLabel *playLabel;

    void setupUi(QWidget *PlayPage)
    {
        if (PlayPage->objectName().isEmpty())
            PlayPage->setObjectName("PlayPage");
        PlayPage->resize(400, 300);
        playLabel = new QLabel(PlayPage);
        playLabel->setObjectName("playLabel");
        playLabel->setGeometry(QRect(170, 120, 49, 16));

        retranslateUi(PlayPage);

        QMetaObject::connectSlotsByName(PlayPage);
    } // setupUi

    void retranslateUi(QWidget *PlayPage)
    {
        PlayPage->setWindowTitle(QCoreApplication::translate("PlayPage", "Form", nullptr));
        playLabel->setText(QCoreApplication::translate("PlayPage", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayPage: public Ui_PlayPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYPAGE_H
