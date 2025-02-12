/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   construct/CrossPipe.cxx
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
#include <memory>
#include <array>

#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "Vec3D.h"
#include "surfRegister.h"
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
#include "FixedOffset.h"
#include "ContainedComp.h"
#include "BaseMap.h"
#include "CellMap.h"
#include "ExternalCut.h"
#include "FrontBackCut.h"
#include "SurfMap.h"

#include "CrossPipe.h" 

namespace constructSystem
{

CrossPipe::CrossPipe(const std::string& Key) : 
  attachSystem::FixedOffset(Key,6),
  attachSystem::ContainedComp(),attachSystem::CellMap(),
  attachSystem::SurfMap(),attachSystem::FrontBackCut()
  /*!
    Constructor BUT ALL variable are left unpopulated.
    \param Key :: KeyName
  */
{
  nameSideIndex(4,"baseFlange");
  nameSideIndex(5,"topFlange");
}

CrossPipe::CrossPipe(const CrossPipe& A) : 
  attachSystem::FixedOffset(A),attachSystem::ContainedComp(A),
  attachSystem::CellMap(A),attachSystem::SurfMap(A),
  attachSystem::FrontBackCut(A),
  horrRadius(A.horrRadius),
  vertRadius(A.vertRadius),height(A.height),depth(A.depth),
  frontLength(A.frontLength),backLength(A.backLength),
  feThick(A.feThick),topPlate(A.topPlate),basePlate(A.basePlate),
  flangeRadius(A.flangeRadius),flangeLength(A.flangeLength),
  voidMat(A.voidMat),feMat(A.feMat)
  /*!
    Copy constructor
    \param A :: CrossPipe to copy
  */
{}

CrossPipe&
CrossPipe::operator=(const CrossPipe& A)
  /*!
    Assignment operator
    \param A :: CrossPipe to copy
    \return *this
  */
{
  if (this!=&A)
    {
      attachSystem::FixedOffset::operator=(A);
      attachSystem::ContainedComp::operator=(A);
      attachSystem::CellMap::operator=(A);
      attachSystem::SurfMap::operator=(A);
      attachSystem::FrontBackCut::operator=(A);
      horrRadius=A.horrRadius;
      vertRadius=A.vertRadius;
      height=A.height;
      depth=A.depth;
      frontLength=A.frontLength;
      backLength=A.backLength;
      feThick=A.feThick;
      topPlate=A.topPlate;
      basePlate=A.basePlate;
      flangeRadius=A.flangeRadius;
      flangeLength=A.flangeLength;
      voidMat=A.voidMat;
      feMat=A.feMat;
    }
  return *this;
}

CrossPipe::~CrossPipe() 
  /*!
    Destructor
  */
{}

void
CrossPipe::populate(const FuncDataBase& Control)
  /*!
    Populate all the variables
    \param Control :: DataBase of variables
  */
{
  ELog::RegMethod RegA("CrossPipe","populate");
  
  FixedOffset::populate(Control);

  // Void + Fe special:
  horrRadius=Control.EvalVar<double>(keyName+"HorrRadius");
  vertRadius=Control.EvalVar<double>(keyName+"VertRadius");
  height=Control.EvalVar<double>(keyName+"Height");
  depth=Control.EvalVar<double>(keyName+"Depth");

  const double length=Control.EvalDefVar<double>(keyName+"Length",0.0);
  frontLength=Control.EvalDefVar<double>(keyName+"FrontLength",length/2.0);
  backLength=Control.EvalDefVar<double>(keyName+"BackLength",length/2.0);

  feThick=Control.EvalVar<double>(keyName+"FeThick");
  topPlate=Control.EvalVar<double>(keyName+"TopPlate");
  basePlate=Control.EvalVar<double>(keyName+"BasePlate");
  
  flangeRadius=Control.EvalDefVar<double>(keyName+"FlangeRadius",-1.0);
  flangeLength=Control.EvalDefVar<double>(keyName+"FlangeLength",0.0);
  
  voidMat=ModelSupport::EvalDefMat(Control,keyName+"VoidMat",0);
  feMat=ModelSupport::EvalMat<int>(Control,keyName+"FeMat");
  plateMat=ModelSupport::EvalDefMat(Control,keyName+"PlateMat",feMat);

  return;
}

void
CrossPipe::createUnitVector(const attachSystem::FixedComp& FC,
                             const long int sideIndex)
  /*!
    Create the unit vectors
    \param FC :: Fixed component to link to
    \param sideIndex :: Link point and direction [0 for origin]
  */
{
  ELog::RegMethod RegA("CrossPipe","createUnitVector");

  FixedComp::createUnitVector(FC,sideIndex);
  yStep+=(frontLength+backLength)/2.0;
  applyOffset();

  return;
}


void
CrossPipe::createSurfaces()
  /*!
    Create the surfaces
  */
{
  ELog::RegMethod RegA("CrossPipe","createSurfaces");
  
  // middle of the flange
  //  const double midFlange((length-flangeLength)/2.0);
  
  // Inner void
  if (frontActive())
    FrontBackCut::getShiftedFront(SMap,buildIndex+101,Y,flangeLength);
  else
    {
      ModelSupport::buildPlane(SMap,buildIndex+1,Origin-Y*frontLength,Y);
      ModelSupport::buildPlane
	(SMap,buildIndex+101,Origin-Y*(frontLength-flangeLength),Y);
      FrontBackCut::setFront(SMap.realSurf(buildIndex+1));
    }
  
  // Inner void
  if (backActive())
    // create surface 102:
    FrontBackCut::getShiftedFront(SMap,buildIndex+102,Y,-flangeLength);
  else
    {
      ModelSupport::buildPlane(SMap,buildIndex+2,Origin+Y*backLength,Y);
      ModelSupport::buildPlane
	(SMap,buildIndex+102,Origin+Y*(backLength-flangeLength),Y);
      FrontBackCut::setBack(-SMap.realSurf(buildIndex+2));
    }

  
  // MAIN SURFACES axial:
  ModelSupport::buildCylinder(SMap,buildIndex+7,Origin,Y,horrRadius);
  ModelSupport::buildCylinder(SMap,buildIndex+17,Origin,Y,horrRadius+feThick);

  // FLANGE SURFACES:
  if (flangeRadius>horrRadius && flangeLength>Geometry::zeroTol)
    ModelSupport::buildCylinder(SMap,buildIndex+107,Origin,Y,flangeRadius);

  // Secondary SURFACES:

  ModelSupport::buildCylinder(SMap,buildIndex+207,Origin,Z,vertRadius);
  ModelSupport::buildCylinder(SMap,buildIndex+217,Origin,Z,vertRadius+feThick);

  // top plates
  ModelSupport::buildPlane(SMap,buildIndex+206,Origin+Z*height,Z);
  ModelSupport::buildPlane(SMap,buildIndex+216,Origin+Z*(height+topPlate),Z);

  // base plates
  ModelSupport::buildPlane(SMap,buildIndex+205,Origin-Z*depth,Z);
  ModelSupport::buildPlane(SMap,buildIndex+215,Origin-Z*(depth+basePlate),Z);

  return;
}

void
CrossPipe::createObjects(Simulation& System)
  /*!
    Adds the vacuum box
    \param System :: Simulation to create objects in
  */
{
  ELog::RegMethod RegA("CrossPipe","createObjects");

  std::string Out;
  
  const std::string frontStr=frontRule();
  const std::string backStr=backRule();
  
  // Void [want a single void]
  Out=ModelSupport::getComposite(SMap,buildIndex," (-7 : -207) 205 -206  ");
  System.addCell(MonteCarlo::Object(cellIndex++,voidMat,0.0,Out+frontStr+backStr));
  addCell("Void",cellIndex-1);

  // Main steel pipe
  Out=ModelSupport::getComposite(SMap,buildIndex," -17 7 207 ");
  System.addCell(MonteCarlo::Object(cellIndex++,feMat,0.0,Out+frontStr+backStr));
  addCell("Pipe",cellIndex-1);

  // Vert steel pipe
  Out=ModelSupport::getComposite(SMap,buildIndex," 17 -217 207 205 -206 ");
  System.addCell(MonteCarlo::Object(cellIndex++,feMat,0.0,Out));
  addCell("Pipe",cellIndex-1);

  // BasePlate
  Out=ModelSupport::getComposite(SMap,buildIndex," -217 215 -205 ");
  System.addCell(MonteCarlo::Object(cellIndex++,feMat,0.0,Out));
  addCell("BasePlate",cellIndex-1);

  // BasePlate
  Out=ModelSupport::getComposite(SMap,buildIndex," -217 206 -216 ");
  System.addCell(MonteCarlo::Object(cellIndex++,feMat,0.0,Out));
  addCell("TopPlate",cellIndex-1);
  

  if (flangeRadius>Geometry::zeroTol && flangeLength>Geometry::zeroTol)
    {
      Out=ModelSupport::getComposite(SMap,buildIndex," 17 -107 -101 ");
      System.addCell(MonteCarlo::Object(cellIndex++,feMat,0.0,Out+frontStr));
      addCell("Flange",cellIndex-1);

      Out=ModelSupport::getComposite(SMap,buildIndex," 17 -107 102 ");
      System.addCell(MonteCarlo::Object(cellIndex++,feMat,0.0,Out+backStr));
      addCell("Flange",cellIndex-1);

      Out=ModelSupport::getComposite(SMap,buildIndex," 17 -107 101 -102 217 ");
      System.addCell(MonteCarlo::Object(cellIndex++,0,0.0,Out));
      addCell("FlangeVoid",cellIndex-1);
      Out=ModelSupport::getComposite(SMap,buildIndex," (-107 : -217) 215 -216  ");
    }
  else
    Out=ModelSupport::getComposite(SMap,buildIndex," (-17 : -217) 215 -216  ");


  addOuterSurf(Out+frontStr+backStr);

  return;
}
  
void
CrossPipe::createLinks()
  /*!
    Determines the link point on the outgoing plane.
    It must follow the beamline, but exit at the plane
  */
{
  ELog::RegMethod RegA("CrossPipe","createLinks");

  //stufff for intersection


  FrontBackCut::createLinks(*this,Origin,Y);  //front and back

  FixedComp::setConnect(2,Origin-X*horrRadius,-X);
  FixedComp::setConnect(3,Origin+X*horrRadius,X);
  FixedComp::setConnect(4,Origin-Z*depth,-Z);
  FixedComp::setConnect(5,Origin+Z*height,Z);
  
  FixedComp::setLinkSurf(2,SMap.realSurf(buildIndex+7));
  FixedComp::setLinkSurf(3,SMap.realSurf(buildIndex+7));
  FixedComp::setLinkSurf(4,SMap.realSurf(buildIndex+5));
  FixedComp::setLinkSurf(5,SMap.realSurf(buildIndex+6));

  return;
}
  
  
void
CrossPipe::createAll(Simulation& System,
		      const attachSystem::FixedComp& FC,
		      const long int FIndex)
 /*!
    Generic function to create everything
    \param System :: Simulation item
    \param FC :: FixedComp
    \param FIndex :: Fixed Index
  */
{
  ELog::RegMethod RegA("CrossPipe","createAll(FC)");

  populate(System.getDataBase());
  createUnitVector(FC,FIndex);
  createSurfaces();    
  createObjects(System);
  createLinks();
  insertObjects(System);   
  
  return;
}
  
}  // NAMESPACE constructSystem
