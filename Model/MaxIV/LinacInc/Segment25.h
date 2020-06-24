/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   LinacInc/Segment25.h
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
#ifndef tdcSystem_Segment25_h
#define tdcSystem_Segment25_h

namespace constructSystem
{
 class Bellows;
 class VacuumPipe;
}

namespace tdcSystem
{
  class FlatPipe;
  class TriPipe;
  class SixPortTube;
  class MultiPipe;
  class DipoleDIBMag;
  class YagUnit;
  class YagScreen;
  

  /*!
    \class Segment25
    \version 1.0
    \author S. Ansell
    \date June 2020
    \brief Dividing segment in the TDC from the linac
  */

class Segment25 :
  public TDCsegment
{
 private:

  std::unique_ptr<attachSystem::InnerZone> IZTop;        ///< Flat inner zone
  std::unique_ptr<attachSystem::InnerZone> IZMid;        ///< Mid inner zone
  std::unique_ptr<attachSystem::InnerZone> IZLower;      ///< Lower inner zone
  
  /// first pipe
  std::shared_ptr<constructSystem::Bellows> bellowA;
  /// first pipe
  std::shared_ptr<tdcSystem::TriPipe> triPipeA;

  /// first  dipole
  std::shared_ptr<tdcSystem::DipoleDIBMag> dipoleA;

  /// Join pipe
  std::shared_ptr<constructSystem::VacuumPipe> pipeB;

  /// multi-way
  std::shared_ptr<tdcSystem::SixPortTube> sixPortA;

  /// MultiPipe
  std::shared_ptr<tdcSystem::MultiPipe> multiPipe;
  
  /// Exit bellows
  std::shared_ptr<constructSystem::Bellows> bellowAA;
  std::shared_ptr<constructSystem::Bellows> bellowBA;
  std::shared_ptr<constructSystem::Bellows> bellowCA;

  /// Join pipe 
  std::shared_ptr<constructSystem::VacuumPipe> pipeAA;
  std::shared_ptr<constructSystem::VacuumPipe> pipeBA;
  std::shared_ptr<constructSystem::VacuumPipe> pipeCA;

  /// Connect bellows
  std::shared_ptr<constructSystem::Bellows> bellowAB;
  std::shared_ptr<constructSystem::Bellows> bellowBB;
  std::shared_ptr<constructSystem::Bellows> bellowCB;


  /// Double yag screen
  std::shared_ptr<tdcSystem::YagUnit> yagUnitA;
  std::shared_ptr<tdcSystem::YagUnit> yagUnitB;

  std::shared_ptr<tdcSystem::YagScreen> yagScreenA;
  std::shared_ptr<tdcSystem::YagScreen> yagScreenB;

  /// Exit pipe 
  std::shared_ptr<constructSystem::VacuumPipe> pipeAB;
  std::shared_ptr<constructSystem::VacuumPipe> pipeBB;
  std::shared_ptr<constructSystem::VacuumPipe> pipeCB;


  void buildObjects(Simulation&);
  void createLinks();

  void createSplitInnerZone(Simulation&);
  
 public:

  Segment25(const std::string&);
  Segment25(const Segment25&);
  Segment25& operator=(const Segment25&);
  ~Segment25();


  using FixedComp::createAll;
  virtual void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int);

};

}

#endif
