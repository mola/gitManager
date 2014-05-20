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

#ifndef REPOSITORYMODEL_H
#define REPOSITORYMODEL_H

#include <QtCore>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
 
#include "repositorynode.h"

class RepositoryModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    RepositoryModel(QObject *parent = 0);
    ~RepositoryModel();
    
    void afterCreate();
    QVariant data(const QModelIndex& index, int role) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& child) const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                             int role = Qt::DisplayRole) const;
			     
    void addRepository(git_repository *repo, QString path);
    QStringList getAllDirectores();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                  int role = Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation,
                        const QVariant &value, int role = Qt::EditRole);

    bool insertColumns(int position, int columns,
                        const QModelIndex &parent = QModelIndex());
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool insertRows(int position, int rows,
                     const QModelIndex &parent = QModelIndex());
    bool removeRows(int position, int rows,
                     const QModelIndex &parent = QModelIndex());

private:
  RepositoryNode* nodeFromIndex(const QModelIndex& index) const;
  
private:
  RepositoryNode * rootItem;
  QModelIndex  _rootModel;
};

#endif // REPOSITORYMODEL_H
