#include "aboutdialog.h"
#include <src/ui_aboutdialog.h>
#include "ui_aboutdialog.h"


aboutDialog::aboutDialog(QWidget* parent): QDialog(parent)
{
	ui = new Ui::aboutDialog;
	ui->setupUi(this);
}

aboutDialog::~aboutDialog()
{
    delete ui;
}

void aboutDialog::on_pushButton_close_clicked()
{
	close();
}

#include "src/about/projects/aboutdialog.moc"