/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   t1Build/channel.cxx
 *
 * Copyright (c) 2004-2022 by Stuart Ansell
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
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <complex>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <boost/format.hpp>

#include "Exception.h"
#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "Vec3D.h"
#include "Surface.h"
#include "surfIndex.h"
#include "surfRegister.h"
#include "Quadratic.h"
#include "Plane.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
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
#include "ContainedComp.h"

#include "channel.h"

namespace ts1System
{

channel::channel(const std::string& Key,const int ID,
		 const int baseSurfN) : 
		
  attachSystem::ContainedComp(),
  attachSystem::FixedComp(Key+std::to_string(ID),0),
  blockIndex(ID),cIndex(baseSurfN)
  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param ID :: Index value of block
    \param baseSurfN :: surface Index of outer component
    \param Key :: Name for item in search
  */
{}

channel::channel(const channel& A) : 
  attachSystem::ContainedComp(A),attachSystem::FixedComp(A),
  blockIndex(A.blockIndex),cIndex(A.cIndex),
  centX(A.centX),centZ(A.centZ),
  width(A.width),height(A.height),midGap(A.midGap),
  inStep(A.inStep),inDepth(A.inDepth),matN(A.matN)
  /*!
    Copy constructor
    \param A :: channel to copy
  */
{}

channel&
channel::operator=(const channel& A)
  /*!
    Assignment operator
    \param A :: channel to copy
    \return *this
  */
{
  if (this!=&A)
    {
      attachSystem::ContainedComp::operator=(A);
      attachSystem::FixedComp::operator=(A);

      centX=A.centX;
      centZ=A.centZ;
      width=A.width;
      height=A.height;
      midGap=A.midGap;
      inStep=A.inStep;
      inDepth=A.inDepth;
      matN=A.matN;
    }
  return *this;
}


double
channel::getVar(const size_t Item) const
  /*!
    Get the value based on an index reference
    \param Item :: Index value to variable
    \return value
  */
{
  ELog::RegMethod RegA("channel","getVar");
  
  switch(Item)
    {
    case 0:
      return centX;
    case 1:
      return centZ;
    case 2:
      return width;
    case 3:
      return height;
    case 4:
      return midGap;
    case 5:
      return inStep;
    case 6:
      return inDepth;
    case 7:
      return matN;
    }
  throw ColErr::IndexError<size_t>(Item,8,"Index out of range");
}


void
channel::setVar(const FuncDataBase& Control,
		const size_t Item,
		const std::string& VarStr)
  /*!
    Convert a string into an item value
    \param Control :: DataBase to get value from
    \param Item :: Index value to variable
    \param VarStr :: String to convert into values
  */
{
  ELog::RegMethod RegA("channel","setVar<Control>");

  double* DArray[]={&centX,&centZ,&width,&height,
			  &midGap,&inStep,&inDepth};
  if (Item<7)
    *DArray[Item]=Control.EvalVar<double>(VarStr);
  else if (Item==7)
    matN=ModelSupport::EvalMat<int>(Control,VarStr);    
  else 
    throw ColErr::IndexError<size_t>(Item,8,"Var Index unknown");
  return;
}

void
channel::setVar(const size_t Item,const channel& CRef)
  /*!
    Given a value set the item
    \param Item :: Index value to variable
    \param V :: Value
  */
{
  double* DArray[]={&centX,&centZ,&width,&height,
			  &midGap,&inStep,&inDepth};
  const double* CRefArray[]={&CRef.centX,&CRef.centZ,&CRef.width,
			     &CRef.height,&CRef.midGap,
			     &CRef.inStep,&CRef.inDepth};
  if (Item<7)
    *DArray[Item] = *CRefArray[Item];
  else if (Item==7)
    matN=CRef.matN;
  else 
    throw ColErr::IndexError<size_t>(Item,8,"Var Index unknown");
  return;
}


void
channel::populate(const FuncDataBase& Control,
		  const channel* defChannel)
  /*!
    Populate all the variables
    Requires that unset values are copied from previous block
    \param System :: Simulation to use
    \param defChannel :: Standard block to use
  */
{
  ELog::RegMethod RegA("channel","populate");

  const int Size(8);
  const char* sndKey[Size]=
    {"XOffset","ZOffset","Width","Height",
     "MidGap","InStep","InDepth","Mat"};
    
  for(size_t i=0;i<Size;i++)
    {
      std::ostringstream cx;
      cx<<keyName<<sndKey[i];
      if (Control.hasVariable(cx.str()))
	setVar(Control,i,cx.str());
      else if (defChannel)
	setVar(i,*defChannel);
      else
	{
	  ELog::EM<<"Failed to connect on first component:"
		  <<blockIndex+1<<" :: "<<cx.str()<<ELog::endErr;
	}
    }  
  return;
}

void
channel::createSurfaces()
  /*!
    Creates/duplicates the surfaces for this block
  */
{
  ELog::RegMethod RegA("channel","createSurface");
  ModelSupport::surfIndex& SurI= ModelSupport::surfIndex::Instance();
  const double signV((centZ<0) ? -1.0 : 1.0);
 
  ModelSupport::buildPlane(SMap,buildIndex+3,
			   Origin+X*(centX-width),X);
  ModelSupport::buildPlane(SMap,buildIndex+4,
			   Origin+X*(centX+width),X);
  ModelSupport::buildPlane(SMap,buildIndex+5,
			   Origin+Z*(centZ-signV*height),Z*signV);
  ModelSupport::buildPlane(SMap,buildIndex+6,
			   Origin+Z*(centZ+signV*height),Z*signV);

  // get front plate surface for offset
  const int fplate((centX<0) ? cIndex+8 : cIndex+9);
  const Geometry::Plane* FSurf
    =SMap.realPtr<Geometry::Plane>(fplate);

  const Geometry::Vec3D NormA=FSurf->getNormal();
  const double DA=FSurf->getDistance();

  // Ugly movement of the cut surface: 
  Geometry::Plane* PX=
    SurI.createUniqSurf<Geometry::Plane>(buildIndex+1); 
  PX->setPlane(NormA,DA-inStep);      
  SMap.registerSurf(buildIndex+1,PX);

  // the L part section:
  // From centre of target.
  ModelSupport::buildPlane(SMap,buildIndex+15,Origin+Z*signV*midGap,Z*signV);


  PX=SurI.createUniqSurf<Geometry::Plane>(buildIndex+11); 
  PX->setPlane(NormA,DA-(inStep+inDepth));     
//  PX->setPlane(NormA,DA-(inStep+3.0*height));       
  SMap.registerSurf(buildIndex+11,PX);
  
  return;
}

void
channel::createObjects(Simulation& System)
  /*!
    Create the objects
    \param System :: Simulation
  */
{
  ELog::RegMethod RegA("channel","createObjects");

  std::string Out;
  Out=ModelSupport::getComposite(SMap,buildIndex,"-1 3 -4 5 -6 ");
  addOuterSurf(Out);

  Out=ModelSupport::getComposite(SMap,buildIndex,"-1 11 3 -4 -5 15 ");
  addOuterUnionSurf(Out);
  System.addCell(MonteCarlo::Object(cellIndex++,matN,0.0,Out));

  Out=ModelSupport::getComposite(SMap,buildIndex,cIndex,"-1 -2M 3 -4 5 -6 ");
  System.addCell(MonteCarlo::Object(cellIndex++,matN,0.0,Out));
  
  return;
}

void
channel::setDefaultValues(const FuncDataBase& Control,
			  const channel* ZB)
  /*!
    \param Control :: Target origin system
    \param ZB :: Channel to copy default values from
  */
{
  populate(Control,ZB);
  return;
}

void
channel::createAll(Simulation& System,
		   const attachSystem::FixedComp& FC,
		   const long int sideIndex)

  /*!
    Global creation of the hutch
    \param System :: Simulation to add vessel to
    \param FC :: Target origin system
    \param ZB :: Channel to take default values
  */
{
  ELog::RegMethod RegA("channel","createAll");


  createUnitVector(FC,sideIndex);
  createSurfaces();
  createObjects(System);
  insertObjects(System);       

  return;
}

} // NAMESPACE t1System
