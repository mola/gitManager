#ifndef gitManager_H
#define gitManager_H

#include <QtWidgets/QMainWindow>
#include <QtCore/qglobal.h>

#include "docks/dockprojects.h"
#include "docks/dockconsole.h"
#include "docks/dockstatus.h"
#include "globalsettings.h"

namespace Ui {
class MainWindow;
}

class gitManager : public QMainWindow
{
    Q_OBJECT
public:
    gitManager(QWidget *parent = 0);
    virtual ~gitManager();

    void writeSettings();
    void readSettings();
    
private slots:
    void on_actionQuit_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    dockProjects *_dockProjects;
    dockConsole  *_dockConsole;
    dockStatus   *_dockStatus;
    
    gitCore *_gitCore;
};

#endif // gitManager_H
