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
#include <QtGui/QFileDialog>
#include <QtGui/QAction>
#include <QtGui/QStandardItemModel>
#include "src/gitcore.h"

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
  void actionMenu_toggled(bool checked);
  
  void on_toolBtn_AddDirectory_clicked();
  void on_toolBtn_UpdateAll_clicked();

  void newRepo(QString repo);

private:
      Ui::DockWidget *ui;
      gitCore *_core;
      QAction *_actionMenu;
      
      QStandardItemModel *_tablemodel;

};

#endif // DOCKPROJECTS_H
