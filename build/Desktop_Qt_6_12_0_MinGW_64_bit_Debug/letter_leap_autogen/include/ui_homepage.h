/********************************************************************************
** Form generated from reading UI file 'homepage.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomePage
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer_3;
    QPushButton *bkButton;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer;
    QPushButton *trieButton;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QPushButton *quitButton;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *HomePage)
    {
        if (HomePage->objectName().isEmpty())
            HomePage->setObjectName("HomePage");
        HomePage->resize(567, 452);
        verticalLayout_2 = new QVBoxLayout(HomePage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(HomePage);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Noto Sans JP Black")});
        font.setPointSize(40);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        bkButton = new QPushButton(HomePage);
        bkButton->setObjectName("bkButton");

        verticalLayout->addWidget(bkButton);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        trieButton = new QPushButton(HomePage);
        trieButton->setObjectName("trieButton");

        verticalLayout->addWidget(trieButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        quitButton = new QPushButton(HomePage);
        quitButton->setObjectName("quitButton");

        verticalLayout->addWidget(quitButton);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(HomePage);

        QMetaObject::connectSlotsByName(HomePage);
    } // setupUi

    void retranslateUi(QWidget *HomePage)
    {
        HomePage->setWindowTitle(QCoreApplication::translate("HomePage", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("HomePage", "Letter Leap!", nullptr));
        bkButton->setText(QCoreApplication::translate("HomePage", "Play with BK Tree", nullptr));
        trieButton->setText(QCoreApplication::translate("HomePage", "Play with Trie", nullptr));
        quitButton->setText(QCoreApplication::translate("HomePage", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomePage: public Ui_HomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
