/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   speciesInc/speciesOpticsBeamline.h
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
#ifndef xraySystem_speciesOpticsBeamline_h
#define xraySystem_speciesOpticsBeamline_h

namespace insertSystem
{
  class insertPlate;
}

namespace constructSystem
{
  class SupplyPipe;
  class CrossPipe;
  class VacuumPipe;
  class Bellows;
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
  class GrateMonoBox;
  class GratingMono;
  class BeamMount;
  class Mirror;
  class PipeShield;
  class JawValve;
  class TankMonoVessel;
  class TwinPipe;
    
  /*!
    \class speciesOpticsBeamline
    \version 1.0
    \author S. Ansell
    \date January 2018
    \brief General constructor for the xray system
  */

class speciesOpticsBeamline :
  public attachSystem::CopiedComp,
  public attachSystem::ContainedComp,
  public attachSystem::FixedOffset,
  public attachSystem::ExternalCut,
  public attachSystem::CellMap
{
 private:

  /// System for building a divided inner
  attachSystem::InnerZone buildZone;
  
  /// Shared point to use for last component:
  std::shared_ptr<attachSystem::FixedComp> lastComp;

  /// Bellows to ionPump
  std::shared_ptr<constructSystem::Bellows> bellowA;
  /// Real Ion pump (KF40) 24.4cm vertical
  std::shared_ptr<constructSystem::CrossPipe> ionPA;
  /// Gate block
  std::shared_ptr<constructSystem::PipeTube> gateTubeA;
  /// Bellow to first connect line
  std::shared_ptr<constructSystem::Bellows> bellowB;
  /// Front port of mirror box
  std::shared_ptr<constructSystem::VacuumPipe> pipeA;
  /// M1 - Mirror box
  std::shared_ptr<constructSystem::PipeTube> M1Tube;
  /// M1 - Mirror
  std::shared_ptr<xraySystem::Mirror> M1Mirror;
  /// Bellow to first connect line
  std::shared_ptr<constructSystem::Bellows> bellowC;
    /// Pipe to some stuff
  std::shared_ptr<constructSystem::VacuumPipe> pipeB;
  /// First screen
  std::shared_ptr<xraySystem::PipeShield> screenA;
  /// Gate valve [after screen]
  std::shared_ptr<constructSystem::GateValve> gateA;
  /// Small Pipe to slit section
  std::shared_ptr<constructSystem::VacuumPipe> pipeC;
  /// Small Pipe to slit section
  std::shared_ptr<constructSystem::PipeTube> slitTube;
  /// Jaws for the slit tube (x/z pair)
  std::array<std::shared_ptr<xraySystem::BeamMount>,4> jaws;
  /// Small Pipe to gate-valve
  std::shared_ptr<constructSystem::VacuumPipe> pipeD;
  /// First screen
  std::shared_ptr<xraySystem::PipeShield> screenB;
  /// First screen
  std::shared_ptr<xraySystem::TankMonoVessel> monoVessel;


  double outerRadius;           ///< Radius for inner void
  

  int constructDivideCell(Simulation&,const bool,
			   const attachSystem::FixedComp&,
			   const long int,
			   const attachSystem::FixedComp&,
			   const long int);

  int createDoubleVoidUnit(Simulation&,
			   HeadRule&,
			   const attachSystem::FixedComp&,
			   const long int);
  
  void insertFlanges(Simulation&,const constructSystem::PipeTube&);
  

  void buildFrontTable(Simulation&,MonteCarlo::Object*,
		       const attachSystem::FixedComp&,const long int);
  void buildM1Mirror(Simulation&,MonteCarlo::Object*,
		     const attachSystem::FixedComp&,const long int);
  void buildM3Mirror(Simulation&,MonteCarlo::Object*,
		     const attachSystem::FixedComp&,const long int);
  void buildMono(Simulation&,MonteCarlo::Object*,
		 const attachSystem::FixedComp&,const long int);
  void buildSlitPackage(Simulation&,MonteCarlo::Object*,
		       const attachSystem::FixedComp&,const long int);
  void buildSplitter(Simulation&,MonteCarlo::Object*,MonteCarlo::Object*,
		     const attachSystem::FixedComp&,const long int);
  
  void populate(const FuncDataBase&);
  void createUnitVector(const attachSystem::FixedComp&,
			const long int);
  void createSurfaces();
  void buildObjects(Simulation&);
  void createLinks();
  
 public:
  
  speciesOpticsBeamline(const std::string&);
  speciesOpticsBeamline(const speciesOpticsBeamline&);
  speciesOpticsBeamline& operator=(const speciesOpticsBeamline&);
  ~speciesOpticsBeamline();

  void buildOutGoingPipes(Simulation&,const int,const int,
			  const std::vector<int>&);
  
  void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int);

};

}

#endif
