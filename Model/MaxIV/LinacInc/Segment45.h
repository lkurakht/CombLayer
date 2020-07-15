/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   LinacInc/Segment45.h
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
#ifndef tdcSystem_Segment45_h
#define tdcSystem_Segment45_h

namespace tdcSystem
{
  /*!
    \class Segment45
    \version 1.0
    \author K. Batkov
    \date July 2020
    \brief SPF segment 45
  */

class Segment45 :
  public TDCsegment
{
 private:

  std::shared_ptr<tdcSystem::CeramicGap> ceramic;     // #1 ceramic gap
  std::shared_ptr<constructSystem::VacuumPipe> pipeA; // #2
  std::shared_ptr<tdcSystem::YagUnitBig> yagUnit;     // #3
  std::shared_ptr<tdcSystem::YagScreen> yagScreen;    // #3
  std::shared_ptr<constructSystem::VacuumPipe> pipeB; // #5

  void buildObjects(Simulation&);
  void createLinks();

 public:

  Segment45(const std::string&);
  Segment45(const Segment45&);
  Segment45& operator=(const Segment45&);
  ~Segment45();

  using FixedComp::createAll;
  void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int);

};

}

#endif
