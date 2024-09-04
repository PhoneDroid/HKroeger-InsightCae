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

#ifndef INSIGHT_CAD_COMPOUND_H
#define INSIGHT_CAD_COMPOUND_H

#include "cadfeature.h"

namespace insight 
{
namespace cad 
{


    
    
typedef std::vector<FeaturePtr> CompoundFeatureList;
typedef std::map<std::string, FeaturePtr>  CompoundFeatureMap;
typedef std::vector<boost::fusion::vector<std::string, FeaturePtr> > CompoundFeatureMapData;




class Compound
    : public Feature
{
protected:
    CompoundFeatureMap components_;

    Compound();
    Compound ( const CompoundFeatureList& m1 );
    Compound ( const CompoundFeatureMap& m1 );

    size_t calcHash() const override;
    void build() override;

public:
    declareType ( "Compound" );

    CREATE_FUNCTION(Compound);

    static std::shared_ptr<Compound> create_named( const CompoundFeatureMapData& m1 );

    static void insertrule ( parser::ISCADParser& ruleset );
    static FeatureCmdInfoList ruleDocumentation();

    double mass ( double density_ovr=-1., double aw_ovr=-1. ) const override;
    arma::mat modelCoG ( double density_ovr=-1. ) const override;
    arma::mat modelInertia ( double density_ovr=-1. ) const override;

    Compound& operator=(const Compound& o);
};




}
}

#endif // INSIGHT_CAD_COMPOUND_H
