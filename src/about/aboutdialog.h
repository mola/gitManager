#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtGui/qdialog.h>
#include <QtGui/QWidget>

namespace Ui
{
class aboutDialog;
}

class aboutDialog : public QDialog
{
    Q_OBJECT
public:
     aboutDialog(QWidget* parent = 0);
    ~aboutDialog();

private slots:
	void on_pushButton_close_clicked();
private:
    Ui::aboutDialog* ui;
};

#endif // ABOUTDIALOG_H
