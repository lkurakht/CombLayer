/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   Model/MaxIV/LinacInc/YagScreenGenerator.h
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
#ifndef setVariable_YagScreenGenerator_h
#define setVariable_YagScreenGenerator_h

class FuncDataBase;

namespace setVariable
{

/*!
  \class YagScreenGenerator
  \version 1.0
  \author Konstantin Batkov
  \date May 2020
  \brief YagScreenGenerator for variables
*/

class YagScreenGenerator
{
 private:

  double jbLength;              ///< electronics junction box length
  double jbWidth;               ///< electronics junction box width
  double jbHeight;              ///< electronics junction box height
  double jbWallThick;           ///< electronics junction box wall thickness

  std::string jbWallMat;        ///< electronics junction box material
  std::string jbMat;            ///< electronics junction box cable/inside material

  double ftLength;              ///< linear pneumatics feedthrough length
  double ftInnerRadius;         ///< linear pneumatics feedthrough inner radius
  double ftWallThick;           ///< linear pneumatics feedthrough wall thickness
  double ftFlangeLen;           ///< linear pneumatic feedthrough flange length
  double ftFlangeRadius;        ///< linear pneumatic feedthrough flange radius
  std::string ftWallMat;        ///< linear pneumatics feedthrough wall material

  double threadLift;            ///< screen thread lift inside vacuum system
  double threadRad;             ///< screen thread inner radius
  std::string threadMat;        ///< screen thread material

  double mirrorRadius;          ///< quartz mirror radius
  double mirrorAngle;           ///< quartz mirror inclination angle [deg]
  double mirrorThick;           ///< quartz mirror thickness
  std::string mirrorMat;        ///< mirror material
  double screenOffset;          ///< distance between mirror and screen

  double screenRadius;          ///< screen radius
  double screenAngle;           ///< screen inclination angle [deg]
  double screenHolderRadius;    ///< screen holder outer radius
  double screenHolderThick;    ///< screen holder thickness
  std::string screenHolderMat;       ///< screen holder material

  std::string voidMat;          ///< void material

  bool closed;                  ///< screen and mirror are in the beam

 public:

  YagScreenGenerator();
  YagScreenGenerator(const YagScreenGenerator&);
  YagScreenGenerator& operator=(const YagScreenGenerator&);
  ~YagScreenGenerator();

  template<typename CF> void setCF();
  template<typename CF> void setFlangeCF();

  void generateScreen(FuncDataBase&,const std::string&,
		      const bool) const;

};

}

#endif