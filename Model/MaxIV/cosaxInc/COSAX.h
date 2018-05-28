/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   balderInc/COSAX.h
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
#ifndef xraySystem_COSAX_h
#define xraySystem_COSAX_h

namespace constructSystem
{
  class SupplyPipe;
  class CrossPipe;
  class VacuumPipe;
  class Bellows;
  class LeadPipe;
  class VacuumBox;
  class portItem;
  class PortTube;
  class GateValve;
  class JawValve;
    
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
  class OpticsHutch;
  class ExperimentalHutch;
  class cosaxOpticsLine;
  class FrontEndCave;
  class ConnectZone;
  class FrontEnd;
  
  
  /*!
    \class COSAX
    \version 1.0
    \author S. Ansell
    \date January 2018
    \brief General constructor for the xray system
  */

class COSAX : public attachSystem::CopiedComp
{
 private:

  std::string startPoint;       ///< Start point
  std::string stopPoint;        ///< End point
  /// Front end cave volume
  std::shared_ptr<FrontEndCave> frontCave;

  /// the components in the front end
  std::shared_ptr<FrontEnd> frontBeam;
  
  /// Pipe joining frontend to optics hut
  std::shared_ptr<constructSystem::VacuumPipe> joinPipe;

  /// Optics hutch
  std::shared_ptr<OpticsHutch> opticsHut;
  /// Optics beamlines 
  std::shared_ptr<cosaxOpticsLine> opticsBeam;

  /// Pipe joining frontend to optics hut
  std::shared_ptr<constructSystem::VacuumPipe> joinPipeB;

 public:
  
  COSAX(const std::string&);
  COSAX(const COSAX&);
  COSAX& operator=(const COSAX&);
  ~COSAX();
  
  void build(Simulation&,const attachSystem::FixedComp&,
	     const long int);

};

}

#endif
