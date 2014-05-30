#include "gitManager.h"

#include "ui_main.h"
#include "about/aboutdialog.h"
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
    
    globalsettings::instance()->beginGroup("GitRepoPath");
    globalsettings::instance()->beginWriteArray("Repository");
    
    QStringList paths ( _gitCore->getModel()->getAllDirectores() );
    
    for (int i = 0; i < paths.count(); ++i) 
    {
     globalsettings::instance()->setArrayIndex(i);
     globalsettings::instance()->setValue("Path", paths[i]);
    }
    globalsettings::instance()->endArray();
    globalsettings::instance()->endGroup();
 
}

void gitManager::readSettings()
{
    globalsettings::instance()->beginGroup("MainWindow");
    restoreGeometry(globalsettings::instance()->value("geometry").toByteArray());
    restoreState(globalsettings::instance()->value("windowState").toByteArray());
    globalsettings::instance()->endGroup();

    globalsettings::instance()->beginGroup("GitRepoPath");
    int size = globalsettings::instance()->beginReadArray("Repository");
    
    QList<QRepo *> repolist = _gitCore->getRepoList();
    for (int i = 0; i < size; ++i) 
    {
      globalsettings::instance()->setArrayIndex(i);
      _gitCore->addDirectory( globalsettings::instance()->value("Path").toString() );
    }
    globalsettings::instance()->endArray();
    globalsettings::instance()->endGroup();
    
  
}

void gitManager::on_actionQuit_toggled(bool checked)
{
  qDebug() << "Hello";
  QApplication::quit();
}

void gitManager::on_actionAbout_triggered(bool checked)
{
	aboutDialog about;
	about.exec();
}



#include "gitManager.moc"
