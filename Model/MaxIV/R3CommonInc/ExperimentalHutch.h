/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   R3CommonInc/ExperimentalHutch.h
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
#ifndef xraySystem_ExperimentalHutch_h
#define xraySystem_ExperimentalHutch_h

class Simulation;

namespace xraySystem
{
  class PortChicane;
  
/*!
  \class ExperimentalHutch
  \version 1.0
  \author S. Ansell
  \date January 2018
  \brief ExperimentalHutch unit  

  Built around the central beam axis
*/

class ExperimentalHutch :
  public attachSystem::FixedRotate,
  public attachSystem::ContainedComp,
  public attachSystem::ExternalCut,
  public attachSystem::CellMap,
  public attachSystem::SurfMap
{
 private:
  
  double height;                ///< void height to roof (from origin)
  double length;                ///< void out side width
  double ringWidth;             ///< void flat part to ring
  double outWidth;              ///< out side width

  double cornerAngle;           ///< angle at corner
  double cornerLength;          ///< length to corner

  double innerThick;            ///< Inner wall/roof skin
  double pbWallThick;           ///< Thickness of lead in walls
  double pbFrontThick;          ///< Thickness of lead in front plate(if used)
  double pbBackThick;           ///< Thickness of lead in back plate
  double pbRoofThick;           ///< Thickness of lead in Roof
  double outerThick;            ///< Outer wall/roof skin

  double fHoleRadius;            ///< Radius of front hole (if used)
  double fHoleXStep;             ///< X step offset
  double fHoleZStep;             ///< Z step offset

  std::vector<Geometry::Vec3D> holeOffset;  ///< hole offsets [y ignored]
  std::vector<double> holeRadius;           ///< hole radii
  
  double innerOutVoid;          ///< Extension for inner void space (side)
  double outerOutVoid;          ///< Extension for outer void space (side)
  double frontVoid;             ///< Extension for inner front void space
  double backVoid;              ///< Extension for inner back void space
  double outerBackVoid;         ///< Extension for outer back void space
  
  std::string forkWall;         ///< Wall for forklift [only one allowed]
  double forkXStep;             ///< Step across beamline for forklift hole
  double forkYStep;             ///< Step down beamline for forklift hole
  double forkLength;            ///< length of units
  double forkHeight;            ///< height of unit
  std::vector<double> fZStep;   ///< step of units
  
  int voidMat;                  ///< Void material [air]
  int skinMat;                  ///< Fe layer material for walls
  int pbMat;                    ///< pb layer material for walls

  /// Chicanes 
  std::vector<std::shared_ptr<PortChicane>> PChicane;  

  forkHoles forks;              ///< Forklift holes if made
  
  void populate(const FuncDataBase&);
  void createSurfaces();
  void createObjects(Simulation&);
  void createLinks();

  void createChicane(Simulation&);
  void createForkCut(Simulation&);
  
 public:

  ExperimentalHutch(const std::string&);
  ExperimentalHutch(const ExperimentalHutch&);
  ExperimentalHutch& operator=(const ExperimentalHutch&);
  virtual ~ExperimentalHutch();

  /// accessor to void mat
  int getInnerMat() const { return voidMat; }

  const PortChicane* getPortItem(const size_t) const;
  
  void splitChicane(Simulation& System,const size_t,const size_t);
  using FixedComp::createAll;
  virtual void createAll(Simulation&,
			 const attachSystem::FixedComp&,
			 const long int);

};

}

#endif
 
