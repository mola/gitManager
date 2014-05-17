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

#include "dockprojects.h"

#include "ui_dockprojects.h"

dockProjects::dockProjects(QWidget *parent) :
QDockWidget(parent), ui(new Ui::DockWidget)
{
  ui->setupUi(this);
  _actionMenu =  new QAction("Projects", parent);
  _actionMenu->setCheckable( true );
  _actionMenu->setChecked( true );
  connect(_actionMenu, SIGNAL(toggled(bool)),SLOT(actionMenu_toggled(bool)) );
  
}

dockProjects::~dockProjects()
{
}

QAction* dockProjects::getMenu()
{
  return _actionMenu;
}

void dockProjects::actionMenu_toggled(bool checked)
{
  if (checked)
    show();
  else
    hide();
}


#include "docks/projects/dockprojects.moc"
