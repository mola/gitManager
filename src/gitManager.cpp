#include "gitManager.h"

#include "ui_main.h"
#include <QDebug>

gitManager::gitManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    
    // Initlize dock projects
    _dockProjects = new dockProjects( this );
    addDockWidget(Qt::LeftDockWidgetArea , _dockProjects);
    ui->menuPanels->addAction (_dockProjects->getMenu()) ;
}

gitManager::~gitManager()
{}

void gitManager::on_actionQuit_toggled(bool checked)
{
  qDebug() << "Hello";
  QApplication::quit();
}

#include "gitManager.moc"
