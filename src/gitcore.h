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

#ifndef GITCORE_H
#define GITCORE_H

#include <git2.h>
#include <git2/merge.h>
#include <git2/remote.h>

#include <QtCore/qobject.h>
#include <QtCore/QList>
#include <QtCore/QDir>
#include <QtCore/QProcess>

#include "qrepo.h"
#include "repositorymodel.h"

class gitCore : public QObject
{
    Q_OBJECT
public:
    gitCore(QObject* parent = 0);
    virtual ~gitCore();
    
    void addDirectory(QString dir);
    void removeDirectory(QString dir);
    
    bool is_git_dir(QString path);
    void updateAllRepo();

    QList<QRepo *> getRepoList();
    
    RepositoryModel* getModel();
    
signals:
  void newRepository(QRepo *repo);
  void newLog(QString);
  
private:
    QList<QRepo *> _repoList;
    
    RepositoryModel *_Model;
};

#endif // GITCORE_H
