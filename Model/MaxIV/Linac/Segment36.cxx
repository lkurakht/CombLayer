/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File: Linac/Segment36.cxx
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
#include "generalConstruct.h"
#include "Object.h"

#include "VacuumPipe.h"
#include "LQuadF.h"
#include "CorrectorMag.h"
#include "VirtualTube.h"
#include "PipeTube.h"
#include "CylGateValve.h"
#include "StriplineBPM.h"
#include "EArrivalMon.h"

#include "LObjectSupport.h"
#include "TDCsegment.h"
#include "Segment36.h"

namespace tdcSystem
{

// Note currently uncopied:


Segment36::Segment36(const std::string& Key) :
  TDCsegment(Key,2),
  gauge(new constructSystem::PipeTube(keyName+"Gauge")),
  pipeA(new constructSystem::VacuumPipe(keyName+"PipeA")),
  quadA(new tdcSystem::LQuadF(keyName+"QuadA")),
  cMagH(new tdcSystem::CorrectorMag(keyName+"CMagH")),
  cMagV(new tdcSystem::CorrectorMag(keyName+"CMagV")),
  quadB(new tdcSystem::LQuadF(keyName+"QuadB")),
  bpmA(new tdcSystem::StriplineBPM(keyName+"BPMA")),
  pipeB(new constructSystem::VacuumPipe(keyName+"PipeB")),
  beamArrivalMon(new tdcSystem::EArrivalMon(keyName+"BeamArrivalMon")),
  pipeC(new constructSystem::VacuumPipe(keyName+"PipeC")),
  pipeD(new constructSystem::VacuumPipe(keyName+"PipeD")),
  bpmB(new tdcSystem::StriplineBPM(keyName+"BPMB")),
  gate(new xraySystem::CylGateValve(keyName+"Gate")),
  pipeE(new constructSystem::VacuumPipe(keyName+"PipeE"))

  /*!
    Constructor
    \param Key :: Name of construction key
  */
{
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  OR.addObject(gauge);
  OR.addObject(pipeA);
  OR.addObject(quadA);
  OR.addObject(cMagH);
  OR.addObject(cMagV);
  OR.addObject(quadB);
  OR.addObject(bpmA);
  OR.addObject(pipeB);
  OR.addObject(beamArrivalMon);
  OR.addObject(pipeC);
  OR.addObject(pipeD);
  OR.addObject(bpmB);
  OR.addObject(gate);
  OR.addObject(pipeE);

  setFirstItems(gauge);
}

Segment36::~Segment36()
  /*!
    Destructor
   */
{}

void
Segment36::buildObjects(Simulation& System)
  /*!
    Build all the objects relative to the main FC
    point.
    \param System :: Simulation to use
  */
{
  ELog::RegMethod RegA("Segment36","buildObjects");

  int outerCell;

  MonteCarlo::Object* masterCell=buildZone->getMaster();
  if (!masterCell)
    masterCell=buildZone->constructMasterCell(System);

  gauge->addAllInsertCell(masterCell->getName());
  if (isActive("front"))
    gauge->copyCutSurf("front", *this, "front");
  gauge->createAll(System,*this,0);
  if (!masterCell)
    masterCell=buildZone->constructMasterCell(System,*gauge,-1);
  outerCell=buildZone->createOuterVoidUnit(System,masterCell,*gauge,2);
  gauge->insertAllInCell(System,outerCell);

  pipeA->createAll(System,*gauge, "back");
  pipeMagUnit(System,*buildZone,pipeA,"#front","outerPipe",quadA);
  pipeMagUnit(System,*buildZone,pipeA,"#front","outerPipe",cMagH);
  pipeMagUnit(System,*buildZone,pipeA,"#front","outerPipe",cMagV);
  pipeMagUnit(System,*buildZone,pipeA,"#front","outerPipe",quadB);
  pipeTerminate(System,*buildZone,pipeA);

  constructSystem::constructUnit
    (System,*buildZone,masterCell,*pipeA,"back",*bpmA);

  constructSystem::constructUnit
    (System,*buildZone,masterCell,*bpmA,"back",*pipeB);

  constructSystem::constructUnit
    (System,*buildZone,masterCell,*pipeB,"back",*beamArrivalMon);

  constructSystem::constructUnit
    (System,*buildZone,masterCell,*beamArrivalMon,"back",*pipeC);

  constructSystem::constructUnit
    (System,*buildZone,masterCell,*pipeC,"back",*pipeD);

  constructSystem::constructUnit
    (System,*buildZone,masterCell,*pipeD,"back",*bpmB);

  constructSystem::constructUnit
    (System,*buildZone,masterCell,*bpmB,"back",*gate);

  constructSystem::constructUnit
    (System,*buildZone,masterCell,*gate,"back",*pipeE);

  buildZone->removeLastMaster(System);
  return;
}

void
Segment36::createLinks()
  /*!
    Create a front/back link
   */
{
  setLinkSignedCopy(0,*gauge,1);
  setLinkSignedCopy(1,*pipeE,2);

  joinItems.push_back(FixedComp::getFullRule(2));
  return;
}

void
Segment36::createAll(Simulation& System,
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
  ELog::RegMethod RControl("Segment36","build");

  FixedRotate::populate(System.getDataBase());
  createUnitVector(FC,sideIndex);
  buildObjects(System);
  createLinks();

  return;
}


}   // NAMESPACE tdcSystem
