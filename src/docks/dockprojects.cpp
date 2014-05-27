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

	_model = _core->getModel();
    _tablemodel = new QStandardItemModel(0,2, this);

    QStandardItem *col =  new QStandardItem(QString("Repository name") );
    _tablemodel->setHorizontalHeaderItem(0,col);

    _tablemodel->setHorizontalHeaderItem(1, new QStandardItem(QString("Repository path")));
    ui->treeView->setModel(_model);

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView,SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(contextualMenu(const QPoint &)));

    connect(_actionMenu, SIGNAL(toggled(bool)),SLOT(actionMenu_toggled(bool)) );
    connect(_core,SIGNAL(newRepository(QRepo*)), SLOT(newRepo(QRepo*)) );
}

dockProjects::~dockProjects()
{
}

QAction* dockProjects::getMenu()
{
  return _actionMenu;
}

void dockProjects::contextualMenu(const QPoint& point)
{
 QModelIndex index = ui->treeView->currentIndex();
 RepositoryNode *item = _model->nodeFromIndex(index);

 if(item->getNodeType() == RepositoryNode::RepoNodeType)
 {
  QMenu *menu = new QMenu(ui->treeView);
  QString fileName = _model->data(_model->index(index.row(), 0),0).toString();
  if (!item->is_repository_open())
  menu->addAction(QString("Open"), this, SLOT(test_slot()));
  else
  menu->addAction(QString("Close"), this, SLOT(test_slot()));
  menu->exec(QCursor::pos());
 }
}


void dockProjects::actionMenu_toggled(bool checked)
{
  if (checked)
    show();
  else
    hide();
}

void dockProjects::newRepo(QRepo *repo)
{
  qDebug() << repo->getName();
  QStandardItem *Repo = new QStandardItem(QString(repo->getName() ));
  QStandardItem *Path = new QStandardItem(QString(repo->getDirPath() ));
  _tablemodel->setItem(0,0,Repo);
  _tablemodel->setItem(0,1,Path);
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
