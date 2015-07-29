#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filesystembrowser.h"
#include <QtGui>

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = 0);

signals:

public slots:

private:
  QVBoxLayout *layout;
  QWidget *central;
  QPushButton *openFileBrowser;
  QAction *openFileBrowserAct;
  QMenu *fileMenu;

  FileSystemBrowser *fileBrowser;
};

#endif // MAINWINDOW_H
