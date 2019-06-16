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

#ifndef INSIGHT_CAD_SCALARFEATUREPROP_H
#define INSIGHT_CAD_SCALARFEATUREPROP_H

#include "cadparameter.h"
#include "cadtypes.h"

namespace insight {
namespace cad {

class ScalarFeatureProp 
: public Scalar
{
  FeaturePtr model_;
  std::string name_;
  
public:
  ScalarFeatureProp(FeaturePtr model, const std::string& name);
  virtual double value() const;
};

class FeatureVolume 
: public Scalar
{
  FeaturePtr model_;
  
public:
  FeatureVolume(FeaturePtr model);
  virtual double value() const;
};

class CumulativeEdgeLength 
: public Scalar
{
  FeaturePtr model_;
  
public:
  CumulativeEdgeLength(FeaturePtr model);
  virtual double value() const;
};

class CircleDiameter
: public Scalar
{
  ConstFeatureSetPtr pfs_;

public:
  CircleDiameter(ConstFeatureSetPtr pfs);
  virtual double value() const;
};

}
}

#endif // INSIGHT_CAD_SCALARFEATUREPROP_H
