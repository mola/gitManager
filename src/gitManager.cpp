#include "gitManager.h"

#include "ui_main.h"
#include <QDebug>

gitManager::gitManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    globalsettings::create(this);
    
    // Initilize Core
    _gitCore = new gitCore(this);
    
    // Initlize dock projects
    _dockProjects = new dockProjects( this , _gitCore);
    addDockWidget(Qt::LeftDockWidgetArea , _dockProjects);
    ui->menuPanels->addAction (_dockProjects->getMenu()) ;
    
    readSettings();
}

gitManager::~gitManager()
{
  writeSettings();
}

void gitManager::writeSettings()
{
    globalsettings::instance()->beginGroup("MainWindow");
    globalsettings::instance()->setValue("geometry", saveGeometry());
    globalsettings::instance()->setValue("windowState", saveState());
    globalsettings::instance()->endGroup();	
}

void gitManager::readSettings()
{
    globalsettings::instance()->beginGroup("MainWindow");
    restoreGeometry(globalsettings::instance()->value("geometry").toByteArray());
    restoreState(globalsettings::instance()->value("windowState").toByteArray());
    globalsettings::instance()->endGroup();
}

void gitManager::on_actionQuit_toggled(bool checked)
{
  qDebug() << "Hello";
  QApplication::quit();
}

#include "gitManager.moc"
