/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   constructInc/FlangePlate.h
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
#ifndef constructSystem_FlangePlate_h
#define constructSystem_FlangePlate_h

class Simulation;

namespace constructSystem
{
  
/*!
  \class FlangePlate
  \version 1.0
  \author S. Ansell
  \date January 2018
  \brief FlangePlate for capping ports/vac-tubes etc
*/

class FlangePlate :
  public attachSystem::FixedRotate,
  public attachSystem::ContainedComp,
  public attachSystem::CellMap,
  public attachSystem::SurfMap,
  public attachSystem::FrontBackCut
{
 private:

  double innerRadius;           ///< Inner window (or void) if present
  double innerThick;            ///< Inner thickness if present
  double flangeRadius;          ///< void radius [inner] 
  double flangeLength;          ///< Flange thickness

  int voidMat;                  ///< Void materia;
  int windowMat;                 ///< inner (Void) materia;
  int flangeMat;                ///< Main material  
  
  void populate(const FuncDataBase&);
  void createSurfaces();
  void createObjects(Simulation&);
  void createLinks();

 public:

  FlangePlate(const std::string&);
  FlangePlate(const FlangePlate&);
  FlangePlate& operator=(const FlangePlate&);
  virtual ~FlangePlate();

  using FixedComp::createAll;
  void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int);

};

}

#endif
 
