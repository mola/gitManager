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
#include <QtGui/QAction>

namespace Ui {
class DockWidget;
}

class dockProjects : public QDockWidget
{
    Q_OBJECT

public:
    dockProjects(QWidget *parent = 0);
    ~dockProjects();
    
    QAction* getMenu();

private slots:
  void actionMenu_toggled(bool checked);

private:
      Ui::DockWidget *ui;
      QAction *_actionMenu;

};

#endif // DOCKPROJECTS_H
