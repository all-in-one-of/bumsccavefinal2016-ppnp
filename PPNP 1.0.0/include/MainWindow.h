#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NGLScene.h"
#include <QListWidgetItem>

/// @namespace Ui our Ui namespace created from the MainWindow class
namespace Ui {
    class MainWindow;
}
//----------------------------------------------------------------------------------------------------------------------
/// @file MainWindow.h
/// @brief The main class for our UI window
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/10/10
/// Revision History :
/// Initial Version 10/10/10 (Binary day ;-0 )
/// @class MainWindow
/// @brief our main UI window, created by MainWindow.ui and extended here
//----------------------------------------------------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  //----------------------------------------------------------------------------------------------------------------------
  //----------------------------------------------------------------------------------------------------------------------
    explicit MainWindow(QWidget *parent = 0);
  //----------------------------------------------------------------------------------------------------------------------
  //----------------------------------------------------------------------------------------------------------------------
    ~MainWindow();

private slots:
  void on_m_constructLatticePushButton_clicked();

  void on_m_latticeComboBox_currentIndexChanged(int index);

  void on_m_nSpinBox_valueChanged(int arg1);

  void on_m_distanceDoubleSpinBox_valueChanged(double arg1);

  void on_m_weightFunctionTypeComboBox_currentIndexChanged(int index);

  void on_m_alphaDoubleSpinBox_valueChanged(double arg1);

  void on_m_filenameLineEdit_textChanged(const QString &arg1);

  void on_m_browsePushButton_clicked();

  void on_m_rootIndexSpinBox_valueChanged(int arg1);

  void on_m_calcDistancesPushButton_clicked();

  void on_m_addEndPointPushButton_clicked();

  void on_m_deleteEndPointPushButton_clicked();

  void on_m_generatePathsPushButton_clicked();

  void on_actionExportPaths_triggered();

  void on_actionExitApp_triggered();

  void on_actionDisplayLatticeNodeIndices_triggered();

  void on_actionHideLatticeNodeIndices_triggered();

  void on_actionDisplayEdgeWeights_triggered();

  void on_actionHideEdgeWeights_triggered();

  void on_actionDisplayDistances_triggered();

  void on_actionHideDistances_triggered();

  void on_actionDisplayLatticeAll_triggered();

  void on_actionHideLatticeAll_triggered();

  void on_actionRefinePaths_triggered();

  void on_pushButton_2_clicked();

  void on_actionW_toggled(bool arg1);

  void on_actionL_toggled(bool arg1);

  void on_actionD_toggled(bool arg1);

  void on_actionN_toggled(bool arg1);

  void on_actionI_toggled(bool arg1);

  void on_m_isIrregular_clicked(bool checked);

  void on_m_endpointIndicesList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

  void on_actionB_toggled(bool arg1);

  void on_m_xMin_valueChanged(double arg1);

  void on_m_yMin_valueChanged(double arg1);

  void on_m_zMin_valueChanged(double arg1);

  void on_m_xMax_valueChanged(double arg1);

  void on_m_yMax_valueChanged(double arg1);

  void on_m_zMax_valueChanged(double arg1);

  void on_m_previewBoundingBox_clicked();

  void on_m_randomEndPointCount_valueChanged(int arg1);

private:
    //----------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------------------------------
    Ui::MainWindow *m_ui;
    //----------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------------------------------
    NGLScene *m_gl;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief override the keyPressEvent inherited from QObject so we can handle key presses.
    /// @param [in] _event the event to process
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent( QKeyEvent *_event );

    // user parameters provided by the ui
    int m_latticeTypeIndex;
    int m_n;
    ngl::Real m_distance;
    int m_weightFunctionTypeIndex;
    int m_rootIndex;
    ngl::Real m_alpha;
    std::string m_filename;
    bool m_latticeIsIrregular;
    bool m_3D;
    int m_randEndpointCount;
    ngl::Vec3 m_randEndpointMinBounds;
    ngl::Vec3 m_randEndpointMaxBounds;
};

#endif // MAINWINDOW_H
