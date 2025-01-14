/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   attachCompInc/FrontBackCut.h
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
#ifndef attachSystem_FrontBackCut_h
#define attachSystem_FrontBackCut_h

class Simulation;

namespace attachSystem
{
  
/*!
  \class FrontBackCut
  \version 1.0
  \author S. Ansell
  \date September 2016
  \brief FrontBackCut unit  
  
  System to add this to components that need to be cut
*/

class FrontBackCut :
  public ExternalCut
{
 public:

  FrontBackCut();
  FrontBackCut(const FrontBackCut&);
  FrontBackCut& operator=(const FrontBackCut&);
  virtual ~FrontBackCut();

  void setFront(const ExternalCut&);
  void setBack(const ExternalCut&);
  void setFront(const int);
  void setBack(const int);
  void setFront(const std::string&);
  void setBack(const std::string&);
  void setFront(const HeadRule&);
  void setBack(const HeadRule&);
  void setFront(const attachSystem::FixedComp&,const long int);
  void setBack(const attachSystem::FixedComp&,const long int);
  void setFront(const attachSystem::FixedComp&,const std::string&);
  void setBack(const attachSystem::FixedComp&,const std::string&);

  void setFrontDivider(const std::string&);
  void setBackDivider(const std::string&);
  void setFrontDivider(const HeadRule&);
  void setBackDivider(const HeadRule&);

  void createLinks(attachSystem::FixedComp&,
		   const Geometry::Vec3D&,const Geometry::Vec3D&);
  void createFrontLinks(attachSystem::FixedComp&,
		   const Geometry::Vec3D&,const Geometry::Vec3D&);
  void createBackLinks(attachSystem::FixedComp&,
		   const Geometry::Vec3D&,const Geometry::Vec3D&);
  
  /// Flag accessor
  bool frontActive() const { return isActive("front"); }
  /// Flag accessor
  bool backActive() const { return isActive("back"); }


  std::string frontRule() const;
  std::string backRule() const;

  std::string frontComplement() const;
  std::string backComplement() const;

  std::string frontBridgeRule() const;
  std::string backBridgeRule() const;

  void getShiftedFront(ModelSupport::surfRegister&,const int,
		       const Geometry::Vec3D&,const double) const;
  void getShiftedBack(ModelSupport::surfRegister&,const int,
		      const Geometry::Vec3D&,const double) const;
  
  /// accessor
  const HeadRule& getFrontRule() const { return getRule("front"); }
  /// accessor
  const HeadRule& getBackRule() const { return getRule("back"); }
  /// accessor
  const HeadRule& getFrontBridgeRule() const { return getDivider("front"); }
  /// accessor
  const HeadRule& getBackBridgeRule() const { return getDivider("back"); }

  Geometry::Vec3D frontInterPoint(const Geometry::Vec3D&,
				  const Geometry::Vec3D&) const;
  Geometry::Vec3D backInterPoint(const Geometry::Vec3D&,
				 const Geometry::Vec3D&) const;
};

}

#endif
 
