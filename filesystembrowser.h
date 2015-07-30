#ifndef FILESYSTEMBROWSER_H
#define FILESYSTEMBROWSER_H
#include <QtGui>
class FileSystemBrowser
    : public QWidget
{
 Q_OBJECT
public:
  FileSystemBrowser(QWidget *parent = 0);
  void initialise(QWidget *parent = 0);
  QModelIndex getParent(QModelIndex child);
signals:
  void pathChanged(QModelIndex);
  void addressPathChanged(QString);
public slots:
  void changeRootIndex(QModelIndex);
  void changeRootIndexAddress(int);
  void moveUpOne();
  void repopulateAddressBar(QModelIndex);
  void syncSelection(QItemSelection,QItemSelection);
//  void setAddressPath(const QModelIndex &file);
private:
  QFileSystemModel *model;
  QSplitter *splitter;
  QVBoxLayout *layout;
  QHBoxLayout *layout1;
  QTableView *tableView;
  QColumnView *columnView;
  QPushButton *up;
  QComboBox *addressBar;
  QListView *listView;
  QString *currentDir;
};

#endif // FILESYSTEMBROWSER_H
