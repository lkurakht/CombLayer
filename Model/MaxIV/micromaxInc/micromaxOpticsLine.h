/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   micromaxInc/micromaxOpticsLine.h
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>. 
 *
 ****************************************************************************/
#ifndef xraySystem_micromaxOpticsLine_h
#define xraySystem_micromaxOpticsLine_h

namespace insertSystem
{
  class insertPlate;
}

namespace tdcSystem
{
  class YagScreen;
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
  class PipeTube;
  class GateValveCube;
  class JawValveCube;
  class JawFlange;
  class DiffPumpXIADP03;
}

namespace xraySystem
{
  class BeamScrapper;
  class BremColl;
  class BremBlock;
  class BeamPair;
  class BremMonoColl;
  class CollTube;
  class CollUnit;
  class CooledScreen;
  class CRLTube;
  class CylGateValve;
  class DCMTank;
  class FourPortTube;
  class FlangeMount;
  class GaugeTube;
  class Mirror;
  class MLMono;
  class MonoBlockXstals;
  class RoundMonoShutter;
  class ShutterUnit;
  class SquareFMask;
  class IonGauge;
  class TriggerTube;
  class HPJaws;
  class BremTube;
  class ViewScreenTube;
  class PipeShield;
  class Table;
  
    
  /*!
    \class micromaxOpticsLine
    \version 1.0
    \author S. Ansell
    \date January 2019
    \brief Constructor for the micromax optics components
  */

class micromaxOpticsLine :
  public attachSystem::CopiedComp,
  public attachSystem::ContainedComp,
  public attachSystem::FixedOffset,
  public attachSystem::ExternalCut,
  public attachSystem::CellMap
{
 private:

  /// string for pre-insertion into mastercell:0
  std::shared_ptr<attachSystem::ContainedGroup> preInsert;
  /// construction space for main object
  attachSystem::BlockZone buildZone;
  int innerMat;                         ///< inner material if used

  /// Shared point to use for last component:
  std::shared_ptr<attachSystem::FixedComp> lastComp;

  /// Inital bellow
  std::shared_ptr<constructSystem::Bellows> pipeInit;
  /// vacuum trigger system
  std::shared_ptr<xraySystem::TriggerTube> triggerPipe;
  /// first ion pump+gate
  std::shared_ptr<xraySystem::CylGateValve> gateTubeA;
  /// Addaptor to connect from pump into point to diffuser
  std::shared_ptr<constructSystem::VacuumPipe> pipeA;
  /// bellow to collimator
  std::shared_ptr<constructSystem::Bellows> bellowA;
  /// Brem for collimator
  std::shared_ptr<xraySystem::SquareFMask> whiteCollA;
  /// bellow to collimator
  std::shared_ptr<constructSystem::Bellows> bellowB;
  /// Brem block tube
  std::shared_ptr<xraySystem::IonGauge> bremHolderA;
  /// first BremCollimator
  std::shared_ptr<xraySystem::BremBlock> bremCollA;
  /// Bellow exit
  std::shared_ptr<constructSystem::Bellows> bellowC;
  /// View Tube 
  std::shared_ptr<xraySystem::ViewScreenTube> viewTubeA;
  /// view screen
  std::shared_ptr<xraySystem::CooledScreen> cooledScreenA;
  /// Bellow exit
  std::shared_ptr<constructSystem::Bellows> bellowD;
  /// Attn Tube 
  std::shared_ptr<xraySystem::CollTube> attnTube;
  /// Attn Unit [internal]
  std::shared_ptr<xraySystem::CollUnit> attnUnit;
  /// Bellow exit
  std::shared_ptr<constructSystem::Bellows> bellowE;
  /// Table for diag table 
  std::shared_ptr<xraySystem::Table> tableA;

  /// H-res DMM mono vessel
  std::shared_ptr<xraySystem::DCMTank> dmmVessel;
  /// Mirror mono
  std::shared_ptr<xraySystem::MLMono> mlm;
  
  /// Bellow exit
  std::shared_ptr<constructSystem::Bellows> bellowF;
  /// Gate valve between monos
  std::shared_ptr<xraySystem::CylGateValve> gateTubeB;
  /// Bellow exit
  std::shared_ptr<constructSystem::Bellows> bellowG;


  /// H-res DCM mono vessel
  std::shared_ptr<xraySystem::DCMTank> dcmVessel;
  /// Crystal pair
  std::shared_ptr<xraySystem::MonoBlockXstals> mbXstals;

  /// Bellow exit
  std::shared_ptr<constructSystem::Bellows> bellowH;
  /// Brem block tube
  std::shared_ptr<constructSystem::VacuumPipe> pipeB;
  /// Gate valve between mono/diag2
  std::shared_ptr<xraySystem::CylGateValve> gateTubeC;


  /// BremTube (with heat trapping)
  std::shared_ptr<xraySystem::BremTube> monoBremTube;
  /// Pre-brem scrapper
  std::shared_ptr<xraySystem::BeamScrapper> bremScrapper;
  /// BremBlock
  std::shared_ptr<xraySystem::BremBlock> bremCollB;
  /// jaws
  std::shared_ptr<xraySystem::HPJaws> hpJawsA;
  /// Bellow exit
  std::shared_ptr<constructSystem::Bellows> bellowI;
  /// view screen tube
  std::shared_ptr<xraySystem::ViewScreenTube> viewTubeB;
  /// view screen
  std::shared_ptr<xraySystem::CooledScreen> cooledScreenB;
  /// Gate valve between diag2/CRL
  std::shared_ptr<xraySystem::CylGateValve> gateTubeD;
  /// Addaptor to CRL tube
  std::shared_ptr<constructSystem::VacuumPipe> crlPipeA;
  /// First CRL System  
  std::shared_ptr<xraySystem::CRLTube> crlTubeA;
  /// Mid  CRL pipe
  std::shared_ptr<constructSystem::VacuumPipe> crlPipeB;
  /// Mid  CRL pipe
  std::shared_ptr<constructSystem::VacuumPipe> crlPipeC;
  /// Second CRL System  
  std::shared_ptr<xraySystem::CRLTube> crlTubeB;
  /// End  CRL pipe
  std::shared_ptr<constructSystem::VacuumPipe> crlPipeD;
  /// Really long pipe
  std::shared_ptr<constructSystem::VacuumPipe> longPipeA;
  /// Really long pipe
  std::shared_ptr<constructSystem::VacuumPipe> longPipeB;
  /// Gate valve at end of really long pipe
  std::shared_ptr<xraySystem::CylGateValve> gateTubeE;
  /// Bellow exit
  std::shared_ptr<constructSystem::Bellows> bellowJ;
  /// view screen tube
  std::shared_ptr<xraySystem::ViewScreenTube> viewTubeC;
  /// view screen
  std::shared_ptr<xraySystem::CooledScreen> cooledScreenC;
  /// Bellow exit
  std::shared_ptr<constructSystem::Bellows> bellowK;
  /// jaws
  std::shared_ptr<xraySystem::HPJaws> hpJawsB;
  /// BremTube (with heat trapping)
  std::shared_ptr<xraySystem::FourPortTube> crlBremTube;
  /// BremBlock
  std::shared_ptr<xraySystem::BremBlock> bremCollC;
  /// BremBlock
  std::shared_ptr<constructSystem::Bellows> bellowL;  
  /// The main mono shutter
  std::shared_ptr<xraySystem::RoundMonoShutter> monoShutter;

  double outerLeft;    ///< Left Width for cut rectangle
  double outerRight;   ///< Right width for cut rectangle
  double outerTop;     ///< Top lift for cut rectangle

  void constructHDMM(Simulation&,const attachSystem::FixedComp&, 
		     const std::string&);
  void constructHDCM(Simulation&,const attachSystem::FixedComp&, 
		     const std::string&);
  void constructDiag2(Simulation&,const attachSystem::FixedComp&, 
		      const std::string&);
  void constructCRL(Simulation&,const attachSystem::FixedComp&, 
		      const std::string&);
  void constructDiag3(Simulation&,const attachSystem::FixedComp&, 
		      const std::string&);
  void constructMonoShutter(Simulation&,const attachSystem::FixedComp&, 
			    const std::string&);

  void populate(const FuncDataBase&);
  void createSurfaces();
  void buildObjects(Simulation&);
  void createLinks();
  
 public:
  
  micromaxOpticsLine(const std::string&);
  micromaxOpticsLine(const micromaxOpticsLine&);
  micromaxOpticsLine& operator=(const micromaxOpticsLine&);
  ~micromaxOpticsLine();

  /// Assignment to inner void
  void setInnerMat(const int M) {  innerMat=M; }
  /// Assignment to extra for first volume
  void setPreInsert
    (const std::shared_ptr<attachSystem::ContainedGroup>& A) { preInsert=A; }

  using FixedComp::createAll;
  void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int);

};

}

#endif
