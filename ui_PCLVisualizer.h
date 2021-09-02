/********************************************************************************
** Form generated from reading UI file 'PCLVisualizer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
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
    QAction *actionExit;
    QAction *actionOpenlas;
    QAction *actionOpentxt;
    QAction *actionOpenbin;
    QAction *actionOpenpcd;
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
        PCLVisualizerClass->resize(1403, 749);
        actionExit = new QAction(PCLVisualizerClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionOpenlas = new QAction(PCLVisualizerClass);
        actionOpenlas->setObjectName(QStringLiteral("actionOpenlas"));
        actionOpentxt = new QAction(PCLVisualizerClass);
        actionOpentxt->setObjectName(QStringLiteral("actionOpentxt"));
        actionOpenbin = new QAction(PCLVisualizerClass);
        actionOpenbin->setObjectName(QStringLiteral("actionOpenbin"));
        actionOpenpcd = new QAction(PCLVisualizerClass);
        actionOpenpcd->setObjectName(QStringLiteral("actionOpenpcd"));
        centralWidget = new QWidget(PCLVisualizerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(0, 0, 1401, 691));
        PCLVisualizerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PCLVisualizerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1403, 23));
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
        menuFile->addAction(actionExit);
        menuFile->addAction(actionOpenlas);
        menuFile->addAction(actionOpentxt);
        menuFile->addAction(actionOpenbin);
        menuFile->addAction(actionOpenpcd);

        retranslateUi(PCLVisualizerClass);

        QMetaObject::connectSlotsByName(PCLVisualizerClass);
    } // setupUi

    void retranslateUi(QMainWindow *PCLVisualizerClass)
    {
        PCLVisualizerClass->setWindowTitle(QApplication::translate("PCLVisualizerClass", "PCLVisualizer", Q_NULLPTR));
        actionExit->setText(QApplication::translate("PCLVisualizerClass", "Exit", Q_NULLPTR));
        actionOpenlas->setText(QApplication::translate("PCLVisualizerClass", "Openlas", Q_NULLPTR));
        actionOpentxt->setText(QApplication::translate("PCLVisualizerClass", "Opentxt", Q_NULLPTR));
        actionOpenbin->setText(QApplication::translate("PCLVisualizerClass", "Openbin", Q_NULLPTR));
        actionOpenpcd->setText(QApplication::translate("PCLVisualizerClass", "Openpcd", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("PCLVisualizerClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PCLVisualizerClass: public Ui_PCLVisualizerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCLVISUALIZER_H
