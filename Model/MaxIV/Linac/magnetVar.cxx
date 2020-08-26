/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   linac/magVariables.cxx
 *
 * Copyright (c) 2004-2020 by Stuart Ansell/Konstantin Batkov
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

#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "Vec3D.h"
#include "Code.h"
#include "varList.h"
#include "FuncDataBase.h"

#include "CFFlanges.h"
#include "PipeGenerator.h"
#include "SplitPipeGenerator.h"
#include "BellowGenerator.h"
#include "GateValveGenerator.h"
#include "CorrectorMagGenerator.h"
#include "LinacQuadGenerator.h"
#include "LinacSexuGenerator.h"
#include "PortTubeGenerator.h"
#include "JawFlangeGenerator.h"
#include "PipeTubeGenerator.h"
#include "PortItemGenerator.h"
#include "StriplineBPMGenerator.h"
#include "CylGateValveGenerator.h"
#include "GateValveGenerator.h"
#include "DipoleDIBMagGenerator.h"
#include "EArrivalMonGenerator.h"
#include "YagScreenGenerator.h"
#include "YagUnitGenerator.h"
#include "YagUnitBigGenerator.h"
#include "FlatPipeGenerator.h"
#include "TriPipeGenerator.h"
#include "TriGroupGenerator.h"
#include "BeamDividerGenerator.h"
#include "ScrapperGenerator.h"
#include "SixPortGenerator.h"
#include "CeramicGapGenerator.h"
#include "EBeamStopGenerator.h"
#include "TWCavityGenerator.h"
#include "UndVacGenerator.h"
#include "FMUndulatorGenerator.h"
#include "subPipeUnit.h"
#include "MultiPipeGenerator.h"
#include "ButtonBPMGenerator.h"
#include "CurveMagGenerator.h"
#include "CleaningMagnetGenerator.h"

#include "magnetVar.h"

namespace setVariable
{

namespace linacVar
{

void
Segment32Magnet(FuncDataBase& Control,
		   const std::string& lKey)
  /*!
    This should be for the magnet unit but currently doing segment32
    to make fast compiles
    \param Control :: Variable Database
    \param lKey :: key name
  */
{
  ELog::RegMethod RegA("linacVariables[F]","Segment32");

  setVariable::PipeGenerator PGen;
  setVariable::FlatPipeGenerator FPGen;
  setVariable::DipoleDIBMagGenerator DIBGen;
  setVariable::BellowGenerator BellowGen;


  FPGen.generateFlat(Control,lKey+"FlatA",82.64); // measured
  Control.addVariable(lKey+"FlatAXYAngle",-1.29);
  
  DIBGen.generate(Control,lKey+"DMA"); 

  PGen.setMat("Stainless316L","Stainless304L");
  PGen.setNoWindow();
  PGen.setCF<CF40_22>();

  PGen.generatePipe(Control,lKey+"PipeA",94.351); // measured
  Control.addVariable(lKey+"PipeAXYAngle",-1.985);


  FPGen.generateFlat(Control,lKey+"FlatB",82.582); // measured
  Control.addVariable(lKey+"FlatBXYAngle",-1.6);

  DIBGen.generate(Control,lKey+"DMB");

  BellowGen.setCF<setVariable::CF40_22>();
  BellowGen.setMat("Stainless304L", "Stainless304L%Void%3.0");
  BellowGen.generateBellow(Control,lKey+"Bellow",7.5); // measured
  Control.addVariable(lKey+"BellowXYAngle",0.0);
  
  return;
}

void
Segment34Magnet(FuncDataBase& Control,
		const std::string& lKey)
  /*!
    This should be for the magnet unit but currently doing segment34
    to make fast compiles
    \param Control :: Variable Database
    \param lKey :: key name
  */
{
  ELog::RegMethod RegA("linacVariables[F]","Segment34");

  setVariable::PipeGenerator PGen;
  setVariable::FlatPipeGenerator FPGen;
  setVariable::DipoleDIBMagGenerator DIBGen;
  setVariable::BellowGenerator BellowGen;


  FPGen.generateFlat(Control,lKey+"FlatA",82.64); // measured
  Control.addVariable(lKey+"FlatAXYAngle",-1.29);
  
  DIBGen.generate(Control,lKey+"DMA"); 

  PGen.setMat("Stainless316L","Stainless304L");
  PGen.setNoWindow();
  PGen.setCF<CF40_22>();

  PGen.generatePipe(Control,lKey+"PipeA",94.351); // measured
  Control.addVariable(lKey+"PipeAXYAngle",-1.985);


  FPGen.generateFlat(Control,lKey+"FlatB",82.582); // measured
  Control.addVariable(lKey+"FlatBXYAngle",-1.6);

  DIBGen.generate(Control,lKey+"DMB");

  BellowGen.setCF<setVariable::CF40_22>();
  BellowGen.setMat("Stainless304L", "Stainless304L%Void%3.0");
  BellowGen.generateBellow(Control,lKey+"Bellow",7.5); // measured
  Control.addVariable(lKey+"BellowXYAngle",-1.525);
  
  return;
}



}  // NAMESPACE linacVAR

}   // NAMESPACE setVariable
