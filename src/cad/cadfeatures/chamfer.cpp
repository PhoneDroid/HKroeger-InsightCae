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

#include "chamfer.h"
#include "base/boost_include.h"
#include "base/translations.h"

#include <boost/spirit/include/qi.hpp>


namespace qi = boost::spirit::qi;
namespace repo = boost::spirit::repository;
namespace phx   = boost::phoenix;

using namespace std;
using namespace boost;

namespace insight {
namespace cad {


    
    
defineType(Chamfer);
//addToFactoryTable(Feature, Chamfer);
addToStaticFunctionTable(Feature, Chamfer, insertrule);
addToStaticFunctionTable(Feature, Chamfer, ruleDocumentation);

size_t Chamfer::calcHash() const
{
  ParameterListHash h;
  h+=this->type();
  h+=*edges_;
  h+=l_->value();
  h+=angle_->value();
  return h.getHash();
}




Chamfer::Chamfer(FeatureSetPtr edges, ScalarPtr l, ScalarPtr angle)
: DerivedFeature(edges->model()), edges_(edges), l_(l), angle_(angle)
{}






void Chamfer::build()
{
    double l1=l_->value();
    double l2=::tan(angle_->value())*l1;

    const Feature& m1=*(edges_->model());

    m1.unsetLeaf();
    BRepFilletAPI_MakeChamfer fb(m1);

    for (FeatureID f: edges_->data())
    {
        TopoDS_Edge e = m1.edge(f);
        TopTools_IndexedDataMapOfShapeListOfShape mapEdgeFace;
        TopExp::MapShapesAndAncestors(m1, TopAbs_EDGE, TopAbs_FACE, mapEdgeFace);
        int i = mapEdgeFace.FindIndex(e);
        fb.Add(l1, l2, e, TopoDS::Face(mapEdgeFace(i).First()) );
    }

    fb.Build();
    setShape(fb.Shape());
}




void Chamfer::insertrule(parser::ISCADParser& ruleset)
{
    ruleset.modelstepFunctionRules.add
    (
        "Chamfer",
            std::make_shared<parser::ISCADParser::ModelstepRule>(
            ( '(' 
                >> ruleset.r_edgeFeaturesExpression >> ',' 
                >> ruleset.r_scalarExpression 
                >> ( (',' >> ruleset.r_scalarExpression) | qi::attr(scalarconst(45.*M_PI/180.)) ) 
                >> ')' )
            [ qi::_val = phx::bind(
                         &Chamfer::create<FeatureSetPtr, ScalarPtr, ScalarPtr>,
                         qi::_1, qi::_2, qi::_3) ]
        )
    );
}



FeatureCmdInfoList Chamfer::ruleDocumentation()
{
    return {
        FeatureCmdInfo
        (
            "Chamfer",
         
            "( <edgeSelection:edges>, <scalar:l> )",

            _("Creates chamfers at selected edges of a solid. All edges in the selection set edges are chamfered with width l.")
        )
    };
}


}
}
