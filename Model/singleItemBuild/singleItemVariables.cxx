/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   singleItemBuild/singleItemVariables.cxx
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include <complex>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <memory>

#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "Vec3D.h"
#include "Code.h"
#include "varList.h"
#include "FuncDataBase.h"

#include "CFFlanges.h"
#include "CryoGenerator.h"
#include "BladeGenerator.h"
#include "PipeGenerator.h"
#include "RectPipeGenerator.h"
#include "TwinBaseGenerator.h"
#include "TwinGenerator.h"
#include "TwinFlatGenerator.h"
#include "ChopperGenerator.h"
#include "DipoleGenerator.h"
#include "DipoleExtractGenerator.h"
#include "QuadrupoleGenerator.h"
#include "LinacQuadGenerator.h"
#include "LinacSexuGenerator.h"
#include "SexupoleGenerator.h"
#include "OctupoleGenerator.h"
#include "EPSeparatorGenerator.h"
#include "EPCombineGenerator.h"
#include "PreDipoleGenerator.h"
#include "DipoleChamberGenerator.h"
#include "DipoleSndBendGenerator.h"
#include "R3ChokeChamberGenerator.h"
#include "MagnetM1Generator.h"
#include "MagnetBlockGenerator.h"
#include "CorrectorMagGenerator.h"
#include "QuadUnitGenerator.h"
#include "CurveMagGenerator.h"
#include "CylGateValveGenerator.h"
#include "GateValveGenerator.h"
#include "DipoleDIBMagGenerator.h"
#include "EArrivalMonGenerator.h"
#include "StriplineBPMGenerator.h"
#include "ButtonBPMGenerator.h"
#include "CeramicGapGenerator.h"
#include "BeamDividerGenerator.h"
#include "EBeamStopGenerator.h"
#include "ScrapperGenerator.h"
#include "FlatPipeGenerator.h"
#include "SixPortGenerator.h"
#include "CrossWayGenerator.h"
#include "GaugeGenerator.h"
#include "PrismaChamberGenerator.h"
#include "TriPipeGenerator.h"
#include "TriGroupGenerator.h"
#include "subPipeUnit.h"
#include "MultiPipeGenerator.h"
#include "YagScreenGenerator.h"
#include "YagUnitGenerator.h"
#include "YagUnitBigGenerator.h"
#include "TWCavityGenerator.h"
#include "UndVacGenerator.h"
#include "FMUndulatorGenerator.h"
#include "CollGenerator.h"
#include "SqrFMaskGenerator.h"
#include "SplitPipeGenerator.h"
#include "BellowGenerator.h"
#include "PipeTubeGenerator.h"
#include "PortTubeGenerator.h"
#include "PortItemGenerator.h"
#include "JawFlangeGenerator.h"
#include "CleaningMagnetGenerator.h"
#include "IonPTubeGenerator.h"

namespace setVariable
{


void
SingleItemVariables(FuncDataBase& Control)
  /*!
    Function to set the control variables and constants
    -- This version is for ESS ()
    \param Control :: Function data base to add constants too
  */
{
  ELog::RegMethod RegA("singleItemVariables[F]","SingleItemVariables");
// -----------
// GLOBAL stuff
// -----------
  Control.addVariable("zero",0.0);     // Zero
  Control.addVariable("one",1.0);      // one

  // photon test
  Control.addVariable("TargetZStep",0.0);
  Control.addVariable("TargetRadius",5.0);
  Control.addVariable("TargetMat","Stainless304");

  Control.addVariable("ShieldInnerRadius",50.0);
  Control.addVariable("ShieldOuterRadius",100.0);
  Control.addVariable("ShieldMat","Stainless304");

  Control.addVariable("TubeYStep",10.0);
  Control.addVariable("TubeRadius",5.0);
  Control.addVariable("TubeLength",30.0);
  Control.addVariable("TubeDepth",10.0);
  Control.addVariable("TubeWidth",20.0);
  Control.addVariable("TubeHeight",20.0);
  Control.addVariable("TubeMat","Stainless304");

  Control.addVariable("TubeARadius",5.0);
  Control.addVariable("TubeALength",25.0);
  Control.addVariable("TubeBRadius",5.0);
  Control.addVariable("TubeBLength",5.0);
  Control.addVariable("TubeAMat","Stainless304");
  Control.addVariable("TubeBMat","Lead");

  Control.addVariable("CryoBOuterRadius",20.0);

  Control.addVariable("CryoBNLayers",0);
  Control.addVariable("CryoBLRadius0",1.0);
  Control.addVariable("CryoBLRadius1",3.0);
  Control.addVariable("CryoBLRadius2",5.0);
  Control.addVariable("CryoBLRadius3",8.0);
  Control.addVariable("CryoBLThick",0.5);
  Control.addVariable("CryoBLTemp",300.0);

  Control.addVariable("CryoBTopOffset",1.0);
  Control.addVariable("CryoBBaseOffset",1.0);
  Control.addVariable("CryoBCutTopAngle",10.0);
  Control.addVariable("CryoBCutBaseAngle",10.0);

  Control.addVariable("CryoBTopThick",10.0);
  Control.addVariable("CryoBBaseThick",10.0);

  Control.addVariable("CryoBApertureWidth",2.0);
  Control.addVariable("CryoBApertureHeight",2.0);

  Control.addVariable("CryoBMat","Aluminium");

  setVariable::EArrivalMonGenerator EMonGen;
  EMonGen.generateMon(Control,"BeamMon",0.0);

  setVariable::CryoGenerator CryGen;
  CryGen.generateFridge(Control,"singleCryo",3.0,-10,4.5);

  setVariable::PrismaChamberGenerator PCGen;
  PCGen.generateChamber(Control,"PrismaChamber");

  setVariable::TwinGenerator TGen;
  TGen.generateChopper(Control,"singleTwinB",0.0,16.0,10.0);

  setVariable::TwinFlatGenerator TCGen;
  TCGen.generateChopper(Control,"singleTwinC",0.0,16.0,10.0);

  TCGen.generateChopper(Control,"singleTwinD",80.0,16.0,10.0);

  setVariable::RectPipeGenerator RPipeGen;
  RPipeGen.generatePipe(Control,"singleBoxPipeA",0.0,80.0);
  RPipeGen.generatePipe(Control,"singleBoxPipeB",0.0,80.0);

  setVariable::ChopperGenerator CGen;
  CGen.setMotorRadius(10.0);
  CGen.generateChopper(Control,"singleChopper",10.0,12.0,5.55);
  Control.addVariable("singleChopperMotorBodyLength",15.0);


  setVariable::BladeGenerator BGen;
  // Single Blade chopper
  BGen.setThick({0.2});
  BGen.addPhase({95,275},{30.0,30.0});
  BGen.generateBlades(Control,"singleBBladeTop",-2.0,22.5,35.0);

  // Single Blade chopper
  BGen.setThick({0.2});
  BGen.addPhase({95,275},{30.0,30.0});
  BGen.generateBlades(Control,"singleBBladeLow",2.0,22.5,35.0);


  // collimator block
  setVariable::SqrFMaskGenerator FMaskGen;
  FMaskGen.setPipeRadius(-10.0);
  // FMaskGen.setCF<CF63>();
  // FMaskGen.setBFlangeCF<CF40>();
  // FMaskGen.setFrontGap(3.99,1.97);  //1033.8
  // FMaskGen.setBackGap(0.71,0.71);
  // FMaskGen.setMinSize(10.2,0.71,0.71);
  FMaskGen.generateColl(Control,"FMask",0.0,15.0);

  
  setVariable::EPSeparatorGenerator EPSGen;
  EPSGen.generatePipe(Control,"EPSeparator");

  setVariable::DipoleChamberGenerator DCGen;
  DCGen.generatePipe(Control,"DipoleChamber",0.0);

  setVariable::DipoleExtractGenerator DEGen;
  DEGen.generatePipe(Control,"DipoleExtract",0.0);

  setVariable::DipoleSndBendGenerator DBGen;
  DBGen.generatePipe(Control,"DipoleSndBend",0.0);

  setVariable::R3ChokeChamberGenerator CCGen;
  CCGen.generateChamber(Control,"R3Chamber");

  setVariable::MagnetM1Generator M1Gen;
  M1Gen.generateBlock(Control,"M1Block");

  setVariable::PreDipoleGenerator PBGen;
  PBGen.generatePipe(Control,"PreDipole");

  setVariable::EPCombineGenerator EPCGen;
  EPCGen.generatePipe(Control,"EPCombine");

  setVariable::QuadrupoleGenerator QGen;
  QGen.generateQuad(Control,"QFend",20.0,25.0);

  setVariable::OctupoleGenerator OGen;
  OGen.generateOcto(Control,"OXX",20.0,25.0);

  setVariable::DipoleGenerator DGen;
  DGen.generateDipole(Control,"M1BlockDIM",0.0,60.0);

  setVariable::SexupoleGenerator SGen;
  SGen.generateHex(Control,"SXX",20.0,25.0);

  setVariable::SixPortGenerator SPGen;
  SPGen.generateSixPort(Control,"SixPort");

  setVariable::CrossWayGenerator MSPGen;
  MSPGen.generateCrossWay(Control,"CrossWay");

  setVariable::GaugeGenerator GTGen;
  GTGen.generateGauge(Control,"GaugeTube",0.0,0.0);

  setVariable::CrossWayGenerator CWBlankGen;
  CWBlankGen.setCF<CF63>();
  CWBlankGen.setMainLength(2.4,13.6);
  CWBlankGen.setPortLength(5.9,8.1);
  CWBlankGen.setCrossLength(6.25,6.25);
  CWBlankGen.setPortCF<CF35_TDC>();
  CWBlankGen.setCrossCF<CF35_TDC>();
  CWBlankGen.generateCrossWay(Control,"CrossBlank");

  setVariable::IonPTubeGenerator IonPGen;
  IonPGen.generateTube(Control,"IonPTube");

  // multipipe
  setVariable::MultiPipeGenerator MPGen;
  MPGen.setPipe<CF40>(Geometry::Vec3D(0,0,5.0),45.0, 0.0, 3.7);
  MPGen.setPipe<CF40>(Geometry::Vec3D(0,0,0.0),41.0, 0.0, 0.0);
  MPGen.setPipe<CF40>(Geometry::Vec3D(0,0,-5.0),37.0, 0.0, -3.7);
  MPGen.generateMulti(Control,"MultiPipe");

  const double startWidth(2.33/2.0);
  const double endWidth(6.70/2.0);
  setVariable::TriPipeGenerator TPGen;
  TPGen.setBFlangeCF<CF100>();
  TPGen.setXYWindow(startWidth,startWidth,endWidth,endWidth);
  TPGen.generateTri(Control,"TriPipe");

  setVariable::TriGroupGenerator TGGen;
  //  TPGen.setBFlangeCF<CF100>();
  TGGen.generateTri(Control,"TriGroup");

  setVariable::FlatPipeGenerator FPGen;
  FPGen.generateFlat(Control,"FlatPipe",80.0);
  Control.addVariable("FlatPipeXYAngle",0);

  setVariable::LinacQuadGenerator LQGen;
  LQGen.generateQuad(Control,"LQ",20.0);

  setVariable::LinacSexuGenerator LSGen;
  LSGen.generateSexu(Control,"LS",20.0);

  // Block for new R1-M1
  setVariable::MagnetBlockGenerator MBGen;
  MBGen.generateBlock(Control,"M1",0.0);

  setVariable::QuadUnitGenerator M1QGen;
  M1QGen.generatePipe(Control,"M1QuadUnit",0.0);

  //  setVariable::DipoleChamberGenerator DCGen;
  DCGen.generatePipe(Control,"M1DipoleChamber",0.0);

  DEGen.generatePipe(Control,"M1DipoleExtract",0.0);

  DBGen.generatePipe(Control,"M1DipoleSndBend",2.8);

  DEGen.setLength(82.0);
  DEGen.generatePipe(Control,"M1DipoleOut",0.0);

  // corrector mag
  setVariable::CorrectorMagGenerator CMGen;
  // last argument is vertical/horizontal switch
  CMGen.generateMag(Control,"CM",0.0,0);

  setVariable::PipeGenerator PGen;
  PGen.setNoWindow();
  PGen.setCF<setVariable::CF40_22>();
  PGen.setMat("Stainless316L");
  PGen.generatePipe(Control,"CorrectorMagPipe",40.0);
  Control.addVariable("CorrectorMagPipe",-20.0);

  LQGen.generateQuad(Control,"QF",20.0);

  PGen.setCF<setVariable::CF40_22>();
  PGen.generatePipe(Control,"QHVC",80.0);
  Control.addVariable("QHVC",-40.0);
  Control.addVariable("QHVCRadius",0.4);
  LQGen.setRadius(0.56, 2.31);
  LQGen.generateQuad(Control,"QH",20.0);
  Control.addVariable("QHLength",18.7);
  Control.addVariable("QHYokeOuter",9.5);
  Control.addVariable("QHPolePitch",26.0);

  // CylGateValve
  setVariable::CylGateValveGenerator GVGen;
  GVGen.generateGate(Control,"GV",1);

  // CylGateValve
  setVariable::GateValveGenerator CGateGen;

  CGateGen.setOuter(3.4,13.0,20.0,20.0);
  CGateGen.setBladeMat("Stainless304L");
  CGateGen.setBladeThick(0.8);
  CGateGen.setPortPairCF<CF40,CF63>();
  CGateGen.generateValve(Control,"GVCube",0.0,1);

  //  dipole magnet DIB
  setVariable::DipoleDIBMagGenerator DIBGen;
  DIBGen.generate(Control,"DIB");

  PGen.setCF<setVariable::CF40_22>();
  PGen.generatePipe(Control,"VC",80.0);
  Control.addVariable("VC",-40.0);

  setVariable::YagScreenGenerator YagGen;
  YagGen.generateScreen(Control,"YAG",1);  // in beam
  Control.addVariable("YAGYAngle",-90.0);

  setVariable::CurveMagGenerator CMagGen;
  CMagGen.generateMag(Control,"CMag");  

  setVariable::StriplineBPMGenerator BPMGen;
  BPMGen.generateBPM(Control,"BPM",0.0);

  setVariable::UndVacGenerator UVGen;
  UVGen.generateUndVac(Control,"UVac");
  setVariable::FMUndulatorGenerator UUGen;
  UUGen.generateUndulator(Control,"UVacUndulator",482.0);


  setVariable::CeramicGapGenerator CSGen;
  CSGen.generateCeramicGap(Control,"CerSep");

  setVariable::CF40 CF40unit;
  setVariable::BeamDividerGenerator BDGen(CF40unit);
  BDGen.generateDivider(Control,"BeamDiv",0.0);

  setVariable::EBeamStopGenerator EBGen;
  EBGen.generateEBeamStop(Control,"EBeam",0);
  
  setVariable::ScrapperGenerator SCGen;
  SCGen.generateScrapper(Control,"Scrapper",1.0);   // z lift


  setVariable::YagUnitGenerator YagUnitGen;
  YagUnitGen.generateYagUnit(Control,"YU");
  Control.addVariable("YUYAngle",90.0);

  setVariable::YagUnitBigGenerator YagUnitBigGen;
  YagUnitBigGen.generateYagUnit(Control,"YUBig");
  Control.addVariable("YUBigYAngle",90.0);

  // traveling wave cavity
  PGen.setNoWindow();
  PGen.setCF<setVariable::CF40_22>();
  PGen.setMat("Stainless304L","Stainless304L");
  setVariable::TWCavityGenerator TDCGen;

  const double flangeLength(3.7);
  RPipeGen.generatePipe(Control,"PipeA",0.0,flangeLength);
  Control.addVariable("PipeARadius",1.16);
  Control.addVariable("PipeAFeThick",0.2);

  TDCGen.generate(Control,"TWCavity");

  RPipeGen.generatePipe(Control,"PipeB",0.0,flangeLength);
  Control.addParse<double>("PipeBRadius","PipeARadius");
  Control.addParse<double>("PipeBFeThick","PipeAFeThick");

  // Bellow
  setVariable::BellowGenerator BellowGen;
  BellowGen.setCF<setVariable::CF40>();
  BellowGen.generateBellow(Control,"Bellow",7.5);

  // PipeTube
  setVariable::PipeTubeGenerator SimpleTubeGen;
  setVariable::PortItemGenerator PItemGen;
  SimpleTubeGen.setCF<CF63>();
  SimpleTubeGen.generateTube(Control,"PipeTube",0.0,20.0);

  Control.addVariable("PipeTubeNPorts",2);
  PItemGen.setCF<setVariable::CF40>(12.0);
  PItemGen.generatePort(Control,"PipeTubePort0",
			Geometry::Vec3D(0.0, 3.0, 0.0),
			Geometry::Vec3D(0.5, -0.5, 0.866));
  PItemGen.setNoPlate();
  PItemGen.setCF<setVariable::CF40>(10.0);
  PItemGen.generatePort(Control,"PipeTubePort1",
			Geometry::Vec3D(0.0, -3.0, 0.0),
			Geometry::Vec3D(-1.0, 0.0, 0.0));

  // PortTube
  setVariable::PortTubeGenerator PortTubeGen;
  PortTubeGen.setPipeCF<CF63>();
  PortTubeGen.setPortCF<CF40>();
  PortTubeGen.setPortLength(5.0,6.0);
  PortTubeGen.generateTube(Control,"PortTube",0.0,20.0);

  Control.addVariable("PortTubeNPorts",2);
  PItemGen.setCF<setVariable::CF40>(12.0);
  PItemGen.generatePort(Control,"PortTubePort0",
			Geometry::Vec3D(0.0, 3.0, 0.0),
			Geometry::Vec3D(0.5, -0.5, 0.866));
  PItemGen.setNoPlate();
  PItemGen.setCF<setVariable::CF40>(10.0);
  PItemGen.generatePort(Control,"PortTubePort1",
			Geometry::Vec3D(0.0, -3.0, 0.0),
			Geometry::Vec3D(-1.0, 0.0, 0.0));

  // BlankTube
  SimpleTubeGen.generateBlank(Control,"BlankTube",0.0,20.0);
  // Control.addVariable("BlankTubeFlangeCapThick",setVariable::CF63::flangeLength);
  // Control.addVariable("BlankTubeFlangeCapMat","Lead");
  //  Control.addVariable("BlankTubeYAngle", 30.0);
  Control.addVariable("BlankTubeNPorts",2);
  PItemGen.setCF<setVariable::CF40>(6.0);
  PItemGen.setPlate(setVariable::CF40_22::flangeLength, "Aluminium");
  PItemGen.generatePort(Control,"BlankTubePort0",
			Geometry::Vec3D(0.0, 3.0, 0.0),
			Geometry::Vec3D(0.5, -0.5, 0.866));

  PItemGen.setNoPlate();
  //  PItemGen.setCF<setVariable::CF40>(7.0);
  PItemGen.setLength(7.0);
  PItemGen.generatePort(Control,"BlankTubePort1",
			Geometry::Vec3D(0.0, -3.0, 0.0),
			Geometry::Vec3D(-1.0, 0.0, 0.0));
  //  Control.addVariable("BlankTubePort1WallMat","Stainless316L");

  // Button pickup BPM
  setVariable::ButtonBPMGenerator ButtonBPMGen;
  ButtonBPMGen.setCF<setVariable::CF40_22>();
  ButtonBPMGen.generate(Control,"ButtonBPM");

  // Cleaning magnet
  setVariable::CleaningMagnetGenerator ClMagGen;
  ClMagGen.generate(Control,"CleaningMagnet");

  // Jaws
  const std::string Name="DiagnosticBox";
  const double DLength(16.0);

  setVariable::PortTubeGenerator PTubeGen;

  PTubeGen.setMat("Stainless304");

  const double Radius(7.5);
  const double WallThick(0.5);
  const double PortRadius(Radius+WallThick+0.5);
  PTubeGen.setPipe(Radius,WallThick);
  PTubeGen.setPortCF<setVariable::CF40>();
  const double sideWallThick(1.0);
  PTubeGen.setPortLength(-sideWallThick,sideWallThick);
  PTubeGen.setAFlange(PortRadius,sideWallThick);
  PTubeGen.setBFlange(PortRadius,sideWallThick);
  PTubeGen.generateTube(Control,Name,0.0,DLength);
  Control.addVariable(Name+"NPorts",4);

  const std::string portName=Name+"Port";
  const Geometry::Vec3D MidPt(0,1.5,0);
  const Geometry::Vec3D XVec(1,0,0);
  const Geometry::Vec3D ZVec(0,0,1);
  const Geometry::Vec3D PPos(0.0,DLength/8.0,0);

  // first 2 ports are with jaws, others - without jaws
  PItemGen.setOuterVoid(1);  // create boundary round flange
  PItemGen.setCF<setVariable::CF63>(5.0);
  PItemGen.generatePort(Control,portName+"0",-PPos,ZVec);
  PItemGen.setCF<setVariable::CF63>(10.0);
  PItemGen.generatePort(Control,portName+"1",MidPt,XVec);

  PItemGen.setCF<setVariable::CF63>(5.0);
  PItemGen.generatePort(Control,portName+"2",-PPos,-ZVec);
  PItemGen.setCF<setVariable::CF63>(10.0);
  PItemGen.generatePort(Control,portName+"3",MidPt,-XVec);

  // PItemGen.setCF<setVariable::CF63>(10.0);
  // PItemGen.generatePort(Control,portName+"4",MidPt,
  // 			Geometry::Vec3D(1,0,1));

  JawFlangeGenerator JFlanGen;
  JFlanGen.setSlits(2.5, 2.5, 0.4, "Tantalum"); // W,H,T,mat
  JFlanGen.generateFlange(Control,Name+"JawUnit0");
  JFlanGen.generateFlange(Control,Name+"JawUnit1");

  Control.addVariable(Name+"JawUnit0JOpen",1.7);
  Control.addVariable(Name+"JawUnit1JOpen",1.7);

  return;
}

}  // NAMESPACE setVariable
