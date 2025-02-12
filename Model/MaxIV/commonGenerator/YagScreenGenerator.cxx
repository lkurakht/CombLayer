/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   commonGenerator/YagScreenGenerator.cxx
 *
 * Copyright (c) 2004-2021 by Konstantin Batkov
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
#include <stack>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <memory>

#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "Vec3D.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "CFFlanges.h"

#include "ScreenGenerator.h"
#include "YagScreenGenerator.h"

namespace setVariable
{

YagScreenGenerator::YagScreenGenerator() :
  ScreenGenerator(),

  holderWidth(4.50),holderDepth(3.25),
  holderShortLen(1.32),holderLongLen(4.4),

  mirrorAngle(-45.0),mirrorRadius(1.75),
  mirrorThick(0.5),

  screenAngle(5.0), screenVOffset(0.3),
  screenRadius(1.0),screenThick(0.1),
 
  screenHolderRadius(1.3), screenHolderThick(0.3), // measured,
  
  holderMat("Stainless304L"),
  mirrorMat("SiO2"),
  screenMat("SiO2"),
  screenHolderMat("Aluminium")
  /*!
    Constructor and defaults
  */
{}

YagScreenGenerator::~YagScreenGenerator()
 /*!
   Destructor
 */
{}


void
YagScreenGenerator::generateScreen(FuncDataBase& Control,
				   const std::string& keyName,
				   const bool inBeam) const
/*!
    Primary funciton for setting the variables
    \param Control :: Database to add variables
    \param keyName :: Head name for variable
    \param inBeam :: is item in beam
  */
{
  ELog::RegMethod RegA("YagScreenGenerator","generate");

  ScreenGenerator::generateScreen(Control,keyName,inBeam);
  
  Control.addVariable(keyName+"HolderWidth",holderWidth);
  Control.addVariable(keyName+"HolderDepth",holderDepth);
  Control.addVariable(keyName+"HolderShortLen",holderShortLen);
  Control.addVariable(keyName+"HolderLongLen",holderLongLen);
  
  Control.addVariable(keyName+"MirrorAngle",mirrorAngle);
  Control.addVariable(keyName+"MirrorRadius",mirrorRadius);
  Control.addVariable(keyName+"MirrorThick",mirrorThick);
  
  Control.addVariable(keyName+"ScreenAngle",screenAngle);
  Control.addVariable(keyName+"ScreenVOffset",screenVOffset);
  Control.addVariable(keyName+"ScreenRadius",screenRadius);
  Control.addVariable(keyName+"ScreenThick",screenThick);
  Control.addVariable(keyName+"ScreenHolderRadius",screenHolderRadius);
  Control.addVariable(keyName+"ScreenHolderThick",screenHolderThick);
  
  Control.addVariable(keyName+"HolderMat",holderMat);
  Control.addVariable(keyName+"MirrorMat",mirrorMat);
  Control.addVariable(keyName+"ScreenMat",screenMat);
  Control.addVariable(keyName+"ScreenHolderMat",screenHolderMat);
     
 return;

}

}  // namespace setVariable
