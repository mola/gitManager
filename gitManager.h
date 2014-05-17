#ifndef gitManager_H
#define gitManager_H

#include <QtGui/QMainWindow>

class gitManager : public QMainWindow
{
Q_OBJECT
public:
    gitManager(QWidget *parent = 0);
    virtual ~gitManager();

private:
      Ui::MainWindow *ui;    
};

#endif // gitManager_H
