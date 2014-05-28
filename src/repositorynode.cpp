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

#include "repositorynode.h"

RepositoryNode::RepositoryNode(RepositoryNode *parentNode, QObject* parent): QObject(parent)
{
  _dirPath = "";
  _gitrepo = 0;
  _name = "";
  _open = false;
  _parentItem = 0;
  _itemCoulmns.insert(0, _name);
  _nodeType = RepositoryNode::RepoNodeType;
  QPixmap pixmap = QPixmap (":/document-open-folder.png");
  _icon = QIcon(pixmap);  
}

RepositoryNode::RepositoryNode(git_repository *e, QString dirpath, RepositoryNode *parentNode): QObject()
{
  _parentItem = parentNode;
  
  _dirPath = dirpath;
  _gitrepo = e;
  
  dirpath = dirpath.trimmed();
  QStringList na = dirpath.split("/");
  na.removeAll("");
  _name = na.last();
  _itemCoulmns.insert(0, _name);
  _open = false;
}

RepositoryNode::~RepositoryNode()
{
  qDeleteAll(childItems);
}

RepositoryNode* RepositoryNode::parent()
{
  return _parentItem;
}

QString RepositoryNode::getDirPath()
{
  return _dirPath;
}

QString RepositoryNode::getDisplayName()
{
  return _name;
}

git_repository* RepositoryNode::getGitRepository()
{
  return _gitrepo;
}

void RepositoryNode::repositoryOpen()
{
	QPixmap pixmap = QPixmap (":/document-open.png");
	_icon = QIcon(pixmap);
	_open = true;
}

void RepositoryNode::repositoryClose()
{
	QPixmap pixmap = QPixmap (":/document-open-folder.png");
	_icon = QIcon(pixmap);
  _open = false;

}

bool RepositoryNode::is_repository_open()
{
  return _open;
}

RepositoryNode* RepositoryNode::child(int number)
{
  return childItems.value(number);
}

bool RepositoryNode::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        RepositoryNode *item = new RepositoryNode(this);
        childItems.insert(position, item);
    }

    return true;
}

bool RepositoryNode::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

int RepositoryNode::childCount() const
{
    return childItems.count();
}


int RepositoryNode::childNumber()
{
    if (_parentItem)
        return _parentItem->childItems.indexOf(const_cast<RepositoryNode*>(this));

    return 0;
}

int RepositoryNode::columnCount() const
{
  return _itemCoulmns.count();
}

bool RepositoryNode::insertColumns(int position, int columns)
{
    if (position < 0 || position > _itemCoulmns.size())
        return false;

    for (int column = 0; column < columns; ++column)
        _itemCoulmns.insert(position, QVariant());

    foreach (RepositoryNode *child, childItems)
        child->insertColumns(position, columns);

    return true;
}

bool RepositoryNode::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > _itemCoulmns.size())
        return false;

    for (int column = 0; column < columns; ++column)
        _itemCoulmns.remove(position);

    foreach (RepositoryNode *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

QVariant RepositoryNode::data(int column) const
{
  return _itemCoulmns.value(column);
}

bool RepositoryNode::setData(int column, const QVariant& value)
{
    if (column < 0 || column >= _itemCoulmns.size())
        return false;

    QObject *pp = qvariant_cast<QObject *> (value);
    RepositoryNode *node = ( RepositoryNode * ) pp ;
    
    _dirPath = node->getDirPath();
    _name = node->getDisplayName();
    _gitrepo = node->getGitRepository();
    
    _itemCoulmns[column] = _name;
    return true;
}

void RepositoryNode::setCoulmns(QVector< QVariant >& data)
{
  _itemCoulmns = data;
}

void RepositoryNode::setNodeType(NodeType e)
{
	_nodeType = e;
}

RepositoryNode::NodeType RepositoryNode::getNodeType()
{
	return _nodeType;
}

void RepositoryNode::setIcon(QIcon icon)
{
	_icon = icon;
}

QIcon RepositoryNode::getIcon()
{
	return _icon;
}

#include "repositorynode.moc"
