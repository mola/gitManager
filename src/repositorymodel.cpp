/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "repositorymodel.h"

RepositoryModel::RepositoryModel(QObject *parent) :
    QAbstractItemModel(parent)
{
//   QString path ("/home/mola/Source/git2/osgearth/");
//    git_repository *e;
// 
//    int res = git_repository_open_ext( &e, path.toStdString().data(), 0, ".");
//   RepositoryNode *rr = new RepositoryNode (e, path,_rootItem);
   
   
//    qDebug() << rr->getDisplayName();
//   _repository.append( rr );
   
  QStringList headers;
  headers << tr("Name");
  
  rootItem = new RepositoryNode();
  
  QVector<QVariant> rootData;
  foreach (QString header, headers)
        rootData << header;
    
  rootItem->setCoulmns(rootData);

//   qDebug() << "ROOT MODEL :: " << _rootModel.row() << _rootModel.column();
  

    
}

void RepositoryModel::afterCreate()
{
//   qDebug() << "INDEX SIZE :: "  << this->persistentIndexList().size();
}

RepositoryModel::~RepositoryModel()
{
}

QVariant RepositoryModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    RepositoryNode *item = nodeFromIndex(index);

//     qDebug() << item->data(index.column());
    return item->data(index.column());
}

int RepositoryModel::columnCount(const QModelIndex& parent) const
{
    return rootItem->columnCount();
}

int RepositoryModel::rowCount(const QModelIndex& parent) const
{
    RepositoryNode *parentItem = nodeFromIndex(parent);

    if (parentItem == 0 )
      return 0;
    return parentItem->childCount();
}

QModelIndex RepositoryModel::parent(const QModelIndex& index) const
{
      if (!index.isValid())
        return QModelIndex();

    RepositoryNode *childItem = nodeFromIndex(index);
    RepositoryNode *parentItem = childItem->parent();

    if (parentItem == 0)
      return QModelIndex();
    
    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
    
//       const RepositoryNode* node = nodeFromIndex(child);
// 
//     if (node == 0)
//             return QModelIndex();
// 
// //     RepositoryNode* nodeParent = node->parent();
// // 
// //         if (nodeParent == 0)
// //             return QModelIndex();
// // 
// //    RepositoryNode* nodeGrandParent = nodeParent->parent();
// // 
// //         if (nodeGrandParent == 0)
//             return QModelIndex();
// 
// //     int row = nodeGrandParent->indexOfNode(nodeParent);
// 
// //     return createIndex(child.row(), child.column(), *node);

}

QModelIndex RepositoryModel::index(int row, int column, const QModelIndex& parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();


    RepositoryNode *parentItem = nodeFromIndex(parent);
    
//     if (parentItem == 0)
//       return createIndex(row, column, rootItem);
    
    RepositoryNode *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QVariant RepositoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

Qt::ItemFlags RepositoryModel::flags(const QModelIndex& index) const
{
   if (!index.isValid())
         return 0;

     return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  
}

bool RepositoryModel::insertColumns(int position, int columns, const QModelIndex& parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
  
}

bool RepositoryModel::insertRows(int position, int rows, const QModelIndex& parent)
{
    RepositoryNode *parentItem = nodeFromIndex(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
  
}

bool RepositoryModel::removeColumns(int position, int columns, const QModelIndex& parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
  
}

bool RepositoryModel::removeRows(int position, int rows, const QModelIndex& parent)
{
    RepositoryNode *parentItem = nodeFromIndex(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
  
}

bool RepositoryModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role != Qt::EditRole)
        return false;

    RepositoryNode *item = nodeFromIndex(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);
}

bool RepositoryModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role)
{
    return QAbstractItemModel::setHeaderData(section, orientation, value, role);
}

RepositoryNode* RepositoryModel::nodeFromIndex(const QModelIndex& index) const
{
    if (index.isValid()) {
        RepositoryNode *item = static_cast<RepositoryNode*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}

void RepositoryModel::addRepository(git_repository *repo, QString path)
{
    RepositoryNode *rr = new RepositoryNode (repo, path);

    QModelIndex index = QModelIndex();
    if (this->insertRow(0, index))
    {
        for (int column = 0; column < this->columnCount(index); ++column) {
            QModelIndex child = this->index(0, column, index);
	    QVariant rv = qVariantFromValue(rr);
            this->setData(child, rv, Qt::EditRole);
        }
    }
    
}

QStringList RepositoryModel::getAllDirectores()
{
	QStringList res;
	
	for (int i = 0; i< rootItem->childCount(); i++)
	{
		res << rootItem->child(i)->getDirPath();
	}
	return res;
}

#include "repositorymodel.moc"
