/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   t1Build/makeT1Real.cxx
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

#include "Exception.h"
#include "FileReport.h" 
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "Vec3D.h"
#include "inputParam.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "HeadRule.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "FixedUnit.h"
#include "FixedOffset.h"
#include "FixedRotate.h"
#include "LayerComp.h"
#include "ContainedComp.h"
#include "BaseMap.h"
#include "CellMap.h"
#include "ExternalCut.h"
#include "ContainedGroup.h"
#include "t1Reflector.h"
#include "H2Moderator.h"
#include "CH4Moderator.h"
#include "MerlinModerator.h"
#include "FlightLine.h"
#include "pipeUnit.h"
#include "PipeLine.h"
#include "WaterPipe.h"
#include "H2Pipe.h"
#include "CH4Pipe.h"
#include "Window.h"
#include "t1CylVessel.h"
#include "t1BulkShield.h"
#include "TargetBase.h"
#include "TS2target.h"
#include "TS2ModifyTarget.h"
#include "t1PlateTarget.h"
#include "Cannelloni.h"
#include "InnerTarget.h"
#include "SideCoolTarget.h"
#include "OpenBlockTarget.h"
#include "MonoPlug.h"
#include "World.h"

#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "HeadRule.h"
#include "Importance.h"
#include "Object.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "groupRange.h"
#include "objectGroups.h"
#include "Simulation.h"
#include "makeT1Real.h"

namespace ts1System
{

makeT1Real::makeT1Real() :
  RefObj(new t1Reflector("t1Reflect")),
  Lh2ModObj(new H2Moderator("H2Mod")),
  CH4ModObj(new CH4Moderator("CH4Mod")),
  MerlinMod(new MerlinModerator("MerlinMod")),
  WaterModObj(new MerlinModerator("WaterMod")),
  WaterPipeObj(new WaterPipe("WaterPipe")),
  MPipeObj(new WaterPipe("MerlinPipe")),
  H2PipeObj(new H2Pipe("H2Pipe")),
  CH4PipeObj(new CH4Pipe("CH4Pipe")),  
  
  VoidObj(new shutterSystem::t1CylVessel("t1CylVessel")),
  BulkObj(new shutterSystem::t1BulkShield("t1Bulk")),

  MonoTopObj(new shutterSystem::MonoPlug("MonoTop")),
  MonoBaseObj(new shutterSystem::MonoPlug("MonoBase")),

  H2FL(new moderatorSystem::FlightLine("H2Flight")),
  CH4NorthFL(new moderatorSystem::FlightLine("CH4FlightN")),
  CH4SouthFL(new moderatorSystem::FlightLine("CH4FlightS")),
  MerlinFL(new moderatorSystem::FlightLine("MerlinFlight")),
  WaterNorthFL(new moderatorSystem::FlightLine("WatNorthFlight")),
  WaterSouthFL(new moderatorSystem::FlightLine("WatSouthFlight"))

  /*!
    Constructor
  */
{
  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  OR.addObject(RefObj);
  OR.addObject(Lh2ModObj);
  OR.addObject(CH4ModObj);
  OR.addObject(MerlinMod);
  OR.addObject(WaterModObj);

  OR.addObject(VoidObj);
  OR.addObject(BulkObj);
  OR.addObject(MonoTopObj);
  OR.addObject(MonoBaseObj);

  OR.addObject(H2FL);
  OR.addObject(CH4NorthFL);
  OR.addObject(CH4SouthFL);
  OR.addObject(MerlinFL);
  OR.addObject(WaterNorthFL);
  OR.addObject(WaterSouthFL);

  OR.addObject(WaterPipeObj);
  OR.addObject(MPipeObj);
  OR.addObject(H2PipeObj);
  OR.addObject(CH4PipeObj);    
}

makeT1Real::makeT1Real(const makeT1Real& A) : 
  TarObj((A.TarObj) ? 
	 std::shared_ptr<TMRSystem::TargetBase>
	 (A.TarObj->clone()) : A.TarObj),  
  RefObj(new t1Reflector(*A.RefObj)),
  Lh2ModObj(new H2Moderator(*A.Lh2ModObj)),
  CH4ModObj(new CH4Moderator(*A.CH4ModObj)),
  MerlinMod(new MerlinModerator(*A.MerlinMod)),
  WaterModObj(new MerlinModerator(*A.WaterModObj)),
  MPipeObj(new WaterPipe(*A.MPipeObj)),
  H2PipeObj(new H2Pipe(*A.H2PipeObj)),
  CH4PipeObj(new CH4Pipe(*A.CH4PipeObj)),    
  H2FL(new moderatorSystem::FlightLine(*A.H2FL)),
  CH4NorthFL(new moderatorSystem::FlightLine(*A.CH4NorthFL)),
  CH4SouthFL(new moderatorSystem::FlightLine(*A.CH4SouthFL)),
  MerlinFL(new moderatorSystem::FlightLine(*A.MerlinFL)),
  WaterNorthFL(new moderatorSystem::FlightLine(*A.WaterNorthFL)),
  WaterSouthFL(new moderatorSystem::FlightLine(*A.WaterSouthFL))
  /*!
    Copy constructor
    \param A :: makeT1Real to copy
  */
{}

makeT1Real&
makeT1Real::operator=(const makeT1Real& A)
  /*!
    Assignment operator
    \param A :: makeT1Real to copy
    \return *this
  */
{
  if (this!=&A)
    {
      *TarObj = *A.TarObj;
      *RefObj = *A.RefObj;
      *Lh2ModObj = *A.Lh2ModObj;
      *CH4ModObj = *A.CH4ModObj;
      *WaterModObj = *A.WaterModObj;
      *MerlinMod = *A.MerlinMod;
      *MPipeObj = *A.MPipeObj;
      *H2PipeObj = *A.H2PipeObj;
      *CH4PipeObj = *A.CH4PipeObj;            
      *H2FL = *A.H2FL;
      *CH4NorthFL = *A.CH4NorthFL;
      *CH4SouthFL = *A.CH4SouthFL;
      *MerlinFL = *A.MerlinFL;
      *WaterNorthFL = *A.WaterNorthFL;
      *WaterSouthFL = *A.WaterSouthFL;
    }
  return *this;
}

makeT1Real::~makeT1Real()
  /*!
    Destructor
   */
{}


void
makeT1Real::flightLines(Simulation& System)
  /*!
    Build the flight lines of the reflector
    \param SimPtr :: Simulation to add to
   */
{
  ELog::RegMethod RegA("makeT1Real","flightLines");

  std::string Out;
  std::string Out1;

  RefObj->addToInsertChain(H2FL->getCC("outer"));
  Out=RefObj->getComposite(" 3 ");
  H2FL->addBoundarySurf("inner",Out);  
  H2FL->addBoundarySurf("outer",Out);  
  H2FL->createAll(System,*Lh2ModObj,1);
  
  RefObj->addToInsertChain(CH4NorthFL->getCC("outer"));
  Out=RefObj->getComposite(" 3 -12 ");
  Out1=Lh2ModObj->getComposite(" (-61:64)  ");
  CH4NorthFL->addBoundarySurf("inner",Out+Out1);
  CH4NorthFL->addBoundarySurf("outer",Out+Out1);
  CH4NorthFL->createAll(System,*CH4ModObj,1);

  RefObj->addToInsertChain(CH4SouthFL->getCC("outer"));
  Out=RefObj->getComposite(" 1 -4 -13 ");
  CH4SouthFL->addBoundarySurf("inner",Out);
  CH4SouthFL->addBoundarySurf("outer",Out);
  CH4SouthFL->createAll(System,*CH4ModObj,2); 

  Out=RefObj->getComposite(" -4 ");
  MerlinFL->addBoundarySurf("inner",Out);
  MerlinFL->addBoundarySurf("outer",Out);
  RefObj->addToInsertChain(MerlinFL->getCC("outer"));
  MerlinFL->createAll(System,*MerlinMod,1);
  
  Out=RefObj->getComposite(" 1 3 -11 ");
  RefObj->addToInsertChain(WaterNorthFL->getCC("outer"));
  WaterNorthFL->addBoundarySurf("inner",Out);
  WaterNorthFL->addBoundarySurf("outer",Out);
  WaterNorthFL->createAll(System,*WaterModObj,1);

  Out=RefObj->getComposite(" -14 -4 ");
  RefObj->addToInsertChain(WaterSouthFL->getCC("outer"));
  WaterSouthFL->addBoundarySurf("inner",Out);
  WaterSouthFL->addBoundarySurf("outer",Out);
  WaterSouthFL->createAll(System,*WaterModObj,2); 

  // Flight line intersects:
  MerlinFL->processIntersectMinor(System,*WaterSouthFL,"inner","outer");
  WaterSouthFL->processIntersectMajor(System,*MerlinFL,"inner","outer");

  CH4NorthFL->processIntersectMajor(System,*H2FL,"inner","outer");
  H2FL->processIntersectMinor(System,*CH4NorthFL,"inner","outer");
  return;
}

std::string
makeT1Real::buildTarget(Simulation& System,
			const std::string& TType,
			const int voidCell)
  /*!
    Create a target based on the 
    \param System :: Simulation for target
    \param TType :: Target Name
    \param voidCell :: Void cell number
    \return Container for reflector
  */
{
  ELog::RegMethod RegA("makeT1Real","buildTarget");

  ModelSupport::objectRegister& OR=
    ModelSupport::objectRegister::Instance();

  if (TType=="t1PlateTarget" || TType=="t1Plate")
    {
      TarObj=std::shared_ptr<TMRSystem::TargetBase>
	(new t1PlateTarget("T1PlateTarget"));
      TarObj->setCutSurf("RefBoundary",RefObj->getLinkString(-1));
      OR.addObject(TarObj);
      TarObj->addInsertCell(voidCell);
      RefObj->addToInsertChain(*TarObj);
      TarObj->createAll(System,World::masterOrigin(),0);
      return "PVessel";
    }
  else if (TType=="t1CylTarget" || TType=="t1Cyl")
    {
      TarObj=std::shared_ptr<TMRSystem::TargetBase>
	(new TMRSystem::TS2target("t1CylTarget"));
      OR.addObject(TarObj);
      TarObj->setCutSurf("FrontPlate",RefObj->getLinkSurf(-5));
      //     TarObj->setCutSurf("BackPlate",);

      TarObj->createAll(System,World::masterOrigin(),0);
      return "t1CylTarget";
    }    
  else if (TType=="t1InnerTarget" || TType=="t1Inner")
    {
      TarObj=std::shared_ptr<TMRSystem::TargetBase>
	(new ts1System::InnerTarget("t1Inner"));
      OR.addObject(TarObj);
      TarObj->setCutSurf("FrontPlate",RefObj->getLinkSurf(-5));
      TarObj->createAll(System,World::masterOrigin(),0);
      return "t1Inner";
    }    
  else if (TType=="t1CylFluxTrap" || TType=="t1CylFluxTrapTarget")
    {
      TarObj=std::shared_ptr<TMRSystem::TargetBase>
	(new TMRSystem::TS2target("t1CylTarget"));
      OR.addObject(TarObj);
      TarObj->setCutSurf("FrontPlate",RefObj->getLinkSurf(-5));
      TarObj->createAll(System,World::masterOrigin(),0);

      std::shared_ptr<TMRSystem::TS2ModifyTarget> TarObjModify
	(new TMRSystem::TS2ModifyTarget("t1CylFluxTrap"));
      TarObjModify->createAll(System,*TarObj,0);
      OR.addObject(TarObjModify);

      return "t1CylTarget";
    }    
  else if (TType=="t1Side" || TType=="t1SideTarget")
    {
      TarObj=std::shared_ptr<TMRSystem::TargetBase>
	(new ts1System::SideCoolTarget("t1EllCylTarget"));
      OR.addObject(TarObj);
      TarObj->setCutSurf("FrontPlate",RefObj->getLinkSurf(-5));
      TarObj->createAll(System,World::masterOrigin(),0);
      return "t1EllCylTarget";
    }    
  else if (TType=="t1CannelloniTarget" || TType=="t1Cannelloni")
    {
      TarObj=std::shared_ptr<TMRSystem::TargetBase>
	(new ts1System::Cannelloni("t1Cannelloni"));
      OR.addObject(TarObj);
      TarObj->setCutSurf("FrontPlate",RefObj->getLinkSurf(-5));
      TarObj->createAll(System,World::masterOrigin(),0);
      return "t1Cannelloni";
    }    
  else if (TType=="t1Block" || TType=="t1BlockTarget")
    {
      TarObj=std::shared_ptr<TMRSystem::TargetBase>
	(new ts1System::OpenBlockTarget("t1BlockTarget"));
      OR.addObject(TarObj);
      RefObj->addToInsertChain(*TarObj);
      TarObj->setCutSurf("FrontPlate",RefObj->getLinkSurf(-3));
      TarObj->createAll(System,World::masterOrigin(),0);
      return "t1BlockTarget";
    }    

  else if (TType=="Help" || TType=="help")
    {
      ELog::EM<<"Options = "<<ELog::endBasic;
      ELog::EM<<"    t1Block :: Open void blocks"<<ELog::endBasic;
      ELog::EM<<"    t1CylFluxTrap :: Flux Trap target"<<ELog::endBasic;
      ELog::EM<<"    t1Cannelloni :: Inner cannolloni target"<<ELog::endBasic;
      ELog::EM<<"    t1Inner :: Inner triple core target"<<ELog::endBasic;
      ELog::EM<<"    t1Cyl   :: TS2 style cylindrical target"<<ELog::endBasic;
      ELog::EM<<"    t1Plate :: Plate target [current]"<<ELog::endBasic;
      ELog::EM<<"    t1Cyl   :: Side cooled target"<<ELog::endBasic;
      throw ColErr::ExitAbort("help exit");
    }    
  
  ELog::EM<<"Failed to understand target type :"
	  <<TType<<ELog::endErr;
  return "";
}

void 
makeT1Real::build(Simulation& System,
		  const mainSystem::inputParam& IParam)
  
  /*!
    Carry out the full build
    \param SimPtr :: Simulation system
    \param IParam :: Input parameters
   */
{
  // For output stream
  ELog::RegMethod RControl("makeT1Real","build");

  const std::string TarName=
    IParam.getValue<std::string>("targetType",0);

  int voidCell(74123);
  if (!IParam.flag("exclude") ||
      (!IParam.compValue("E",std::string("Bulk")) && 
       !IParam.compValue("E",std::string("Reflector")) )) 
    {
    //  VoidObj->addInsertCell(74123);  
      VoidObj->createAll(System,World::masterOrigin(),0);

      BulkObj->addInsertCell(voidCell);
      BulkObj->setCutSurf("Inner",VoidObj->getFullRule(1));
      BulkObj->setCutSurf("FullInner",VoidObj->getCompExclude());
      BulkObj->createAll(System,*VoidObj,0);

      MonoTopObj->setCutSurf("voidSurf",VoidObj->getLinkString(3));
      MonoTopObj->setCutSurf("outSurf",VoidObj->getLinkString(-1));
      MonoTopObj->setCutSurf("bulkSurf",BulkObj->getLinkString(-3));
      MonoBaseObj->setCutSurf("voidSurf",VoidObj->getLinkString(2));
      MonoBaseObj->setCutSurf("outSurf",VoidObj->getLinkString(-1));
      MonoBaseObj->setCutSurf("bulkSurf",BulkObj->getLinkString(-2));
      
      MonoTopObj->createAll(System,*VoidObj,3);
      MonoBaseObj->createAll(System,*VoidObj,2);
      
      voidCell=VoidObj->getVoidCell();
    }
  else
    {
      VoidObj->createStatus(System,World::masterOrigin(),0);
    }
  RefObj->addInsertCell(voidCell);  
  RefObj->createAll(System,*VoidObj,0);

  const std::string TarExcludeName=
    buildTarget(System,TarName,voidCell);
  if (IParam.flag("exclude") &&
      IParam.compValue("E",std::string("Reflector")))
    return;

  // Add target flight line
  TarObj->addProtonLine(System); // *RefObj,-1

  RefObj->addToInsertChain(*Lh2ModObj);
  Lh2ModObj->createAll(System,*VoidObj,0);

  RefObj->addToInsertChain(*CH4ModObj);
  CH4ModObj->createAll(System,*VoidObj,0);

  RefObj->addToInsertChain(*MerlinMod);
  MerlinMod->createAll(System,*VoidObj,0);

  RefObj->addToInsertChain(*WaterModObj);
  WaterModObj->createAll(System,*VoidObj,0);

  flightLines(System);

  RefObj->createBoxes(System,TarExcludeName);

  H2PipeObj->createAll(System,*Lh2ModObj,5);   // long int sideIndex

  WaterPipeObj->createAll(System,*WaterModObj,12);

  MPipeObj->createAll(System,*MerlinMod,12);


  CH4PipeObj->createAll(System,*CH4ModObj,5);  // long int sideIndex

  if (IParam.flag("BeRods"))
    RefObj->createRods(System);  


  return;
}

}   // NAMESPACE ts1System

