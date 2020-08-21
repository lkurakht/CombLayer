/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   LinacInc/Segment47.h
 *
 * Copyright (c) 2004-2020 by Konstantin Batkov
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
#ifndef tdcSystem_Segment47_h
#define tdcSystem_Segment47_h

namespace tdcSystem
{
  /*!
    \class Segment47
    \version 1.0
    \author K. Batkov
    \date July 2020
    \brief SPF segment 47
  */

class Segment47 :
  public TDCsegment
{
 private:

  std::unique_ptr<attachSystem::InnerZone> IZThin;       ///< Extra limited zone
  
  std::shared_ptr<constructSystem::VacuumPipe> pipeA; // #1
  std::shared_ptr<constructSystem::BlankTube> prismaChamberA; ///< #2 and #3
  std::shared_ptr<constructSystem::PipeTube> mirrorChamberA; ///< #4
  std::shared_ptr<constructSystem::VacuumPipe> pipeB; // #5
  std::shared_ptr<constructSystem::PipeTube> mirrorChamberB; ///< #4
  std::shared_ptr<constructSystem::VacuumPipe> pipeC; // #5
  std::shared_ptr<constructSystem::PipeTube> mirrorChamberC; ///< #4
  std::shared_ptr<constructSystem::VacuumPipe> pipeD; // #6
  std::shared_ptr<xraySystem::CylGateValve> gateA;    // #7
  std::shared_ptr<constructSystem::Bellows> bellowA;  // #8
  std::shared_ptr<constructSystem::VacuumPipe> pipeE; // #6

  void createSplitInnerZone(Simulation&);
  
  void buildObjects(Simulation&);
  void createLinks();

 public:

  Segment47(const std::string&);
  Segment47(const Segment47&);
  Segment47& operator=(const Segment47&);
  ~Segment47();

  using FixedComp::createAll;
  void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int);

};

}

#endif
