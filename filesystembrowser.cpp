#include "filesystembrowser.h"
void FileSystemBrowser::initialise(QWidget *parent)
{
  model = new QFileSystemModel;
  model->setRootPath(QDir::homePath ());

  tableView = new QTableView(parent);
  tableView->setModel(model);
  tableView->verticalHeader ()->hide();

  columnView = new QColumnView(parent);
  columnView->setModel(model);
  /// set up splitter
  splitter = new QSplitter;
  splitter->addWidget(columnView);
  splitter->addWidget(tableView);

  up = new QPushButton(tr("Up"));

  addressBar = new QComboBox(parent);
  addressBar->setModel(model);

  listView = new QListView(parent);
  listView->setModel(model);

  layout = new QVBoxLayout();

  layout1 = new QHBoxLayout();
  layout1->addWidget(up);
  layout1->addWidget(addressBar);
  layout->addLayout(layout1);
  layout->addWidget(splitter);
  setLayout(layout);
}

FileSystemBrowser::FileSystemBrowser(QWidget *parent)
  : QWidget(parent)
{
  initialise();
  /// change sizes
  int w = tableView->columnWidth(0) * model->columnCount (QModelIndex());
  splitter->widget(1)->setMinimumWidth(w);
  QList <int > listOfSizes;
  listOfSizes << static_cast < int >(columnView->width() * 3) << w ;
  splitter->setSizes(listOfSizes);

  /// synchronise the two views
  columnView->setSelectionMode (QAbstractItemView::SingleSelection);
  tableView->setSelectionMode (QAbstractItemView::SingleSelection);
  QItemSelectionModel *selectionModel = columnView->selectionModel();
  tableView->setSelectionModel(selectionModel);

  // connections

  QObject::connect( columnView
                   ,SIGNAL(pressed(QModelIndex))
                   ,tableView
                   ,SLOT(setCurrentIndex(QModelIndex)));
//  QObject::connect(columnView
//                  ,SIGNAL(pressed(QModelIndex))
//                  ,this
//                  ,SLOT(changeRootIndex(QModelIndex)));
//  QObject::connect(tableView
//                  ,SIGNAL(pressed(QModelIndex))
//                  ,this
//                  ,SLOT(changeRootIndex(QModelIndex)));
  QObject::connect( selectionModel
                   ,SIGNAL(selectionChanged(QItemSelection,QItemSelection))
                   ,this
                   ,SLOT(syncSelection(QItemSelection,QItemSelection)));


  /// synchronise the up button with the views

  QObject::connect(up, SIGNAL(clicked()), this, SLOT (moveUpOne()));

  /// set the address bar
  up->setMaximumWidth (80);


  QObject::connect(this, SIGNAL(pathChanged(QModelIndex))
                   ,columnView, SLOT(setCurrentIndex(QModelIndex)));


  addressBar->setEditable (true);
  addressBar->setView (listView);

  /// synchronise list with other views
  listView->setSelectionMode (QAbstractItemView::SingleSelection);
  // sync lineedit with other views
  QObject::connect(this, SIGNAL(addressPathChanged(QString))
                  ,addressBar, SLOT(setEditText(QString)));

  // sync list with other views
  QObject::connect(this, SIGNAL(pathChanged(QModelIndex))
                  ,listView, SLOT(setCurrentIndex(QModelIndex)));

  QObject::connect(addressBar, SIGNAL(currentIndexChanged(int))
                  ,this, SLOT(changeRootIndexAddress(int)));
//  QObject::connect(listView, SIGNAL(clicked(QModelIndex))
//                  ,this, SLOT(changeRootIndex(QModelIndex)));
  const QModelIndex &index = columnView->rootIndex ();
  qDebug() << index.child (0,0).data (QFileSystemModel::FileNameRole).toString ();
  selectionModel->select (QItemSelection(index, index), QItemSelectionModel::Select);
  changeRootIndex (index);
}
void FileSystemBrowser::changeRootIndexAddress(int index)
{
  qDebug() << "maybe";
  changeRootIndex(listView->currentIndex());
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
  if (child.data (Qt::DisplayRole).toString() != QDir::rootPath ())
    return child.parent();
  return QModelIndex();
}

void FileSystemBrowser::moveUpOne()
{
  const QModelIndex &index = getParent(tableView->rootIndex());
  changeRootIndex(index);
}

void FileSystemBrowser::changeRootIndex(QModelIndex index)
{
  if (index.isValid ())
  {
    if (model->fileInfo(index).isDir())
    {
      qDebug() << tr("no");
      tableView->setRootIndex(index);
      listView->setRootIndex (index);
      emit pathChanged(index);
      emit addressPathChanged(model->filePath(index));
    }
    else
    {
      tableView->setRootIndex(index.parent());
    }
  }
}

void FileSystemBrowser::repopulateAddressBar(QModelIndex)
{

}
