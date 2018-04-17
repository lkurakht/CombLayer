/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   tallyInc/userBdxConstruct.h
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
#ifndef tallySystem_userBdxConstruct_h
#define tallySystem_userBdxConstruct_h

namespace attachSystem
{
  class FixedComp;
}

namespace mainSystem
{
  class inputParam;
}

class Simulation;

namespace flukaSystem
{

/*!
  \class userBdxConstruct
  \version 1.0
  \author S. Ansell
  \date July 2012
  \brief Constructs a mesh tally from inputParam
*/

class userBdxConstruct 
{
  private:
  
  /// Private constructor
  userBdxConstruct() {}

  static bool constructLinkRegion(const Simulation&,const std::string&,
				  const std::string&,int&,int&);

  static bool checkLinkCells(const Simulation&,const int,const int);
  
  static void createTally(SimFLUKA&,const std::string&,const int,
			  const int,const int,
			  const bool,const double,const double,const size_t,
			  const bool,const double,const double,const size_t);
  
 public:

  static void processBDX(SimFLUKA&,const mainSystem::inputParam&,
			 const size_t);
  
  static void writeHelp(std::ostream&);
};

}

#endif
 