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

#ifndef QREPO_H
#define QREPO_H

#include <QtCore>
#include <QtCore/qobject.h>
#include <git2.h>

class QRepo : public QObject
{
    Q_OBJECT
public:
    QRepo(git_repository *, QString);
    virtual ~QRepo();
    
    void setGitRepository(git_repository *e);
    git_repository* getGitRepository();
    
    void setDirPath(QString path);
    QString getDirPath();
    
    QString getName();
    
private:
  git_repository *_gitrepo;
  QString	  _dirPath;
  QString	  _name;
};

#endif // QREPO_H
