/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   physics/PhysicsCards.cxx
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 *
 ****************************************************************************/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <array>
#include <boost/algorithm/string.hpp>

#include "Exception.h"
#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "support.h"
#include "writeSupport.h"
#include "MapRange.h"
#include "MatrixBase.h"
#include "ModeCard.h"
#include "PhysCard.h"
#include "PStandard.h"
#include "PSimple.h"
#include "LSwitchCard.h"
#include "nameCard.h"
#include "EUnit.h"
#include "ExtControl.h"
#include "PWTControl.h"
#include "DXTControl.h"
#include "PhysImp.h"
#include "PhysicsCards.h"

namespace physicsSystem
{

PhysicsCards::PhysicsCards() :
  mcnpVersion(6),nps(10000),histp(0),
  RAND(new nameCard("RAND",0)),
  PTRAC(new nameCard("PTRAC",0)),
  dbCard(new nameCard("dbcn",1)),
  voidCard(0),prdmp("1e7 1e7 0 2 1e7"),
  ExtCard(new ExtControl),
  PWTCard(new PWTControl),DXTCard(new DXTControl)
  /*!
    Constructor
  */
{
  ELog::RegMethod RegA("PhysicsCards","[Constructor]");
  
  PTRAC->registerItems
    (
     {"BUFFER INT","FILE STR","MAX INT","MEPH INT","WRITE STR",
      "COINC STR","EVENT STR","FILTER STR","TYPE STR",
      "NPS STR","CELL STR","SURFACE STR","TALLY STR"}
     );

  RAND->registerItems
    (
     {"SEED INT"}
     );

  dbCard->registerItems
    ({
     "rndSeed INT 1234567871",  "debugPrint INT",
     "eventStart INT",          "eventEnd INT",
     "maxEvents INT",           "detUnderFlowLimit DBL",
     "printSurfCalcFlag INT",   "histStart INT",
     "surfTol DBL",             "default J",
     "printCollision INT",      "default J",
     "stride INT",              "gen INT",
     "printVOV INT",            "histScale DBL",
     "eleAngDefMethod INT",     "electronStragglingType INT",  // 18
     "default J",               "default J",
     "default J",               "default J",
     "forcePHTVRtree INT",      "default J",
     "default J",               "default J",
     "default J",               "bankSize INT",            // 28
     "default J",               "default J",
     "default J",               "genxsType INT",
     "ionSmooth INT",           "default J",               // 34
     "default J",               "default J",
     "default J",               "default J",              
     "sqwMethod INT"                 });
}

PhysicsCards::PhysicsCards(const PhysicsCards& A) : 
  mcnpVersion(A.mcnpVersion),nps(A.nps),
  histp(A.histp),histpCells(A.histpCells),
  RAND(new nameCard(*A.RAND)), PTRAC(new nameCard(*A.PTRAC)),
  dbCard(new nameCard(*A.dbCard)),
  Basic(A.Basic),mode(A.mode),
  voidCard(A.voidCard),wImpOut(A.wImpOut),printNum(A.printNum),
  prdmp(A.prdmp),
  PCards(),LEA(A.LEA),
  ExtCard(new ExtControl(*A.ExtCard)),
  PWTCard(new PWTControl(*A.PWTCard)),
  DXTCard(new DXTControl(*A.DXTCard))
  /*!
    Copy constructor
    \param A :: PhysicsCards to copy
  */
{
  for(const PhysCard* PC : A.PCards)
    PCards.push_back(PC->clone());      
}

PhysicsCards&
PhysicsCards::operator=(const PhysicsCards& A)
  /*!
    Assignment operator
    \param A :: PhysicsCards to copy
    \return *this
  */
{
  if (this!=&A)
    {
      mcnpVersion=A.mcnpVersion;
      nps=A.nps;
      histp=A.histp;
      histpCells=A.histpCells;
      *RAND=*A.RAND;
      *PTRAC=*A.PTRAC;
      *dbCard = *A.dbCard;
      Basic=A.Basic;      
      mode=A.mode;
      voidCard=A.voidCard;
      printNum=A.printNum;
      prdmp=A.prdmp;
      LEA=A.LEA;
      *ExtCard= *A.ExtCard;
      *PWTCard= *A.PWTCard;
      *DXTCard= *A.DXTCard;
      
      deletePhysImp();
      for(const PhysImp* PI : A.PImpVec)
	PImpVec.push_back(new PhysImp(*PI));      

      deletePCards();
      for(const PhysCard* PC : A.PCards)
	PCards.push_back(PC->clone());      

    }
  return *this;
}


PhysicsCards::~PhysicsCards()
  /*!
    Destructor
  */
{
  deletePhysImp();
  deletePCards();
}

void
PhysicsCards::deletePCards()
  /*!
    Delete the memory
  */
{
  for(PhysCard* PC : PCards)
    delete PC;
  PCards.clear();
  return;
}

void
PhysicsCards::deletePhysImp()
  /*!
    Delete the memory
  */
{
  for(PhysImp* PI : PImpVec)
    delete PI;
  PImpVec.clear();
  return;
}
  
void
PhysicsCards::clearAll()
  /*!
    The big reset
  */
{
  histpCells.clear();
  Basic.clear();
  mode.clear();
  printNum.clear();
  deletePCards();
  deletePhysImp();
  RAND->reset();
  PTRAC->reset();
  dbCard->reset();
  ExtCard->clear();
  PWTCard->clear();
  DXTCard->clear();
  return;
}

void
PhysicsCards::setWImpFlag(const std::string& particleType)
  /*!
    Set the imp than are excluded because they have 
    a wcell/wwg mesh
    \param particleType :: particle type
  */
{
  wImpOut.insert(particleType);
  return;
}

void
PhysicsCards::clearWImpFlag(const std::string& particleType)
  /*!
    Set the imp than are excluded because they have 
    a wcell/wwg mesh
    \param particleType :: particle type
  */
{
  wImpOut.erase(particleType);
  return;
}

bool
PhysicsCards::hasWImpFlag(const std::string& particleType) const
  /*!
    Set the imp than are excluded because they have 
    a wcell/wwg mesh
    \param particleType :: particle type
    \return true if particle exists
  */
{
  return (wImpOut.find(particleType) == wImpOut.end()) ? 0 : 1;
}

void
PhysicsCards::addHistpCells(const std::set<int>& AL)
  /*!
    Adds a cell list to the hist tape file
    \param AL :: List to add
   */
{
  ELog::RegMethod RegA("PhysicsCards","addHistpCells");

  for(const int CellN : AL)
    histpCells.emplace(CellN);
  return;
}

void
PhysicsCards::clearHistpCells()
  /*!
    Clears the cell list from the hist tape file
   */
{
  histpCells.clear();
  return;
}

int 
PhysicsCards::processCard(const std::string& Line)
  /*!
    Attempt to process a card.
    If comment, store in 'Comments' and insert '0' into 'Cards'
    If card, insert "" into Comments and store in Cards.
    \param Line :: string to process
    \retval :: -ve on fail
    \retval 1 on successful addition of a card
    \retval 0 on null line/comment line
    \todo Trim leading space
  */
{
  ELog::RegMethod RegA("PhysicsCards","processCard");
  if(Line.empty())
    return 0;  
  
  std::string Comd=Line;
  StrFunc::stripComment(Comd);
  Comd=StrFunc::removeOuterSpace(Comd);

  // Check the first 2 characters for comment
  if(Comd.size()<2 || (isspace(Comd[1]) &&
		       ( tolower(Comd[0])=='c' || Comd[0]=='!'))) 
    return 0;
  
  std::string::size_type pos=Comd.find("mode ");
  if (pos!=std::string::npos)
    {
      std::string item;
      Comd.erase(0,pos+5);
      while(StrFunc::section(Comd,item))
	mode.addElm(item);
      return 1;
    }
  pos=Comd.find("print ");
  if (pos!=std::string::npos)
    {
      printNum.clear();
      std::string Item=Comd.substr(pos+1);
      int pNum;
      while(StrFunc::section(Item,pNum))
	printNum.push_back(pNum);
    }
  
  pos=Comd.find("histp");
  if (pos!=std::string::npos)
    {
      histp=1;
      return 1;
    }

  // This is ignored since we have a prdmp card
  pos=Comd.find("prdmp");    
  if (pos!=std::string::npos)
    {
      return 1;
    }

  pos=Comd.find("nps");
  if (pos!=std::string::npos)
    {
      Comd.erase(0,pos+3);
      if (!StrFunc::convert(Comd,nps))
	nps=800000;
      return 1;
    }

  pos=Comd.find("dbcn");
  if (pos!=std::string::npos)
    {
      long int RS;
      std::string keyName;
      Comd.erase(0,pos+4);
      if (StrFunc::convert(Comd,RS))
	dbCard->setRegItem("rndSeed",RS);
      else
	{
	  ELog::EM<<"DBCN [rnd] error  == "<<Comd<<ELog::endErr;
	}

      return 1;
    }
  pos=Comd.find("cut:");
  if (pos!=std::string::npos)
    {
      Comd.erase(0,pos+4);
      PStandard* PC=new PStandard("cut");
      std::string Item;
      if (StrFunc::section(Comd,Item))
        {
	  std::vector<std::string> part;
	  boost::split(part,Item,boost::is_any_of(","));
	  for(std::string& PStr : part)
	    boost::trim(PStr,std::locale());
	  // ensure no empty particles
	  part.erase(
		     remove_if(part.begin(),part.end(),
			       [](const std::string& A) { return A.empty(); } 
                     ));

	  for(const std::string& PStr : part)
	    PC->addElm(PStr);
	  // Strip and process numbers / j
	  for(size_t i=0;i<5 && !Comd.empty();i++)
	    {
	      double d;
	      if (StrFunc::section(Comd,d))
		PC->setValue(i,d);
	      else if (StrFunc::section(Comd,Item))
	        {
		  if (Item.size()==1 && tolower(Item[0]=='j'))
		    PC->setDef(i);
		}
	    }
	  PCards.push_back(PC);
	}
      else
        delete PC;
      
      return 1;
    }
  return 1;
}

void
PhysicsCards::setEnergyCut(const double E) 
  /*!
    Sets the minimium energy cut
    \param E :: Energy [MeV]
  */
{
  ELog::RegMethod RegA("PhysicsCards","setEnergyCut");

  for(PhysCard* PC : PCards)
    PC->setEnergyCut(E);
  
  return;
}

template<typename T>
T*
PhysicsCards::addPhysCard(const std::string& Key,
			  const std::string& Particle)
  /*!
    Adds a particular card [if not already present].
    If ANY particle is found in the current cards, then 
    all remaining particles are added and the 
    card returned. If not then a new card is created
    \tparam T :: PhysCard Template
    \param Key :: KeyName
    \param Particle :: Particle to add [n,p,e] etc

    \return PhysCard<T>
  */
{
  ELog::RegMethod RegA("PhysicsCards","addPhysCard");
  const std::vector<std::string> PList=
    StrFunc::StrParts(Particle);
  
  for(PhysCard* PC : PCards)
    {
      int found(0);
      if (PC->getKey()==Key)  	// First determine if any key exists:
	{
	  T* PX=(dynamic_cast<T*>(PC));
	  if (PX)
	    {
	      for(size_t i=0;i<PList.size();i++)
		{
		  const std::string particle=PList[i];
		  if (!found && PX->hasElm(particle))
		    {
		      // Add old non-found particles [previous]
		      for(size_t j=0;j<i;j++)
			PX->addElm(PList[i]);
		      found=1;
		    }
		  else if (found && !PX->hasElm(particle))
		    PX->addElm(particle);
		}
	      if (found)
		return PX;
	    }
	}
    }
  // No card found add: ADD PSTANDARD
  T* PX=new T(Key);
  PCards.push_back(PX);
  for(const std::string& particle :  PList)
    PX->addElm(particle);
  return PX;
}

const PhysCard*
PhysicsCards::getPhysCard(const std::string& Key,
			  const std::string& particle) const
  /*!
    Gets a particular card with Key and 
    particle [if empty first card with key]
    \param Key :: KeyName
    \param particle :: Particle to find [n,p,e] etc [empty for any]
    \return PhysCard
  */
{
  ELog::RegMethod RegA("PhysicsCards","getPhysCard");
  
  for(const PhysCard* PC : PCards)
    if (PC->getKey()==Key &&
	(particle.empty() || PC->hasElm(particle)))  
      return PC;

  throw ColErr::InContainerError<std::string>
    (Key+":"+particle,"PhysCard search");
}


// General object [All Particles]:

PhysImp&
PhysicsCards::getPhysImp(const std::string& piType,
			 const std::string& particleList,
			 const double defValue)
  /*!
    Construct a PhysImp card based on type/particle list
    \param piType :: PhysImp type
    \param particleList :: ParticleList
   */
{
  PhysImp& PImp=getPhysImp(piType,particleList);
  PImp.setDefValue(defValue);
  return PImp;
}


PhysImp&
PhysicsCards::getPhysImp(const std::string& piType,
			 const std::string& particleList)
  /*!
    Construct a PhysImp card based on type/particle list
    \param piType :: PhysImp type
    \param particleList :: ParticleList
   */
{
  ELog::RegMethod RegA("PhysicsCards","getPhysImp(s,s)");

  // calculate the PhysImp to get the keyname [ugly but works]
  std::unique_ptr<PhysImp> PIptr(new PhysImp(piType,particleList));

  PhysImp* PMatch(nullptr);
  for(PhysImp* currentPI : PImpVec)
    {
      if (piType==currentPI->getType())
	{
	  // full match
	  if (PIptr->getName()==currentPI->getName())
	    return *currentPI;

	  if (currentPI->commonParticles(*PIptr))
	    {
	      if (PMatch)
		throw ColErr::InContainerError<std::string>
		  (PIptr->getName()+":"+PMatch->getName(),"Overlap");

	      PMatch=currentPI;
	    }
	}
    }

  // We had ONE match (but not exact so at least one particle left)
  if (PMatch)
    {  
      PMatch->removeParticle(*PIptr);
      PIptr->copyValues(*PMatch);
    }
  
  PImpVec.push_back(PIptr.release());
  return *(PImpVec.back());
}


// Specific : Particle + Type

  
void
PhysicsCards::removeCell(const int Index)
  /*!
    Remove a particular cell (normally since a cutter cell)
    \param Index :: Cell id to remove
  */
{
  ELog::RegMethod RegA("PhysicsCards","removeCell");
  
  for(PhysImp* PI : PImpVec)
    PI->removeCell(Index);
  return;
}

double
PhysicsCards::getValue(const std::string& Type,
		       const std::string& Particle,
		       const int cellID) const
  /*!
    Return the importance of a given cell
    \param Type :: importance identifier
    \param Particle :: particle list
    \param cellID :: Cell number
    \throw InContainerError if Type+Particle is not found
    \return importance of the cell
  */
{
  const PhysImp& AP=getPhysImp(Type,Particle);
  return AP.getValue(cellID);
}

const PhysImp&
PhysicsCards::getPhysImp(const std::string& Type,
			 const std::string& particle) const
  /*!
    Return the PhysImp for a particle type
    \param Type :: type of importance
    \param particle :: particle type
    \throw InContainerError if pType is not found
    \return importance of the cell
  */
{
  ELog::RegMethod RegA("PhysicsCards","getPhysImp(const)");
    
  for(const PhysImp* PI : PImpVec)
    {
      if (PI->getType()==Type &&
	  PI->hasParticle(particle))
	return *PI;
    }
  
  throw ColErr::InContainerError<std::string>
    (Type+"/"+particle,"type/particle not found");
}

void
PhysicsCards::setPWT(const int cellID,const double V)
  /*!
    Sets the PWT of a particular cell
    \param cellID :: the particular cell number to set
    \param V :: New importance value  
  */
{
  PWTCard->setUnit(cellID,V);
  return;
}

void
PhysicsCards::setRND(const long int N,
		     const long int H)
  /*!
    Set the randome number seed to N
    \param N :: Index number
    \param H :: History
  */
{
  ELog::RegMethod RegA("PhysicsCards","setRND");
  if (N)
    {
      if (mcnpVersion==10)
	dbCard->setRegItem("rndSeed",N);
      else 
	{
	  dbCard->setDefItem("rndSeed");
	  RAND->setRegItem("SEED",N);
	}
    }
  if (H) RAND->setRegItem("HIST",H);

  return;
}

void
PhysicsCards::setPTRACactive(const bool F)
  /*!
    Set the PTRAC active 
    \param F :: Flag value
  */
{
  PTRAC->setActive(F);
}

void
PhysicsCards::setDBCNactive(const bool F)
  /*!
    Set the PTRAC active 
    \param F :: Flag value
  */
{
  dbCard->setActive(F);
}
  
template<typename T>
void
PhysicsCards::setPTRAC(const std::string& kY,
		       const T& Val)
  /*!
    Set the ptrac card
    \param kY :: key Value of Cardd
    \param Val :: Value to seet
   */
{
  ELog::RegMethod RegA("PhysicsCards","setPTRAC");
  PTRAC->setRegItem(kY,Val);
  return;
}

template<typename T>
void
PhysicsCards::setDBCN(const std::string& kY,
                      const T& Val)
  /*!
    Set the dbcn card
    \param kY :: key Value of Cardd
    \param Val :: Value to seet
   */
{
  ELog::RegMethod RegA("PhysicsCards","setDBCN");
  dbCard->setRegItem(kY,Val);
  return;
}
  
long int
PhysicsCards::getRNDseed() const
  /*!
    Get the random number seed
    \return seed
   */
{
  return  (mcnpVersion==10) ?
    dbCard->getItem<long int>("rndSeed") :
    RAND->getItem<long int>("SEED");
}
  
void
PhysicsCards::substituteCell(const int oldCell,const int newCell)
  /*!
    Substitute all cells in all physics cards that use cells
    \param oldCell :: old cell number
    \param newCell :: new cell number
   */
{
  ELog::RegMethod RegA("PhysicsCards","substituteCell");

  std::set<int>::iterator vc=histpCells.find(oldCell);
  if (vc!=histpCells.end())
    {
      histpCells.erase(vc);
      histpCells.emplace(newCell);
    }

  for(PhysImp* PI : PImpVec)
    PI->renumberCell(oldCell,newCell);

  PWTCard->renumberCell(oldCell,newCell);
  ExtCard->renumberCell(oldCell,newCell);

  return;
}
  
void
PhysicsCards::setMode(std::string Particles) 
  /*!
    Set the mode card if not already set
    \param Particles :: Particle list
  */
{
  ELog::RegMethod RegA("PhysicsCards","setMode");

  mode.clear();
  std::string item;
      while(StrFunc::section(Particles,item))
	mode.addElm(item);
  return;
}
      
void
PhysicsCards::rotateMaster()
  /*!
    Apply the global rotation sytem
    to the physics cards that need it.
  */
{
  return;
}
  
void
PhysicsCards::setPrintNum(std::string Numbers) 
  /*!
    Set the print card if not already set
    \param Numbers ::  list of number [not checked]
  */
{
  ELog::RegMethod RegA("PhysicsCards","setPrintNum");
  if (printNum.empty())
    {
      int item;
      while(StrFunc::section(Numbers,item))
	printNum.push_back(item);
    }
  return;
}

void
PhysicsCards::writeHelp(const std::string& keyName) const
  /*!
    Write out help about a physics card
    \param keyName :: Card name
  */
{
  ELog::RegMethod RegA("PhysicsCards","writeHelp");

  if (keyName=="ptrac")
    PTRAC->writeHelp(ELog::EM.Estream());
  else if (keyName=="rand")
    RAND->writeHelp(ELog::EM.Estream());
  else if (keyName=="event" || keyName=="dbcn")
    dbCard->writeHelp(ELog::EM.Estream());

  ELog::EM<<ELog::endDiag;
  return;
}

void 
PhysicsCards::write(std::ostream& OX,
		    const std::vector<int>& cellOutOrder,
		    const std::set<int>& voidCells) const 
  /*!
    Write out each of the cards
    \param OX :: Output stream
    \param cellOutOrder :: Cell List
    \param voidCell :: List of void cells
    \todo Check that histp does not need a line cut.
  */
{
  ELog::RegMethod RegA("PhysicsCards","write");

  dbCard->write(OX);

  OX<<"nps "<<nps<<std::endl;
  if (voidCard)
    OX<<"void"<<std::endl;
  
  if (histp)
    {
      std::ostringstream cx;
      cx<<"histp";
      if (!histpCells.empty())
	{
	  cx<<" -500000000 ";
	  for(const int CN : histpCells)
	    cx<<" "<<CN;
	}
      StrFunc::writeMCNPX(cx.str(),OX);
    }
  if (mcnpVersion!=10) RAND->write(OX);
  PTRAC->write(OX);
  
  mode.write(OX);

  for(const PhysImp* PI : PImpVec)
    PI->write(OX,wImpOut,cellOutOrder);
  
  PWTCard->write(OX,cellOutOrder,voidCells);

  for(const PhysCard* PC : PCards)
    PC->write(OX);

  for(const std::string& PC : Basic)
    StrFunc::writeMCNPX(PC,OX);

  ExtCard->write(OX,cellOutOrder,voidCells);
  DXTCard->write(OX);
  
  LEA.write(OX);
  
  if (!prdmp.empty())
    StrFunc::writeMCNPX("prdmp "+prdmp,OX);
  
  if (!printNum.empty())
    {
      std::ostringstream cx;
      cx<<"print ";
      copy(printNum.begin(),printNum.end(),
	   std::ostream_iterator<int>(cx," "));
      StrFunc::writeMCNPX(cx.str(),OX);
    }

  return;
}

///\cond TEMPLATE
  
template void
PhysicsCards::setPTRAC(const std::string&,
                       const std::string&);
template void
PhysicsCards::setPTRAC(const std::string&,
                       const double&);
template void
PhysicsCards::setPTRAC(const std::string&,
                       const long int&);

template void
PhysicsCards::setDBCN(const std::string&,
                       const std::string&);
template void
PhysicsCards::setDBCN(const std::string&,
                       const double&);
template void
PhysicsCards::setDBCN(const std::string&,
                       const long int&);

  
template PStandard*
PhysicsCards::addPhysCard(const std::string&,const std::string&);

template PSimple*
PhysicsCards::addPhysCard(const std::string&,const std::string&);

///\endcond TEMPLATE


} // NAMESPACE physicsSystem
      
   
