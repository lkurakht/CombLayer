/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   essBuild/LayeredBulkModule.cxx
 *
 * Copyright (c) 2004-2018 by Stuart Ansell
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
#include "stringCombine.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Quaternion.h"
#include "localRotate.h"
#include "masterRotate.h"
#include "Surface.h"
#include "surfIndex.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "surfEqual.h"
#include "surfDivide.h"
#include "surfDIter.h"
#include "Quadratic.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Line.h"
#include "Rules.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "inputParam.h"
#include "ReadFunctions.h"
#include "HeadRule.h"
#include "Object.h"
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
#include "SurfMap.h"
#include "CellMap.h"
#include "World.h"
#include "LayeredBulkModule.h"

namespace essSystem
{

LayeredBulkModule::LayeredBulkModule(const std::string& Key)  :
  attachSystem::ContainedComp(),attachSystem::FixedOffset(Key,9),
  attachSystem::SurfMap(),attachSystem::CellMap()
  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param Key :: Name for item in search
  */
{}

LayeredBulkModule::LayeredBulkModule(const LayeredBulkModule& A) : 
  attachSystem::ContainedComp(A),attachSystem::FixedOffset(A),
  attachSystem::SurfMap(A),attachSystem::CellMap(A),
  nLayer(A.nLayer),radius(A.radius),height(A.height),depth(A.depth),
  COffset(A.COffset),Mat(A.Mat)
  /*!
    Copy constructor
    \param A :: LayeredBulkModule to copy
  */
{}

LayeredBulkModule&
LayeredBulkModule::operator=(const LayeredBulkModule& A)
  /*!
    Assignment operator
    \param A :: LayeredBulkModule to copy
    \return *this
  */
{
  if (this!=&A)
    {
      attachSystem::ContainedComp::operator=(A);
      attachSystem::FixedOffset::operator=(A);
      attachSystem::SurfMap::operator=(A);
      attachSystem::CellMap::operator=(A);
      nLayer=A.nLayer;
      radius=A.radius;
      height=A.height;
      depth=A.depth;
      COffset=A.COffset;
      Mat=A.Mat;
    }
  return *this;
}

LayeredBulkModule::~LayeredBulkModule() 
  /*!
    Destructor
  */
{}

void
LayeredBulkModule::populate(const FuncDataBase& Control)
 /*!
   Populate all the variables
   \param Control :: DataBase to use
 */
{
  ELog::RegMethod RegA("LayeredBulkModule","populate");
  
  FixedOffset::populate(Control);
  
  nLayer=Control.EvalVar<size_t>(keyName+"NLayer");
  if (!nLayer) return;
  radius.resize(nLayer);
  height.resize(nLayer);
  depth.resize(nLayer);
  Mat.resize(nLayer);
  COffset.resize(nLayer);
  for(size_t i=0;i<nLayer;i++)
    {
      radius[i]=Control.EvalVar<double>
	(keyName+StrFunc::makeString("Radius",i+1));
      height[i]=Control.EvalVar<double>
	(keyName+StrFunc::makeString("Height",i+1));
      depth[i]=Control.EvalVar<double>
	(keyName+StrFunc::makeString("Depth",i+1));
      Mat[i]=ModelSupport::EvalMat<int>(Control,
	keyName+StrFunc::makeString("Mat",i+1));
      if (i)
	COffset[i]=Control.EvalDefVar<Geometry::Vec3D>
	  (keyName+StrFunc::makeString("Offset",i+1),
	   Geometry::Vec3D(0,0,0));
    }
  return;
}
  
void
LayeredBulkModule::createUnitVector(const attachSystem::FixedComp& FC,
			     const long int sideIndex)
  /*!
    Create the unit vectors
    \param FC :: Linked object
    \param sideIndex :: Link point 
  */
{
  ELog::RegMethod RegA("LayeredBulkModule","createUnitVector");

  FixedComp::createUnitVector(FC,sideIndex);
  applyOffset();
    
  for(size_t i=0;i<nLayer;i++)
    COffset[i]=X*COffset[i].X()+Y*COffset[i].Y();

  return;
}
  
void
LayeredBulkModule::createSurfaces()
  /*!
    Create All the surfaces
  */
{
  ELog::RegMethod RegA("LayeredBulkModule","createSurface");

  // rotation of axis:

  // divider
  ModelSupport::buildPlane(SMap,buildIndex+1,Origin,Y);

  int RI(buildIndex);    
  for(size_t i=0;i<nLayer;i++)
    {
      ModelSupport::buildPlane(SMap,RI+5,Origin-Z*depth[i],Z);
      ModelSupport::buildPlane(SMap,RI+6,Origin+Z*height[i],Z);
      ModelSupport::buildCylinder(SMap,RI+7,Origin+COffset[i]
				  ,Z,radius[i]);
      addSurf("Radius"+std::to_string(i),SMap.realSurf(RI+7));
      RI+=10;
    }

  return;
}

void
LayeredBulkModule::createObjects(Simulation& System,
			  const attachSystem::ContainedComp& CC)
  /*!
    Adds the all the components
    \param System :: Simulation to create objects in
    \param CC :: Inner reflector
  */
{
  ELog::RegMethod RegA("LayeredBulkModule","createObjects");

  std::string Out,OutX,cellName;
  int RI(buildIndex);
  for(size_t i=0;i<nLayer;i++)
    {
      Out=ModelSupport::getComposite(SMap,RI,"5 -6 -7 ");
      if(i){
	//((i==(nLayer-1))&&(nLayer>1)){
        OutX=ModelSupport::getComposite(SMap,RI-10," 15 -5 -17");
        cellName="Lower";
               makeCell(cellName,System,cellIndex++,Mat[i],0.0,OutX);
        OutX=ModelSupport::getComposite(SMap,RI-10," 6 -16 -17");
        cellName="Top";
	makeCell(cellName,System,cellIndex++,Mat[i],0.0,OutX);
	 Out=ModelSupport::getComposite(SMap,RI-10,"5 -6 -17 ");
	cellName="Outer";
	OutX=ModelSupport::getComposite(SMap,RI-10,"(-5:6:7)");
      }
      // else if (i){
      //	cellName="Outer";
      //	OutX=ModelSupport::getComposite(SMap,RI-10,"(-5:6:7)");
      // }
      else
	{
	  OutX=CC.getExclude();
      //  setCell("Inner", cellIndex);
	    cellName="Inner";
	}
      // System.addCell(MonteCarlo::Object(cellIndex++,Mat[i],0.0,Out+OutX));
      makeCell(cellName,System,cellIndex++,Mat[i],0.0,Out+OutX);

      RI+=10;
    }

  Out=ModelSupport::getComposite(SMap,RI-10,"5 -6 -7 ");
  
  addOuterSurf(Out);
  return;
}

std::string
LayeredBulkModule::getComposite(const std::string& surfList) const
  /*!
    Exposes local version of getComposite
    \param surfList :: surface list
    \return Composite string
  */
{
  return ModelSupport::getComposite(SMap,buildIndex,surfList);
}

void
LayeredBulkModule::createLinks()
  /*!
    Create all the linkes [OutGoing]
  */
{
  ELog::RegMethod RegA("LayeredBulkModule","createLinks");

  if (nLayer>1)
    {
      size_t index(0);
      for(size_t j=0;j<2;j++)
        {
	  const size_t i(nLayer-(j+1));
	  
	  FixedComp::setConnect
	    (index,Origin+COffset[i]-Z*depth[i],-Z);  // base
	  FixedComp::setConnect
	    (index+1,Origin+COffset[i]+Z*height[i],Z);  // top
	  FixedComp::setConnect
	    (index+2,Origin+COffset[i]+Y*radius[i],Y);   // outer point
	  FixedComp::setConnect
	    (index+3,Origin+COffset[i]-Y*radius[i],-Y);   // outer point
	  
	  const int RI(static_cast<int>(i)*10+buildIndex);
	  FixedComp::setLinkSurf(index,-SMap.realSurf(RI+5));
	  FixedComp::setLinkSurf(index+1,SMap.realSurf(RI+6));
	  FixedComp::setLinkSurf(index+2,SMap.realSurf(RI+7));
	  FixedComp::setLinkSurf(index+3,SMap.realSurf(RI+7));
	  FixedComp::setBridgeSurf(index+3,-SMap.realSurf(buildIndex+1));

	  index+=4;
	}

      FixedComp::setConnect(8,Origin+COffset[0]+Y*radius[0],-Y);
      FixedComp::setLinkSurf(8,-SMap.realSurf(buildIndex+7));
    }
  return;
}

void 
LayeredBulkModule::addFlightUnit(Simulation& System,
			  const attachSystem::FixedComp& FC)
  /*!
    Adds a flight unit based on an existing flight line
    it is effectively an extension. This method only works
    with a >=2 layer system.
    \param System :: simulation
    \param FC :: Flight component [uses link surf 2-5] 
  */
{
  ELog::RegMethod RegA("LayeredBulkModule","addFlightUnit");

  std::string Out;

  std::stringstream cx;
  cx<<" (";
  for(long int index=3;index<6;index++)
    cx<<FC.getLinkString(index)<<" : ";
  cx<<FC.getLinkString(6)<<" )";

  // AVOID INNER
  for(int i=1;i<static_cast<int>(nLayer);i++)
    {
      MonteCarlo::Object* OPtr=System.findObject(buildIndex+i+1);
      if (!OPtr)
	throw ColErr::InContainerError<int>(buildIndex+i+1,"layerCells");
      OPtr->addSurfString(cx.str());
    }
  // Now make internal surface
  cx.str("");
  for(long int index=3;index<7;index++)
    cx<<FC.getLinkString(-index)<<" ";

  Out=ModelSupport::getComposite(SMap,buildIndex,
				 buildIndex+10*static_cast<int>(nLayer-1),
				 " 7 -7M ");
  // Dividing surface ?
  System.addCell(MonteCarlo::Object(cellIndex++,0,0.0,Out+cx.str()));
  return;
}

void
LayeredBulkModule::createAll(Simulation& System,
		      const attachSystem::FixedComp& FC,
		      const attachSystem::ContainedComp& CC)
  /*!
    Generic function to create everything
    \param System :: Simulation item
    \param FC :: Central origin
    \param CC :: Central origin
  */
{
  ELog::RegMethod RegA("LayeredBulkModule","createAll");

  populate(System.getDataBase());
  createUnitVector(FC,0);
  createSurfaces();
  createLinks();
  createObjects(System,CC);
  insertObjects(System);              

  return;
}

}  // NAMESPACE essSystem
