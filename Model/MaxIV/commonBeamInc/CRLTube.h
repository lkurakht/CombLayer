/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   commonBeamInc/CRLTube.h
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
#ifndef xraySystem_CRLTube_h
#define xraySystem_CRLTube_h

class Simulation;

namespace xraySystem
{

/*!
  \class CRLTube
  \version 1.0
  \author Stuart Ansell
  \date February 2021
  \brief Compound Refractive Lens system
*/

class CRLTube :
  public attachSystem::ContainedGroup,
  public attachSystem::FixedRotate,
  public attachSystem::CellMap,
  public attachSystem::SurfMap,
  public attachSystem::ExternalCut
{
 private:

  bool inBeam;                   ///< Object in beam
  double zLift;                  ///< zLift distance

  double length;                 ///< Main box length
  double width;                  ///< Main box width
  double height;                 ///< Main box height

  double innerLength;            ///< Main box width
  double secondary;              ///< construct inner frame secondary
  
  double captureWidth;           ///< Void around main tube
  double captureHeight;          ///< Void around main tube
  double captureDepth;           ///< void in capture space
  
  double supportWidth;           ///< support width
  double supportHeight;          ///< support height (+Z)
  double supportDepth;           ///< support depth  (-)

  double magWidth;               ///< Magnet Width
  double magHeight;              ///< Magnet Height
  double magDepth;               ///< Magnet Depth

  size_t lensNSize;              ///< Number lens
  double lensLength;             ///< lens total length [unit]
  double lensMidGap;             ///< lens mid gap (with material)
  double lensRadius;             ///< lens Curve radius (focus)
  double lensOuterRadius;        ///< lens Outer radius 
  double lensSupportRadius;       ///< lens Support radius 

  double innerRadius;            ///< inner pipe radius
  double innerThick;             ///< inner pipe thickness
  
  double viewRadius;             ///< cut in main box
  
  double portLength;             ///< Port length
  double portRadius;             ///< port Radius 
  double portThick;              ///< thickness of pipe

  double flangeRadius;           ///< Flange radius
  double flangeLength;           ///< Flange thickness

  int voidMat;               ///< Void Material
  int lensMat;               ///< Lens Material
  int lensOuterMat;          ///< Lens Outer Material
  int pipeMat;               ///< Pipe Material
  int mainMat;               ///< Support Material
  int magnetMat;             ///< Magnet material
  int flangeMat;             ///< Flange material

  void populate(const FuncDataBase&);
  void createSurfaces();
  void createObjects(Simulation&);
  void createLinks();

 public:

  CRLTube(const std::string&);
  CRLTube(const CRLTube&);
  CRLTube& operator=(const CRLTube&);
  virtual ~CRLTube();

  using FixedComp::createAll;
  void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int);

};

}

#endif


