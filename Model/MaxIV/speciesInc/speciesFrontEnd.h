/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   speciesInc/speciesFrontEnd.h
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
#ifndef xraySystem_speciesFrontEnd_h
#define xraySystem_speciesFrontEnd_h

namespace insertSystem
{
  class insertCylinder;
}

namespace constructSystem
{
  class Bellows;
  class CrossPipe;
  class GateValveCube;
  class OffsetFlangePipe;
  class portItem;
  class PipeTube;
  class PortTube;
  class SupplyPipe;
  class VacuumBox;
  class VacuumPipe; 
}



/*!
  \namespace xraySystem
  \brief General xray optics system
  \version 1.0
  \date January 2018
  \author S. Ansell
*/

namespace xraySystem
{
  class BremBlock;
  class BeamMount;
  class FlangeMount;
  class HeatDump;
  class LCollimator;
  class SquareFMask;
  class UTubePipe;
  class Undulator;

    
  /*!
    \class speciesFrontEnd
    \version 1.0
    \author S. Ansell
    \date March 2018
    \brief General constructor front end optics
  */

class speciesFrontEnd :  public R1FrontEnd
{
 private:

  /// Pipe in undulator
  std::shared_ptr<xraySystem::UTubePipe> undulatorPipe;
  /// Undulator in vacuum box
  std::shared_ptr<xraySystem::Undulator> undulator;

  virtual const attachSystem::FixedComp&
    buildUndulator(Simulation&,
		   const attachSystem::FixedComp&,
		   const std::string&);
			      
  virtual void createLinks();
  
 public:
  
  speciesFrontEnd(const std::string&);
  speciesFrontEnd(const speciesFrontEnd&);
  speciesFrontEnd& operator=(const speciesFrontEnd&);
  virtual ~speciesFrontEnd();

};

}

#endif
