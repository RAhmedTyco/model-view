#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  layout = new QVBoxLayout (parent);

  /// create a button
  QPushButton *openFileBrowser = new QPushButton(tr("&File Browser"));
  layout->addWidget (openFileBrowser);

  /// create a menu
  fileMenu = menuBar()->addMenu(tr("&File"));
  QAction *openFileBrowserAct = new QAction(tr("&File Browser"), parent);
  fileMenu->addAction(openFileBrowserAct);
  // connect(openFileBrowserAct, SIGNAL(triggered()), openFileBrowser, SLOT(click()));

  /// set the layout on the widget (i.e. button),
  /// and then set the mainwindow's central widget
  central = new QWidget(parent);
  central->setLayout (layout);
  setCentralWidget(central);

  fileBrowser = new FileSystemBrowser;
  connect (openFileBrowserAct, SIGNAL(triggered()), fileBrowser, SLOT(showMaximized()));
  connect (openFileBrowser, SIGNAL(clicked()), fileBrowser, SLOT(showMaximized()));
  connect (openFileBrowser, SIGNAL(clicked()), this, SLOT(close()));
  show();
}
