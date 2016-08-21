/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExportPaths;
    QAction *actionExitApp;
    QAction *actionW;
    QAction *actionI;
    QAction *actionN;
    QAction *actionD;
    QAction *actionL;
    QAction *actionRefinePaths;
    QAction *actionB;
    QWidget *m_centralwidget;
    QGridLayout *s_mainGridLayout;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_5;
    QGroupBox *groupBox_6;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QDoubleSpinBox *m_yMin;
    QDoubleSpinBox *m_zMax;
    QDoubleSpinBox *m_zMin;
    QDoubleSpinBox *m_xMax;
    QLabel *label_2;
    QDoubleSpinBox *m_xMin;
    QDoubleSpinBox *m_yMax;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QSpinBox *m_randomEndPointCount;
    QPushButton *m_previewBoundingBox;
    QGroupBox *groupBox_7;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_5;
    QLineEdit *m_endpointIndexLineEdit;
    QLabel *label_5;
    QPushButton *m_addEndPointPushButton;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_6;
    QListWidget *m_endpointIndicesList;
    QPushButton *m_deleteEndPointPushButton;
    QPushButton *m_generatePathsPushButton;
    QGroupBox *groupBox_4;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_7;
    QLabel *m_rootIndexLabel;
    QSpinBox *m_rootIndexSpinBox;
    QPushButton *m_calcDistancesPushButton;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QSpinBox *m_nSpinBox;
    QLabel *label;
    QLabel *m_distanceLabel;
    QComboBox *m_latticeComboBox;
    QLabel *m_typeLabel;
    QCheckBox *m_isIrregular;
    QDoubleSpinBox *m_distanceDoubleSpinBox;
    QLabel *m_nLabel;
    QGroupBox *groupBox_3;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_4;
    QComboBox *m_weightFunctionTypeComboBox;
    QLabel *m_filenameLabel;
    QPushButton *m_constructLatticePushButton;
    QHBoxLayout *m_filebrowseHorizontalLayout;
    QLineEdit *m_filenameLineEdit;
    QPushButton *m_browsePushButton;
    QLabel *m_weightFunctionLabel;
    QLabel *m_alphaLabel;
    QDoubleSpinBox *m_alphaDoubleSpinBox;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1321, 798);
        MainWindow->setBaseSize(QSize(0, 0));
        actionExportPaths = new QAction(MainWindow);
        actionExportPaths->setObjectName(QStringLiteral("actionExportPaths"));
        actionExitApp = new QAction(MainWindow);
        actionExitApp->setObjectName(QStringLiteral("actionExitApp"));
        actionExitApp->setIconVisibleInMenu(true);
        actionW = new QAction(MainWindow);
        actionW->setObjectName(QStringLiteral("actionW"));
        actionW->setCheckable(true);
        actionI = new QAction(MainWindow);
        actionI->setObjectName(QStringLiteral("actionI"));
        actionI->setCheckable(true);
        actionI->setChecked(false);
        actionN = new QAction(MainWindow);
        actionN->setObjectName(QStringLiteral("actionN"));
        actionN->setCheckable(true);
        actionN->setChecked(true);
        actionD = new QAction(MainWindow);
        actionD->setObjectName(QStringLiteral("actionD"));
        actionD->setCheckable(true);
        actionL = new QAction(MainWindow);
        actionL->setObjectName(QStringLiteral("actionL"));
        actionL->setCheckable(true);
        actionL->setChecked(true);
        actionRefinePaths = new QAction(MainWindow);
        actionRefinePaths->setObjectName(QStringLiteral("actionRefinePaths"));
        actionB = new QAction(MainWindow);
        actionB->setObjectName(QStringLiteral("actionB"));
        actionB->setCheckable(true);
        m_centralwidget = new QWidget(MainWindow);
        m_centralwidget->setObjectName(QStringLiteral("m_centralwidget"));
        s_mainGridLayout = new QGridLayout(m_centralwidget);
        s_mainGridLayout->setObjectName(QStringLiteral("s_mainGridLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_5 = new QGroupBox(m_centralwidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(0, 176));
        groupBox_5->setMaximumSize(QSize(16777215, 16777215));
        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, 30, 351, 151));
        gridLayoutWidget_2 = new QWidget(groupBox_6);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 20, 351, 128));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(gridLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        m_yMin = new QDoubleSpinBox(gridLayoutWidget_2);
        m_yMin->setObjectName(QStringLiteral("m_yMin"));
        m_yMin->setMinimum(-99);
        m_yMin->setSingleStep(0.1);

        gridLayout_2->addWidget(m_yMin, 1, 2, 1, 1);

        m_zMax = new QDoubleSpinBox(gridLayoutWidget_2);
        m_zMax->setObjectName(QStringLiteral("m_zMax"));
        m_zMax->setMinimum(-99);
        m_zMax->setSingleStep(1);
        m_zMax->setValue(2);

        gridLayout_2->addWidget(m_zMax, 2, 3, 1, 1);

        m_zMin = new QDoubleSpinBox(gridLayoutWidget_2);
        m_zMin->setObjectName(QStringLiteral("m_zMin"));
        m_zMin->setMinimum(-99);
        m_zMin->setSingleStep(0.1);

        gridLayout_2->addWidget(m_zMin, 1, 3, 1, 1);

        m_xMax = new QDoubleSpinBox(gridLayoutWidget_2);
        m_xMax->setObjectName(QStringLiteral("m_xMax"));
        m_xMax->setMinimum(-99);
        m_xMax->setSingleStep(1);
        m_xMax->setValue(2);

        gridLayout_2->addWidget(m_xMax, 2, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        m_xMin = new QDoubleSpinBox(gridLayoutWidget_2);
        m_xMin->setObjectName(QStringLiteral("m_xMin"));
        m_xMin->setMinimum(-99);
        m_xMin->setSingleStep(0.1);
        m_xMin->setValue(0);

        gridLayout_2->addWidget(m_xMin, 1, 1, 1, 1);

        m_yMax = new QDoubleSpinBox(gridLayoutWidget_2);
        m_yMax->setObjectName(QStringLiteral("m_yMax"));
        m_yMax->setMinimum(-99);
        m_yMax->setSingleStep(1);
        m_yMax->setValue(2);

        gridLayout_2->addWidget(m_yMax, 2, 2, 1, 1);

        label_3 = new QLabel(gridLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 3, 0, 1, 5);

        m_randomEndPointCount = new QSpinBox(gridLayoutWidget_2);
        m_randomEndPointCount->setObjectName(QStringLiteral("m_randomEndPointCount"));
        m_randomEndPointCount->setValue(1);

        gridLayout_2->addWidget(m_randomEndPointCount, 0, 1, 1, 4);

        m_previewBoundingBox = new QPushButton(gridLayoutWidget_2);
        m_previewBoundingBox->setObjectName(QStringLiteral("m_previewBoundingBox"));

        gridLayout_2->addWidget(m_previewBoundingBox, 1, 4, 2, 1);

        groupBox_7 = new QGroupBox(groupBox_5);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(0, 180, 351, 201));
        gridLayoutWidget_4 = new QWidget(groupBox_7);
        gridLayoutWidget_4->setObjectName(QStringLiteral("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(0, 20, 351, 29));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        m_endpointIndexLineEdit = new QLineEdit(gridLayoutWidget_4);
        m_endpointIndexLineEdit->setObjectName(QStringLiteral("m_endpointIndexLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_endpointIndexLineEdit->sizePolicy().hasHeightForWidth());
        m_endpointIndexLineEdit->setSizePolicy(sizePolicy);
        m_endpointIndexLineEdit->setMinimumSize(QSize(0, 24));
        m_endpointIndexLineEdit->setMaximumSize(QSize(16777215, 24));

        gridLayout_5->addWidget(m_endpointIndexLineEdit, 0, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_5->addWidget(label_5, 0, 0, 1, 1);

        m_addEndPointPushButton = new QPushButton(gridLayoutWidget_4);
        m_addEndPointPushButton->setObjectName(QStringLiteral("m_addEndPointPushButton"));
        m_addEndPointPushButton->setMaximumSize(QSize(30, 24));

        gridLayout_5->addWidget(m_addEndPointPushButton, 0, 2, 1, 1);

        gridLayoutWidget_5 = new QWidget(groupBox_7);
        gridLayoutWidget_5->setObjectName(QStringLiteral("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(0, 50, 351, 135));
        gridLayout_6 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        m_endpointIndicesList = new QListWidget(gridLayoutWidget_5);
        m_endpointIndicesList->setObjectName(QStringLiteral("m_endpointIndicesList"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_endpointIndicesList->sizePolicy().hasHeightForWidth());
        m_endpointIndicesList->setSizePolicy(sizePolicy1);
        m_endpointIndicesList->setMinimumSize(QSize(0, 100));
        m_endpointIndicesList->setMaximumSize(QSize(16777215, 100));

        gridLayout_6->addWidget(m_endpointIndicesList, 0, 1, 1, 1);

        m_deleteEndPointPushButton = new QPushButton(gridLayoutWidget_5);
        m_deleteEndPointPushButton->setObjectName(QStringLiteral("m_deleteEndPointPushButton"));
        m_deleteEndPointPushButton->setMaximumSize(QSize(30, 24));

        gridLayout_6->addWidget(m_deleteEndPointPushButton, 0, 2, 1, 1);

        m_generatePathsPushButton = new QPushButton(gridLayoutWidget_5);
        m_generatePathsPushButton->setObjectName(QStringLiteral("m_generatePathsPushButton"));
        m_generatePathsPushButton->setMaximumSize(QSize(16777215, 26));

        gridLayout_6->addWidget(m_generatePathsPushButton, 1, 1, 1, 2);


        gridLayout->addWidget(groupBox_5, 5, 0, 2, 1);

        groupBox_4 = new QGroupBox(m_centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 80));
        groupBox_4->setMaximumSize(QSize(16777215, 80));
        gridLayoutWidget_6 = new QWidget(groupBox_4);
        gridLayoutWidget_6->setObjectName(QStringLiteral("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(0, 20, 351, 62));
        gridLayout_7 = new QGridLayout(gridLayoutWidget_6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        m_rootIndexLabel = new QLabel(gridLayoutWidget_6);
        m_rootIndexLabel->setObjectName(QStringLiteral("m_rootIndexLabel"));

        gridLayout_7->addWidget(m_rootIndexLabel, 0, 0, 1, 1);

        m_rootIndexSpinBox = new QSpinBox(gridLayoutWidget_6);
        m_rootIndexSpinBox->setObjectName(QStringLiteral("m_rootIndexSpinBox"));
        m_rootIndexSpinBox->setMaximum(10000);

        gridLayout_7->addWidget(m_rootIndexSpinBox, 0, 1, 1, 1);

        m_calcDistancesPushButton = new QPushButton(gridLayoutWidget_6);
        m_calcDistancesPushButton->setObjectName(QStringLiteral("m_calcDistancesPushButton"));

        gridLayout_7->addWidget(m_calcDistancesPushButton, 1, 0, 1, 2);


        gridLayout->addWidget(groupBox_4, 3, 0, 1, 1);

        groupBox = new QGroupBox(m_centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(360, 235));
        groupBox->setMaximumSize(QSize(16777215, 240));
        groupBox->setLayoutDirection(Qt::LeftToRight);
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 30, 481, 81));
        gridLayoutWidget = new QWidget(groupBox_2);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 20, 351, 61));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        m_nSpinBox = new QSpinBox(gridLayoutWidget);
        m_nSpinBox->setObjectName(QStringLiteral("m_nSpinBox"));
        m_nSpinBox->setMaximum(100);
        m_nSpinBox->setDisplayIntegerBase(10);

        gridLayout_3->addWidget(m_nSpinBox, 0, 3, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 1, 2, 1, 1);

        m_distanceLabel = new QLabel(gridLayoutWidget);
        m_distanceLabel->setObjectName(QStringLiteral("m_distanceLabel"));
        m_distanceLabel->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(m_distanceLabel, 1, 0, 1, 1);

        m_latticeComboBox = new QComboBox(gridLayoutWidget);
        m_latticeComboBox->setObjectName(QStringLiteral("m_latticeComboBox"));
        m_latticeComboBox->setFrame(true);

        gridLayout_3->addWidget(m_latticeComboBox, 0, 1, 1, 1);

        m_typeLabel = new QLabel(gridLayoutWidget);
        m_typeLabel->setObjectName(QStringLiteral("m_typeLabel"));
        m_typeLabel->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(m_typeLabel, 0, 0, 1, 1);

        m_isIrregular = new QCheckBox(gridLayoutWidget);
        m_isIrregular->setObjectName(QStringLiteral("m_isIrregular"));

        gridLayout_3->addWidget(m_isIrregular, 1, 3, 1, 1);

        m_distanceDoubleSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        m_distanceDoubleSpinBox->setObjectName(QStringLiteral("m_distanceDoubleSpinBox"));
        m_distanceDoubleSpinBox->setMaximum(5);
        m_distanceDoubleSpinBox->setSingleStep(0.1);

        gridLayout_3->addWidget(m_distanceDoubleSpinBox, 1, 1, 1, 1);

        m_nLabel = new QLabel(gridLayoutWidget);
        m_nLabel->setObjectName(QStringLiteral("m_nLabel"));
        m_nLabel->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(m_nLabel, 0, 2, 1, 1);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 120, 351, 121));
        gridLayoutWidget_3 = new QWidget(groupBox_3);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(0, 20, 351, 91));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        m_weightFunctionTypeComboBox = new QComboBox(gridLayoutWidget_3);
        m_weightFunctionTypeComboBox->setObjectName(QStringLiteral("m_weightFunctionTypeComboBox"));
        m_weightFunctionTypeComboBox->setEnabled(true);
        m_weightFunctionTypeComboBox->setMaximumSize(QSize(200, 16777215));

        gridLayout_4->addWidget(m_weightFunctionTypeComboBox, 0, 1, 1, 1);

        m_filenameLabel = new QLabel(gridLayoutWidget_3);
        m_filenameLabel->setObjectName(QStringLiteral("m_filenameLabel"));
        m_filenameLabel->setEnabled(false);

        gridLayout_4->addWidget(m_filenameLabel, 2, 0, 1, 1);

        m_constructLatticePushButton = new QPushButton(gridLayoutWidget_3);
        m_constructLatticePushButton->setObjectName(QStringLiteral("m_constructLatticePushButton"));

        gridLayout_4->addWidget(m_constructLatticePushButton, 3, 0, 1, 4);

        m_filebrowseHorizontalLayout = new QHBoxLayout();
        m_filebrowseHorizontalLayout->setObjectName(QStringLiteral("m_filebrowseHorizontalLayout"));
        m_filenameLineEdit = new QLineEdit(gridLayoutWidget_3);
        m_filenameLineEdit->setObjectName(QStringLiteral("m_filenameLineEdit"));
        m_filenameLineEdit->setEnabled(false);

        m_filebrowseHorizontalLayout->addWidget(m_filenameLineEdit);

        m_browsePushButton = new QPushButton(gridLayoutWidget_3);
        m_browsePushButton->setObjectName(QStringLiteral("m_browsePushButton"));
        m_browsePushButton->setEnabled(false);
        m_browsePushButton->setMaximumSize(QSize(30, 27));

        m_filebrowseHorizontalLayout->addWidget(m_browsePushButton);


        gridLayout_4->addLayout(m_filebrowseHorizontalLayout, 2, 1, 1, 3);

        m_weightFunctionLabel = new QLabel(gridLayoutWidget_3);
        m_weightFunctionLabel->setObjectName(QStringLiteral("m_weightFunctionLabel"));
        m_weightFunctionLabel->setMinimumSize(QSize(100, 0));
        m_weightFunctionLabel->setMaximumSize(QSize(100, 16777215));

        gridLayout_4->addWidget(m_weightFunctionLabel, 0, 0, 1, 1);

        m_alphaLabel = new QLabel(gridLayoutWidget_3);
        m_alphaLabel->setObjectName(QStringLiteral("m_alphaLabel"));
        m_alphaLabel->setEnabled(false);

        gridLayout_4->addWidget(m_alphaLabel, 0, 2, 1, 1);

        m_alphaDoubleSpinBox = new QDoubleSpinBox(gridLayoutWidget_3);
        m_alphaDoubleSpinBox->setObjectName(QStringLiteral("m_alphaDoubleSpinBox"));
        m_alphaDoubleSpinBox->setEnabled(false);
        m_alphaDoubleSpinBox->setMaximum(5);

        gridLayout_4->addWidget(m_alphaDoubleSpinBox, 0, 3, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        s_mainGridLayout->addLayout(gridLayout, 0, 2, 7, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainGridLayout->addItem(horizontalSpacer_3, 6, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainGridLayout->addItem(horizontalSpacer_2, 6, 1, 1, 1);

        MainWindow->setCentralWidget(m_centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1321, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menuFile->addAction(actionExportPaths);
        menuFile->addSeparator();
        menuFile->addAction(actionExitApp);
        menuTools->addAction(actionRefinePaths);
        toolBar->addAction(actionW);
        toolBar->addAction(actionI);
        toolBar->addAction(actionN);
        toolBar->addAction(actionD);
        toolBar->addAction(actionL);
        toolBar->addAction(actionB);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Path Planning for Modelling Natural Phenomena 1.0", 0));
        actionExportPaths->setText(QApplication::translate("MainWindow", "Export Paths", 0));
        actionExitApp->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionW->setText(QApplication::translate("MainWindow", "W", 0));
#ifndef QT_NO_TOOLTIP
        actionW->setToolTip(QApplication::translate("MainWindow", "Toggle Weights", 0));
#endif // QT_NO_TOOLTIP
        actionI->setText(QApplication::translate("MainWindow", "I", 0));
#ifndef QT_NO_TOOLTIP
        actionI->setToolTip(QApplication::translate("MainWindow", "Toggle Reference Image", 0));
#endif // QT_NO_TOOLTIP
        actionN->setText(QApplication::translate("MainWindow", "N", 0));
#ifndef QT_NO_TOOLTIP
        actionN->setToolTip(QApplication::translate("MainWindow", "Toggle Node Indices", 0));
#endif // QT_NO_TOOLTIP
        actionD->setText(QApplication::translate("MainWindow", "D", 0));
#ifndef QT_NO_TOOLTIP
        actionD->setToolTip(QApplication::translate("MainWindow", "Toggle Distances", 0));
#endif // QT_NO_TOOLTIP
        actionL->setText(QApplication::translate("MainWindow", "L", 0));
#ifndef QT_NO_TOOLTIP
        actionL->setToolTip(QApplication::translate("MainWindow", "Toggle Lattice", 0));
#endif // QT_NO_TOOLTIP
        actionL->setShortcut(QApplication::translate("MainWindow", "L", 0));
        actionRefinePaths->setText(QApplication::translate("MainWindow", "Refine Paths", 0));
        actionB->setText(QApplication::translate("MainWindow", "B", 0));
#ifndef QT_NO_TOOLTIP
        actionB->setToolTip(QApplication::translate("MainWindow", "Toggle Endpoint Bounding Box", 0));
#endif // QT_NO_TOOLTIP
        actionB->setShortcut(QApplication::translate("MainWindow", "B", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Step 3 - Select End Points", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Random Select", 0));
        label_4->setText(QApplication::translate("MainWindow", "Max", 0));
        label_2->setText(QApplication::translate("MainWindow", "Amount", 0));
        label_3->setText(QApplication::translate("MainWindow", "Min", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Select Random Endpoints", 0));
        m_previewBoundingBox->setText(QApplication::translate("MainWindow", "P", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Index Select", 0));
        label_5->setText(QApplication::translate("MainWindow", "Endpoint", 0));
        m_addEndPointPushButton->setText(QApplication::translate("MainWindow", "+", 0));
        m_deleteEndPointPushButton->setText(QApplication::translate("MainWindow", "-", 0));
        m_generatePathsPushButton->setText(QApplication::translate("MainWindow", "Generate Paths", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Step 2 - Select Root", 0));
        m_rootIndexLabel->setText(QApplication::translate("MainWindow", "Root Index", 0));
        m_calcDistancesPushButton->setText(QApplication::translate("MainWindow", "Calculate Distances From Root", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Step 1 - Construct Weighted Lattice", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Lattice Options", 0));
        label->setText(QApplication::translate("MainWindow", "Irregular", 0));
        m_distanceLabel->setText(QApplication::translate("MainWindow", "Edge Length", 0));
        m_latticeComboBox->clear();
        m_latticeComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Square 2D", 0)
         << QApplication::translate("MainWindow", "Hexagon 2D", 0)
         << QApplication::translate("MainWindow", "Cube", 0)
        );
        m_typeLabel->setText(QApplication::translate("MainWindow", "Type", 0));
        m_isIrregular->setText(QString());
        m_nLabel->setText(QApplication::translate("MainWindow", "Steps", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Weight Function Options", 0));
        m_weightFunctionTypeComboBox->clear();
        m_weightFunctionTypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", 0)
         << QApplication::translate("MainWindow", "Default (eR^alpha)", 0)
         << QApplication::translate("MainWindow", "Image (2D Lattices Only)", 0)
        );
        m_filenameLabel->setText(QApplication::translate("MainWindow", "Filename", 0));
        m_constructLatticePushButton->setText(QApplication::translate("MainWindow", "Construct Lattice", 0));
        m_browsePushButton->setText(QApplication::translate("MainWindow", "...", 0));
        m_weightFunctionLabel->setText(QApplication::translate("MainWindow", "Type", 0));
        m_alphaLabel->setText(QApplication::translate("MainWindow", "Alpha", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
