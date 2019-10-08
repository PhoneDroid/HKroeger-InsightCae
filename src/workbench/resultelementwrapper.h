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


#ifndef RESULTELEMENTWRAPPER_H
#define RESULTELEMENTWRAPPER_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QGroupBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#ifndef Q_MOC_RUN
#include "base/factory.h"
#include "base/resultset.h"
#endif

class ResultElementWrapper 
: public QObject, //QWidget,
  public QTreeWidgetItem
{
  Q_OBJECT
  
public:
//   typedef boost::tuple<QTreeWidgetItem *, const QString&, insight::ResultElement&> ConstrP;
  
  declareFactoryTable(ResultElementWrapper, LIST(QTreeWidgetItem* tree, const QString& name, insight::ResultElement& res), LIST(tree, name, res));  

protected:
  QString name_;
  insight::ResultElement& p_;
  QTimer *resizeTimer_;
  
public:
  declareType("ResultElementWrapper");
  ResultElementWrapper(QTreeWidgetItem* tree, const QString& name, insight::ResultElement& res);
  virtual ~ResultElementWrapper();


public Q_SLOTS:
  void onSectionResized(int column, int oldsize, int newsize);
  virtual void onUpdateGeometry() =0;
};

class CommentWrapper
: public ResultElementWrapper
{
  Q_OBJECT
protected:
  QLabel *le_;
public:
  declareType(insight::Comment::typeName_());
  CommentWrapper(QTreeWidgetItem* tree, const QString& name, insight::ResultElement& res);
  inline insight::Comment& res() { return dynamic_cast<insight::Comment&>(p_); }

  void onUpdateGeometry() override;
};

class ScalarResultWrapper
: public ResultElementWrapper
{
  Q_OBJECT
protected:
  QLabel *le_;
public:
  declareType(insight::ScalarResult::typeName_());
  ScalarResultWrapper(QTreeWidgetItem* tree, const QString& name, insight::ResultElement& res);
  inline insight::ScalarResult& res() { return dynamic_cast<insight::ScalarResult&>(p_); }
  void onUpdateGeometry() override;
};

class ResultSectionWrapper
: public ResultElementWrapper
{
  Q_OBJECT
protected:
  QGroupBox *frame_;
public:
  declareType(insight::ResultSection::typeName_());
  
  ResultSectionWrapper(QTreeWidgetItem* tree, const QString& name, insight::ResultElement& res);
  inline insight::ResultSection& res() { return dynamic_cast<insight::ResultSection&>(p_); }
  void onUpdateGeometry() override;
};

class ResultSetWrapper
: public ResultElementWrapper
{
  Q_OBJECT
protected:
  QGroupBox *frame_;
public:
  declareType(insight::ResultSet::typeName_());
  
  ResultSetWrapper(QTreeWidgetItem* tree, const QString& name, insight::ResultElement& res);
  inline insight::ResultSet& res() { return dynamic_cast<insight::ResultSet&>(p_); }
  void onUpdateGeometry() override;
};

class ImageWrapper
: public ResultElementWrapper
{
  Q_OBJECT
protected:
  QLabel *le_;
public:
  declareType(insight::Image::typeName_());
  ImageWrapper(QTreeWidgetItem* tree, const QString& name, insight::ResultElement& res);
  inline insight::Image& res() { return dynamic_cast<insight::Image&>(p_); }
  void onUpdateGeometry() override;
};

class ChartWrapper
: public ResultElementWrapper
{
  Q_OBJECT
protected:
  boost::filesystem::path chart_file_;
  QLabel *le_;
public:
  declareType(insight::Chart::typeName_());
  ChartWrapper(QTreeWidgetItem* tree, const QString& name, insight::ResultElement& res);
  ~ChartWrapper();
  inline insight::Chart& res() { return dynamic_cast<insight::Chart&>(p_); }
  void onUpdateGeometry() override;
};

class TabularResultWrapper
: public ResultElementWrapper
{
  Q_OBJECT
protected:
  QTableWidget *le_;
public:
  declareType(insight::TabularResult::typeName_());
  TabularResultWrapper(QTreeWidgetItem* tree, const QString& name, insight::ResultElement& res);
  inline insight::TabularResult& res() { return dynamic_cast<insight::TabularResult&>(p_); }
  void onUpdateGeometry() override;
};

class AttributeTableResultWrapper
: public ResultElementWrapper
{
  Q_OBJECT
protected:
  QTableWidget *le_;
public:
  declareType(insight::AttributeTableResult::typeName_());
  AttributeTableResultWrapper(QTreeWidgetItem* tree, const QString& name, insight::ResultElement& res);
  inline insight::AttributeTableResult& res() { return dynamic_cast<insight::AttributeTableResult&>(p_); }
  void onUpdateGeometry() override;
};

void addWrapperToWidget(insight::ResultElementCollection& rset, QTreeWidgetItem *node, QWidget *superform=NULL);

#endif // RESULTELEMENTWRAPPER_H
