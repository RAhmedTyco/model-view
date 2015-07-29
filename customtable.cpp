#include "customtable.h"
#include <QDebug>
#include <QtGui>

CustomTable::CustomTable(QWidget *parent) :
  QTableView(parent)
{
}

void CustomTable::syncSelection(QItemSelection selected, QItemSelection deselected)
{
  qDebug() << tr("yes");
  if(!selected.isEmpty ())
  {
    QModelIndex lastSelected = selected.back ().indexes ().back ();
    changeRootIndex(lastSelected);
  }
}
/// called by syncSelection()
void CustomTable::changeRootIndex(QModelIndex index)
{
  if (index.isValid ())
  {
    setRootIndex(index);
    emit dataChanged(index, index);
    emit rootChangedTo(index.data(Qt::DisplayRole).toString());
  }
  qDebug() << tr("no");
}

void CustomTable::previousDir()
{
  const QModelIndex &index = getParent(this->rootIndex());
  changeRootIndex(index);
  emit getRootIndex(index);
}

QModelIndex CustomTable::getParent(QModelIndex child)
{
  QString st = child.data (Qt::DisplayRole).toString();
  qDebug() << st;
  if (st != QDir::rootPath ())
  {
    return child.parent();
  }
  else
    qDebug() << tr("oh no, root reached");
  return QModelIndex();
}

void CustomTable::findFolder(QString dir)
{

}
