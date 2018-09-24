/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   essBuild/RFQ.cxx
 *
 * Copyright (c) 2018 by Konstantin Batkov
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
 ****************************************************************************/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include <complex>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <memory>

#include "Exception.h"
#include "FileReport.h"
#include "GTKreport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "support.h"
#include "stringCombine.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Quaternion.h"
#include "Surface.h"
#include "surfIndex.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "surfEqual.h"
#include "Quadratic.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Line.h"
#include "Rules.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "inputParam.h"
#include "HeadRule.h"
#include "Object.h"
#include "Qhull.h"
#include "Simulation.h"
#include "ReadFunctions.h"
#include "ModelSupport.h"
#include "MaterialSupport.h"
#include "generateSurf.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "FixedOffset.h"
#include "ContainedComp.h"
#include "BaseMap.h"
#include "surfDBase.h"
#include "surfDIter.h"
#include "surfDivide.h"
#include "SurInter.h"
#include "mergeTemplate.h"

#include "RFQ.h"

namespace essSystem
{

RFQ::RFQ(const std::string& Key)  :
  attachSystem::ContainedComp(),
  attachSystem::FixedOffset(Key,6),
  surfIndex(ModelSupport::objectRegister::Instance().cell(Key)),
  cellIndex(surfIndex+1)
  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param Key :: Name for item in search
  */
{}

RFQ::RFQ(const RFQ& A) : 
  attachSystem::ContainedComp(A),
  attachSystem::FixedOffset(A),
  surfIndex(A.surfIndex),cellIndex(A.cellIndex),
  engActive(A.engActive),
  length(A.length),outerWidth(A.outerWidth),height(A.height),
  wallThick(A.wallThick),
  mainMat(A.mainMat),wallMat(A.wallMat)
  /*!
    Copy constructor
    \param A :: RFQ to copy
  */
{}

RFQ&
RFQ::operator=(const RFQ& A)
  /*!
    Assignment operator
    \param A :: RFQ to copy
    \return *this
  */
{
  if (this!=&A)
    {
      attachSystem::ContainedComp::operator=(A);
      attachSystem::FixedOffset::operator=(A);
      cellIndex=A.cellIndex;
      engActive=A.engActive;
      length=A.length;
      outerWidth=A.outerWidth;
      height=A.height;
      wallThick=A.wallThick;
      mainMat=A.mainMat;
      wallMat=A.wallMat;
    }
  return *this;
}

RFQ*
RFQ::clone() const
/*!
  Clone self
  \return new (this)
 */
{
    return new RFQ(*this);
}
  
RFQ::~RFQ() 
  /*!
    Destructor
  */
{}

void
RFQ::populate(const FuncDataBase& Control)
  /*!
    Populate all the variables
    \param Control :: Variable data base
  */
{
  ELog::RegMethod RegA("RFQ","populate");

  FixedOffset::populate(Control);
  engActive=Control.EvalPair<int>(keyName,"","EngineeringActive");

  length=Control.EvalVar<double>(keyName+"Length");
  outerWidth=Control.EvalVar<double>(keyName+"OuterWidth");
  height=Control.EvalVar<double>(keyName+"Height");
  wallThick=Control.EvalVar<double>(keyName+"WallThick");

  mainMat=ModelSupport::EvalMat<int>(Control,keyName+"MainMat");
  wallMat=ModelSupport::EvalMat<int>(Control,keyName+"WallMat");

  return;
}
  
void
RFQ::createUnitVector(const attachSystem::FixedComp& FC,
			      const long int sideIndex)
  /*!
    Create the unit vectors
    \param FC :: object for origin
    \param sideIndex :: link point for origin
  */
{
  ELog::RegMethod RegA("RFQ","createUnitVector");

  FixedComp::createUnitVector(FC,sideIndex);
  applyOffset();

  return;
}
  
void
RFQ::createSurfaces()
  /*!
    Create All the surfaces
  */
{
  ELog::RegMethod RegA("RFQ","createSurfaces");

  const double theta(45.0);

  ModelSupport::buildPlane(SMap,surfIndex+1,Origin,Y);
  ModelSupport::buildPlane(SMap,surfIndex+2,Origin+Y*(length),Y);

  ModelSupport::buildPlane(SMap,surfIndex+3,Origin-X*(outerWidth/2.0),X);
  ModelSupport::buildPlane(SMap,surfIndex+4,Origin+X*(outerWidth/2.0),X);

  ModelSupport::buildPlane(SMap,surfIndex+5,Origin-Z*(outerWidth/2.0),Z);
  ModelSupport::buildPlane(SMap,surfIndex+6,Origin+Z*(outerWidth/2.0),Z);

  // inner surfaces
  Geometry::Vec3D dirX(X);
  const double dx(outerWidth/2.0-wallThick*cos(theta*M_PI/180.0));
  Geometry::Quaternion::calcQRotDeg(-theta,Y).rotate(dirX);
  ModelSupport::buildPlane(SMap,surfIndex+13,Origin-X*(dx),dirX);
  ModelSupport::buildPlane(SMap,surfIndex+14,Origin+X*(dx),dirX);

  Geometry::Vec3D dirZ(Z);
  Geometry::Quaternion::calcQRotDeg(-theta,Y).rotate(dirZ);
  ModelSupport::buildPlane(SMap,surfIndex+15,Origin-Z*(dx),dirZ);
  ModelSupport::buildPlane(SMap,surfIndex+16,Origin+Z*(dx),dirZ);

  // outer surfaces
  ModelSupport::buildShiftedPlane(SMap,surfIndex+23,
                                  SMap.realPtr<Geometry::Plane>(surfIndex+13),
				  -wallThick);
  ModelSupport::buildShiftedPlane(SMap,surfIndex+24,
                                  SMap.realPtr<Geometry::Plane>(surfIndex+14),
                                  wallThick);
  ModelSupport::buildShiftedPlane(SMap,surfIndex+25,
                                  SMap.realPtr<Geometry::Plane>(surfIndex+15),
                                  -wallThick);
  ModelSupport::buildShiftedPlane(SMap,surfIndex+26,
                                  SMap.realPtr<Geometry::Plane>(surfIndex+16),
                                  wallThick);

  return;
}
  
void
RFQ::createObjects(Simulation& System)
  /*!
    Adds the all the components
    \param System :: Simulation to create objects in
  */
{
  ELog::RegMethod RegA("RFQ","createObjects");

  std::string Out;
  Out=ModelSupport::getComposite(SMap,surfIndex," 1 -2 13 -14 15 -16 ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,mainMat,0.0,Out));

  Out=ModelSupport::getComposite(SMap,surfIndex," 1 -2 23 -24 25 -26 3 -4 5 -6 (-13:14:-15:16) ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,wallMat,0.0,Out));

  Out=ModelSupport::getComposite(SMap,surfIndex," 1 -2 23 -24 25 -26 3 -4 5 -6 ");
  addOuterSurf(Out);

  return;
}

  
void
RFQ::createLinks()
  /*!
    Create all the linkes
  */
{
  ELog::RegMethod RegA("RFQ","createLinks");

  //  FixedComp::setConnect(0,Origin,-Y);
  //  FixedComp::setLinkSurf(0,-SMap.realSurf(surfIndex+1));
  
  return;
}
  
  

  
void
RFQ::createAll(Simulation& System,
		       const attachSystem::FixedComp& FC,
		       const long int sideIndex)
  /*!
    Generic function to create everything
    \param System :: Simulation item
    \param FC :: Central origin
    \param sideIndex :: link point for origin
  */
{
  ELog::RegMethod RegA("RFQ","createAll");

  populate(System.getDataBase());
  createUnitVector(FC,sideIndex);
  createSurfaces();
  createObjects(System);
  createLinks();
  insertObjects(System);              

  return;
}

}  // essSystem
