
/// @file MainWindow.cpp
/// @brief basic implementation file for the MainWindow class
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QStandardPaths>

//----------------------------------------------------------------------------------------------------------------------
MainWindow::MainWindow( QWidget *parent ) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  // setup the user interface
  m_ui->setupUi(this);
  m_gl = new NGLScene(this);
  m_ui->s_mainGridLayout->addWidget(m_gl, 0, 0, 7, 2);

  // slots for the menu bar actions
  // QAction* exportPathsAction = m_ui->menuFile->actions().at(0);
  // connect(exportPathsAction, SIGNAL(triggered()), this, SLOT(on_actionExportPaths_triggered()));
  QAction* exitAppAction = m_ui->menuFile->actions().at(2);
  connect(exitAppAction, SIGNAL(triggered()), this, SLOT(on_actionExitApp_triggered()));

  // set good default values
  m_latticeTypeIndex = 0;
  m_n = 2;
  m_distance = 1.0;
  m_weightFunctionTypeIndex = 0;
  m_rootIndex = 0;
  m_alpha = 0;
  m_latticeIsIrregular = false;
  m_3D = false;
  m_randEndpointCount = 1;
  m_randEndpointMinBounds = ngl::Vec3(0, 0, 0);
  m_randEndpointMaxBounds = ngl::Vec3(2, 2, 2);
}

//----------------------------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
  delete m_ui;
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::keyPressEvent(QKeyEvent *_event  )
{
  this->setFocus(Qt::ActiveWindowFocusReason);

  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
    case Qt::Key_Escape :{ QApplication::exit(EXIT_SUCCESS); break;}
    // show full screen
    default : break;
  }
  // finally update the GLWindow and re-draw
  m_gl->update();
}

// Event Slots

void MainWindow::on_m_latticeComboBox_currentIndexChanged(int index)
{
  m_latticeTypeIndex = index;

  if(index == 2)
  {
    m_3D = true;
  }
}

void MainWindow::on_m_nSpinBox_valueChanged(int arg1)
{
  m_n = arg1;
}

void MainWindow::on_m_distanceDoubleSpinBox_valueChanged(double arg1)
{
  m_distance = arg1;
}

void MainWindow::on_m_weightFunctionTypeComboBox_currentIndexChanged(int index)
{
  m_weightFunctionTypeIndex = index;

  if(index == 0)
  {
    m_ui->m_alphaLabel->setEnabled(false);
    m_ui->m_alphaDoubleSpinBox->setEnabled(false);
    m_ui->m_filenameLabel->setEnabled(false);
    m_ui->m_filenameLineEdit->setEnabled(false);
    m_ui->m_browsePushButton->setEnabled(false);
  }
  else if (index == 1)
  {
    m_ui->m_alphaLabel->setEnabled(true);
    m_ui->m_alphaDoubleSpinBox->setEnabled(true);
    m_ui->m_filenameLabel->setEnabled(false);
    m_ui->m_filenameLineEdit->setEnabled(false);
    m_ui->m_browsePushButton->setEnabled(false);
  }
  else
  {
    m_ui->m_alphaLabel->setEnabled(false);
    m_ui->m_alphaDoubleSpinBox->setEnabled(false);
    m_ui->m_filenameLabel->setEnabled(true);
    m_ui->m_filenameLineEdit->setEnabled(true);
    m_ui->m_browsePushButton->setEnabled(true);
  }
}

void MainWindow::on_m_alphaDoubleSpinBox_valueChanged(double arg1)
{
  m_alpha = arg1;
}

void MainWindow::on_m_filenameLineEdit_textChanged(const QString &arg1)
{
  m_filename = arg1.toStdString();
}

void MainWindow::on_m_browsePushButton_clicked()
{
  QString filename = QFileDialog::getOpenFileName(this,
                                                  tr("Select Image"),
                                                  QStandardPaths::displayName(QStandardPaths::HomeLocation),
                                                  tr("Image Files (*.jpg *.png *.bmp)"));
  m_ui->m_filenameLineEdit->setText(filename);

  m_filename = filename.toStdString();
}

void MainWindow::on_m_constructLatticePushButton_clicked()
{
  std::vector<std::string> largs;
  std::vector<std::string> wargs;

  largs.push_back(std::to_string(m_n));
  largs.push_back(std::to_string(m_distance));

  // if the user selected square we need to pass in additional parameters
  if(m_latticeTypeIndex == 0 || m_latticeTypeIndex == 2)
  {
    largs.push_back("0"); // centre x
    largs.push_back("0"); // centre y
    largs.push_back("0"); // centre z
    largs.push_back("1"); // is weighted

    if(m_3D)
    {
      largs.push_back("1");
    }
    else
    {
      largs.push_back("0");
    }

    if(m_latticeIsIrregular)
    {
      largs.push_back("1");
    }
    else
    {
      largs.push_back("0");
    }
  }

  if(m_weightFunctionTypeIndex == 1) // default
  {
    wargs.push_back(std::to_string(m_alpha));
  }
  else if (m_weightFunctionTypeIndex == 2) // image
  {
    wargs.push_back(m_filename);
  }

  m_gl->constructLattice(m_latticeTypeIndex, m_weightFunctionTypeIndex, largs, wargs);
}

void MainWindow::on_m_rootIndexSpinBox_valueChanged(int arg1)
{
  m_rootIndex = arg1;
}

void MainWindow::on_m_calcDistancesPushButton_clicked()
{
  m_gl->setRootByIndex(m_rootIndex);
  m_gl->calculateDistancesFromRoot();
}

void MainWindow::on_m_addEndPointPushButton_clicked()
{
  if(!m_ui->m_endpointIndexLineEdit->text().isEmpty())
  {
    m_ui->m_endpointIndicesList->addItem(m_ui->m_endpointIndexLineEdit->text());
  }
}

void MainWindow::on_m_deleteEndPointPushButton_clicked()
{
  QListWidgetItem* selected = m_ui->m_endpointIndicesList->currentItem();
  int value = selected->text().toInt();

  if(selected != nullptr)
  {
    m_ui->m_endpointIndicesList->takeItem(m_ui->m_endpointIndicesList->row(selected));
    m_gl->removeEndPointByIndex(value);
  }
}

void MainWindow::on_m_generatePathsPushButton_clicked()
{
    std::vector<int> endpointIndices;

    for(int i = 0; i < m_ui->m_endpointIndicesList->count(); ++i)
    {
      endpointIndices.push_back(m_ui->m_endpointIndicesList->item(i)->text().toInt());
    }

    m_gl->generatePaths(endpointIndices);
}

void MainWindow::on_actionExportPaths_triggered()
{
  m_gl->exportPaths();
}

void MainWindow::on_actionExitApp_triggered()
{
  QApplication::exit(EXIT_SUCCESS);
}

void MainWindow::on_actionDisplayLatticeNodeIndices_triggered()
{
  m_gl->setIndicesDisplay(true);
}

void MainWindow::on_actionDisplayEdgeWeights_triggered()
{
  m_gl->setWeightsDisplay(true);
}

void MainWindow::on_actionDisplayDistances_triggered()
{
  m_gl->setDistancesDisplay(true);
}

void MainWindow::on_actionHideLatticeNodeIndices_triggered()
{
  m_gl->setIndicesDisplay(false);
}

void MainWindow::on_actionHideEdgeWeights_triggered()
{
  m_gl->setWeightsDisplay(false);
}

void MainWindow::on_actionHideDistances_triggered()
{
  m_gl->setDistancesDisplay(false);
}

void MainWindow::on_actionDisplayLatticeAll_triggered()
{
  m_gl->setDisplayAll(true);
}

void MainWindow::on_actionHideLatticeAll_triggered()
{
  m_gl->setDisplayAll(false);
}

void MainWindow::on_actionRefinePaths_triggered()
{
  m_gl->refinePaths();
}
// end Event Slots

void MainWindow::on_pushButton_2_clicked()
{
  std::vector<int> randomEndPointIndices = m_gl->setRandomEndPoints(m_randEndpointCount, m_randEndpointMinBounds, m_randEndpointMaxBounds);
  //std::vector<int> randomEndPointIndices = m_gl->setRandomEndPoints();

  for(int i = 0; i < randomEndPointIndices.size(); ++i)
  {
    std::string index = std::to_string(randomEndPointIndices[i]);
     m_ui->m_endpointIndicesList->addItem(QString::fromStdString(index));
  }
}

void MainWindow::on_actionW_toggled(bool arg1)
{
    m_gl->setWeightsDisplay(arg1);
}

void MainWindow::on_actionL_toggled(bool arg1)
{
    m_gl->setLatticeDisplay(arg1);
}

void MainWindow::on_actionD_toggled(bool arg1)
{
    m_gl->setDistancesDisplay(arg1);
}

void MainWindow::on_actionN_toggled(bool arg1)
{
    m_gl->setIndicesDisplay(arg1);
}

void MainWindow::on_actionI_toggled(bool arg1)
{
    m_gl->setImageDisplay(arg1);
}

void MainWindow::on_m_isIrregular_clicked(bool checked)
{
    m_ui->menuTools->actions().at(0)->setEnabled(!checked);
    m_latticeIsIrregular = checked;
}

void MainWindow::on_m_endpointIndicesList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
  m_gl->setPathSelected(current->text().toInt(), true);

  if(previous != nullptr)
  {
     m_gl->setPathSelected(previous->text().toInt(), false);
  }

  m_gl->update();
}

void MainWindow::on_actionB_toggled(bool arg1)
{
  m_gl->setBoundingBoxDisplay(arg1);
}

void MainWindow::on_m_xMin_valueChanged(double arg1)
{
  this->m_randEndpointMinBounds.m_x = arg1;
}

void MainWindow::on_m_yMin_valueChanged(double arg1)
{
  this->m_randEndpointMinBounds.m_y = arg1;
}

void MainWindow::on_m_zMin_valueChanged(double arg1)
{
  this->m_randEndpointMinBounds.m_z = arg1;
}

void MainWindow::on_m_xMax_valueChanged(double arg1)
{
  this->m_randEndpointMaxBounds.m_x = arg1;
}

void MainWindow::on_m_yMax_valueChanged(double arg1)
{
  this->m_randEndpointMaxBounds.m_y = arg1;
}

void MainWindow::on_m_zMax_valueChanged(double arg1)
{
  this->m_randEndpointMaxBounds.m_z = arg1;
}

void MainWindow::on_m_previewBoundingBox_clicked()
{
  m_gl->createBoundingBox(m_randEndpointMinBounds, m_randEndpointMaxBounds);
}

void MainWindow::on_m_randomEndPointCount_valueChanged(int arg1)
{
    m_randEndpointCount = arg1;
}
