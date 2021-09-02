/********************************************************************************
** Form generated from reading UI file 'PCLVisualizer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCLVISUALIZER_H
#define UI_PCLVISUALIZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_PCLVisualizerClass
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionOpentxt;
    QAction *actiontest;
    QWidget *centralWidget;
    QVTKWidget *qvtkWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PCLVisualizerClass)
    {
        if (PCLVisualizerClass->objectName().isEmpty())
            PCLVisualizerClass->setObjectName(QStringLiteral("PCLVisualizerClass"));
        PCLVisualizerClass->resize(600, 400);
        actionOpen = new QAction(PCLVisualizerClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(PCLVisualizerClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionOpentxt = new QAction(PCLVisualizerClass);
        actionOpentxt->setObjectName(QStringLiteral("actionOpentxt"));
        actiontest = new QAction(PCLVisualizerClass);
        actiontest->setObjectName(QStringLiteral("actiontest"));
        centralWidget = new QWidget(PCLVisualizerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(0, 0, 581, 341));
        PCLVisualizerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PCLVisualizerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        PCLVisualizerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PCLVisualizerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PCLVisualizerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PCLVisualizerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PCLVisualizerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionExit);
        menuFile->addAction(actionOpentxt);
        menuFile->addAction(actiontest);

        retranslateUi(PCLVisualizerClass);

        QMetaObject::connectSlotsByName(PCLVisualizerClass);
    } // setupUi

    void retranslateUi(QMainWindow *PCLVisualizerClass)
    {
        PCLVisualizerClass->setWindowTitle(QApplication::translate("PCLVisualizerClass", "PCLVisualizer", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("PCLVisualizerClass", "Open", Q_NULLPTR));
        actionExit->setText(QApplication::translate("PCLVisualizerClass", "Exit", Q_NULLPTR));
        actionOpentxt->setText(QApplication::translate("PCLVisualizerClass", "Opentxt", Q_NULLPTR));
        actiontest->setText(QApplication::translate("PCLVisualizerClass", "test", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("PCLVisualizerClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PCLVisualizerClass: public Ui_PCLVisualizerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCLVISUALIZER_H
