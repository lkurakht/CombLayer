/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   essBuild/Berm.cxx
 *
 * Copyright (c) 2004-2021 by Konstantin Batkov
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
#include "Importance.h"
#include "Object.h"
#include "groupRange.h"
#include "objectGroups.h"
#include "Simulation.h"
#include "ModelSupport.h"
#include "MaterialSupport.h"
#include "generateSurf.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "FixedOffset.h"
#include "ContainedComp.h"
#include "BaseMap.h"
#include "CellMap.h"
#include "ExternalCut.h"

#include "Berm.h"

namespace essSystem
{

Berm::Berm(const std::string& Key)  :
  attachSystem::ContainedComp(),
  attachSystem::FixedOffset(Key,6),
  attachSystem::CellMap(),
  attachSystem::ExternalCut()
  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param Key :: Name for item in search
  */
{}

Berm::Berm(const Berm& A) :
  attachSystem::ContainedComp(A),
  attachSystem::FixedOffset(A),
  attachSystem::CellMap(A),
  attachSystem::ExternalCut(A),
  lengthBack(A.lengthBack),
  lengthFront(A.lengthFront),
  widthLeft(A.widthLeft),
  widthRight(A.widthRight),
  height(A.height),
  depth(A.depth),
  roofAngle(A.roofAngle),
  mat(A.mat)
  /*!
    Copy constructor
    \param A :: Berm to copy
  */
{}

Berm&
Berm::operator=(const Berm& A)
  /*!
    Assignment operator
    \param A :: Berm to copy
    \return *this
  */
{
  if (this!=&A)
    {
      attachSystem::ContainedComp::operator=(A);
      attachSystem::FixedOffset::operator=(A);
      attachSystem::CellMap::operator=(A);
      lengthBack=A.lengthBack;
      lengthFront=A.lengthFront;
      widthLeft=A.widthLeft;
      widthRight=A.widthRight;
      height=A.height;
      depth=A.depth;
      roofAngle=A.roofAngle;
      mat=A.mat;
    }
  return *this;
}

Berm*
Berm::clone() const
/*!
  Clone self
  \return new (this)
 */
{
    return new Berm(*this);
}

Berm::~Berm()
  /*!
    Destructor
  */
{}

void
Berm::populate(const FuncDataBase& Control)
  /*!
    Populate all the variables
    \param Control :: Variable data base
  */
{
  ELog::RegMethod RegA("Berm","populate");

  FixedOffset::populate(Control);

  lengthBack=Control.EvalVar<double>(keyName+"LengthBack");
  lengthFront=Control.EvalVar<double>(keyName+"LengthFront");
  widthLeft=Control.EvalVar<double>(keyName+"WidthLeft");
  widthRight=Control.EvalVar<double>(keyName+"WidthRight");
  height=Control.EvalVar<double>(keyName+"Height");
  depth=Control.EvalVar<double>(keyName+"Depth");
  roofAngle=Control.EvalVar<double>(keyName+"RoofAngle");

  mat=ModelSupport::EvalMat<int>(Control,keyName+"Mat");

  return;
}


void
Berm::createSurfaces()
  /*!
    Create All the surfaces
  */
{
  ELog::RegMethod RegA("Berm","createSurfaces");

  ModelSupport::buildPlane(SMap,buildIndex+1,Origin-Y*(lengthBack),Y);
  ModelSupport::buildPlane(SMap,buildIndex+2,Origin+Y*(lengthFront),Y);

  ModelSupport::buildPlane(SMap,buildIndex+3,Origin-X*(widthLeft),X);
  ModelSupport::buildPlane(SMap,buildIndex+4,Origin+X*(widthRight),X);

  ModelSupport::buildPlane(SMap,buildIndex+5,Origin-Z*(depth),Z);

  Geometry::Vec3D topNorm(Z);
  Geometry::Quaternion::calcQRotDeg(-roofAngle,Y).rotate(topNorm);
  ModelSupport::buildPlane(SMap,buildIndex+6,
			   Origin+Z*(height)-X*widthLeft,
			   topNorm);

  Geometry::Vec3D holeBerm(Z);
  Geometry::Quaternion::calcQRotDeg(90.0-10.898,Y).rotate(holeBerm);
  ModelSupport::buildPlane(SMap,buildIndex+7,
			   Origin+X*1095.08, 
			   holeBerm);

  ModelSupport::buildPlane(SMap,buildIndex+8,Origin+Z*440.0,Z);

  return;
}

void
Berm::createObjects(Simulation& System)
  /*!
    Adds the all the components
    \param System :: Simulation to create objects in
  */
{
  ELog::RegMethod RegA("Berm","createObjects");

  const HeadRule sideHR=getRule("ExternalSide");
  const HeadRule floorHR=getRule("Floor");
  
  HeadRule HR;
  HR=ModelSupport::getHeadRule
    (SMap,buildIndex," 1 -2 3 5 -6 (-7:-8)")*sideHR;
  //    KG.getLinkString(kgSide)
  makeCell("RightSoil",System,cellIndex++,mat,0.0,HR);

  addOuterSurf(HR);

  HR=ModelSupport::getHeadRule
    (SMap,buildIndex,"1 -2 -4 5")*sideHR*floorHR;
  //    KG.getLinkString(-kgSide) + KG.getLinkString(kgFloor);
  makeCell("LeftSoil",System,cellIndex++,mat,0.0,HR);


  addOuterUnionSurf(HR);

  return;
}


void
Berm::createLinks()
  /*!
    Create all the linkes
  */
{
  ELog::RegMethod RegA("Berm","createLinks");

  FixedComp::setConnect(0,Origin-Y*(lengthBack),-Y);
  FixedComp::setLinkSurf(0,-SMap.realSurf(buildIndex+1));

  FixedComp::setConnect(1,Origin+Y*(lengthFront),Y);
  FixedComp::setLinkSurf(1,SMap.realSurf(buildIndex+2));

  FixedComp::setConnect(2,Origin-X*(widthLeft),-X);
  FixedComp::setLinkSurf(2,-SMap.realSurf(buildIndex+3));

  FixedComp::setConnect(3,Origin+X*(widthRight),X);
  FixedComp::setLinkSurf(3,SMap.realSurf(buildIndex+4));

  FixedComp::setConnect(4,Origin-Z*(depth),-Z);
  FixedComp::setLinkSurf(4,-SMap.realSurf(buildIndex+5));

  FixedComp::setConnect(5,Origin+Z*(height)+X*widthRight,Z);
  FixedComp::setLinkSurf(5,SMap.realSurf(buildIndex+6));

  return;
}




void
Berm::createAll(Simulation& System,
		const attachSystem::FixedComp& FC,

		const long int sideIndex)
/*!
    Generic function to create everything
    \param System :: Simulation item
    \param FC :: Central origin
    \param sideIndex :: link point for origin
  */
{
  ELog::RegMethod RegA("Berm","createAll");

  populate(System.getDataBase());
  createUnitVector(FC,sideIndex);
  createSurfaces();
  createObjects(System);
  createLinks();
  insertObjects(System);

  return;
}

}  // essSystem
