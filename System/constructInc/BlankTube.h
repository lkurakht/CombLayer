/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   constructInc/BlankTube.h
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
#ifndef constructSystem_BlankTube_h
#define constructSystem_BlankTube_h

class Simulation;

namespace constructSystem
{
  
/*!
  \class BlankTube
  \version 1.0
  \author S. Ansell
  \date January 2018
  \brief BlankTube unit  
*/

class BlankTube :
  public VirtualTube
{
 protected:
  
  double flangeRadius;        ///< Joining Flange radius
  double flangeLength;        ///< Joining Flange length
  double flangeCapThick;       ///< Thickness of Flange cap if present
  double blankThick;           ///< Thickness of blank cap 
  
  
  virtual void populate(const FuncDataBase&);
  virtual void createSurfaces();
  virtual void createObjects(Simulation&);
  virtual void createLinks();

  std::string makeOuterVoid(Simulation&);

 public:

  BlankTube(const std::string&);
  BlankTube(const BlankTube&);
  BlankTube& operator=(const BlankTube&);
  virtual ~BlankTube();

  using VirtualTube::createPorts;
  virtual void createPorts(Simulation&);
  
      
};

}

#endif
 
