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
public slots:
  void findFolder(QString);
};

#endif // CUSTOMTABLE_H
