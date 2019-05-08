/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   R3Common/MagnetM1.cxx
 *
 * Copyright (c) 2004-2019 by Stuart Ansell
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
#include "ExternalCut.h" 
#include "BaseMap.h"
#include "SurfMap.h"
#include "CellMap.h"
#include "InnerZone.h" 

#include "PreBendPipe.h"
#include "EPCombine.h"
#include "Quadrupole.h"
#include "MagnetM1.h"

namespace xraySystem
{

MagnetM1::MagnetM1(const std::string& Key) : 
  attachSystem::FixedOffset(Key,6),
  attachSystem::ContainedComp(),
  attachSystem::ExternalCut(),
  attachSystem::CellMap(),
  preDipole(new xraySystem::PreBendPipe(keyName+"PreBendPipe")),
  epCombine(new xraySystem::EPCombine(keyName+"EPCombine")),
  QFend(new xraySystem::Quadrupole(keyName+"QFend"))
  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param Key :: KeyName
  */
{
  nameSideIndex(2,"Photon");
  nameSideIndex(3,"Electron");

  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();
  
  OR.addObject(preDipole);
  OR.addObject(epCombine);
  OR.addObject(QFend);
}


MagnetM1::~MagnetM1() 
  /*!
    Destructor
  */
{}

void
MagnetM1::populate(const FuncDataBase& Control)
  /*!
    Populate all the variables
    \param Control :: DataBase for variables
  */
{
  ELog::RegMethod RegA("MagnetM1","populate");

  FixedOffset::populate(Control);

  blockYStep=Control.EvalVar<double>(keyName+"BlockYStep");
  length=Control.EvalVar<double>(keyName+"Length");

  outerVoid=Control.EvalVar<double>(keyName+"OuterVoid");
  ringVoid=Control.EvalVar<double>(keyName+"RingVoid");
  topVoid=Control.EvalVar<double>(keyName+"TopVoid");
  baseVoid=Control.EvalVar<double>(keyName+"BaseVoid");
  baseThick=Control.EvalVar<double>(keyName+"BaseThick");
  wallThick=Control.EvalVar<double>(keyName+"WallThick");
  voidMat=ModelSupport::EvalMat<int>(Control,keyName+"VoidMat");
  wallMat=ModelSupport::EvalMat<int>(Control,keyName+"WallMat");
  
  
  return;
}

void
MagnetM1::createUnitVector(const attachSystem::FixedComp& FC,
			    const long int sideIndex)
  /*!
    Create the unit vectors
    \param FC :: FixedComp to attach to
    \param sideIndex :: Link point
  */
{
  ELog::RegMethod RegA("MagnetM1","createUnitVector");
  
  FixedComp::createUnitVector(FC,sideIndex);
  applyOffset();
  return;
}

void
MagnetM1::createSurfaces()
  /*!
    Create All the surfaces
  */
{
  ELog::RegMethod RegA("MagnetM1","createSurface");

  // Do outer surfaces (vacuum ports)
  ModelSupport::buildPlane(SMap,buildIndex+1,Origin+Y*blockYStep,Y);
  ModelSupport::buildPlane(SMap,buildIndex+2,Origin+Y*(length+blockYStep),Y);


  ModelSupport::buildPlane(SMap,buildIndex+3,Origin-X*outerVoid,X);
  ModelSupport::buildPlane(SMap,buildIndex+4,Origin+X*ringVoid,X);
  ModelSupport::buildPlane(SMap,buildIndex+5,Origin-Z*baseVoid,Z);
  ModelSupport::buildPlane(SMap,buildIndex+6,Origin+Z*topVoid,Z);

  ModelSupport::buildPlane(SMap,buildIndex+13,Origin-X*(outerVoid+wallThick),X);
  ModelSupport::buildPlane(SMap,buildIndex+14,Origin+X*(ringVoid+wallThick),X);
  ModelSupport::buildPlane(SMap,buildIndex+15,Origin-Z*(baseVoid+baseThick),Z);
  ModelSupport::buildPlane(SMap,buildIndex+16,Origin+Z*(topVoid+baseThick),Z);


  return;
}

void
MagnetM1::createObjects(Simulation& System)
  /*!
    Builds all the objects
    \param System :: Simulation to create objects in
  */
{
  ELog::RegMethod RegA("MagnetM1","createObjects");

  std::string Out;

  Out=ModelSupport::getComposite
    (SMap,buildIndex,"1 -2 3 -4 5 -6 ");
  makeCell("Void",System,cellIndex++,voidMat,0.0,Out);

  Out=ModelSupport::getComposite
    (SMap,buildIndex," 1 -2 13 -14 15 -16 (-3:4:-5:6) ");
  makeCell("Outer",System,cellIndex++,wallMat,0.0,Out);

  Out=ModelSupport::getComposite
    (SMap,buildIndex," 1 -2 13 -14 15 -16 ");
  addOuterSurf(Out);

  return;
}

void 
MagnetM1::createLinks()
  /*!
    Create the linked units
   */
{
  ELog::RegMethod RegA("MagnetM1","createLinks");

  // link 0 / 1 from PreDipole / EPCombine
  setLinkSignedCopy(0,*preDipole,1);
  setLinkSignedCopy(2,*epCombine,epCombine->getSideIndex("Photon"));
  setLinkSignedCopy(3,*epCombine,epCombine->getSideIndex("Electron"));
  
  setConnect(4,Origin+Y*blockYStep,-Y);
  setLinkSurf(4,-SMap.realSurf(buildIndex+1));

  setConnect(5,Origin+Y*(length+blockYStep),Y);
  setLinkSurf(5,SMap.realSurf(buildIndex+2));

  return;
}

void
MagnetM1::createAll(Simulation& System,
		      const attachSystem::FixedComp& FC,
		      const long int sideIndex)
  /*!
    Generic function to create everything
    \param System :: Simulation item
    \param FC :: Fixed point track 
    \param sideIndex :: link point
  */
{
  ELog::RegMethod RegA("MagnetM1","createAll");

  int outerCell;
  
  populate(System.getDataBase());

  createUnitVector(FC,sideIndex);
  createSurfaces();
  createObjects(System);
  createLinks();
  preDipole->addInsertCell(this->getInsertCells());
  epCombine->addInsertCell(this->getInsertCells());
  insertObjects(System);

  if (isActive("front"))
    preDipole->copyCutSurf("front",*this,"front");
  
  preDipole->addInsertCell(getCells("Void"));
  preDipole->createAll(System,FC,sideIndex);

  epCombine->addInsertCell(getCells("Void"));
  epCombine->createAll(System,*preDipole,2);


  MonteCarlo::Object* masterCell=
    preDipole->getBuildZone().getMaster();
  QFend->createAll(System,*this,0);
  outerCell=preDipole->getBuildZone().
    createOuterVoidUnit(System,masterCell,*preDipole,2);
  
  return;
}
  
}  // NAMESPACE xraySystem