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

#ifndef REPOSITORYNODE_H
#define REPOSITORYNODE_H

#include <QtCore>
#include <git2.h>

enum NodeType {
    FileNodeType = 1,
    FolderNodeType = 2
};

// class Node: public QObject
// {
//   Q_OBJECT
//   
// public:
//   virtual QString displayName() const;
//   
// private:
//   NodeType m_nodeType;  
// };

class RepositoryNode : public QObject
{
    Q_OBJECT

public:
    explicit RepositoryNode(RepositoryNode *parentNode =0,QObject* parent = 0);
    RepositoryNode(git_repository *e, QString dirpath, RepositoryNode *parentNode=0);
    ~RepositoryNode();

    void setCoulmns(QVector<QVariant> &data);
    int columnCount() const;
    QVariant data(int column) const;
    
    RepositoryNode *child(int number);
    int childCount() const;

    int childNumber();
    bool insertChildren(int position, int count, int columns);
    bool removeChildren(int position, int count);

    bool setData(int column, const QVariant &value);

    RepositoryNode* parent();
    git_repository* getGitRepository();
    QString getDirPath();
    QString getDisplayName();
    
    void repositoryOpen();
    void repositoryClose();
    bool is_repository_open();
    

    bool insertColumns(int position, int columns);
    bool removeColumns(int position, int columns);
    
private:
  RepositoryNode *_parentItem;
  git_repository *_gitrepo;
  QString	  _dirPath;
  QString	  _name;
  
  QList<RepositoryNode*> childItems;
  QVector<QVariant> _itemCoulmns;
  
  bool _open;
};

#endif // REPOSITORYNODE_H
