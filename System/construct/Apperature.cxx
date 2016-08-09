/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   construct/Apperature.cxx
 *
 * Copyright (c) 2004-2016 by Stuart Ansell
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
#include <numeric>
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
#include "HeadRule.h"
#include "neutron.h"
#include "Object.h"
#include "Qhull.h"
#include "Simulation.h"
#include "ModelSupport.h"
#include "MaterialSupport.h"
#include "generateSurf.h"
#include "surfExpand.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "FixedOffset.h"
#include "ContainedComp.h"
#include "Apperature.h"

namespace constructSystem
{

Apperature::Apperature(const std::string& Key)  :
  attachSystem::ContainedComp(),
  attachSystem::FixedOffset(Key,6),
  appIndex(ModelSupport::objectRegister::Instance().cell(Key)),
  cellIndex(appIndex+1)

  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param Key :: Name for item in search
  */
{}


Apperature::~Apperature() 
  /*!
    Destructor
  */
{}

void
Apperature::populate(const FuncDataBase& Control)
  /*!
    Populate all the variables
    \param Control :: DataBase of variables
  */
{
  ELog::RegMethod RegA("VacuumBox","populate");
  
  FixedOffset::populate(Control);

  // Void + Fe special:
  innerWidth=Control.EvalVar<double>(keyName+"InnerWidth");
  innerHeight=Control.EvalVar<double>(keyName+"InnerHeight");
  width=Control.EvalVar<double>(keyName+"Width");
  height=Control.EvalVar<double>(keyName+"Height");
  depth=Control.EvalVar<double>(keyName+"Depth");

  voidMat=ModelSupport::EvalDefMat<int>(Control,keyName+"VoidMat",0);
  defMat=ModelSupport::EvalMat<int>(Control,keyName+"DefMat");

  return;
}
  
void
Apperature::createUnitVector(const attachSystem::FixedComp& FC,
                             const long int sideIndex)
  /*!
    Create the unit vectors
    - Y Down the beamline
    \param FC :: Linked object
    \param sideIndex :: Link point
  */
{
  ELog::RegMethod RegA("Apperature","createUnitVector");
  
  attachSystem::FixedComp::createUnitVector(FC,sideIndex);
  applyOffset();
  return;
}
  
void
Apperature::createSurfaces()
  /*!
    Create all the surfaces
  */
{
  ELog::RegMethod RegA("Apperature","createSurfaces");
  

  ModelSupport::buildPlane(SMap,appIndex+1,Origin-Y*depth/2.0,Y);
  ModelSupport::buildPlane(SMap,appIndex+2,Origin+Y*depth/2.0,Y);

  ModelSupport::buildPlane(SMap,appIndex+3,Origin-X*width/2.0,X);
  ModelSupport::buildPlane(SMap,appIndex+4,Origin+X*width/2.0,X);
  
  ModelSupport::buildPlane(SMap,appIndex+5,Origin-Z*height/2.0,Z);
  ModelSupport::buildPlane(SMap,appIndex+6,Origin+Z*height/2.0,Z);
  
  ModelSupport::buildPlane(SMap,appIndex+13,Origin-X*innerWidth/2.0,X);
  ModelSupport::buildPlane(SMap,appIndex+14,Origin+X*innerWidth/2.0,X);
  
  ModelSupport::buildPlane(SMap,appIndex+15,Origin-Z*innerHeight/2.0,Z);
  ModelSupport::buildPlane(SMap,appIndex+16,Origin+Z*innerHeight/2.0,Z);

  
  return;
}

void 
Apperature::createObjects(Simulation& System)
  /*!
    Create a window object
    \param System :: Simulation
  */
{
  ELog::RegMethod RegA("Apperature","createObjects");
  std::string Out;

  Out=ModelSupport::getComposite(SMap,appIndex,"1 -2 13 -14 15 -16 ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,voidMat,0.0,Out));

  Out=ModelSupport::getComposite(SMap,appIndex,
                                 "1 -2 3 -4 5 -6 (-13:14:-15:16) ");
  System.addCell(MonteCarlo::Qhull(cellIndex++,defMat,0.0,Out));


  Out=ModelSupport::getComposite(SMap,appIndex,"1 -2 3 -4 5 -6 ");
  addOuterSurf(Out);
  return;
}

void
Apperature::createLinks()
  /*!
    Determines the link point on the outgoing plane.
    It must follow the beamline, but exit at the plane
  */
{
  ELog::RegMethod RegA("VacuumBox","createLinks");


  FixedComp::setConnect(0,Origin-Y*(depth/2.0),-Y);
  FixedComp::setConnect(1,Origin+Y*(depth/2.0),Y);
  FixedComp::setConnect(2,Origin-X*(width/2.0),-X);
  FixedComp::setConnect(3,Origin+X*(width/2.0),X);
  FixedComp::setConnect(4,Origin-Z*(height/2.0),-Z);
  FixedComp::setConnect(5,Origin+Z*(height/2.0),Z);  

  FixedComp::setLinkSurf(0,-SMap.realSurf(appIndex+1));
  FixedComp::setLinkSurf(1,SMap.realSurf(appIndex+2));
  FixedComp::setLinkSurf(2,-SMap.realSurf(appIndex+3));
  FixedComp::setLinkSurf(3,SMap.realSurf(appIndex+4));
  FixedComp::setLinkSurf(4,-SMap.realSurf(appIndex+5));
  FixedComp::setLinkSurf(5,SMap.realSurf(appIndex+6));
  
  return;
}


void
Apperature::createAll(Simulation& System,
                      const attachSystem::FixedComp& FC,
                      const long int sideIndex)
  /*!
    Global creation of the hutch
    \param System :: Simulation to add vessel to
    \param FC :: Fixed Component to place object within
    \param sideIndex :: sideIndex
  */
{
  ELog::RegMethod RegA("Apperature","createAll");

  populate(System.getDataBase());
  createUnitVector(FC,sideIndex);
  createSurfaces();
  createObjects(System);
  createLinks();
      
  insertObjects(System);       

  return;
}

  
}  // NAMESPACE ts1System

