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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *playLabel;
    QLabel *targetLabel;
    QLabel *statusLabel;
    QScrollArea *tileScroll;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *backButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *resetButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *solutionButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *PlayPage)
    {
        if (PlayPage->objectName().isEmpty())
            PlayPage->setObjectName("PlayPage");
        PlayPage->resize(782, 446);
        verticalLayout = new QVBoxLayout(PlayPage);
        verticalLayout->setObjectName("verticalLayout");
        playLabel = new QLabel(PlayPage);
        playLabel->setObjectName("playLabel");

        verticalLayout->addWidget(playLabel);

        targetLabel = new QLabel(PlayPage);
        targetLabel->setObjectName("targetLabel");

        verticalLayout->addWidget(targetLabel);

        statusLabel = new QLabel(PlayPage);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

        tileScroll = new QScrollArea(PlayPage);
        tileScroll->setObjectName("tileScroll");
        tileScroll->setFrameShape(QFrame::Shape::NoFrame);
        tileScroll->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        tileScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        tileScroll->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 764, 330));
        tileScroll->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(tileScroll);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        backButton = new QPushButton(PlayPage);
        backButton->setObjectName("backButton");

        horizontalLayout->addWidget(backButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        resetButton = new QPushButton(PlayPage);
        resetButton->setObjectName("resetButton");

        horizontalLayout->addWidget(resetButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        solutionButton = new QPushButton(PlayPage);
        solutionButton->setObjectName("solutionButton");

        horizontalLayout->addWidget(solutionButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PlayPage);

        QMetaObject::connectSlotsByName(PlayPage);
    } // setupUi

    void retranslateUi(QWidget *PlayPage)
    {
        PlayPage->setWindowTitle(QCoreApplication::translate("PlayPage", "Form", nullptr));
        playLabel->setText(QCoreApplication::translate("PlayPage", "TextLabel", nullptr));
        targetLabel->setText(QCoreApplication::translate("PlayPage", "TextLabel", nullptr));
        statusLabel->setText(QCoreApplication::translate("PlayPage", "Errors/Feedback will be shown here!", nullptr));
        backButton->setText(QCoreApplication::translate("PlayPage", "Back to Menu", nullptr));
        resetButton->setText(QCoreApplication::translate("PlayPage", "Reset", nullptr));
        solutionButton->setText(QCoreApplication::translate("PlayPage", "Show Solution", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayPage: public Ui_PlayPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYPAGE_H
