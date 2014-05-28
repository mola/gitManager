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

#ifndef DOCKPROJECTS_H
#define DOCKPROJECTS_H

#include <QtWidgets/QDockWidget>
#include <QtGui>
#include <QtGui/QFileDialog>
#include <QtGui/QMenu>
#include "src/gitcore.h"
#include "src/repositorymodel.h"
#include "src/repositorynode.h"

namespace Ui {
class DockWidget;
}

class dockProjects : public QDockWidget
{
    Q_OBJECT

public:
    dockProjects(QWidget *parent, gitCore *core);
    ~dockProjects();
    
    QAction* getMenu();

private slots:
	void contextualMenu(const QPoint& point);
  void actionMenu_toggled(bool checked);
  
  void on_toolBtn_AddDirectory_clicked();
  void on_toolBtn_UpdateAll_clicked();

  void newRepo(QRepo *repo);
  void menuOpenProject();
  void menuCloseProject();

private:
      Ui::DockWidget *ui;
      gitCore *_core;
      QAction *_actionMenu;
      RepositoryModel *_model;
	  
      QStandardItemModel *_tablemodel;

};

#endif // DOCKPROJECTS_H
