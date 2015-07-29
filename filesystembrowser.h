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
  void getRootIndex(QModelIndex index);
  void rootChangedTo(QString);
  void dataChanged(QModelIndex, QModelIndex);
public slots:
//  void changeRootIndex(QModelIndex);
//  void syncSelection(QItemSelection, QItemSelection);
  void previousDir();
//  void findFolder(QString);
private:
  QFileSystemModel *model;
  QSplitter *splitter;
  QVBoxLayout *layout;
  QHBoxLayout *layout1;
  QTableView *tableView;
  QColumnView *columnView;
  QPushButton *up;
  QComboBox *addressBar;
};

#endif // FILESYSTEMBROWSER_H
