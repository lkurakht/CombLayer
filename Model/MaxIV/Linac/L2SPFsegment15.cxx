/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File: Linac/L2SPFsegment15.cxx
 *
 * Copyright (c) 2004-2020 by Konstantin Batkov
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
#include <iterator>
#include <memory>

#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "Vec3D.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "Code.h"
#include "varList.h"
#include "FuncDataBase.h"
#include "HeadRule.h"
#include "Object.h"
#include "groupRange.h"
#include "objectGroups.h"
#include "Simulation.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "FixedOffset.h"
#include "FixedRotate.h"
#include "ContainedComp.h"
#include "ContainedGroup.h"
#include "BaseMap.h"
#include "CellMap.h"
#include "SurfMap.h"
#include "ExternalCut.h"
#include "FrontBackCut.h"
#include "InnerZone.h"
#include "generateSurf.h"
#include "ModelSupport.h"
#include "MaterialSupport.h"
#include "generalConstruct.h"

#include "VacuumPipe.h"
#include "portItem.h"
#include "VirtualTube.h"
#include "PipeTube.h"


#include "TDCsegment.h"
#include "L2SPFsegment15.h"

namespace tdcSystem
{

// Note currently uncopied:

L2SPFsegment15::L2SPFsegment15(const std::string& Key) :
  TDCsegment(Key,2),
  pipeA(new constructSystem::VacuumPipe(keyName+"PipeA")),
  mirrorChamber(new constructSystem::PipeTube(keyName+"MirrorChamber")),
  ionPump(new constructSystem::PipeTube(keyName+"IonPump")),
  pipeB(new constructSystem::VacuumPipe(keyName+"PipeB"))
  /*!
    Constructor
    \param Key :: Name of construction key
  */
{
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  OR.addObject(pipeA);
  OR.addObject(mirrorChamber);
  OR.addObject(ionPump);
  OR.addObject(pipeB);
}

L2SPFsegment15::~L2SPFsegment15()
  /*!
    Destructor
   */
{}

void
L2SPFsegment15::buildObjects(Simulation& System)
  /*!
    Build all the objects relative to the main FC
    point.
    \param System :: Simulation to use
  */
{
  ELog::RegMethod RegA("L2SPFsegment15","buildObjects");

  int outerCell;
  MonteCarlo::Object* masterCell=buildZone->getMaster();

  pipeA->createAll(System,*this,0);
  if (!masterCell)
    masterCell=buildZone->constructMasterCell(System,*pipeA,-1);
  outerCell=buildZone->createOuterVoidUnit(System,masterCell,*pipeA,2);
  pipeA->insertInCell(System,outerCell);

  // Mirror chamber
  mirrorChamber->addAllInsertCell(masterCell->getName());
  mirrorChamber->setPortRotation(3, Geometry::Vec3D(1,0,0));
  mirrorChamber->createAll(System,*pipeA,2);
  for (size_t i=2; i<=3; ++i)
    for (size_t j=0; j<=1; ++j)
      mirrorChamber->intersectPorts(System,i,j);

  const constructSystem::portItem& mirrorChamberPort1=mirrorChamber->getPort(1);
  outerCell=buildZone->createOuterVoidUnit(System,
					  masterCell,
					  mirrorChamberPort1,
					  mirrorChamberPort1.getSideIndex("OuterPlate"));
  mirrorChamber->insertAllInCell(System,outerCell);

  // Ion pump
  ionPump->addAllInsertCell(masterCell->getName());
  ionPump->setPortRotation(3, Geometry::Vec3D(1,0,0));
  ionPump->createAll(System,mirrorChamberPort1,2);
  for (size_t i=2; i<=3; ++i)
    for (size_t j=0; j<=1; ++j)
      ionPump->intersectPorts(System,i,j);

  const constructSystem::portItem& ionPumpPort1=ionPump->getPort(1);
  outerCell=
    buildZone->createOuterVoidUnit(System,
				   masterCell,
				   ionPumpPort1,
				   ionPumpPort1.getSideIndex("OuterPlate"));
  ionPump->insertAllInCell(System,outerCell);

  constructSystem::constructUnit
    (System,*buildZone,masterCell,ionPumpPort1,"OuterPlate",*pipeB);

  buildZone->removeLastMaster(System);  

  return;
}

void
L2SPFsegment15::createLinks()
  /*!
    Create a front/back link
   */
{
  ELog::RegMethod RegA("L2SPFsegment15","createLinks");
  
  setLinkSignedCopy(0,*pipeA,1);
  setLinkSignedCopy(1,*pipeB,2);
  return;
}

void
L2SPFsegment15::createAll(Simulation& System,
		       const attachSystem::FixedComp& FC,
		       const long int sideIndex)
  /*!
    Carry out the full build
    \param System :: Simulation system
    \param FC :: Fixed component
    \param sideIndex :: link point
   */
{
  // For output stream
  ELog::RegMethod RControl("L2SPFsegment15","build");

  FixedRotate::populate(System.getDataBase());
  createUnitVector(FC,sideIndex);

  buildObjects(System);
  createLinks();
  return;
}


}   // NAMESPACE tdcSystem
