#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QTableView>

class CustomTable : public QTableView
{
  Q_OBJECT
public:
  explicit CustomTable(QWidget *parent = 0);
  QModelIndex getParent(QModelIndex child);
signals:
  void getRootIndex(QModelIndex index);
  void rootChangedTo(QString);
public slots:
  void changeRootIndex(QModelIndex);
  void syncSelection(QItemSelection, QItemSelection);
  void previousDir();
  void findFolder(QString);
};

#endif // CUSTOMTABLE_H
