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

#include <QDebug>

dockProjects::dockProjects(QWidget *parent, gitCore *core) :
QDockWidget(parent), ui(new Ui::DockWidget), _core(core)
{
  ui->setupUi(this);
  _actionMenu =  new QAction("Projects", parent);
  _actionMenu->setCheckable( true );
  _actionMenu->setChecked( true );
  
  _tablemodel = new QStandardItemModel(0,1, this);
  _tablemodel->setHorizontalHeaderItem(0, new QStandardItem(QString("Repository path")));
  ui->tableView->setModel(_tablemodel);
  
  connect(_actionMenu, SIGNAL(toggled(bool)),SLOT(actionMenu_toggled(bool)) );
  connect(_core,SIGNAL(newRepository(QString )), SLOT(newRepo(QString)) ); 
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

void dockProjects::newRepo(QString repo)
{
  QStandardItem *firstRow = new QStandardItem(QString(repo));
  _tablemodel->setItem(0,0,firstRow);
}

void dockProjects::on_toolBtn_AddDirectory_clicked()
{
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             QDir::homePath(),
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
  
  _core->addDirectory(dir);
}


void dockProjects::on_toolBtn_UpdateAll_clicked()
{
  _core->updateAllRepo();
}

#include "docks/projects/dockprojects.moc"
