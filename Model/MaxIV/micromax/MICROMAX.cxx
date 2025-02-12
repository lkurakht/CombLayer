/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File: micromax/MICROMAX.cxx
 *
 * Copyright (c) 2004-2021 by Stuart Ansell
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
#include "Vec3D.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "HeadRule.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "FixedOffset.h"
#include "FixedRotate.h"
#include "ContainedComp.h"
#include "ContainedGroup.h"
#include "BaseMap.h"
#include "CellMap.h"
#include "SurfMap.h"
#include "CopiedComp.h"
#include "ExternalCut.h"
#include "FrontBackCut.h"
#include "BlockZone.h"

#include "VacuumPipe.h"
#include "PipeShield.h"
#include "forkHoles.h"
#include "OpticsHutch.h"
#include "OpticsStepHutch.h"
#include "ExperimentalHutch.h"
#include "WallLead.h"
#include "R3Ring.h"
#include "R3FrontEnd.h"
#include "micromaxFrontEnd.h"
#include "micromaxOpticsLine.h"
#include "micromaxExptLine.h"
#include "micromaxExptLineB.h"
#include "PortChicane.h"

#include "R3Beamline.h"
#include "MICROMAX.h"

namespace xraySystem
{

MICROMAX::MICROMAX(const std::string& KN) :
  R3Beamline("Balder",KN),
  frontBeam(new micromaxFrontEnd(newName+"FrontBeam")),
  wallLead(new WallLead(newName+"WallLead")),
  joinPipe(new constructSystem::VacuumPipe(newName+"JoinPipe")),
  opticsHut(new OpticsStepHutch(newName+"OpticsHut")),
  opticsBeam(new micromaxOpticsLine(newName+"OpticsLine")),
  exptHut(new ExperimentalHutch(newName+"ExptHut")),
  joinPipeB(new constructSystem::VacuumPipe(newName+"JoinPipeB")),
  pShield(new xraySystem::PipeShield(newName+"PShield")),
  exptBeam(new micromaxExptLine(newName+"ExptLine")),
  exptHutB(new ExperimentalHutch(newName+"ExptHutB")),
  joinPipeC(new constructSystem::VacuumPipe(newName+"JoinPipeC")),
  exptBeamB(new micromaxExptLineB(newName+"ExptLineB"))
  /*!
    Constructor
    \param KN :: Keyname
  */
{
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  OR.addObject(frontBeam);
  OR.addObject(wallLead);
  OR.addObject(joinPipe);
  
  OR.addObject(opticsHut);
  OR.addObject(opticsBeam);
  OR.addObject(joinPipeB);
  OR.addObject(exptHut);
  OR.addObject(exptBeam);
  OR.addObject(exptHutB);
  OR.addObject(joinPipeC);
  OR.addObject(exptBeamB);
}

MICROMAX::~MICROMAX()
  /*!
    Destructor
   */
{}

void 
MICROMAX::build(Simulation& System,
	      const attachSystem::FixedComp& FCOrigin,
	      const long int sideIndex)
  /*!
    Carry out the full build
    \param System :: Simulation system
    \param FCOrigin :: Start origin
    \param sideIndex :: link point for origin
  */
{
  ELog::RegMethod RControl("MICROMAX","build");

  const size_t NS=r3Ring->getNInnerSurf();
  const size_t PIndex=static_cast<size_t>(std::abs(sideIndex)-1);
  const size_t SIndex=(PIndex+1) % NS;
  const size_t prevIndex=(NS+PIndex-1) % NS;

  const std::string exitLink="ExitCentre"+std::to_string(PIndex);

  frontBeam->setStopPoint(stopPoint);
  frontBeam->setCutSurf("REWall",-r3Ring->getSurf("BeamInner",PIndex));
  // believed active on Micromax
  //  frontBeam->deactivateFM3();
  frontBeam->addInsertCell(r3Ring->getCell("InnerVoid",SIndex));

  frontBeam->setBack(-r3Ring->getSurf("BeamInner",PIndex));
  frontBeam->createAll(System,FCOrigin,sideIndex);

  wallLead->addInsertCell(r3Ring->getCell("FrontWall",PIndex));
  wallLead->setFront(r3Ring->getSurf("BeamInner",PIndex));
  wallLead->setBack(-r3Ring->getSurf("BeamOuter",PIndex));    
  wallLead->createAll(System,FCOrigin,sideIndex);

  if (stopPoint=="frontEnd" || stopPoint=="Dipole"
      || stopPoint=="FM1" || stopPoint=="FM2" || stopPoint=="FM3")
    return;

  buildOpticsHutch(System,opticsHut,PIndex,exitLink);

  if (stopPoint=="opticsHut") return;

  joinPipe->addAllInsertCell(frontBeam->getCell("MasterVoid"));
  joinPipe->addInsertCell("Main",wallLead->getCell("Void"));
  joinPipe->createAll(System,*frontBeam,2);
  // new

  opticsBeam->setInnerMat(opticsHut->getCellMat(System,"Void"));
  opticsBeam->addInsertCell(opticsHut->getCell("Void"));
  opticsBeam->setCutSurf("front",*opticsHut,
			 opticsHut->getSideIndex("innerFront"));
  opticsBeam->setCutSurf("back",*opticsHut,
			 opticsHut->getSideIndex("innerBack"));
  opticsBeam->setCutSurf("floor",r3Ring->getSurf("Floor"));
  opticsBeam->setPreInsert(joinPipe);
  opticsBeam->createAll(System,*joinPipe,2);

  exptHut->setCutSurf("floor",r3Ring->getSurf("Floor"));
  exptHut->setCutSurf("frontWall",*opticsHut,"back");
  exptHut->addInsertCell(r3Ring->getCell("OuterSegment",PIndex));
  exptHut->addInsertCell(r3Ring->getCell("OuterSegment",prevIndex));
  exptHut->createAll(System,*opticsHut,"back");
  exptHut->splitChicane(System,1,2);

  joinPipeB->addAllInsertCell(opticsBeam->getCell("LastVoid"));  
  joinPipeB->addInsertCell("Main",opticsHut->getCell("ExitHole"));
  joinPipeB->setFront(*opticsBeam,2);
  joinPipeB->createAll(System,*opticsBeam,2);

  // pipe shield goes around joinPipeB:

  pShield->addAllInsertCell(opticsBeam->getCell("LastVoid"));
  pShield->setCutSurf("inner",*joinPipeB,"outerPipe");
  pShield->createAll(System,*opticsHut,"innerBack");

  if (stopPoint=="exptHut") return;

  exptBeam->setInsertCell(exptHut->getCells("Void"));
  exptBeam->setOuterMat(exptHut->getInnerMat());
  exptBeam->setCutSurf("front",*exptHut,
			 exptHut->getSideIndex("innerFront"));
  exptBeam->setCutSurf("back",*exptHut,
			 exptHut->getSideIndex("innerBack"));
  exptBeam->setCutSurf("floor",r3Ring->getSurf("Floor"));
  exptBeam->setPreInsert(joinPipeB);
  exptBeam->createAll(System,*joinPipeB,2);

  exptHutB->setCutSurf("floor",r3Ring->getSurf("Floor"));
  exptHutB->setCutSurf("frontWall",*exptHut,"back");
  exptHutB->addInsertCell(r3Ring->getCell("OuterSegment",PIndex));
  exptHutB->addInsertCell(r3Ring->getCell("OuterSegment",prevIndex));
  exptHutB->createAll(System,*exptHut,"back");
  // special for portItem transfer
  const PortChicane* PCPtr=exptHut->getPortItem(4);
  if (PCPtr)
    PCPtr->insertInCell
      ("Main",System,exptHutB->getCell("FrontVoid"));
  
  joinPipeC->addAllInsertCell(exptBeam->getCell("LastVoid"));  
  joinPipeC->addInsertCell("Main",exptHut->getCell("ExitHole"));
  joinPipeC->setFront(*exptBeam,2);
  joinPipeC->createAll(System,*exptBeam,2);

  exptBeamB->setInsertCell(exptHutB->getCells("Void"));
  exptBeamB->setOuterMat(exptHutB->getInnerMat());
  exptBeamB->setCutSurf("front",*exptHutB,
			 exptHutB->getSideIndex("innerFront"));
  exptBeamB->setCutSurf("back",*exptHutB,
			 exptHutB->getSideIndex("innerBack"));
  exptBeamB->setCutSurf("floor",r3Ring->getSurf("Floor"));
  exptBeamB->setPreInsert(joinPipeC);
  exptBeamB->createAll(System,*joinPipeC,2);


  return;
}


}   // NAMESPACE xraySystem

