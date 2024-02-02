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

#ifndef INSIGHT_CAD_PLACE_H
#define INSIGHT_CAD_PLACE_H

#include "derivedfeature.h"




namespace insight {
namespace cad {

    
    
    
class Place
    : public DerivedFeature
{
    FeaturePtr m_;
    VectorPtr p0_;
    VectorPtr ex_;
    VectorPtr ez_;
    VectorPtr refpt_;
    FeaturePtr other_;

    std::shared_ptr<gp_Trsf> trsf_;

    Place ( FeaturePtr m, const gp_Ax2& cs );
    Place ( FeaturePtr m, VectorPtr p0, VectorPtr ex, VectorPtr ez, VectorPtr refpt = VectorPtr() );
    Place ( FeaturePtr m, FeaturePtr other );

    size_t calcHash() const override;
    void build() override;

public:
    declareType ( "Place" );

    CREATE_FUNCTION(Place);

    static void insertrule ( parser::ISCADParser& ruleset );
    static FeatureCmdInfoList ruleDocumentation();

    bool isTransformationFeature() const override
    {
        return true;
    }
    gp_Trsf transformation() const override;
};




}
}

#endif // INSIGHT_CAD_PLACE_H
