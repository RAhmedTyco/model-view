#include "filesystembrowser.h"

FileSystemBrowser::FileSystemBrowser(QWidget *parent)
  : QWidget(parent)
{
  model = new QFileSystemModel;
  model->setRootPath(QDir::homePath ());

  tableView = new QTableView(parent);
  tableView->setModel(model);
  tableView->verticalHeader ()->hide();

  columnView = new QColumnView(parent);
  columnView->setModel(model);

  splitter = new QSplitter;
  splitter->addWidget(columnView);
  splitter->addWidget(tableView);
  int w = tableView->columnWidth(0) * model->columnCount (QModelIndex());
  splitter->widget(1)->setMinimumWidth(w);
  QList <int > listOfSizes;
  listOfSizes << static_cast < int >(columnView->width() * 3) << w ;
  splitter->setSizes(listOfSizes);
  //synchronise the two views

  QItemSelectionModel *selectionModel = columnView->selectionModel();

  columnView->setSelectionMode (QAbstractItemView::SingleSelection);
  tableView->setSelectionModel(selectionModel);
  tableView->setSelectionMode (QAbstractItemView::SingleSelection);

  // connections
  QObject::connect( columnView
                   ,SIGNAL(pressed(QModelIndex))
                   ,tableView
                   ,SLOT(setCurrentIndex(QModelIndex)));

  QObject::connect( selectionModel
                   ,SIGNAL(selectionChanged(QItemSelection,QItemSelection))
                   ,this
                   ,SLOT(syncSelection(QItemSelection,QItemSelection)));


  //synchronise the up button with the views
  up = new QPushButton(tr("Up"));
  up->setMaximumWidth (80);
  QObject::connect(up, SIGNAL(clicked()), this, SLOT (previousDir()));


  QObject::connect(this, SIGNAL(rootChanged(QModelIndex))
                   ,columnView, SLOT(setCurrentIndex(QModelIndex)));

  addressBar = new QComboBox();
  addressBar->setModel(model);

//  QObject::connect(model, SIGNAL(directoryLoaded(QString)), addressBar, SLOT(setEditText(QString)));
//  QObject::connect(tableView, SIGNAL(rootChangedTo(QString)), addressBar, SLOT(setEditText(QString)));
  addressBar->setEditable (true);

//  QObject::connect( tableView, SIGNAL(entered(QModelIndex))
//                   this, );
//  QObject::connect(this, SIGNAL(dataChanged(QModelIndex,QModelIndex))
//                  ,tableView, SLOT(dataChanged(QModelIndex,QModelIndex)));

  layout = new QVBoxLayout();
  layout1 = new QHBoxLayout();
  layout1->addWidget(up);
  layout1->addWidget(addressBar);
  layout->addLayout(layout1);
  layout->addWidget(splitter);
  setLayout(layout);
  //splitter->show();
}
void FileSystemBrowser::syncSelection(QItemSelection selected, QItemSelection deselected)
{
  qDebug() << tr("yes");
  if(!selected.isEmpty ())
  {
    QModelIndex lastSelected = selected.back ().indexes ().back ();
    changeRootIndex(lastSelected);
  }
}

QModelIndex FileSystemBrowser::getParent(QModelIndex child)
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
void FileSystemBrowser::previousDir()
{
  const QModelIndex &index = getParent(this->tableView->rootIndex());
  changeRootIndex(index);
  emit rootChanged(index);
}
void FileSystemBrowser::changeRootIndex(QModelIndex index)
{
  if (index.isValid ())
  {
    tableView->setRootIndex(index);
    emit dataChanged(index, index);
    emit rootChangedTo(index.data(Qt::DisplayRole).toString());
  }
  qDebug() << tr("no");
}

void FileSystemBrowser::changeCurrentDir (QString dir)
{

}
