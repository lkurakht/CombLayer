/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File: R3Common/R3FrontEnd.cxx
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
#include <iterator>
#include <memory>

#include "Exception.h"
#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "GTKreport.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "inputParam.h"
#include "Surface.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "Rules.h"
#include "Code.h"
#include "varList.h"
#include "FuncDataBase.h"
#include "HeadRule.h"
#include "Importance.h"
#include "Object.h"
#include "groupRange.h"
#include "objectGroups.h"
#include "Simulation.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "FixedGroup.h"
#include "FixedOffset.h"
#include "FixedRotate.h"
#include "FixedOffsetGroup.h"
#include "ContainedComp.h"
#include "ContainedGroup.h"
#include "BaseMap.h"
#include "CellMap.h"
#include "SurfMap.h"
#include "ExternalCut.h"
#include "FrontBackCut.h"
#include "CopiedComp.h"
#include "InnerZone.h"
#include "BlockZone.h"
#include "World.h"
#include "AttachSupport.h"
#include "generateSurf.h"
#include "ModelSupport.h"
#include "generalConstruct.h"

#include "VacuumPipe.h"
#include "insertObject.h"
#include "insertCylinder.h"
#include "insertPlate.h"
#include "SplitFlangePipe.h"
#include "Bellows.h"
#include "LCollimator.h"
#include "GateValveCube.h"
#include "CylGateValve.h"
#include "OffsetFlangePipe.h"
#include "VacuumBox.h"
#include "portItem.h"
#include "VirtualTube.h"
#include "PipeTube.h"
#include "PortTube.h"
#include "CrossPipe.h"
#include "SqrCollimator.h"
#include "SquareFMask.h"
#include "BeamMount.h"
#include "HeatDump.h"
#include "EPSeparator.h"
#include "R3ChokeChamber.h"
#include "R3ChokeInsert.h"
#include "EPCombine.h"
#include "PreDipole.h"
#include "MagnetM1.h"

#include "R3FrontEnd.h"

namespace xraySystem
{

// Note currently uncopied:
  
R3FrontEnd::R3FrontEnd(const std::string& Key) :
  attachSystem::CopiedComp(Key,Key),
  attachSystem::ContainedComp(),
  attachSystem::FixedOffset(newName,2),
  attachSystem::FrontBackCut(),
  attachSystem::CellMap(),
  attachSystem::SurfMap(),

  buildZone("R3FrontEnd"),

  transPipe(new constructSystem::VacuumPipe(newName+"TransPipe")),
  magBlockM1(new xraySystem::MagnetM1(newName+"M1Block")),
  epSeparator(new xraySystem::EPSeparator(newName+"EPSeparator")),
  chokeChamber(new xraySystem::R3ChokeChamber(newName+"ChokeChamber")),
  chokeInsert(new xraySystem::R3ChokeInsert(newName+"ChokeInsert")),
  dipolePipe(new constructSystem::VacuumPipe(newName+"DipolePipe")),
  eCutDisk(new insertSystem::insertCylinder(newName+"ECutDisk")),
  eCutMagDisk(new insertSystem::insertCylinder(newName+"ECutMagDisk")),
  bellowA(new constructSystem::Bellows(newName+"BellowA")),
  collA(new xraySystem::SquareFMask(newName+"CollA")),
  bellowB(new constructSystem::Bellows(newName+"BellowB")),
  collABPipe(new constructSystem::VacuumPipe(newName+"CollABPipe")),
  bellowC(new constructSystem::Bellows(newName+"BellowC")),
  collB(new xraySystem::SquareFMask(newName+"CollB")),
  collC(new xraySystem::SquareFMask(newName+"CollC")),
  collExitPipe(new constructSystem::VacuumPipe(newName+"CollExitPipe")),
  heatBox(new constructSystem::PipeTube(newName+"HeatBox")),
  heatDump(new xraySystem::HeatDump(newName+"HeatDump")),
  bellowD(new constructSystem::Bellows(newName+"BellowD")),
  gateTubeA(new xraySystem::CylGateValve(newName+"GateTubeA")),
  ionPB(new constructSystem::CrossPipe(newName+"IonPB")),
  pipeB(new constructSystem::VacuumPipe(newName+"PipeB")),

  bellowE(new constructSystem::Bellows(newName+"BellowE")),
  aperturePipe(new constructSystem::VacuumPipe(newName+"AperturePipe")),
  moveCollA(new xraySystem::LCollimator(newName+"MoveCollA")),  
  bellowF(new constructSystem::Bellows(newName+"BellowF")),
  ionPC(new constructSystem::CrossPipe(newName+"IonPC")),
  bellowG(new constructSystem::Bellows(newName+"BellowG")),
  aperturePipeB(new constructSystem::VacuumPipe(newName+"AperturePipeB")),
  moveCollB(new xraySystem::LCollimator(newName+"MoveCollB")),  
  bellowH(new constructSystem::Bellows(newName+"BellowH")),
  pipeC(new constructSystem::VacuumPipe(newName+"PipeC")),
  
  gateA(new constructSystem::GateValveCube(newName+"GateA")),
  bellowI(new constructSystem::Bellows(newName+"BellowI")),
  florTubeA(new constructSystem::PipeTube(newName+"FlorTubeA")),
  bellowJ(new constructSystem::Bellows(newName+"BellowJ")),
  gateTubeB(new constructSystem::PipeTube(newName+"GateTubeB")),
  offPipeA(new constructSystem::OffsetFlangePipe(newName+"OffPipeA")),
  shutterBox(new constructSystem::PipeTube(newName+"ShutterBox")),
  shutters({
      std::make_shared<xraySystem::BeamMount>(newName+"Shutter0"),
	std::make_shared<xraySystem::BeamMount>(newName+"Shutter1")
	}),
  offPipeB(new constructSystem::OffsetFlangePipe(newName+"OffPipeB")),
  bellowK(new constructSystem::Bellows(newName+"BellowK")) ,

  exitPipe(new constructSystem::VacuumPipe(newName+"ExitPipe")),

  collFM3Active(1)
   
  /*!
    Constructor
    \param Key :: Name of construction key
    \param Index :: Index number
  */
{
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  OR.addObject(transPipe);
  OR.addObject(magBlockM1);
  OR.addObject(epSeparator);
  OR.addObject(chokeChamber);
  OR.addObject(chokeInsert);
      
  OR.addObject(dipolePipe);
  OR.addObject(bellowA);
  OR.addObject(collA);
  OR.addObject(bellowB);
  OR.addObject(collABPipe);
  OR.addObject(bellowC);    
  OR.addObject(collB);
  OR.addObject(collC);
  OR.addObject(eCutDisk);
  OR.addObject(eCutMagDisk);
  OR.addObject(collExitPipe);
  OR.addObject(heatBox);
  OR.addObject(heatDump);    

  OR.addObject(pipeB);
  OR.addObject(bellowE);
  OR.addObject(aperturePipe);
  OR.addObject(moveCollA);
  OR.addObject(bellowF);
  OR.addObject(ionPC);
  OR.addObject(bellowG);
  OR.addObject(aperturePipeB);
  OR.addObject(moveCollB);
  OR.addObject(bellowH);
  OR.addObject(pipeC);

  OR.addObject(gateA);
  OR.addObject(bellowI);
  OR.addObject(florTubeA);
  OR.addObject(bellowJ);
  OR.addObject(gateTubeB);
  OR.addObject(offPipeA);
  OR.addObject(shutterBox);
  OR.addObject(shutters[0]);
  OR.addObject(shutters[1]);
  OR.addObject(offPipeB);
  OR.addObject(bellowK);

 
}
  
R3FrontEnd::~R3FrontEnd()
  /*!
    Destructor
   */
{}

void
R3FrontEnd::populate(const FuncDataBase& Control)
  /*!
    Populate the intial values [movement]
    \param Control :: DataBase
   */
{
  FixedOffset::populate(Control);
  outerRadius=Control.EvalVar<double>(keyName+"OuterRadius");
  frontOffset=Control.EvalDefVar<double>(keyName+"FrontOffset",0.0);
  return;
}


void
R3FrontEnd::createSurfaces()
  /*!
    Create surfaces
  */
{
  ELog::RegMethod RegA("R3FrontEnd","createSurfaces");

  if (outerRadius>Geometry::zeroTol)
    {
      ModelSupport::buildCylinder(SMap,buildIndex+7,Origin,Y,outerRadius);
      buildZone.setSurround(HeadRule(-SMap.realSurf(buildIndex+7)));
    }

  if (!frontActive())
    {
      ModelSupport::buildPlane(SMap,buildIndex+1,Origin+Y*frontOffset,Y);
      buildZone.initFront(HeadRule(SMap.realSurf(buildIndex+1)));
      setFront(-SMap.realSurf(buildIndex+1));
    }
  else
    buildZone.setFront(getFrontRule());
  
  return;
}

void
R3FrontEnd::insertFlanges(Simulation& System,
			  const constructSystem::PipeTube& PT)
  /*!
    Boilerplate function to insert the flanges from pipetubes
    that extend past the linkzone in to ther neighbouring regions.
    \param System :: Simulation to use
    \param PT :: PipeTube
   */
{
  ELog::RegMethod RegA("R3FrontEnd","insertFlanges");
  
  const size_t voidN=CellMap::getNItems("OuterVoid")-3;

  this->insertComponent(System,"OuterVoid",voidN,
			PT.getFullRule("FlangeA"));
  this->insertComponent(System,"OuterVoid",voidN,
			PT.getFullRule("FlangeB"));
  this->insertComponent(System,"OuterVoid",voidN+2,
			PT.getFullRule("FlangeA"));
  this->insertComponent(System,"OuterVoid",voidN+2,
			PT.getFullRule("FlangeB"));
  return;
}

void
R3FrontEnd::buildHeatTable(Simulation& System,
			       const attachSystem::FixedComp& preFC,
			       const long int preSideIndex)

  /*!
    Build the heatDump table
    \param System :: Simulation to use
    \param preFC :: initial Fixedcomp 
    \param preSideIndex :: link point on initial FC
  */
{
  ELog::RegMethod RegA("R3FrontEnd","buildHeatTable");


  int outerCell;

  heatBox->setPortRotation(3,Geometry::Vec3D(1,0,0));
  heatBox->createAll(System,preFC,preSideIndex);

  const constructSystem::portItem& PIA=heatBox->getPort(1);
  outerCell=buildZone.createUnit
    (System,PIA,PIA.getSideIndex("OuterPlate"));
  heatBox->insertAllInCell(System,outerCell);
  

  // cant use heatbox here because of port rotation
  
  heatDump->addInsertCell("Inner",heatBox->getCell("Void"));
  heatDump->addInsertCell("Outer",outerCell);
  heatDump->createAll(System,PIA,0,*heatBox,2);


  //  const constructSystem::portItem& PI=heatBox->getPort(1);  
  bellowD->createAll(System,PIA,PIA.getSideIndex("OuterPlate"));
  outerCell=buildZone.createUnit(System,*bellowD,2);
  bellowD->insertInCell(System,outerCell);


  gateTubeA->createAll(System,*bellowD,2);  
  outerCell=buildZone.createUnit(System,*gateTubeA,2);
  gateTubeA->insertInCell(System,outerCell);

  ionPB->createAll(System,*gateTubeA,"back");
  outerCell=buildZone.createUnit(System,*ionPB,"back");
  ionPB->insertInCell(System,outerCell);
  
  pipeB->createAll(System,*ionPB,2);
  outerCell=buildZone.createUnit(System,*pipeB,2);
  pipeB->insertAllInCell(System,outerCell);
  
  return;
  
}

void
R3FrontEnd::buildApertureTable(Simulation& System,
				   const attachSystem::FixedComp& preFC,
				   const long int preSideIndex)
  
  /*!
    Build the moveable aperature table
    \param System :: Simulation to use
    \param preFC :: Initial cell
    \param preSideIndex :: Initial side index
  */
{
  ELog::RegMethod RegA("R3FrontEnd","buildApertureTable");

  int outerCell;
  // NOTE order for master cell [Next 4 object
  aperturePipe->createAll(System,preFC,preSideIndex);  // pipeB
  moveCollA->addInsertCell(aperturePipe->getCell("Void"));
  moveCollA->createAll(System,*aperturePipe,0);
  
  // bellows AFTER movable aperture pipe
  bellowE->setFront(preFC,preSideIndex);
  bellowE->setBack(*aperturePipe,1);
  bellowE->createAll(System,preFC,preSideIndex);

  ionPC->createAll(System,preFC,preSideIndex);

  // bellows AFTER aperature ionpump and ion pump
  bellowF->setFront(*aperturePipe,2);
  bellowF->setBack(*ionPC,1);
  bellowF->createAll(System,preFC,preSideIndex);

  // now do insert:
  outerCell=buildZone.createUnit(System,*bellowE,2);
  bellowE->insertInCell(System,outerCell);
    
  outerCell=buildZone.createUnit(System,*aperturePipe,2);
  aperturePipe->insertAllInCell(System,outerCell);
  
  outerCell=buildZone.createUnit(System,*bellowF,2);
  bellowF->insertInCell(System,outerCell);

  outerCell=buildZone.createUnit(System,*ionPC,2);
  ionPC->insertInCell(System,outerCell);


  // Next 4 objects need to be build before insertion
  aperturePipeB->createAll(System,*ionPC,2);
  moveCollB->addInsertCell(aperturePipeB->getCell("Void"));
  moveCollB->createAll(System,*aperturePipeB,0);

  // bellows AFTER movable aperture pipe
  bellowG->setFront(*ionPC,2);
  bellowG->setBack(*aperturePipeB,1);
  bellowG->createAll(System,*ionPC,2);

  pipeC->createAll(System,*ionPC,2);

  // bellows AFTER movable aperture pipe
  bellowH->setFront(*aperturePipeB,2);
  bellowH->setBack(*pipeC,1);
  bellowH->createAll(System,*ionPC,2);


  // now do insert:
  outerCell=buildZone.createUnit(System,*bellowG,2);
  bellowG->insertInCell(System,outerCell);
    
  outerCell=buildZone.createUnit(System,*aperturePipeB,2);
  aperturePipeB->insertAllInCell(System,outerCell);
  
  outerCell=buildZone.createUnit(System,*bellowH,2);
  bellowH->insertInCell(System,outerCell);

  outerCell=buildZone.createUnit(System,*pipeC,2);
  pipeC->insertAllInCell(System,outerCell);

  
  return;
}

  
void
R3FrontEnd::buildShutterTable(Simulation& System,
				   const attachSystem::FixedComp& preFC,
				   const long int preSideIndex)
  /*!
    Build the shutter block table
    \param System :: Simulation to use
    \param preFC :: initial Fixedcomp 
    \param preSideIndex :: link point on initial FC
  */
{
  ELog::RegMethod RegA("R3FrontEnd","buildShutterTable");
  int outerCell;
  
  gateA->createAll(System,preFC,preSideIndex);
  outerCell=buildZone.createUnit(System,*gateA,2);
  gateA->insertInCell(System,outerCell);

  // bellows 
  bellowI->createAll(System,*gateA,2);
  outerCell=buildZone.createUnit(System,*bellowI,2);
  bellowI->insertInCell(System,outerCell);

  florTubeA->setPortRotation(3,Geometry::Vec3D(1,0,0));
  florTubeA->createAll(System,*bellowI,2);
  const constructSystem::portItem& FPI=florTubeA->getPort(1);
  outerCell=buildZone.createUnit(System,
				 FPI,FPI.getSideIndex("OuterPlate"));
  florTubeA->insertAllInCell(System,outerCell);

  // bellows 
  bellowJ->createAll(System,FPI,FPI.getSideIndex("OuterPlate"));
  outerCell=buildZone.createUnit(System,*bellowJ,2);
  bellowJ->insertInCell(System,outerCell);

  //  insertFlanges(System,*florTubeA);

  // FAKE insertcell:
  gateTubeB->setPortRotation(3,Geometry::Vec3D(1,0,0));
  gateTubeB->createAll(System,*bellowJ,2);  
  const constructSystem::portItem& GPI=gateTubeB->getPort(1);
  outerCell=buildZone.createUnit(System,
				 GPI,GPI.getSideIndex("OuterPlate"));
  gateTubeB->insertAllInCell(System,outerCell);

  
  offPipeA->createAll(System,GPI,GPI.getSideIndex("OuterPlate"));
  outerCell=buildZone.createUnit(System,*offPipeA,2);
  offPipeA->insertInCell(System,outerCell);

  //  insertFlanges(System,*gateTubeB);

  shutterBox->createAll(System,*offPipeA,
			offPipeA->getSideIndex("FlangeBCentre"));
  outerCell=buildZone.createUnit(System,*shutterBox,2);
  shutterBox->insertAllInCell(System,outerCell);
  
  cellIndex=shutterBox->splitVoidPorts
    (System,"SplitVoid",1001,shutterBox->getCell("Void"),{0,1});

  cellIndex=
    shutterBox->splitVoidPorts(System,"SplitOuter",2001,
			       outerCell,{0,1});
  shutterBox->addAllInsertCell(outerCell);

  for(size_t i=0;i<shutters.size();i++)
    {
      const constructSystem::portItem& PI=shutterBox->getPort(i);
      shutters[i]->addInsertCell("Support",PI.getCell("Void"));
      shutters[i]->addInsertCell("Support",shutterBox->getCell("SplitVoid",i));
      shutters[i]->addInsertCell("Block",shutterBox->getCell("SplitVoid",i));

      shutters[i]->createAll(System,*offPipeA,
			     offPipeA->getSideIndex("FlangeACentre"),
			     PI,PI.getSideIndex("InnerPlate"));
    }

  offPipeB->createAll(System,*shutterBox,2);
  outerCell=buildZone.createUnit(System,*offPipeB,2);
  offPipeB->insertInCell(System,outerCell);
    
  // bellows 
  bellowK->createAll(System,*offPipeB,2);
  outerCell=buildZone.createUnit(System,*bellowK,2);
  bellowK->insertInCell(System,outerCell);
  
  return;
}

void
R3FrontEnd::buildObjects(Simulation& System)
  /*!
    Build all the objects relative to the main FC
    point.
    \param System :: Simulation to use
  */
{
  ELog::RegMethod RegA("R3FrontEnd","buildObjects");

  int outerCell;

  buildZone.addInsertCells(this->getInsertCells());

  const attachSystem::FixedComp& undulatorFC=
    buildUndulator(System,*this,0);
					      
  //  constructSystem::constructUnit
  //    (System,buildZone,undulatorFC,"back",*transPipe);


  outerCell=buildZone.createUnit(System,undulatorFC,"back");


  magBlockM1->createAll(System,*this,0);
  transPipe->setCutSurf("front",undulatorFC,2);
  transPipe->setCutSurf("back",*magBlockM1,1);
  transPipe->createAll(System,undulatorFC,2);

  outerCell=buildZone.createUnit(System,*transPipe,2);
  transPipe->insertAllInCell(System,outerCell);

  outerCell=buildZone.createUnit(System,*magBlockM1,2);
  magBlockM1->insertAllInCell(System,outerCell);
  
  epSeparator->setCutSurf("front",*magBlockM1,2);
  epSeparator->setEPOriginPair(*magBlockM1,"Photon","Electron");
  epSeparator->createAll(System,*magBlockM1,2);
  outerCell=buildZone.createUnit(System,*epSeparator,2);
  epSeparator->insertInCell(System,outerCell);


  chokeChamber->setCutSurf("front",*epSeparator,2);
  chokeChamber->setEPOriginPair(*epSeparator,"Photon","Electron");
  chokeChamber->createAll(System,*epSeparator,2);
  outerCell=buildZone.createUnit(System,*chokeChamber,2);
  chokeChamber->insertAllInCell(System,outerCell);

  chokeInsert->setCutSurf("front",*chokeChamber,"innerSide");
  chokeInsert->addInsertCell(chokeChamber->getCell("MainVoid"));
  chokeInsert->addInsertCell(chokeChamber->getCell("SideVoid"));
  chokeInsert->createAll(System,*chokeChamber,"innerSide");

  eCutDisk->setNoInsert();
  eCutDisk->addInsertCell(chokeChamber->getCell("PhotonVoid"));
  eCutDisk->createAll(System,*chokeChamber,
		      chokeChamber->getSideIndex("-photon"));

  eCutMagDisk->setNoInsert();
  eCutMagDisk->addInsertCell(chokeChamber->getCell("ElectronVoid"));
  eCutMagDisk->createAll(System,*chokeChamber,
		      chokeChamber->getSideIndex("-electron"));

  // FM1 Built relateive to MASTER coordinate
  collA->createAll(System,*this,0);
  bellowA->createAll(System,*collA,1);  

  dipolePipe->setFront(*chokeChamber,chokeChamber->getSideIndex("photon"));
  dipolePipe->setBack(*bellowA,2);
  dipolePipe->createAll(System,*chokeChamber,
			chokeChamber->getSideIndex("photon"));
  outerCell=buildZone.createUnit(System,*dipolePipe,2);
  dipolePipe->insertAllInCell(System,outerCell);

  outerCell=buildZone.createUnit(System,*bellowA,1);
  bellowA->insertInCell(System,outerCell);

  outerCell=buildZone.createUnit(System,*collA,2);
  collA->insertInCell(System,outerCell);

  if (stopPoint=="Dipole")
    {
      lastComp=dipolePipe;
      return;
    }
      
  constructSystem::constructUnit
    (System,buildZone,*collA,"back",*bellowB);

  // FM2 Built relateive to MASTER coordinate

  collB->createAll(System,*this,0);    
  bellowC->createAll(System,*collB,1);

  collABPipe->setFront(*bellowB,2);
  collABPipe->setBack(*bellowC,2);
  collABPipe->createAll(System,*bellowB,"back");
  outerCell=buildZone.createUnit(System,*collABPipe,2);
  collABPipe->insertAllInCell(System,outerCell);

  outerCell=buildZone.createUnit(System,*bellowC,1);
  bellowC->insertInCell(System,outerCell);

  outerCell=buildZone.createUnit(System,*collB,2);
  collB->insertInCell(System,outerCell);

  std::shared_ptr<attachSystem::FixedComp> linkFC(collB);
  if (collFM3Active)
    {
      collC->createAll(System,*collB,2);
      outerCell=buildZone.createUnit(System,*collC,2);
      collC->insertInCell(System,outerCell);
      linkFC=collC;
    }

  collExitPipe->setFront(*linkFC,2);
  collExitPipe->createAll(System,*linkFC,2);
  outerCell=buildZone.createUnit(System,*collExitPipe,2);
  collExitPipe->insertAllInCell(System,outerCell);
  
  buildHeatTable(System,*collExitPipe,2);
  buildApertureTable(System,*pipeB,2);
  buildShutterTable(System,*pipeC,2);
  
  exitPipe->createAll(System,*bellowK,2);
  outerCell=buildZone.createUnit(System,*exitPipe,2);
  exitPipe->insertAllInCell(System,outerCell);

  setCell("MasterVoid",outerCell);  
  lastComp=exitPipe;
  return;
}
  
  
void 
R3FrontEnd::createAll(Simulation& System,
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
  ELog::RegMethod RControl("R3FrontEnd","build");

  populate(System.getDataBase());
  createUnitVector(FC,sideIndex);
  createSurfaces();
  buildObjects(System);
  createLinks();

  return;
}


}   // NAMESPACE xraySystem

