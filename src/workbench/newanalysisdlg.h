/*
 * This file is part of Insight CAE, a workbench for Computer-Aided Engineering 
 * Copyright (C) 2014  Hannes Kroeger <hannes@kroegeronline.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef NEWANALYSISDLG_H
#define NEWANALYSISDLG_H

#include <QDialog>
// #include <QTreeWidgetItem>

class WorkbenchMainWindow;

namespace Ui
{
class newAnalysisDlg;
}

class newAnalysisDlg
: public QDialog
{
    Q_OBJECT

private:
    Ui::newAnalysisDlg* ui;

public:
    newAnalysisDlg(WorkbenchMainWindow* parent);
    virtual ~newAnalysisDlg();
    
    void fillAnalysisList();
};

#endif // NEWANALYSISDLG_H
