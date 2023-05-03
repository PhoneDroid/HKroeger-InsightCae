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

#include "stitchedshell.h"
#include "occinclude.h"
#include "base/boost_include.h"
#include <boost/spirit/include/qi.hpp>
#include "base/tools.h"

namespace qi = boost::spirit::qi;
namespace repo = boost::spirit::repository;
namespace phx   = boost::phoenix;

using namespace std;
using namespace boost;

namespace insight {
namespace cad {


defineType(StitchedShell);
//addToFactoryTable(Feature, StitchedShell);
addToStaticFunctionTable(Feature, StitchedShell, insertrule);
addToStaticFunctionTable(Feature, StitchedShell, ruleDocumentation);


size_t StitchedShell::calcHash() const
{
  ParameterListHash h;
  h+=this->type();
  h+=*faces_;
  h+=tol_->value();
  return h.getHash();
}


StitchedShell::StitchedShell(FeatureSetPtr faces, ScalarPtr tol)
:faces_(faces), tol_(tol)
{}

void StitchedShell::build()
{
  ExecTimer t("StitchedShell::build() ["+featureSymbolName()+"]");

  BRepBuilderAPI_Sewing sew(tol_->value());
  
//   TopoDS_Compound aRes;
//   BRep_Builder aBuilder;
//   aBuilder.MakeCompound(aRes);

  for (const FeatureID& fi: faces_->data())
  {
    sew.Add(faces_->model()->face(fi));
//     aBuilder.Add(aRes, bladeFace_[s]);
  }

  sew.Perform();
  sew.Dump();
  
  setShape(sew.SewedShape());
}

void StitchedShell::insertrule(parser::ISCADParser& ruleset)
{
  ruleset.modelstepFunctionRules.add
  (
    "StitchedShell",
    std::make_shared<parser::ISCADParser::ModelstepRule>(

    ( '(' >> ruleset.r_faceFeaturesExpression  >> ( (',' >> ruleset.r_scalarExpression) | qi::attr(scalarconst(1e-3)) ) >> ')' )
                  [ qi::_val = phx::bind(
                       &StitchedShell::create<FeatureSetPtr, ScalarPtr>,
                       qi::_1, qi::_2) ]
      
    )
  );
}

FeatureCmdInfoList StitchedShell::ruleDocumentation()
{
    return {
        FeatureCmdInfo
        (
            "StitchedShell",

            "( <faceSelection> [ <scalar:tol> | 0.001 ] )",

            "Create stitched shell from selected faces."
        )
    };
}

}
}
