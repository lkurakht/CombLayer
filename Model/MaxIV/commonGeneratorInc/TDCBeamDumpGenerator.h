/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   Model/MaxIV/LinacInc/TDCBeamDumpGenerator.h
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
#ifndef setVariable_TDCBeamDumpGenerator_h
#define setVariable_TDCBeamDumpGenerator_h

class FuncDataBase;

namespace setVariable
{

/*!
  \class TDCBeamDumpGenerator
  \version 1.0
  \author Konstantin Batkov
  \date October 2021
  \brief TDCBeamDumpGenerator for variables
*/

class TDCBeamDumpGenerator
{
 private:

  double length;                ///< Total length including void
  double bulkWidthLeft;         ///< Left-side bulk width
  double bulkWidthRight;        ///< Right-side bulk width
  double bulkHeight;            ///< Bulk height
  double bulkDepth;             ///< Bulk depth
  double bulkThickBack;         ///< Bulk thickness behind the core
  double coreRadius;            ///< Core radius
  double coreLength;            ///< Core length
  double preCoreLength;         ///< Length of void before core
  double preCoreRadius;         ///< Radius of void before core
  double skinThick;             ///< Skin thickness
  double frontPlateThick;       ///< Front plate thickness
  double carbonThick;           ///< Carbon plate thickness

  std::string coreMat;          ///< Core material
  std::string bulkMat;          ///< Bulk material
  std::string skinMat;          ///< Skin material
  std::string frontPlateMat;    ///< Front plate material (to reduce activation dose rate)
  std::string carbonMat;        ///< Carbon plate material

 public:

  TDCBeamDumpGenerator();
  TDCBeamDumpGenerator(const TDCBeamDumpGenerator&);
  TDCBeamDumpGenerator& operator=(const TDCBeamDumpGenerator&);
  virtual ~TDCBeamDumpGenerator();

  virtual void generate(FuncDataBase&,const std::string&) const;

};

}

#endif
