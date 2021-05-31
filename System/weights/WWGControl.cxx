/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   weights/WWGControl.cxx
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
#include <memory>
#include <boost/multi_array.hpp>

#include "Exception.h"
#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "Vec3D.h"
#include "Surface.h"
#include "Quadratic.h"
#include "Plane.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "support.h"
#include "weightManager.h"
#include "WForm.h"
#include "groupRange.h"
#include "objectGroups.h"
#include "Simulation.h"
#include "SimMCNP.h"
#include "inputParam.h"
#include "ImportControl.h"
#include "meshConstruct.h"

#include "BasicMesh3D.h"
#include "WWGWeight.h"
#include "MarkovProcess.h"
#include "WWG.h"
#include "WeightControl.h"
#include "WWGControl.h"

namespace WeightSystem
{

WWGControl::WWGControl() :
  nMarkov(0)
  /*!
    Constructor
  */
{}

  
WWGControl::WWGControl(const WWGControl& A) :
  activeParticles(A.activeParticles),
  nMarkov(A.nMarkov),
  planePt(A.planePt),sourcePt(A.sourcePt),
  meshUnit(A.meshUnit)  
  /*!
    Copy Constructor
    \param A :: WWGControl item to copy
  */
{}

WWGControl&
WWGControl::operator=(const WWGControl& A)
  /*!
    Assignment operator
    \param A :: WWGControl to copy
    \return this
  */
{
  if (this!=&A)
    {
      nMarkov=A.nMarkov;
      activeParticles=A.activeParticles;
      planePt=A.planePt;
      sourcePt=A.sourcePt;
      meshUnit=A.meshUnit;
    }
  return *this;
}

WWGControl::~WWGControl()
  /*!
    Destructor
   */
{}

const Geometry::BasicMesh3D&
WWGControl::getGrid(const std::string& gName) const
  /*!
    Simple accessor to grid unit
    \param gName :: Name of BasicGrid3D
    \return BasicMesh from meshUnit
  */
{
  std::map<std::string,Geometry::BasicMesh3D>::const_iterator mc=
    meshUnit.find(gName);
  if (mc==meshUnit.end())
    throw ColErr::InContainerError<std::string>
      (gName,"meshUnit does not have name");
  return mc->second;
}

const Geometry::Vec3D&
WWGControl::getSourcePoint(const std::string& sName) const
  /*!
    Simple accessor to sourcePt
    \param sName :: Name of source
    \return Vec3D point from sourcePt
  */
{
  std::map<std::string,Geometry::Vec3D>::const_iterator mc=
    sourcePt.find(sName);
  if (mc==sourcePt.end())
    throw ColErr::InContainerError<std::string>
      (sName,"sourcePt does not have name");
  return mc->second;
}

const Geometry::Plane&
WWGControl::getPlanePoint(const std::string& pName) const
  /*!
    Simple accessor to planePt
    \param pName :: Name of plane
    \return Plane from planePt
  */
{
  std::map<std::string,Geometry::Plane>::const_iterator mc=
    planePt.find(pName);
  if (mc==planePt.end())
    throw ColErr::InContainerError<std::string>
      (pName,"planePt does not have name");
  return mc->second;
}

  
bool
WWGControl::hasPlanePoint(const std::string& pName) const
  /*!
    Simple check accessor to planePt 
    \param pName :: Name of plane
    \return true if plane exists
  */
{
  return (planePt.find(pName)!=planePt.end());
}

bool
WWGControl::hasSourcePoint(const std::string& sName) const
  /*!
    Simple check accessor to sourcePt 
    \param sName :: Name of source Pt
    \return true if source exists
  */
{
  return (sourcePt.find(sName)!=sourcePt.end());
}

void
WWGControl::procSourcePoint(const Simulation& System,
			       const mainSystem::inputParam& IParam)
  /*!
    Process the source weight point
    \param IParam :: Input param
  */
{
  ELog::RegMethod RegA("WWGControl","procSourcePoint");

  const std::string wKey("wwgSource");
  
  sourcePt.clear();

  const size_t NSource=IParam.setCnt(wKey);
  for(size_t setIndex=0;setIndex<NSource;setIndex++)
    {
      const std::string sourceName=
        IParam.getValueError<std::string>
        (wKey,setIndex,0,"wwgSource:SourceName");
      size_t itemCnt(1);
      const Geometry::Vec3D sPoint=
	mainSystem::getNamedPoint
	(System,IParam,wKey,setIndex,itemCnt,wKey+":Source Point");

      sourcePt.emplace(sourceName,sPoint);
    }
  return;
}
   
void
WWGControl::procPlanePoint(const Simulation& System,
			   const mainSystem::inputParam& IParam)
  /*!
    Determine inf the next component cat be a plane
    Given as two Vec3D from inputParam
    \param IParam :: Input parameters
  */
{
  ELog::RegMethod RegA("WWGControl","procPlanePoint");

  const std::string wKey("wwgPlane");
  
  planePt.clear();
  const size_t NPlane=IParam.setCnt(wKey);
  
  for(size_t setIndex=0;setIndex<NPlane;setIndex++)
    {
      const std::string planeName=
        IParam.getValueError<std::string>
        (wKey,setIndex,0,"wwgPlane:PlaneName");
      size_t itemCnt(1);
      const Geometry::Vec3D PPoint=
	mainSystem::getNamedPoint
	(System,IParam,wKey,setIndex,itemCnt,wKey+"Plane Point");
      const Geometry::Vec3D Norm=
	mainSystem::getNamedAxis
	(System,IParam,wKey,setIndex,itemCnt,wKey+"Plane:Norm");

      planePt.emplace(planeName,Geometry::Plane(0,0,PPoint,Norm));
    }

  return;
}

void
WWGControl::procMeshPoint(const Simulation& System,
			  const mainSystem::inputParam& IParam)
  /*!
    Process the mesh weight point
    Input type :
    - weightMesh meshName  
    \param IParam :: Input param
  */
{
  ELog::RegMethod RegA("WWGControl","procMeshPoint");

  const std::string wKey("wwgMesh");

  Geometry::Vec3D APt,BPt;
  std::array<size_t,3> Nxyz;
  
  meshUnit.clear();

  const size_t NMesh=IParam.setCnt(wKey);
  for(size_t setIndex=0;setIndex<NMesh;setIndex++)
    {
      const std::string meshName=
	IParam.getValueError<std::string>
	(wKey,setIndex,0,"meshName object/free/values");
      if (meshUnit.find(meshName)!=meshUnit.end())
	throw ColErr::InContainerError<std::string>
	  (meshName,"repeated mesh name");
      
      const std::string PType=
	IParam.getValueError<std::string>
	(wKey,setIndex,1,"meshName object/free/values"); 
      
      size_t index(2);  
      if (PType=="object")
	{
	  mainSystem::meshConstruct::getObjectMesh
	    (System,IParam,wKey,setIndex,index,APt,BPt,Nxyz);
	}
      else if (PType=="free")
	{
	  mainSystem::meshConstruct::getFreeMesh
	    (IParam,wKey,setIndex,index,APt,BPt,Nxyz);
	}
      else // assume just free
	{
	  index=1;
	  mainSystem::meshConstruct::getFreeMesh
	    (IParam,wKey,setIndex,index,APt,BPt,Nxyz);
	}
      meshUnit.emplace(meshName,Geometry::BasicMesh3D(0,APt,BPt,Nxyz));
    }
  return;
}

  
void
WWGControl::wwgCreate(const Simulation& System,
                      const mainSystem::inputParam& IParam)
  /*!
    Calculate a WWG weights based. This calls the tracking
    system to calculate the attenuation from the source/adjoint
    to the cell in readiness for the expected Markov process [if used]
    \param System :: Simulation
    \param IParam :: Input deck
   */
{
  ELog::RegMethod RegA("WWGControl","wwgCreate");

  WeightSystem::weightManager& WM=
    WeightSystem::weightManager::Instance();
  WWG& wwg=WM.getWWG();

  const std::string wKey("wwgCalc");
  const size_t NSetCnt=IParam.setCnt(wKey);
  
  for(size_t iSet=0;iSet<NSetCnt;iSet++)
    {
      const std::string meshName=
        IParam.getValueError<std::string>
        (wKey,iSet,0,"wwgCalc without mesh name");

      if (meshName=="help" || meshName=="Help")
	{
	  ELog::EM<<"wwgCalc ==> \n"
	    "       meshName : Name of being begin processed\n"
	    "       particleList : list of particles\n"
	    "       gridName : Name of grid to use\n"
	    "       SourceName [Plane/Point name]\n"
	    "       Energy Cut [default: 0.0] \n"
	    "       ScaleFactor [default: 1.0] \n"
	    "       densityFactor [default: 1.0] \n"
	    "       r2Length factor [default: 1.0] \n"
	    "       r2Power [default: 2.0] \n"<<ELog::endCrit;
	  return;
	}

      std::string particleList=
        IParam.getValueError<std::string>
        (wKey,iSet,1,"wwgCalc without particle naem");
      
      const std::string meshGrid=
        IParam.getValueError<std::string>
	(wKey,iSet,2,"wwgCalc without mesh grid name");
      
      const std::string sourceName=
        IParam.getValueError<std::string>
        (wKey,iSet,3,"wwgCalc without source/plane name");

      size_t index(4);
      const double energyCut=
	IParam.getDefValue<double>(0.0,wKey,iSet,index++);
      const double density=
	IParam.getDefValue<double>(1.0,wKey,iSet,index++);
      const double r2Length=
	IParam.getDefValue<double>(1.0,wKey,iSet,index++);
      const double r2Power=
	IParam.getDefValue<double>(2.0,wKey,iSet,index++);

      const Geometry::BasicMesh3D& mUnit=getGrid(meshGrid);
      if (hasPlanePoint(sourceName))
	{	
	  const Geometry::Plane& planeRef=getPlanePoint(sourceName);
	  WWGWeight& wSet=wwg.createMesh(meshName);
	  wSet.setEnergy(EBin);  // set later [not written yet]
	  wSet.setMesh(mUnit);
	  wSet.wTrack(System,planeRef,density,r2Length,r2Power);
	}
      else if (hasSourcePoint(sourceName))
        {
	  const Geometry::Vec3D& sourceRef=getSourcePoint(sourceName);
	  WWGWeight& wSet=wwg.createMesh(meshName);
	  wSet.setEnergy(EBin);  // set later [not written yet]
	  wSet.setMesh(mUnit);
	  wSet.wTrack(System,sourceRef,density,r2Length,r2Power);
        }
      else 
	throw ColErr::InContainerError<std::string>
	  (sourceName,"SourceType not known");
    }
  return;
}
  

void
WWGControl::wwgMarkov(const Simulation& System,
			 const mainSystem::inputParam& IParam)
  /*!
    Process a Markov chain iteration for the system
    \param System :: Simulation
    \param IParam :: Input deck
   */
{
  ELog::RegMethod RegA("WWGControl","wwgMarkov");

  // Find if we need to do Markov:
  const size_t NSetCnt=IParam.setCnt("wwgMarkov");
  if (!NSetCnt) return;
  
  WeightSystem::weightManager& WM=
    WeightSystem::weightManager::Instance();
  WWG& wwg=WM.getWWG();

  const std::string wKey("wwgMarkov");
  for(size_t iSet=0;iSet<NSetCnt;iSet++)
    {
      size_t index(0);
      const size_t nMult=IParam.getValueError<size_t>
	(wKey,iSet,index++,"Mult count not set");
      const double density=
	IParam.getDefValue<double>(1.0,wKey,iSet,index++);
      const double r2Length=
	IParam.getDefValue<double>(1.0,wKey,iSet,index++);
      const double r2Power=
	IParam.getDefValue<double>(2.0,wKey,iSet,index++);
      
      if (nMarkov)
	{
	  MarkovProcess MCalc;
	  MCalc.initializeData(wwg,wwg.getDefUnit());
	  MCalc.computeMatrix(System,wwg,wwg.getDefUnit(),
			      density,r2Length,r2Power);
	  MCalc.multiplyOut(nMult);
	  MCalc.rePopulateWWG();
	  ELog::EM<<"MARKOV FINISHED"<<ELog::endDiag;
	}
    }

  return;
}

void
WWGControl::wwgNormalize(const mainSystem::inputParam& IParam)
  /*!
    Normalize the main weight system
    \param IParam :: Input parameter
  */
{
  ELog::RegMethod RegA("WWGControl","wwgNormalize");

  WeightSystem::weightManager& WM=
    WeightSystem::weightManager::Instance();
  WWG& wwg=WM.getWWG();
  
  const size_t NNorm=IParam.setCnt("wwgNorm");
  for(size_t setIndex=0;setIndex<NNorm;setIndex++)
    {
      const std::string meshIndex=
	IParam.getValueError<std::string>
	("wwgNorm",setIndex,0,"Mesh Index");
      
      if (meshIndex=="help" || meshIndex=="Help")
	{
	  ELog::EM<<"wwgNorm ==> \n"
	    "       meshIndex :: Name of mesh to process \n"
	    "       log(weightRange) [Manditory] (typical 20) \n"
	    "       lowRange (+ve takes data range) [default 1.0]\n"
	    "       highRange (+ve takes data range) [default 1.0]\n"
		  <<ELog::endCrit;
	  return;
	}
      const double weightRange=
	IParam.getValueError<double>("wwgNorm",setIndex,1,"weightRange");

      // +ve means default
      const double lowRange=
	IParam.getDefValue<double>(1.0,"wwgNorm",setIndex,2);

      const double highRange=
	IParam.getDefValue<double>(1.0,"wwgNorm",setIndex,3);
      
      const WWGWeight& WMesh=wwg.getMesh(meshIndex);
      const size_t NE=WMesh.getESize();
      for(size_t i=0;i<NE;i++)
	wwg.scaleRange(meshIndex,i,lowRange,highRange,weightRange);
      //      wwg.powerRange(powerWeight);
    }
  return;
}
  

void
WWGControl::wwgVTK(const mainSystem::inputParam& IParam)
  /*!
    Write out an vkt file
    \param IParam :: Data for point
  */
{
  ELog::RegMethod RegA("WWGControl","wwgVTK");
  
  WeightSystem::weightManager& WM=
    WeightSystem::weightManager::Instance();

  const size_t nCnt=IParam.setCnt("wwgVTK");

  WWG& wwg=WM.getWWG();  
  for(size_t i=0;i<nCnt;i++)
    {
      const std::string meshIndex=
        IParam.getValueError<std::string>("wwgNorm",i,0,"MeshIndex not given");
      const std::string fileName=
        IParam.getValueError<std::string>("wwgNorm",i,1,"FileName not given");
      wwg.writeVTK(meshIndex,fileName);
    }
  return;
}

void
WWGControl::wwgCombine(const Simulation& System,
		       const mainSystem::inputParam& IParam)
  /*!
    Co-joint the adjoint/source terms
    \param System :: Model simulation
    \param IParam :: input data
   */
{
  ELog::RegMethod RegA("WWGControl","wwgCombine");

  WeightSystem::weightManager& WM=
    WeightSystem::weightManager::Instance();
  WWG& wwg=WM.getWWG();

  const std::string wKey("wwgCADIS");
  
  const size_t cadisCNT=IParam.setCnt(wKey);
  for(size_t iSet=0;iSet<cadisCNT;iSet++)
    {
      size_t itemCnt(0);
      const std::string meshIndex=IParam.getValueError<std::string>
	(wKey,iSet,itemCnt++,"CADIS MeshISet");
      
      const std::string SUnit=IParam.getValueError<std::string>
	(wKey,iSet,itemCnt++,"CADIS SUnit");
      
      const std::string TUnit=IParam.getValueError<std::string>
	(wKey,iSet,itemCnt++,"CADIS TUnit");
      
      const std::string SPt=IParam.getValueError<std::string>
	(wKey,iSet,itemCnt++,"CADIS Source Point");
      
      const std::string TPt=IParam.getValueError<std::string>
	(wKey,iSet,itemCnt++,"CADIS Adjoint Point");

      const double density=
	IParam.getDefValue<double>(1.0,wKey,iSet,itemCnt++);
      const double r2Length=
	IParam.getDefValue<double>(1.0,wKey,iSet,itemCnt++);
      const double r2Power=
	IParam.getDefValue<double>(2.0,wKey,iSet,itemCnt++);

      WWGWeight& MeshGrid=wwg.getMesh(meshIndex);
      const WWGWeight& sourceFlux=wwg.getMesh(SUnit);
      const WWGWeight& adjointFlux=wwg.getMesh(TUnit);
      
      if (hasPlanePoint(SPt) && hasPlanePoint(TPt))
	{
	  const Geometry::Plane& SPlane=getPlanePoint(SPt);
	  const Geometry::Plane& TPlane=getPlanePoint(TPt);
	  MeshGrid.CADISnorm(System,
			     sourceFlux,
			     adjointFlux,
			     SPlane,TPlane,
			     density,r2Length,r2Power);      
	}
      else if (hasSourcePoint(SPt) && hasSourcePoint(TPt))
	{
	  const Geometry::Vec3D& SVec=getSourcePoint(SPt);
	  const Geometry::Vec3D& TVec=getSourcePoint(TPt);
	  MeshGrid.CADISnorm(System,
			     sourceFlux,
			     adjointFlux,
			     SVec,TVec,
			     density,r2Length,r2Power);      
	}
      else
	{
	  ELog::EM<<"Mixed source/plane cadis not currently supported"
		  <<ELog::endErr;
	}
    }
  
  return;
}

void
WWGControl::wwgActivate(const Simulation& System,
			const mainSystem::inputParam& IParam)
  /*!
    Co-joint the adjoint/source terms
    \param System :: Model simulation
    \param IParam :: input data
   */
{
  ELog::RegMethod RegA("WWGControl","wwgActivate");

  WeightSystem::weightManager& WM=
    WeightSystem::weightManager::Instance();
  WWG& wwg=WM.getWWG();

  size_t idCount(1);
  const size_t CNT=IParam.setCnt("wwgActive");
  for(size_t index=0;index<CNT;index++)
    {
      const std::string meshIndex=IParam.getValueError<std::string>
	("wwgActive",index,0,"wwgActive: MeshIndex");

      const std::string outType=
	StrFunc::toUpperString(IParam.getDefValue<std::string>
			       ("LOG","wwgActive",index,1));

      WWGWeight& MeshGrid=wwg.getMesh(meshIndex);
      MeshGrid.setID(idCount);
      if (outType=="LOG")
	MeshGrid.setOutLog();
      idCount++;
    }      
    
  return;
}
  
void
WWGControl::processWeights(Simulation& System,
			   const mainSystem::inputParam& IParam)
  /*!
    External control sequence for WWG:
    Controls full build of WWG mesh/ calculation / and final setting
    \param System :: Simulation
    \param IParam :: input stream
  */
{
  ELog::RegMethod RegA("WWGControl","processWeights");

  WeightSystem::weightManager& WM=
    WeightSystem::weightManager::Instance();  

  if (IParam.flag("wWWG"))
    {
      System.populateCells();
      System.createObjSurfMap();

      procSourcePoint(System,IParam);
      procPlanePoint(System,IParam);
      procMeshPoint(System,IParam);

      wwgCreate(System,IParam);      // LOG space
      wwgMarkov(System,IParam);
      wwgCombine(System,IParam);
      wwgNormalize(IParam);

      wwgActivate(System,IParam);
      //      wwgVTK(IParam);	    
      for(const std::string& P : activeParticles)
	{
	  // don't write a wwp:particle card
	  WM.getParticle(P)->setActiveWWP(0);
	  SimMCNP* SimPtr=dynamic_cast<SimMCNP*>(&System);
	  if (SimPtr)
	    clearWImp(SimPtr->getPC(),P);

	}
    }

  return;
}


  
}  // NAMESPACE weightSystem

