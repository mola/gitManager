#include <QtGui/QApplication>
#include "gitManager.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    gitManager foo;
    foo.show();
    return app.exec();
}
