/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   construct/SupplyBox.cxx
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
 * GNU General Public License for more2 details.
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
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "Vec3D.h"
#include "surfRegister.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "HeadRule.h"
#include "groupRange.h"
#include "objectGroups.h"
#include "Simulation.h"
#include "MaterialSupport.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "FixedUnit.h"
#include "ContainedComp.h"
#include "BaseMap.h"
#include "CellMap.h"
#include "LayerComp.h"
#include "boxValues.h"
#include "boxUnit.h"
#include "BoxLine.h"
#include "SupplyBox.h"

namespace constructSystem
{

SupplyBox::SupplyBox(const std::string& Key)  :
  attachSystem::FixedComp(Key,2),optName(""),
  wallOffset(2),
  Coaxial(Key+"CoAx"),nAngle(12)
  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param Key :: Name for item in search
  */
{}

SupplyBox::SupplyBox(const SupplyBox& A) : 
  attachSystem::FixedComp(A),optName(A.optName),
  NSegIn(A.NSegIn),wallOffset(A.wallOffset),
  Width(A.Width),Depth(A.Depth),Mat(A.Mat),Temp(A.Temp),
  ActiveFlag(A.ActiveFlag),Coaxial(A.Coaxial),
  layerOffset(A.layerOffset),PPts(A.PPts),
  nAngle(A.nAngle)
  /*!
    Copy constructor
    \param A :: SupplyBox to copy
  */
{}

SupplyBox&
SupplyBox::operator=(const SupplyBox& A)
  /*!
    Assignment operator
    \param A :: SupplyBox to copy
    \return *this
  */
{
  if (this!=&A)
    {
      attachSystem::FixedComp::operator=(A);
      NSegIn=A.NSegIn;
      Width=A.Width;
      Depth=A.Depth;
      Mat=A.Mat;
      Temp=A.Temp;
      ActiveFlag=A.ActiveFlag;
      Coaxial=A.Coaxial;
      layerOffset=A.layerOffset;
      PPts=A.PPts;
      nAngle=A.nAngle;
    }
  return *this;
}


SupplyBox::~SupplyBox() 
  /*!
    Destructor
  */
{}

void
SupplyBox::populate(const FuncDataBase& Control)
  /*!
    Populate all the variables
    \param System :: Simulation to use
  */
{
  ELog::RegMethod RegA("SupplyBox","populate");
  
  std::string numStr;
  NSegIn=Control.EvalPair<size_t>(optName+"NSegIn",keyName+"NSegIn");
  for(size_t i=0;i<=NSegIn;i++)
    {
      numStr=std::to_string(i);
      PPts.push_back(Control.EvalPair<Geometry::Vec3D>
		     (optName+"PPt"+numStr,keyName+"PPt"+numStr));
    }

  size_t aN(0);
  numStr=std::to_string(aN);
  while(Control.hasVariable(keyName+"Active"+numStr))
    {
      ActiveFlag.push_back
	(Control.EvalVar<size_t>(keyName+"Active"+numStr)); 
      numStr=std::to_string(++aN);
    }

  const size_t NLayer=Control.EvalVar<size_t>(keyName+"NLayer"); 
  for(size_t i=0;i<NLayer;i++)
    {
      const std::string numStr=std::to_string(i);
      Width.push_back(Control.EvalVar<double>(keyName+"Width"+numStr));
      Depth.push_back(Control.EvalVar<double>(keyName+"Depth"+numStr));
      Mat.push_back
	(ModelSupport::EvalMat<int>(Control,keyName+"Mat"+numStr)); 
      Temp.push_back(Control.EvalDefVar<double>(keyName+"Temp"+numStr,0.0)); 
    }  
  return;
}
  

void
SupplyBox::createUnitVector(const attachSystem::FixedComp& FC,
			     const size_t layerIndex,
			     const long int sideIndex)
  /*!
    Create the unit vectors
    \param FC :: Fixed unit that it is connected to 
    \param layerIndex :: layer for constructionx
    \param sideIndex :: Connection point to use as origin [0 for origin]
  */
{
  ELog::RegMethod RegA("SupplyBox","createUnitVector");

  FixedComp::createUnitVector(FC);
  const attachSystem::LayerComp* LC=
    dynamic_cast<const attachSystem::LayerComp*>(&FC);

  if (LC && sideIndex)
    {
      Origin=LC->getSurfacePoint(layerIndex,sideIndex);
      FC.selectAltAxis(sideIndex,X,Y,Z);
    }
  ELog::EM<<"Side ="<<sideIndex<<" X == "<<X<<ELog::endDebug;
  ELog::EM<<"Y ="<<Y<<" Z == "<<Z<<ELog::endDebug;
  ELog::EM<<"Origin = "<<Origin<<ELog::endDebug;
  return;
}

void
SupplyBox::createUnitVector(const attachSystem::FixedComp& FC,
			     const long int sideIndex)
  /*!
    Create the unit vectors
    \param FC :: Fixed unit that it is connected to 
    \param sideIndex :: Connection point to use as origin [0 for origin]
  */
{
  ELog::RegMethod RegA("SupplyBox","createUnitVector(FC,long int)");

  FixedComp::createUnitVector(FC,sideIndex);
  return;
}


  
void 
SupplyBox::insertInlet(const attachSystem::FixedComp& FC,
			const long int lSideIndex)
  /*!
    Add a pipe to the moderator system:
    \remark This should be called after the moderator has
    been constructed and all objects inserted.
    \param FC :: layer values
    \param lSideIndex :: point for side of moderator
  */
{
  ELog::RegMethod RegA("SupplyBox","insertInlet");
  const attachSystem::LayerComp* LC=
    dynamic_cast<const attachSystem::LayerComp*>(&FC);
 
  if (!LC)
    throw ColErr::CastError<void>(0,"FixedComp toLayerComp");
  layerOffset=X*PPts[0].X()+Z*PPts[0].Z();

  Geometry::Vec3D Pt= Origin+layerOffset+Y*PPts[0].Y();
  // GET Z Point from layer		  
  
  Geometry::Vec3D PtZ=LC->getSurfacePoint(0,lSideIndex);
  PtZ+=layerOffset;
  const int commonSurf=LC->getCommonSurf(lSideIndex);
  const std::string commonStr=(commonSurf) ? 		       
    std::to_string(commonSurf) : "";
  if (PtZ!=Pt)
    Coaxial.addPoint(Pt);
  
  const size_t NL(LC->getNLayers(lSideIndex));

  // First find start point in layer set: [avoid inner layer]
  Coaxial.addSurfPoint
    (PtZ,LC->getLayerString(0,lSideIndex),commonStr);
  
  if (layerSeq.empty())
    {
      for(size_t index=LC->getNInnerLayers(lSideIndex)+
	    wallOffset;index<NL;index+=2)
	layerSeq.push_back(index);
    }

  for(const size_t lIndex : layerSeq)
    {
      PtZ=LC->getSurfacePoint(lIndex,lSideIndex);
      PtZ+=layerOffset;
      Coaxial.addSurfPoint
	(PtZ,LC->getLayerString(lIndex,lSideIndex),commonStr);
    }
  return;
}

void
SupplyBox::addExtraLayer(const attachSystem::LayerComp& LC,
			  const long int lSideIndex)
  /*!
    Add extra Layer for a pre-mod or such
    \param LC :: LayerComp Point [pre-mod for example]
    \param lSideIndex :: Layer to track through
   */
{
  ELog::RegMethod RegA("SupplyBox","addExtraLayer");
  
  const int commonSurf=LC.getCommonSurf(lSideIndex);
  const size_t NL(LC.getNLayers(lSideIndex));

  const std::string commonStr=(commonSurf) ? 		       
    std::to_string(commonSurf) : "";
  const Geometry::Vec3D PtZ=
    LC.getSurfacePoint(NL-1,lSideIndex)+
    layerOffset;
  Coaxial.addSurfPoint
    (PtZ,LC.getLayerString(NL-1,lSideIndex),commonStr);

  return;
}

void
SupplyBox::addOuterPoints()
  /*!
    Add outside point to the pipework
   */
{
  ELog::RegMethod RegA("SupplyBox","addOuterPoints");

  Geometry::Vec3D Pt;
  if (!Coaxial.nPoints())
    {
      Pt=Origin+X*PPts[0].X()+Y*PPts[0].Y()+Z*PPts[0].Z();
      Coaxial.addPoint(Pt);
    }

  // Outer Points
  for(size_t i=1;i<=NSegIn;i++)
    {
      Pt=Origin+X*PPts[i].X()+Y*PPts[i].Y()+Z*PPts[i].Z();
      Coaxial.addPoint(Pt);
    }
    
  for(size_t i=0;i<Width.size();i++)
    Coaxial.addSection(Width[i],Depth[i],Mat[i],Temp[i]);

  return;
}

void
SupplyBox::addInsertCell(const size_t segment,const int CellN)
  /*!
    Add a cell number that is definatively going to be cut by the 
    pipe. This is a method for dealing with ultra-thin cells etc.
    \param segment :: Index of pipe segment+1 [use 0 for all]
    \param CellN :: Cell to exclude
  */
{
  ELog::RegMethod RegA("SupplyBox","addInsertCell");
  Coaxial.addInsertCell(segment,CellN);  
  return; 
}
  
void
SupplyBox::setActive()
  /*!
    Simple set the active units
  */
{
  ELog::RegMethod RegA("SupplyBox","setActive");
  
  for(size_t i=0;i<ActiveFlag.size();i++)
    Coaxial.setActive(i,ActiveFlag[i]);  
  return;
}

void
SupplyBox::createLinks()
  /*!
    Create the links for the first/last pipe
  */
{
  ELog::RegMethod RegA("SupplyBox","createLinks");

  FixedComp::setConnect(0,Origin,-Y);
  FixedComp::setConnect(1,Coaxial.getPt().back(),Y);

  HeadRule EndCap(Coaxial.first().getCap(0));
  EndCap.makeComplement();
  FixedComp::setLinkSurf(0,EndCap);

  EndCap=Coaxial.last().getCap(1);
  EndCap.makeComplement();
  FixedComp::setLinkSurf(1,EndCap);

  return;
}

  
void
SupplyBox::createAll(Simulation& System,
		      const attachSystem::FixedComp& FC,
		      const long int sideIndex)
  /*!
    Generic function to create everything
    \param System :: Simulation to create objects in
    \param FC :: Fixed Base unit
    \param sideIndex :: Link point for origin 
  */
{
  ELog::RegMethod RegA("SupplyBox","createAll");
  populate(System.getDataBase());

  createUnitVector(FC,sideIndex);
  addOuterPoints();
  setActive();

  //  Coaxial.setNAngle(nAngle);
  if (!startSurf.empty())
    Coaxial.setStartSurf(startSurf);
  Coaxial.build(System);
  createLinks();
  return;
}

void
SupplyBox::createAll(Simulation& System,
		      const attachSystem::FixedComp& FC,
		      const size_t orgLayerIndex,
		      const long int orgSideIndex,
		      const long int exitSideIndex)
  /*!
    Generic function to create everything
    \param System :: Simulation to create objects in
    \param FC :: Fixed Base unit
    \param orgLayerIndex :: Link point for origin 
    \param orgSideIndex :: Link point for origin 
    \param exitSideIndex :: layer to pass pipe out though
  */
{
  ELog::RegMethod RegA("SupplyBox","createAll");
  populate(System.getDataBase());

  createUnitVector(FC,orgLayerIndex,orgSideIndex);
  insertInlet(FC,exitSideIndex);
  addOuterPoints();
  setActive();

  //  Coaxial.setNAngle(nAngle);
  if (!startSurf.empty())
    Coaxial.setStartSurf(startSurf);
  Coaxial.build(System);
  
  createLinks();
  return;
}

void
SupplyBox::createAll(Simulation& System,
		      const attachSystem::FixedComp& FC,
		      const size_t orgLayerIndex,
		      const long int orgSideIndex,
		      const long int exitSideIndex,
		      const attachSystem::LayerComp& LC,
		      const long int extraSide)
  /*!
    Generic function to create everything
    \param System :: Simulation to create objects in
    \param FC :: Fixed Base unit
    \param orgLayerIndex :: Link point for origin  [0 for origin]
    \param orgSideIndex :: Link point for X,Y,Z axis [0 for origin]
    \param exitSideIndex :: layer to pass pipe out via
    \param LC :: Point to extra Layer Object if exist [pre-mod]
    \param extraSide :: Side to track through object
  */
{
  ELog::RegMethod RegA("SupplyBox","createAll<LC>");
  populate(System.getDataBase());

  createUnitVector(FC,orgLayerIndex,orgSideIndex);

      
  insertInlet(FC,exitSideIndex);
  addExtraLayer(LC,extraSide);
  addOuterPoints();
  setActive();

  //  Coaxial.setNAngle(nAngle);
  if (!startSurf.empty())
    Coaxial.setStartSurf(startSurf);
  Coaxial.build(System);
  createLinks();
  return;
}
  
}  // NAMESPACE constructSystem
