/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   Process/Process.cxx
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
#include <fstream>
#include <sstream>
#include <cmath>
#include <complex>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <array>

#include "Exception.h"
#include "FileReport.h"
#include "GTKreport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "support.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "inputParam.h"
#include "Quaternion.h"
#include "Surface.h"
#include "surfRegister.h"
#include "objectRegister.h"
#include "Quadratic.h"
#include "Plane.h"
#include "Rules.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "HeadRule.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "Importance.h"
#include "Object.h"
#include "groupRange.h"
#include "objectGroups.h"
#include "Simulation.h"
#include "Zaid.h"
#include "MXcards.h"
#include "Material.h"
#include "DBMaterial.h"

#include "Simulation.h"
#include "Process.h"

namespace ModelSupport
{

std::set<int>
getActiveMaterial(const Simulation& System,
		  std::string material)
  /*!
    Given a material find the active cells
    \param material : material name to use
    \return set of active materials (matching material)
  */
{
  ELog::RegMethod RegA("Process[F]","getActiveMaterial");

  const ModelSupport::DBMaterial& DB=
    ModelSupport::DBMaterial::Instance();
  
  std::set<int> activeMat=System.getActiveMaterial();
  if (material=="All" || material=="all")
    return activeMat;
  
  bool negKey(0);
  if (material.size()>1 && material.back()=='-')
    {
      negKey=1;
      material.pop_back();
    }
  
  if (!DB.hasKey(material))
    throw ColErr::InContainerError<std::string>
      (material,"Material not in material database");
  const int matID=DB.getIndex(material);

  if (negKey)
    {
      activeMat.erase(matID);
      return activeMat;
    }
  if (activeMat.find(matID)==activeMat.end())
    throw ColErr::InContainerError<std::string>
      (material,"Not present in model");
  
  std::set<int> activeOut;
  activeOut.insert(matID);
  return activeOut;
}

std::set<int>
getActiveCell(const objectGroups& OGrp,
	      const std::string& cell)
  /*!
    Given a cell find the active cells
    \param OGrp :: Active group						
    \param cell : cell0 name to use
    \return set of active cell numbers 
  */
{
  ELog::RegMethod RegA("Process[F]","getActiveCell");

  const std::vector<int> Cells=OGrp.getObjectRange(cell);
  std::set<int> activeCell(Cells.begin(),Cells.end());

  activeCell.erase(1);
  return activeCell;
}
  


} // NAMESPACE ModelSupport
