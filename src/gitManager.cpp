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
    _gitCore = new gitCore(ui->tabWidget, this);
    
    // Initlize dock projects
    _dockProjects = new dockProjects( this , _gitCore);
    addDockWidget(Qt::LeftDockWidgetArea , _dockProjects);
    ui->menuPanels->addAction (_dockProjects->getMenu()) ;
    
    _dockConsole = new dockConsole ( this , _gitCore);
	addDockWidget(Qt::BottomDockWidgetArea, _dockConsole);
	ui->menuPanels->addAction (_dockConsole->getMenu()) ;

    _dockStatus = new dockStatus ( this , _gitCore);
	addDockWidget(Qt::RightDockWidgetArea, _dockStatus);
	ui->menuPanels->addAction (_dockStatus->getMenu()) ;

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

void gitManager::on_actionWellcome_page_toggled(bool checked)
{

	if (ui->tabWidget->tabText(0) == "Welcome" )
	{
		ui->tabWidget->removeTab(0);
	} else {
		QTextBrowser *Welcometext = new QTextBrowser();
		QString weltext;
		
		weltext.append("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">");
		weltext.append("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">");
		weltext.append(" p, li { white-space: pre-wrap; }");
		weltext.append("</style></head><body style=\" font-family:'Cantarell'; font-size:10pt; font-weight:400; font-style:normal;\">");
		weltext.append("<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/gitmanager.png\" /></p>");
		weltext.append("<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:18pt; font-weight:600;\">Welcome to gitManager !</span></p>");
		weltext.append("<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif';\"><br /></p></body></html>");
// 		welltext.append();
// 		welltext.append();
		Welcometext->setText(weltext);
// 
//
// 
// 
// 
// );
		
	ui->tabWidget->addTab(Welcometext, "Welcome");
	}
}

void gitManager::on_actionAbout_triggered(bool checked)
{
	aboutDialog *aboutdialog = new aboutDialog(this);
	int res = aboutdialog->exec();
}

void gitManager::on_actionQuit_triggered(bool checked)
{
  QApplication::quit();
}
