/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   commonGeneratorInc/DiffPumpGenerator.h
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 *
 ****************************************************************************/
#ifndef setVariable_DiffPumpGenerator_h
#define setVariable_DiffPumpGenerator_h

class FuncDataBase;

namespace setVariable
{

/*!
  \class HRJawGenerator
  \version 1.0
  \author S. Ansell
  \date April 2020
  \brief DiffPumpGenerator for variables
*/

class DiffPumpGenerator 
{
 private:

  double length;                 ///< Main box length
  double width;                  ///< Main box width
  double height;                 ///< Main box height

  double innerLength;            ///< inner Length
  
  double captureWidth;           ///< void in capture space
  double captureHeight;          ///< void in capture space 

  double magWidth;               ///< Magnet Width
  double magHeight;              ///< Magnet Height

  double innerRadius;            ///< inner pipe radius
  double innerThick;             ///< inner pipe thickness

  double portLength;             ///< Port length
  double portRadius;             ///< port Radius 
  double portThick;              ///< thickness of port pipe

  double flangeRadius;           ///< Flange radius
  double flangeLength;           ///< Flange thickness


  std::string voidMat;               ///< Void Material
  std::string pipeMat;               ///< Pipe Material
  std::string mainMat;               ///< Support Material
  std::string magnetMat;             ///< Magnet material
  std::string flangeMat;             ///< Flange material

 public:

  DiffPumpGenerator();
  DiffPumpGenerator(const DiffPumpGenerator&);
  DiffPumpGenerator& operator=(const DiffPumpGenerator&);
  virtual ~DiffPumpGenerator();

  template<typename T> void setCF();
  template<typename T> void setPortCF(const double);
  
  void generatePump(FuncDataBase&,const std::string&) const;


};

}

#endif
 
