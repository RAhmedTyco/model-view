#ifndef FILESYSTEMBROWSER_H
#define FILESYSTEMBROWSER_H
#include <QtGui>
#include "customtable.h"
class FileSystemBrowser
    : public QWidget
{
 Q_OBJECT
public:
  FileSystemBrowser(QWidget *parent = 0);
  QModelIndex getParent(QModelIndex child);
signals:
  void pathChanged(QModelIndex);
  void addressPath(QString);
  void dataChanged(QModelIndex, QModelIndex);
public slots:
  void changeRootIndex(QModelIndex);
  void syncSelection(QItemSelection, QItemSelection);
  void previousDir();
  void setAddressPath(const QModelIndex &file);
private:
  QFileSystemModel *model;
  QSplitter *splitter;
  QVBoxLayout *layout;
  QHBoxLayout *layout1;
  QTableView *tableView;
  QColumnView *columnView;
  QPushButton *up;
  QComboBox *addressBar;
  QString *currentDir;
};

#endif // FILESYSTEMBROWSER_H
