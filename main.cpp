#include <QtGui/QApplication>
#include "gitManager.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    gitManager mainWindow;
    mainWindow.show();
    return app.exec();
}
