/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   attachCompInc/FixedOffsetUnit.h
 *
 * Copyright (c) 2004-2019 by Stuart Ansell
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
#ifndef attachSystem_FixedOffsetUnit_h
#define attachSystem_FixedOffsetUnit_h

class FuncDataBase;

namespace attachSystem
{
/*!
  \class FixedOffsetUnit
  \version 1.0
  \author S. Ansell
  \date  December 2019
  \brief FixedComp with abstract units removed
*/

class FixedOffsetUnit : public FixedComp
{  
 public:

  FixedOffsetUnit(const std::string& K,const size_t I) :
    FixedComp(K,I) {}
  FixedOffsetUnit(const FixedOffsetUnit& A) : FixedOffset(A) {}
  FixedOffsetUnit(const FixedOffset& A) : FixedOffset(A) {}
  virtual ~FixedOffsetUnit() {}     ///< Destructor

  void createAll(Simulation&,const FixedComp&,const long int) {}
};

}

#endif
 