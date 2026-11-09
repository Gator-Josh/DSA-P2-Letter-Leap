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
#include <QtWidgets/QSpinBox>
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
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_7;
    QLabel *hintText;
    QSpinBox *lengthSpin;
    QPushButton *bkButton;
    QSpacerItem *verticalSpacer;
    QPushButton *trieButton;
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

        verticalSpacer_3 = new QSpacerItem(544, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalSpacer_4 = new QSpacerItem(544, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        verticalSpacer_6 = new QSpacerItem(544, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        verticalSpacer_7 = new QSpacerItem(544, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        hintText = new QLabel(HomePage);
        hintText->setObjectName("hintText");
        hintText->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(hintText);

        lengthSpin = new QSpinBox(HomePage);
        lengthSpin->setObjectName("lengthSpin");
        lengthSpin->setMinimum(3);
        lengthSpin->setMaximum(12);
        lengthSpin->setValue(5);

        verticalLayout->addWidget(lengthSpin);

        bkButton = new QPushButton(HomePage);
        bkButton->setObjectName("bkButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(bkButton->sizePolicy().hasHeightForWidth());
        bkButton->setSizePolicy(sizePolicy);
        bkButton->setMinimumSize(QSize(0, 60));
        bkButton->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(bkButton);

        verticalSpacer = new QSpacerItem(544, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        trieButton = new QPushButton(HomePage);
        trieButton->setObjectName("trieButton");
        trieButton->setMinimumSize(QSize(0, 60));
        trieButton->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(trieButton);

        verticalSpacer_2 = new QSpacerItem(544, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        quitButton = new QPushButton(HomePage);
        quitButton->setObjectName("quitButton");
        quitButton->setMinimumSize(QSize(0, 60));
        quitButton->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(quitButton);

        verticalSpacer_5 = new QSpacerItem(544, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(HomePage);

        QMetaObject::connectSlotsByName(HomePage);
    } // setupUi

    void retranslateUi(QWidget *HomePage)
    {
        HomePage->setWindowTitle(QCoreApplication::translate("HomePage", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("HomePage", "Letter Leap!", nullptr));
        hintText->setText(QCoreApplication::translate("HomePage", "Please select a word size below:", nullptr));
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
