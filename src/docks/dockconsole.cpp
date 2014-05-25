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

#include "dockconsole.h"
#include "ui_dockconsole.h"

dockConsole::dockConsole(QWidget *parent, gitCore *core) :
QDockWidget(parent), ui(new Ui::dockConsole), _core(core)
{
    ui->setupUi(this);
  _actionMenu =  new QAction("Console", parent);
  _actionMenu->setCheckable( true );
  _actionMenu->setChecked( true );	
}

dockConsole::~dockConsole()
{
    delete ui;
}

QAction* dockConsole::getMenu()
{
	return _actionMenu;
}
