/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DOCKCONSOLE_H
#define DOCKCONSOLE_H

#include <QtWidgets/QDockWidget>
#include "src/gitcore.h"

namespace Ui
{
class dockConsole;
}

class dockConsole : public QDockWidget
{
    Q_OBJECT
public:
    dockConsole(QWidget *parent, gitCore *core);
    ~dockConsole();

	QAction* getMenu();

private slots:
		void newLog(QString );
		void actionMenu_toggled(bool checked);
		
private:
    Ui::dockConsole* ui;
	QAction *_actionMenu;
    
	gitCore *_core;	

};

#endif // DOCKCONSOLE_H
