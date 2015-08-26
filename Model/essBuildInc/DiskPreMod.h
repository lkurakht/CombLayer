/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   essBuildInc/DiskPreMod.h
 *
 * Copyright (c) 2004-2015 by Stuart Ansell
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
#ifndef essSystem_DiskPreMod_h
#define essSystem_DiskPreMod_h

class Simulation;

namespace essSystem
{
  class CylFlowGuide;
/*!
  \class DiskPreMod
  \author S. Ansell
  \version 1.0
  \date May 2015
  \brief Specialized for a cylinder pre-mod under moderator
*/

class DiskPreMod : public attachSystem::ContainedComp,
    public attachSystem::LayerComp,
    public attachSystem::FixedComp,
    public attachSystem::CellMap
{
 private:
  
  const int modIndex;             ///< Index of surface offset
  int cellIndex;                  ///< Cell index
  
  double zStep;                   ///< Step away from target
  double outerRadius;             ///< Outer radius of Be Zone
  
  std::vector<double> radius;         ///< cylinder radii [additive]
  std::vector<double> height;         ///< Full heights [additive]
  std::vector<double> depth;          ///< full depths [additive]
  std::vector<double> width;          ///< Widths [additive]
  std::vector<int> mat;               ///< Materials 
  std::vector<double> temp;           ///< Temperatures

  size_t NWidth;                      ///< Number of widths active
  int engActive;                  ///< Engineering active flag
  /// Flow guide pattern inside DiskPreMod (engineering detail)
  std::shared_ptr<CylFlowGuide> InnerComp; 

  double tiltAngle;                   ///< tilting angle
  double tiltRadius;                  ///< radius where tilting starts
  
  void populate(const FuncDataBase&,const double,const double);
  void createUnitVector(const attachSystem::FixedComp&,const long int,
			const bool);

  void createSurfaces(const bool);
  void createObjects(Simulation&, const bool);
  void createLinks();

 public:

  DiskPreMod(const std::string&);
  DiskPreMod(const DiskPreMod&);
  DiskPreMod& operator=(const DiskPreMod&);
  virtual DiskPreMod* clone() const;
  virtual ~DiskPreMod();

  virtual Geometry::Vec3D getSurfacePoint(const size_t,const size_t) const;
  virtual int getLayerSurf(const size_t,const size_t) const;
  virtual std::string getLayerString(const size_t,const size_t) const;

  /// total height of object
  double getZOffset() const { return zStep; }
  double getHeight() const
    { return (depth.empty()) ? 0.0 : depth.back()+height.back(); }

  void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int,const bool,const double,const double, const bool);

};

}

#endif
 
