/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   transport/Detector.cxx
 *
 * Copyright (c) 2004-2022 by Stuart Ansell
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
#include <map>
#include <string>
#include <boost/format.hpp>
#include <boost/multi_array.hpp>

#include "FileReport.h"
#include "OutputLog.h"
#include "Detector.h"

namespace Transport
{

std::ostream&
operator<<(std::ostream& OX,const Detector& A)
/*!
  Standard Output stream
  \param OX :: Output stream
  \param A :: Detector to write
  \return OX
 */

{
  A.write(OX);
  return OX;
}

Detector::Detector(const size_t ID) :
  index(ID),nps(0)
  /*!
    Default constructor
    \param ID :: indenty number
  */
{}

Detector::Detector(const Detector& A) : 
  index(A.index),nps(A.nps)
  /*!
    Copy constructor
    \param A :: Detector to copy
  */
{}

Detector&
Detector::operator=(const Detector& A)
  /*!
    Assignment operator
    \param A :: Detector to copy
    \return *this
  */
{
  if (this!=&A)
    {
      nps=A.nps;
    }
  return *this;
}

Detector::~Detector()
  /*!
    Destructor
  */
{}



} // NAMESPACE Transport


  
