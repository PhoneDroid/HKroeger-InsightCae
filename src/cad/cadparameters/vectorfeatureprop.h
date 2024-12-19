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
 */

#ifndef INSIGHT_CAD_VECTORFEATUREPROP_H
#define INSIGHT_CAD_VECTORFEATUREPROP_H

#include "cadtypes.h"
#include "cadparameter.h"

namespace insight 
{
namespace cad 
{

    
    
    
class PointFeatureProp 
: public insight::cad::Vector
{
  FeaturePtr model_;
  std::string name_;
  
public:
  PointFeatureProp(FeaturePtr model, const std::string& name);
  virtual arma::mat value() const;
};




class VectorFeatureProp 
: public insight::cad::Vector
{
  FeaturePtr model_;
  std::string name_;
  
public:
  VectorFeatureProp(FeaturePtr model, const std::string& name);
  virtual arma::mat value() const;
};




class SinglePointCoords 
: public insight::cad::Vector
{
  ConstFeatureSetPtr pfs_;
  
public:
  SinglePointCoords(ConstFeatureSetPtr pfs);
  virtual arma::mat value() const;
};




class CircleEdgeCenterCoords 
: public insight::cad::Vector
{
  ConstFeatureSetPtr pfs_;
  
public:
  CircleEdgeCenterCoords(ConstFeatureSetPtr pfs);
  void compute(arma::mat& pc, double& D, arma::mat& ex) const;
  arma::mat value() const override;
};




class DatumPointCoord
: public insight::cad::Vector
{
  ConstDatumPtr pfs_;
  
public:
  DatumPointCoord(ConstDatumPtr pfs);
  virtual arma::mat value() const;
};




class DatumDir
: public insight::cad::Vector
{
  ConstDatumPtr pfs_;
  
public:
  DatumDir(ConstDatumPtr pfs);
  virtual arma::mat value() const;
};


class XsecCurveCurve
: public insight::cad::Vector
{
  ConstFeaturePtr c1_, c2_;

public:
  XsecCurveCurve(ConstFeaturePtr c1, ConstFeaturePtr c2);
  virtual arma::mat value() const;
};



class DatumPlaneNormal
: public insight::cad::Vector
{
  ConstDatumPtr pfs_;
  
public:
  DatumPlaneNormal(ConstDatumPtr pfs);
  virtual arma::mat value() const;
};



class DatumPlaneX
    : public insight::cad::Vector
{
    ConstDatumPtr pfs_;

public:
    DatumPlaneX(ConstDatumPtr pfs);
    virtual arma::mat value() const;
};



class DatumPlaneY
    : public insight::cad::Vector
{
    ConstDatumPtr pfs_;

public:
    DatumPlaneY(ConstDatumPtr pfs);
    virtual arma::mat value() const;
};



class BBMin
: public insight::cad::Vector
{
  FeaturePtr model_;
  
public:
  BBMin(FeaturePtr model);
  virtual arma::mat value() const;
};




class BBMax
: public insight::cad::Vector
{
  FeaturePtr model_;
  
public:
  BBMax(FeaturePtr model);
  virtual arma::mat value() const;
};




class COG
: public insight::cad::Vector
{
  FeaturePtr model_;
  
public:
  COG(FeaturePtr model);
  virtual arma::mat value() const;
};




class SurfaceCOG
: public insight::cad::Vector
{
  FeaturePtr model_;
  
public:
  SurfaceCOG(FeaturePtr model);
  virtual arma::mat value() const;
};




class SurfaceInertiaAxis
: public insight::cad::Vector
{
  FeaturePtr model_;
  int axis_;
  
public:
  SurfaceInertiaAxis(FeaturePtr model, int axis);
  virtual arma::mat value() const;
};



class PointInFeatureCS
    : public insight::cad::Vector
{
    FeaturePtr model_;
    VectorPtr locP_;

public:
    PointInFeatureCS(FeaturePtr model, VectorPtr locP);
    virtual arma::mat value() const;
};



}
}

#endif // INSIGHT_CAD_VECTORFEATUREPROP_H
