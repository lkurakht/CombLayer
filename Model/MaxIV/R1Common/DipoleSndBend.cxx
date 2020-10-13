/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   R1Common/DipoleSndBend.cxx
 *
 * Copyright (c) 2004-2020 by Stuart Ansell
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
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Quaternion.h"
#include "Surface.h"
#include "surfIndex.h"
#include "surfDIter.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "surfEqual.h"
#include "Quadratic.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Line.h"
#include "Rules.h"
#include "SurInter.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "HeadRule.h"
#include "Object.h"
#include "SimProcess.h"
#include "groupRange.h"
#include "objectGroups.h"
#include "Simulation.h"
#include "ModelSupport.h"
#include "MaterialSupport.h"
#include "generateSurf.h"
#include "LinkUnit.h"  
#include "FixedComp.h"
#include "FixedOffset.h"
#include "FixedRotate.h"
#include "ContainedComp.h"
#include "ContainedGroup.h"
#include "ExternalCut.h" 
#include "BaseMap.h"
#include "SurfMap.h"
#include "CellMap.h"

#include "DipoleSndBend.h"

namespace xraySystem
{

DipoleSndBend::DipoleSndBend(const std::string& Key) : 
  attachSystem::FixedRotate(Key,6),
  attachSystem::ContainedComp(),
  attachSystem::ExternalCut(),
  attachSystem::CellMap(),
  attachSystem::SurfMap()
  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param Key :: KeyName
  */
{}


DipoleSndBend::~DipoleSndBend() 
  /*!
    Destructor
  */
{}

void
DipoleSndBend::populate(const FuncDataBase& Control)
  /*!
    Populate all the variables
    \param Control :: DataBase for variables
  */
{
  ELog::RegMethod RegA("DipoleSndBend","populate");

  FixedRotate::populate(Control);

  arcAngle=Control.EvalVar<double>(keyName+"ArcAngle");
  curveRadius=Control.EvalVar<double>(keyName+"CurveRadius");
  innerWidth=Control.EvalVar<double>(keyName+"InnerWidth");
  flatWidth=Control.EvalVar<double>(keyName+"FlatWidth");
  wideWidth=Control.EvalVar<double>(keyName+"WideWidth");
  outerFlat=Control.EvalVar<double>(keyName+"OuterFlat");
  height=Control.EvalVar<double>(keyName+"Height");
  outerHeight=Control.EvalVar<double>(keyName+"OuterHeight");
  wallThick=Control.EvalVar<double>(keyName+"WallThick");
  
  voidMat=ModelSupport::EvalMat<int>(Control,keyName+"VoidMat");
  wallMat=ModelSupport::EvalMat<int>(Control,keyName+"WallMat");
  outerMat=ModelSupport::EvalMat<int>(Control,keyName+"OuterMat");

  return;
}

void
DipoleSndBend::createSurfaces()
  /*!
    Create All the surfaces
  */
{
  ELog::RegMethod RegA("DipoleSndBend","createSurface");

  const double coneAngle(M_PI/4.0);
  
  if (!ExternalCut::isActive("front"))
    {
      ModelSupport::buildPlane(SMap,buildIndex+1,Origin,Y);
      setCutSurf("front",SMap.realSurf(buildIndex+1));
    }

  const Geometry::Vec3D CylOrg(Origin+X*curveRadius);
  const Geometry::Quaternion QYA
    (Geometry::Quaternion::calcQRotDeg(arcAngle,-Z));
  const Geometry::Vec3D PY=QYA.makeRotate(Y);
  const Geometry::Vec3D endPoint
    (CylOrg
     -X*(curveRadius*cos(M_PI*arcAngle/180.0))
     +Y*(curveRadius*sin(M_PI*arcAngle/180.0)));

  ELog::EM<<" Y  == "<<Y<<" :: "<<PY<<ELog::endDiag;
  ELog::EM<<" ORG  == "<<CylOrg<<" :: "<<endPoint<<ELog::endDiag;
  
  ModelSupport::buildPlane(SMap,buildIndex+2,endPoint,PY);  
	       
  // tip
  ModelSupport::buildCylinder(SMap,buildIndex+7,CylOrg,Z,curveRadius);
  // first cone end
  ModelSupport::buildCylinder
    (SMap,buildIndex+17,CylOrg,Z,curveRadius+innerWidth);
  // second cone start
  ModelSupport::buildCylinder
    (SMap,buildIndex+27,CylOrg,Z,curveRadius+flatWidth);
  // second cone end
  ModelSupport::buildCylinder
    (SMap,buildIndex+37,CylOrg,Z,curveRadius+wideWidth);

  // First cut:
  const Geometry::Vec3D COrg =
    Origin-X*
    +Z*(height/2.0+curveRadius*cos(coneAngle));
  

  
  ModelSupport::buildPlane(SMap,buildIndex+4,Origin-X*outerFlat,X);
    
  ModelSupport::buildPlane(SMap,buildIndex+5,Origin-Z*(height/2.0),Z);
  ModelSupport::buildPlane(SMap,buildIndex+6,Origin+Z*(height/2.0),Z);

  ModelSupport::buildPlane(SMap,buildIndex+15,Origin-Z*(outerHeight/2.0),Z);
  ModelSupport::buildPlane(SMap,buildIndex+16,Origin+Z*(outerHeight/2.0),Z);

  return;
}

void
DipoleSndBend::createObjects(Simulation& System)
  /*!
    Builds all the objects
    \param System :: Simulation to create objects in
  */
{
  ELog::RegMethod RegA("DipoleSndBend","createObjects");

  std::string Out;
  const std::string fStr=getRuleStr("front");


  Out=ModelSupport::getComposite(SMap,buildIndex,"-17 7 4 5 -6 -2 ");
  makeCell("Void",System,cellIndex++,voidMat,0.0,Out+fStr);
  
  addOuterUnionSurf(Out+fStr);


  return;
}

void 
DipoleSndBend::createLinks()
  /*!
    Create the linked units
   */
{
  ELog::RegMethod RegA("DipoleSndBend","createLinks");
  ExternalCut::createLink("front",*this,0,Origin,Y);
  ExternalCut::createLink("back",*this,1,Origin,Y);
  return;
}


void
DipoleSndBend::createAll(Simulation& System,
			 const attachSystem::FixedComp& FC,
			 const long int sideIndex)
  /*!
    Generic function to create everything
    \param System :: Simulation item
    \param FC :: Fixed point track 
    \param sideIndex :: link point
  */
{
  ELog::RegMethod RegA("DipoleSndBend","createAll");
  
  populate(System.getDataBase());
  createUnitVector(FC,sideIndex);
  createSurfaces();
  createObjects(System);
  createLinks();
  insertObjects(System);   
  
  return;
}
  
}  // NAMESPACE epbSystem
