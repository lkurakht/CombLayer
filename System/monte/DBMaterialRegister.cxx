/*********************************************************************
  CombLayer : MCNP(X) Input builder

 * File:   monte/DBMaterialRegister.cxx
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
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <tuple>

#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "Zaid.h"
#include "MXcards.h"
#include "Material.h"
#include "DBMaterial.h"

namespace ModelSupport
{


void
DBMaterial::initMaterial()
  /*!
     Initialize the database of materials
   */
{
  ELog::RegMethod RegA("DBMaterial","initMaterial");

  const std::string MLib="hlib=.70h pnlib=70u";

  MonteCarlo::Material MObj;
  // THREE ULTRA SPECIAL MATERIALS!!!
  MObj.setMaterial(-2,"InValid","00000.00c 1.0","",MLib);
  setMaterial(MObj);
  MObj.setMaterial(-1,"Empty","00000.00c 1.0","",MLib);
  setMaterial(MObj);
  MObj.setMaterial(0,"Void","00000.00c 1.0","",MLib);
  setMaterial(MObj);
  cloneMaterial("InValid","Null");

  MObj.setMaterial(1,"MachineTugnsten",
		   "26000.55c 0.001773 28000.50c 0.003935 74182.70c 0.0165487 "
		   "74183.70c 0.0089819772 74184.70c 0.0192722  74186.70c "
		   " 0.018014274","",MLib);
  setMaterial(MObj);

  // Density --> 7.65g/cc
  MObj.setMaterial(3,"Stainless304",
		   "6000.70c 3.18640e-4 14028.70c 1.70336e-3 "
		   "15031.70c 6.95038e-5 16032.70c 4.47520e-5 "
		   "24000.50c 1.74813e-2 25055.70c 1.74159e-3 "
		   "26054.70c 3.380e-3 26056.70c 5.3455e-2 "
		   "26057.70c 1.282177e-3 27059.70c 2.453e-4 "
                   "28000.50c 8.15128e-3",
		   "",MLib);
  setMaterial(MObj);

  // Material #4 : Methane + 10% Al.
  MObj.setMaterial(4,"CH4inFoam",
		   "6000.70c 0.0167364 1001.70c 0.066945 13027.70c 0.0060185",
		   "smeth.26t al.20t",MLib);
  setMaterial(MObj);

  // Material #5: Aluminum 5083
  MObj.setMaterial(5,"Aluminium",
		   "13027.70c 0.054381 12024.70c 0.002070 12025.70c "
		   "0.0002621 12026.70c 0.0002885 14028.70c 0.000217 "
		   "22048.70c 0.000087 24052.70c 0.000078 24053.70c 0.000010 "
		   "25055.70c 0.000408 26056.70c 0.000214 26057.70c 0.000005 "
		   "29063.70c 0.00004  29065.70c 0.00002 "
		   "30000.70c 0.000145 ","al.20t",MLib);
  setMaterial(MObj);

  // Material #6: Gadolinium
  // Total atom density 0.03044578 - 7.95 grams per cc
  MObj.setMaterial(6,"Gadolinium",
		   "64152.55c 6.089e-6 64154.55c 6.63718e-4 "
		   "64155.55c 4.50597e-3 64156.55c 6.23225e-3 "
		   "64157.55c 4.764764e-3 64158.55c 7.56273e-3 "
		   "64160.55c 6.65545e-3 ","",MLib);
  setMaterial(MObj);
  //  Material #7: Cadmium
  //  Total atom density 0.04741207 - 8.85 grams per cc
  MObj.setMaterial(7,"Cadmium","48000.42c 0.04741207","",MLib);
  setMaterial(MObj);

  //  Material #8: Inconel
  // Total atom density 8.3309e-02 - 7.8246g/cc
  MObj.setMaterial(8,"Inconnel",
		   "28000.50c 4.2821e-02  24000.50c 1.6328e-02 "
		   "26000.55c 2.4160e-02","",MLib);
  setMaterial(MObj);
  // Material #9: helium at atmospheric pressure
  // Total atom density 2.45e-05
  MObj.setMaterial(9,"helium","2004.70c 2.45e-5","",MLib);
  setMaterial(MObj);

  // Material #10: Beryllium + heavy water
  // Total atom density 0.1187475
  MObj.setMaterial(10,"BeInD2O",
		   "4009.80c 0.0988968 1001.70c 3.31e-5 1002.70c 0.0132007 "
		   "8016.70c 0.0066169","hwtr.01t be.60t",MLib);
  setMaterial(MObj);

  // Material #11: Light water
  // Total atom density 0.10028340 - 1.0 grams per cc
  MObj.setMaterial(11,"H2O",
		   "1001.70c 0.06684557 1002.70c 0.00001003 "
		   "8016.70c 0.03342780","lwtr.01t",MLib);
  setMaterial(MObj);

  // Material #15 ZrH2 number density == 0.1087 on a density of 5.61g/cc
  MObj.setMaterial(15,"ZrH2","1001.70c 2.3316e-3 "
		   "40000.60c 0.10636","h/zr.01t zr/h.01t",MLib);
  setMaterial(MObj);

  // Material #16: Liquid para-hydrogen (original)
  //Total atom density 0.041957 -  20 K; 0.07021 grams per cc
  MObj.setMaterial(16,"paraH2-org","1001.70c 0.041957","parah.20t",MLib);
  setMaterial(MObj);

  // Material #17 Magnox
  // Total atom density 0.04424 - 1.74 gm/cc
  MObj.setMaterial(17,"Magnox","12000.60c 0.03915 13027.70c "
		   "3.32e-3 4009.70c 1.77e-3","",MLib);
  setMaterial(MObj);

  //Material #22  Cooled Be9 [nat 100%]
  MObj.setMaterial(22,"Be77K","4009.80c 0.0988968","be.77t",MLib);
  setMaterial(MObj);

  // Material #23 Lead  11340kg m-3 [0.03296371]
  //204Pb 1.4 206Pb  24.1 207Pb 22.1  208Pb 	52.4
  MObj.setMaterial(23,"Lead","82206.70c 0.00794248 "
		   "82207.70c 0.00728335 82208.70c 0.0172691","",MLib);
  setMaterial(MObj);

  // Material #24 Lead  11340kg m-3 [0.03296371] + Sb at 1.2%
  //204Pb 1.4 206Pb  24.1 207Pb 22.1  208Pb 	52.4
  MObj.setMaterial(24,"Lead+Sb",
		   "51121.70c 0.000227377 51123.70c 0.000170066 "
		   "82204.70c 0.000458119 82206.70c 0.00788619 "
		   "82207.70c 0.00723174 82208.70c 0.0171467 ",
		   "",MLib);
  setMaterial(MObj);

  // Material #25: Liquid para-hydrogen (Granada)
  // Total atom density 0.041957 -  20 K; 0.07021 grams per cc
  MObj.setMaterial(25,"ParaH2","1001.70c 0.041957","ph215.00t",MLib);
  setMaterial(MObj);

  // Material #26 is solid methane (90v/o) and Aluminum (10v/o) 22K
  MObj.setMaterial(26,"CH4+Al22K","6012.70c -0.3439 "
		   "1001.70c -0.1145 13027.70c -0.2698",
		   "smeth.22t al.20t",MLib);
  setMaterial(MObj);

  //Material #27 is solid methane (90v/o) and Aluminum (10v/o) 30K
  MObj.setMaterial(27,"CH4+Al30K","6012.70c -0.3439 1001.70c -0.1145 "
		   "13027.70c -0.2698","smeth.30t al.20t",MLib);
  setMaterial(MObj);

  // Material #28 is solid methane (90v/o) and Aluminum (10v/o) 26K
  MObj.setMaterial(28,"CH4+Al26K",
		   "6012.70c  -0.3439 1001.70c -0.1145 13027.70c -0.2698",
		   "smeth.01t al.20t",MLib);
  setMaterial(MObj);

  // Material #29 is liquid methane at 100K (based on kernel T)
  MObj.setMaterial(29,"CH4Liq",
		   "1001.70c 0.066183 6000.70c 0.016546",
		   "lmeth.01t",MLib);
  setMaterial(MObj);

  // Material #30 Solid ICE at 26K Total atom dens 0.10028340
  MObj.setMaterial(30,"Ice26K",
		   "1001.70c 0.06684557 1002.70c 0.00001003 "
		   "8016.70c 0.03342780",
		   "ice26.00t",MLib);
  setMaterial(MObj);

  // Material #31 Heavy water
  // Total atom density 0.09925325 -
  // (99.75 a% D2O & 0.25 a% H2O) 1.1 grams per cc
  MObj.setMaterial(31,"D2O",
		   "1001.70c 0.00016542 1002.70c 0.06600341 "
		   "8016.70c 0.03308442","hwtr.01t",MLib);
  setMaterial(MObj);

  // Material #32 Tantalum (old version)
  // Total atom density 0.05524655 - 16.60 grams per cc
  MObj.setMaterial(32,"Tantalum","73181.70c 0.05524655","",MLib);
  setMaterial(MObj);

  // Material #33 Nickel
  // Total atom density 0.091321 - 8.9 grams per cc
  MObj.setMaterial(33,"Nickel",
		   "28058.70c 0.062169 28060.70c 0.02394719 "
		   "28061.70c 0.00104097 28062.70c 0.00331906 "
		   "28064.70c 0.00084527","",MLib);
  setMaterial(MObj);


  // Material #37: Beryllium solid at RT
  // Total atom density 0.1187475
  MObj.setMaterial(37,"Be300K","4009.70c 0.1234855","be.60t",MLib);
  setMaterial(MObj);
// Material #38 Solid Pure Tungsten (0.063057)
  MObj.setMaterial(38,"Tungsten",
		   "74182.70c 0.016871 74183.70c 0.00911077 "
		   "74184.70c 0.019507618 74186.70c 0.018100573 ","",MLib);
  setMaterial(MObj);

  // Material #39: Aluminum 2024
  // Total atom density 0.06012961 - 2.76 grams per cc
  MObj.setMaterial(39,"Al2024",
		   "12000.60c 1.02876e-3 13027.70c 5.77646e-2 "
		   "25055.70c 1.82052e-4 "
		   "29000.50c 1.15420e-3","al.20t",MLib);
  setMaterial(MObj);

  // Material #40  Sapphire :
  MObj.setMaterial(40,"Al2O3","13027.70c 0.03333333 "
		   "8016.70c 0.0666666", "",MLib);
  setMaterial(MObj);

  // Material #41 Silicon
  MObj.setMaterial(41,"SiPowder",
		   "14028.70c 0.0460848 14029.70c 0.00234 "
		   "14030.70c 0.0015403","",MLib);
  setMaterial(MObj);

  // Material #42 Niobium
  MObj.setMaterial(42,"Niobium","41093.70c 0.055558","",MLib);
  setMaterial(MObj);

  // Material #43  Low density Al foam (pure)
  MObj.setMaterial(43,"AlFoam","13027.70c 0.0054381","al.20t",MLib);
  setMaterial(MObj);

  // Material #44  Liquid methane + 10% Al at 100K
  MObj.setMaterial(44,"CH4Liq+Al","1001.70c 0.0595647 "
		   "6000.70c 0.014891 13027.70c 0.0058254",
		   "lmeth.01t al.20t",MLib);
  setMaterial(MObj);

  // Material #45: Aluminum 2214
  // Total atom density 0.058254 - 2.65 grams per cc (??)
  // Mg 0.7 : Si 0.7 : Fe 0.5 : NiTi 0.15 : Cr 0.15 : Mn 0.7 :
  // Fe 0.4 : Cu 0.1 : Zn 0.25 :
  MObj.setMaterial(45,"Al2214","12000.60c 0.000468292 "
		   "14028.70c 0.000405257 25055.70c 0.000266369 "
		   "26054.70c 8.50911e-06 26056.70c 0.000133575 "
		   "26057.70c 3.08482e-06 26058.70c 4.10533e-07 "
		   "29063.70c 0.000796451 29065.70c 0.000354989 "
		   "28058.70c 1.8863e-05 28060.70c 7.26565e-06 "
		   "28061.70c 3.15583e-07 "
		   "28062.70c 1.00687e-06 30000.70c 6.21466e-05 50000.40c 3.12712e-05 "
		   "13027.70c 0.0555923",
		   "al.20t",MLib);


  setMaterial(MObj);
  // Material #46 Boron (pure)
  MObj.setMaterial(46,"Boron","5010.70c 0.0273024 "
		   "5011.70c 0.1098957","",MLib);
  setMaterial(MObj);

  // Material #47 B4C
  // Desinty 2.52g/cc
  MObj.setMaterial(47,"B4C","5010.70c 0.021741 "
		   "5011.70c 0.087512 6000.70c 0.027313","",MLib);
  setMaterial(MObj);

  // Material #48 Poly:
  MObj.setMaterial(48,"Poly","6000.70c 0.0333333 "
		   "1001.70c 0.0666666666","poly.01t",MLib);
  MObj.setDensity(-0.91);
  setMaterial(MObj);


  // Material #49 Regular concrete
  // Regular concrete at 2.339 g/cc [supposedly]
  MObj.setMaterial(49,"Concrete",
		   "1001.70c  7.76555E-03 1002.70c  1.16501E-06 "
		   "8016.70c  4.38499E-02 11023.70c 1.04778E-03 "
		   "12000.60c 1.48662E-04 13027.70c 2.38815E-03 "
		   "14028.70c 1.58026E-02 16032.70c 5.63433E-05 "
		   "19000.60c 6.93104E-04 20000.60c 2.91501E-03 "
		   "26054.70c 1.84504E-05 26056.70c 2.86826E-04 "
		   "26057.70c 6.56710E-06 26058.70c 8.75613E-07",
		   "lwtr.01t",MLib);
  setMaterial(MObj);

  // Material #50 High density concrete:: 3.848g/cc
  MObj.setMaterial(50,"HDConcrete",
		   "1001.70c  9.03819E-03 1002.70c  1.35593E-06 "
		   "8016.70c  4.92287E-02 8017.60c  1.97389E-05 "
		   "11023.70c 1.02944E-05 12000.60c 2.09352E-04 "
		   "13027.70c 4.86813E-04 14028.70c 1.69797E-03 "
		   "15031.70c 7.64087E-06 16000.60c 8.11907E-05 "
		   "19000.60c 1.21062E-05 20000.60c 2.47130E-03 "
		   "22000.60c 2.64454E-04 25055.70c 3.87709E-05 "
		   "26054.70c 1.44497E-03 26056.70c 2.27918E-02 "
		   "26057.70c 5.21380E-04 26058.70c 6.95173E-05",
		   "lwtr.01t",MLib);
  setMaterial(MObj);

  // Material #51: Lithium Nitride
  // Total atom density 0.0219560 - 1.270 g/cc
  MObj.setMaterial(51,"Li3N",
		   "3006.60c  1.25007E-03  3007.60c  1.52199E-02 "
		   "7014.70c  5.46980E-03 7015.55c  2.02030E-05","",MLib);
  setMaterial(MObj);

  // Material #52: 5% borated poly
  // Total atom density 0.1154 atom/barn-cm
  MObj.setMaterial(52,"B-Poly","1001.70c  0.0752 6000.70c "
		   "0.0376 5010.70c  0.00051 5011.70c  0.002053",
		   "poly.01t",MLib);
  setMaterial(MObj);

  // Material #53: Lithium
  // Total atom density 0.0219560 - 1.270 g/cc
  MObj.setMaterial(53,"Lithium","3006.70c 0.0047136 "
		   "3007.70c 0.0424228","",MLib);
  setMaterial(MObj);

  // Material #54 Standard Cast Iron [Grey -ASTM A48]:
  // Carbon 3.4%w/w Si 1.8, Mn 0.5 Rest Fe. [ 7.05g/cc]
  MObj.setMaterial( 54,"CastIron","6000.70c 0.00636 "
		    "14028.70c 0.0051404 25055.70c 0.000386 "
		    "26054.70c 0.004190 26056.70c 0.065789 26057.70c 0.00152",
		    "",MLib);
  setMaterial(MObj);

  // Material #55 Silicon with no-bragg
  MObj.setMaterial(55,"SiCrystal","14028.70c 0.05","si.80t",MLib);
  setMaterial(MObj);

  // Material #56 Tin [Density 7310kg/m3]:
  MObj.setMaterial(56,"Tin","50000.42c 0.037088","",MLib);
  setMaterial(MObj);

  // Material #57: Lithium Carbonate
  // Total atom density 0.103 Atom/A3 - 2.11 g/cc
  MObj.setMaterial(57,"LithiumCarbonate",
		   "3006.70c 1.2875e-3 3007.70c 1.5889e-2 "
		   "6000.70c 1.7166e-2 8016.70c 5.15e-2","",MLib);
  setMaterial(MObj);

  // Material #58 : Methane + 10% Al [type 2 at 20K]
  MObj.setMaterial(58,"CH4TypeII","6000.70c 0.01841004 "
		   "1001.70c 0.0736395","smeth.02t",MLib);
  setMaterial(MObj);

  //Material #59 Nimonic 8.19g/cc
  // Total atom density 0.091321 - 8.9 grams per cc

  MObj.setMaterial(59,"Nimonic","28058.70c 0.0444126 28060.70c 0.0171069 "
		   "28061.70c 0.000743037 28062.70c 0.00237067 "
		   "28064.70c 0.000603432 24052.70c 0.0169356 "
		   "24053.70c 0.0042339 ","",MLib);
  setMaterial(MObj);

  // Material #60 Air (Dry, near sea level)
  // Total atom density 4.9873E-05 - 1.2045E-03 grams per cc
  MObj.setMaterial(60,"Air","6000.70c 7.0000e-9 7014.70c 3.91280E-05 "
		   "8016.70c 1.05120E-05 18036.70c 8.1682E-10 "
		   "18038.70c 1.3987E-10 18040.70c 2.3207E-07 ",
		   "",MLib);
  setMaterial(MObj);

  // Material #61 Moly [10.28g/cc : number density 0.06399]

  MObj.setMaterial(61,"Molybdimum","42092.70c 0.00953094 "
		   "42094.70c 0.00595603 42095.70c 0.0102601 "
		   "42096.70c 0.0107634 42097.70c 0.00616898 "
		   "42098.70c 0.0156096 42100.70c 0.00623996 ",
		   "",MLib);
  setMaterial(MObj);

  // Material #62 Para : Ortho 50/50 hydrogen
  MObj.setMaterial(62,"ParaOrtho","1001.70c 0.0209785 1004.70c 0.0209785",
		   "parah.20t orthh.99t",MLib);
  setMaterial(MObj);

  // Material #63 Ortho Pure hydrogen
  MObj.setMaterial(63,"Ortho","1001.70c 0.041957","orthh.99t",MLib);
  setMaterial(MObj);

    // Material #64 : Methane + 10% Al [type 2  about 4K]
  MObj.setMaterial(64,"CH4AlTypeII",
		   "6000.70c 0.01841004 1001.70c 0.0736395",
		   "smeth.03t",MLib);
  setMaterial(MObj);

  // Material #65 Regular concrete [half density]
  // Regular concrete at 2.339/2 g/cc [supposedly]
  MObj.setMaterial(65,"HalfConcrete","1001.70c 3.88277E-03 "
		   "1002.70c 0.582505E-06 "
		   "8016.70c  2.19249E-02 11023.70c 0.523890E-03 "
		   "12000.60c 0.74331E-04 13027.70c 1.194075E-03 "
		   "14028.70c 0.79013E-02 16032.70c 2.817165E-05 "
		   "19000.60c 3.46551E-04 20000.60c 1.457500E-03 "
		   "26054.70c 0.92252E-05 26056.70c 1.434125E-04 "
		   "26057.70c 3.28355E-06 26058.70c 4.378065E-07",
		   "",MLib);

  setMaterial(MObj);
  // Material #66 Boral
  // density 0.084235
  MObj.setMaterial(66,"B4CAluminium","5010.70c 0.006885 "
		   "5011.70c 0.031367 6000.70c 0.009563 "
		   "13027.70c 0.036420","",MLib);
  setMaterial(MObj);

  // Material #67 NELCO Concrete
  // density 2.455g/cc
  MObj.setMaterial(67,"NELCOConcrete",
		   "26054.70c 1.547397e-05 26056.70c 2.429082e-04 "
		   "26057.70c 5.609809e-06 26058.70c 7.465626e-07 "
		   "20040.70c 8.582522e-03 20042.70c 5.728115e-05 "
		   "20043.70c 1.195202e-05 20044.70c 1.846808e-04 "
		   "20046.70c 3.541339e-07 20048.70c 1.655576e-05 "
		   "14028.70c 6.797051e-03 14029.70c 3.451377e-04 "
		   "14030.70c 2.275173e-04 "
		   "1001.70c 1.466620e-02 1002.70c 1.686807e-06 "
		   "8016.70c 5.545897e-02","",MLib);
  setMaterial(MObj);

  // Material #68 Uranium for reactor [delft]
  // Somewhat burnt
  //  Minors left out
  // 95241  3.677946E-09
  // 95243  1.660551E-10
  // 96242  2.660332E-10
  // 96243  5.001810E-13
  MObj.setMaterial(68,"Uranium",
		   "5010.70c  1.800000E-07 5011.70c  7.330000E-07 "
		   "13027.70c 3.491000E-02 14028.70c 7.683000E-03 "
		   "92234.70c 1.453099E-05 92235.70c 1.719715E-03 "
		   "92236.70c 8.740910E-05 92237.70c 3.363964E-08 "
		   "92238.70c 8.662198E-03 93237.70c 8.149635E-07 "
		   "93239.70c 1.898293E-07 94238.70c 3.055927E-08 "
		   "94239.70c 2.874713E-05 94240.70c 2.248326E-06 "
		   "94241.70c 3.508395E-07 94242.70c 1.371115E-08 ","",MLib);
  setMaterial(MObj);

  // #69 Hafnium
  MObj.setMaterial(69,"Hafnium",
		   "72174.70c 7.18534e-05 72176.70c 0.00236218 "
		   "72177.70c 0.00835296 72178.70c 0.012251 "
		   "72179.70c 0.00611652 ","",MLib);
  setMaterial(MObj);

  // Material #70 Glass (Na/Ca/SiO2 : 2.44g/cc)
  MObj.setMaterial(70,"Glass",
		   "20040.70c 2.719913e-03 20042.70c 1.815314e-05 "
		   "20043.70c 3.787750e-06 20044.70c 5.852775e-05 "
		   "20046.70c 1.122296e-07 20048.70c 5.246735e-06 "
		   "11023.70c 6.423108e-03  8016.70c 4.307240e-02 "
		   "14028.70c 1.708774e-02 14029.70c 8.676740e-04 "
		   "14030.70c 5.719771e-04 ","",MLib);
  setMaterial(MObj);


  // Material #71 Steel (proposed for Chipir Collimators)
  // similar to P355NL1  (s/. EN 10028-3)
  // Total atom density 0.08432 - 7.8 grams per cc (assumed)
  MObj.setMaterial(71,"Steel71",
		   "6000.70c 1.011868e-04 14028.70c 2.951280e-04 "
		   "24000.50c 1.686446e-04 25055.70c 5.059338e-04 "
		   "26054.70c 4.841401e-03 26056.70c 7.599964e-02 "
		   "26057.70c 1.755163e-03 26058.70c 2.335800e-04 "
		   "28058.70c 1.722180e-04 28060.70c 6.633503e-05 "
		   "28061.70c 2.881261e-06 28062.70c 9.192715e-06 "
		   "28064.70c 2.339918e-06 29063.70c 1.166515e-04 "
		   "29065.70c 5.199313e-05 ","",MLib);
  setMaterial(MObj);

    // Material #72 : Methane + 10% Al.+ 0.18% number density Ar
    // Mole volume 0.18%
  MObj.setMaterial(72,"CH4Al+Argon",
		   "6012.70c 0.0172756 1001.70c 0.0690944 "
		   "13027.70c 0.0054381 "
		   "18036.70c 1.040783e-07 18038.70c 1.962387e-08 "
		   "18040.70c 3.107482e-05 ","smeth.26t al.20t",MLib);
  setMaterial(MObj);

  // Material #73 : Copper
  // Density : 8.91g/cc rho=0.084438

  MObj.setMaterial(73,"Copper","29063.70c 0.058389212 "
		   "29065.70c 0.02604927","",MLib);
  setMaterial(MObj);

   //Material #74: ChipIR Guide Steel (K Jones spec)
   //Density : 7.800 g/cc
  MObj.setMaterial(74,"ChipIRSteel",
		   "5010.70c 3.459223e-06 5011.70c 1.392381e-05 "
		   "6000.70c 4.694025e-04 "
		   "7014.70c 3.019615e-05 "
		   "13027.70c 2.176586e-04 "
		   "14028.70c 1.672824e-04 "
		   "25055.70c 3.420733e-04 "
		   "15031.70c 7.584178e-05 "
		   "16032.70c 5.563524e-05 16033.70c 4.454102e-07 "
		   "16034.70c 2.514223e-06 16036.70c 1.172132e-08 "
		   "26054.70c 4.849594e-03 26056.70c 7.612826e-02 "
		   "26057.70c 1.758134e-03 26058.70c 2.339753e-04 "
		   "27059.70c 1.594419e-05 "
		   "29063.70c 7.671067e-05 29065.70c 3.419098e-05 "
		   "28058.70c 5.450388e-05 28060.70c 2.099384e-05 "
		   "28061.70c 9.118672e-07 28062.70c 2.909329e-06 "
		   "28064.70c 7.405418e-07 "
		   "24050.70c 3.926008e-06 24052.70c 7.570916e-05 "
		   "24053.70c 8.584811e-06 24054.70c 2.136941e-06 "
		   "42092.70c 7.267852e-06 42094.70c 4.530164e-06 "
		   "42095.70c 7.796779e-06 42096.70c 8.168987e-06 "
		   "42097.70c 4.677088e-06 42098.70c 1.181761e-05 "
		   "42100.70c 4.716268e-06 "
		   "41093.70c 5.056930e-06 "
		   "23051.42c 9.222311e-06 "
		   "50112.70c 4.058814e-08 50114.70c 2.761667e-08 "
		   "50115.70c 1.422677e-08 50116.70c 6.084036e-07 "
		   "50117.70c 3.213576e-07 50118.70c 1.013448e-06 "
		   "50119.70c 3.594352e-07 50120.70c 1.363259e-06 "
		   "50122.70c 1.937351e-07 "
		   "22046.70c 8.097528e-07 22047.70c 7.302498e-07 "
		   "22048.70c 7.235755e-06 22049.70c 5.310015e-07 "
		   "22050.70c 5.084266e-07 ","",MLib);
  setMaterial(MObj);

  // Material #75: Titanium
  // Total atom density 0.057118 - 4.54 g/cc
  MObj.setMaterial(75,"Titanium","22046.70c 4.712234e-03 "
		   "22047.70c 4.249578e-03 22048.70c 4.210738e-02 "
		   "22049.70c 3.090083e-03 22050.70c 2.958712e-03 ",
		   "",MLib);
  setMaterial(MObj);

  // Material #76: Titanium alloy (Grade 5): Ti-6Al-4V
  // Total atom density 0.057135 - 4.43 g/cc
  MObj.setMaterial(76,"Ti-6Al-4V",
		   "22046.70c 4.221076e-03 22047.70c 3.806643e-03 "
		   "22048.70c 3.771851e-02 22049.70c 2.768002e-03 "
		   "22050.70c 2.650324e-03 26054.70c 8.348879e-06 "
		   "26056.70c 1.310595e-04 26057.70c 3.026736e-06 "
		   "26058.70c 4.028030e-07 8016.70c 1.142704e-04 "
		   "13027.70c 3.428111e-03 23051.42c 2.285407e-03 ","",MLib);
  setMaterial(MObj);


  // Material #77: Platinum
  // Total atom density 0.066217 - 21.45 g/cc
  MObj.setMaterial(77,"Platinum",
		   "78190.80c 9.270400e-06 78192.80c 5.178180e-04 "
		   "78194.80c 2.182980e-02 78195.80c 2.240258e-02 "
		   "78196.80c 1.671453e-02 78198.80c 4.743134e-03 ",
		   "",MLib);
  setMaterial(MObj);

  // // Material: #78
  // // Be alloy:  Berilio 1.847810 g/cc
  // MObj.setMaterial(78,"Berilio",
  // 		   "4009.80c  -1.8205E+00 8016.70c -1.7737E-02 "
  // 		   "13027.70c -1.8476E-03 6012.70c -2.7714E-03 "
  // 		   "26054.70c -1.4040E-04 26056.70c -2.2024E-03 "
  // 		   "26057.70c -5.0902E-05 26058.70c -6.7734E-06 "
  // 		   "12024.70c -1.1675E-03 12025.70c -1.4781E-04 "
  // 		   "12026.70c -1.6274E-04 14028.70c -1.0225E-03 "
  // 		   "14029.70c -5.1771E-05 14030.70c -3.4366E-05 ","",MLib);
  // setMaterial(MObj);

  // //Material: #79
  // // Aluminio 6061
  // // -2.698400 g/cc
  // MObj.setMaterial(79,"Aluminium6061",
  // 		   "13027.70c -2.6258E+00 24050.70c -2.2864E-04 "
  // 		   "24052.70c -4.4092E-03 24053.70c -5.0001E-04 "
  // 		   "24054.70c -1.2445E-04 29070.70c -5.1728E-03 "
  // 		   "29065.70c -2.2877E-03 26054.70c -5.5209E-04 "
  // 		   "26056.70c -8.6619E-03 26057.70c -2.0014E-04 "
  // 		   "26058.70c -2.6633E-05 12024.70c -2.1315E-02 "
  // 		   "12025.70c -2.6984E-03 12026.70c -2.9709E-03 "
  // 		   "25055.70c -2.0238E-03 14028.70c -1.4933E-02 "
  // 		   "14029.70c -7.5609E-04 14030.70c -5.0190E-04 "
  // 		   "22046.70c -1.6698E-04 22047.70c -1.5057E-04 "
  // 		   "22048.70c -1.4919E-03 22049.70c -1.0950E-04 "
  // 		   "22050.70c -1.0483E-04 30064.70c -1.6404E-03 "
  // 		   "30066.70c -9.4120E-04 30067.70c -1.3829E-04 "
  // 		   "30068.70c -6.3250E-04 30070.70c -2.0913E-05 ",
  // 		   "al.20t",MLib);
  // setMaterial(MObj);

  // Material #81 Silicon with no-bragg (20K)
  MObj.setMaterial(81,"Silicon20K","14028.70c 0.0460848 "
		   "14029.70c 0.00234 14030.70c 0.0015403","si.81t",MLib);
  setMaterial(MObj);
  // Material #82 Silicon with no-bragg (77K)
  MObj.setMaterial(82,"Silicon80K","14028.70c 0.0460848 "
		   "14029.70c 0.00234 14030.70c 0.0015403","si.82t",MLib);
  setMaterial(MObj);
  // Material #83 Silicon with no-bragg (300K)
  MObj.setMaterial(83,"Silicon300K","14028.70c 0.0460848 "
		   "14029.70c 0.00234 14030.70c 0.0015403","si.83t",MLib);
  setMaterial(MObj);

  // Material #84 Mercury
  MObj.setMaterial(84,"Mercury","80196.70c 6.094517e-05 "
		   "80198.70c 4.050822e-03 80199.70c 6.854300e-03 "
		   "80200.70c 9.385556e-03 80201.70c 5.355049e-03 "
		   "80202.70c 1.213215e-02 80204.70c 2.791289e-03 ",
		   "",MLib);
  setMaterial(MObj);

  // Material #86: 90% Be + 10% D2O + H2O mixture (80% D2O & 20% H2O)
  //  (by VOLUME)
  // Total atom density 0.1212102
  MObj.setMaterial(86,"Be90/8D20/2H2O",
		   "4009.80c 1.112839e-01 "
		   "1001.70c 1.323088e-03 1002.70c 5.277874e-03 "
		   "8016.70c 0.0033253","be.60t lwtr.01t hwtr.01t",
		   MLib);
  setMaterial(MObj);

  // Material #87: Light water with 17-O
  // Total atom density 0.0998517 - 1.0 grams per cc
  MObj.setMaterial(87,"H2O_17O","1001.70c 0.06637790 "
		   "1002.70c 7.634337e-06 8016.70c 0.03345347 "
		   "8017.70c 1.271715e-05","lwtr.01t",MLib);
  setMaterial(MObj);


  // Material #88: D2O + H2O mixture (80% D2O & 20% H2O)    (by VOLUME)
  // Total atom density 0.0996049 - 1.0856 grams per cc
  MObj.setMaterial(88,"80D2O/20H2O","1001.70c 1.327648e-02 "
		   "1002.70c 5.296063e-02 8016.70c 0.03336781",
		   "lwtr.01t hwtr.01t",MLib);
  setMaterial(MObj);

  // Material #89 Boral (95% Aluminium & 5% Boron)
  // density 0.06213
  MObj.setMaterial(89,"Boral5","5010.70c 0.0014482 "
		   "5011.70c 0.0057928 13027.70c 0.054889",
		   "al.20t",MLib);
  setMaterial(MObj);

  // Material #91 Boral (95% Aluminium & 5% Boron) degraded:
  // 10% of initial B-10 left
  // density 0.062979
  MObj.setMaterial(91,"Boral5Degrade","3007.60c 2.008524e-03 "
		   "5010.70c 1.168329e-04 5011.70c 5.724811e-03 "
		   "13027.70c 5.512916e-02","al.20t",MLib);
  setMaterial(MObj);

  // Material #92: Beryllium + heavy water
  // (Dave Bellenger version 90% Be + 10% D2O - by VOLUME)
  // Total atom density 0.121202
  MObj.setMaterial(92,"Be/10D2O","4009.80c 1.112996e-01 1001.70c 1.651935e-05 "
		   "1002.70c 6.568682e-03 8016.70c 0.003316877",
		   "hwtr.01t be.60t",MLib);
  setMaterial(MObj);

  // Material #93: 90% Beryllium + 10% light water
  // Total atom density 0.121264
  MObj.setMaterial(93,"Be/10H2O","4009.80c 1.112186e-01 "
		   "1001.70c 6.677949e-03 1002.70c 7.680525e-07 "
		   "8016.70c 3.366946e-03","lwtr.01t be.60t",MLib);
  setMaterial(MObj);

  // Material #94 Stainless 316L
  // Total atom density 0.086927
  MObj.setMaterial(94,"Stainless316L",
		   "6000.70c 1.203355e-04 14028.70c 1.715374e-03 "
		   "24000.50c 1.575140e-02 25055.70c 1.753871e-03 "
		   "26054.70c 3.301281e-03 26056.70c 5.182305e-02 "
		   "26057.70c 1.196820e-03 26058.70c 1.592748e-04 "
		   "28058.70c 6.705771e-03 28060.70c 2.582933e-03 "
		   "28061.70c 1.121897e-04 28062.70c 3.579432e-04 "
		   "28064.70c 9.111102e-05 42092.70c 1.854269e-04 "
		   "42094.70c 1.158761e-04 42095.70c 1.996132e-04 "
		   "42096.70c 2.094056e-04 42097.70c 1.200190e-04 "
		   "42098.70c 3.036883e-04 42100.70c 1.214000e-04",
		   "",MLib);
  setMaterial(MObj);

  // Material #95 Steel XC-06: Soft magnetic (yoke) steel
  // Total atom density 0.086481
  MObj.setMaterial(95,"SteelXC06",
		   "6000.70c 1.203355e-04 14028.70c 2.229986e-04 "
		   "24000.50c 3.706212e-05 25055.70c 2.630807e-04 "
		   "26054.70c 5.017221e-03 26056.70c 7.875963e-02 "
		   "26057.70c 1.818903e-03 26058.70c 2.420627e-04",
		   "",MLib);
  setMaterial(MObj);

  // Material #96 Carbon, Graphite (Reactor Grade):
  // density 0.085238
  MObj.setMaterial(96,"Graphite",
		   "6012.70c 8.523759e-02 5010.70c "
		   "1.894100e-08 5011.70c 7.576401e-08",
		   "",MLib);
  setMaterial(MObj);

  // Material #97 is liquid methane at 110K (based on kernel T) - this is new TS1 default!!!
  MObj.setMaterial(97,"CH4Liq110K",
		   "1001.70c 0.066183 6000.70c 0.016546",
		   "lmeth.11t",MLib);
  setMaterial(MObj);

    // Material #98 Boral (this is TS1 Boral = Alloy 1100 + B) ->>> 94.7% Al, 5.3% Boron (B-10 enrichment: 98.2%)
    // Density 2.7 g/cm^3
    // Total atom density 0.06566
  MObj.setMaterial(98,"TS1Boral","5010.70c 8.436522e-03 "
		   "5011.70c 1.546409e-04 13027.70c 5.706872e-02",
		   "al.20t",MLib);
  setMaterial(MObj);

  // Material #99: 90% Be + 10% D2O + H2O mixture (50% D2O & 50% H2O)
  //  (by VOLUME)
  // Total atom density 0.1212533
  MObj.setMaterial(99,"Be90/5D20/5H2O",
		   "4009.80c 1.112839e-01 "
		   "1001.70c 3.347044e-03 1002.70c 3.337337e-03 "
		   "8016.70c 0.0033681","be.60t lwtr.01t hwtr.01t",
		   MLib);
  setMaterial(MObj);

  // Material #100 U3SI2 in Al for reactor New Fuel [delft]
  // U density at 4.8g/cc
  MObj.setMaterial(100,"U3Si2",
		   "13027.70c 3.491000e-02 14028.70c 8.576400e-03 "
		   "92234.70c 1.729600e-05 92235.70c 2.429500e-03 "
		   "92236.70c 1.714800e-05 92238.70c 9.712900e-03 "
		   ,"",MLib);
  setMaterial(MObj);

  // Material #101 Highly burnt U3Si2 - projected to 100% burn
  // which is impossible but allows linear fitting with U3SI2
  // Constructed at 4.8g/cc
  MObj.setMaterial(101,"U3Si2Burnt",
		   "13027.70c 3.491000e-02 14028.70c 8.576372e-03 "
		   "58141.70c 4.584777e-06 58142.70c 1.205632e-04 "
		   "58144.70c 3.764883e-05 59143.70c 1.810723e-06 "
		   "60143.70c 9.061769e-05 60144.70c 1.045201e-04 "
		   "60145.70c 7.710946e-05 60146.70c 6.621698e-05 "
		   "60147.70c 5.521043e-07 60148.70c 3.544721e-05 "
		   "61147.70c 2.418047e-05 61148.70c 9.827225e-08 "
		   "92234.70c 1.096144e-05 92236.70c 3.702187e-04 "
		   "92237.70c 1.732356e-07 92238.70c 9.137796e-03 "
		   "93237.70c 9.680188e-06 93239.70c 5.136849e-07 "
		   "94238.70c 1.305033e-06 94239.70c 8.317623e-05 "
		   "94240.70c 2.302631e-05 94241.70c 8.767253e-06 "
		   "94242.70c 2.025269e-06 95241.70c 2.730729e-07 "
		   "95243.70c 8.851011e-08 96242.70c 1.124027e-07 "
		   "96243.70c 8.827472e-10 96244.70c 6.823268e-09 "
		   "96245.70c 7.870824e-11 ","",MLib);
  setMaterial(MObj);

  // Material #102 B4C with 97% B-10
  MObj.setMaterial(102,"10B4C","5010.70c 0.10925 "
		   "5011.70c 0.0032776 6000.70c 0.027313","",MLib);
  setMaterial(MObj);

  // Material #103 BeO
  MObj.setMaterial(103,"BeO",
		   "4009.70c 0.0988968 8016.70c 0.0988968",
		   "beo.60t",MLib);
  MObj.setDensity(0.072276);
  setMaterial(MObj);

  // Material #104 U3SI2 in Al for reactor Original Fuel [delft]
  // U density at 4.3//cc
  MObj.setMaterial(104,"U3Si2Low",
		   "13027.70c 3.491000e-02 14028.70c 8.576400e-03 "
		   "92234.70c 1.549433e-05 92235.70c 2.176427e-03 "
		   "92236.70c 1.536175e-05 92238.70c 8.701140e-03 "
		   ,"",MLib);
  setMaterial(MObj);
  // Material #105 U3SI2 in Al for reactor Original Fuel [delft]
  // U density at 4.3//cc Full 100% burnt for linar interpolationx
  MObj.setMaterial(105,"U3Si2LowBurnt",
		   "13027.70c 3.491000e-02 14028.70c 8.576400e-03 "
		   "58141.70c 4.107196e-06 58142.70c 1.080045e-04 "
		   "58144.70c 3.372708e-05 59143.70c 1.622106e-06 "
		   "60143.70c 8.117835e-05 60144.70c 9.363259e-05 "
		   "60145.70c 6.907722e-05 60146.70c 5.931938e-05 "
		   "60147.70c 4.945934e-07 60148.70c 3.175479e-05 "
		   "61147.70c 2.166167e-05 61148.70c 8.803556e-08 "
		   "92234.70c 9.819623e-06 92236.70c 3.316543e-04 "
		   "92237.70c 1.551902e-07 92238.70c 8.185942e-03 "
		   "93237.70c 8.671835e-06 93239.70c 4.601761e-07 "
		   "94238.70c 1.169092e-06 94239.70c 7.451204e-05 "
		   "94240.70c 2.062774e-05 94241.70c 7.853997e-06 "
		   "94242.70c 1.814303e-06 95241.70c 2.446278e-07 "
		   "95243.70c 7.929031e-08 96242.70c 1.006941e-07 "
		   "96243.70c 7.907944e-10 96244.70c 6.112511e-09 "
		   "96245.70c 7.050947e-11","",MLib);
  setMaterial(MObj);

  // Material #106 Dy2O3 - New material form from Bath Unvirsity
  MObj.setMaterial(106,"Dy2O3",
		   "66160.70c 0.000374013 66161.70c 0.00302247 "
		   "66162.70c 0.00407738 66163.70c 0.00397988 "
		   "66164.70c 0.00450414 8016.70c 0.0398947 "
		   "22046.70c 0.000658263 22047.70c 0.000593634 "
		   "22048.70c 0.00588208 22049.70c 0.000431661 "
		   "22050.70c 0.000413309","",MLib);
  setMaterial(MObj);
  // Material #107
  MObj.setMaterial(107,"Li6ClD2O6Mol",
		   "3006.60c 0.003358 17035.70c 0.0025185 "
		   "17037.70c 0.00083950 "
		   "1002.70c 0.062189 8016.70c 0.031095 ",
                   "hwtr.01t",MLib);
  setMaterial(MObj);
  // Material #108
  MObj.setMaterial(108,"Li7ClD2O6Mol",
		   "3007.60c 0.003358 17035.70c 0.0025185 "
		   "17037.70c 0.00083950 "
		   "1002.70c 0.062189 8016.70c 0.031095 ",
                   "hwtr.01t",MLib);
  setMaterial(MObj);

  // Material #109: Titanium/Zironium Null alloy.
  // Total atom density 0.057118 - 4.54 g/cc
  MObj.setMaterial(109,"TiZr","22046.70c 0.00283485 "
		   "22047.70c 0.00255652 22048.70c 0.0253315 "
		   "22049.70c 0.00185897 22050.70c 0.00177994 "
		   "40090.70c 0.00874443 40091.70c 0.00190695 "
		   "40093.70c 0.00291481 40094.70c 0.0029539 ",
		   "",MLib);
  setMaterial(MObj);

  // Material #110 Vanadium
  // Total atom density 0.72
  MObj.setMaterial(110,"Vanadium","24051.70c 0.072",
		   "",MLib);
  setMaterial(MObj);


  // Material #111: Beryllium(400K) + heavy water (for test only)
  // (90% Be + 10% D2O - by VOLUME)
  // Total atom density 0.121202
  MObj.setMaterial(111,"Be400K/10D2O","4009.80c 1.112996e-01 1001.70c 1.651935e-05 "
		   "1002.70c 6.568682e-03 8016.70c 0.003316877",
		   "hwtr.01t be.61t",MLib);
  setMaterial(MObj);


  // Material #112: Aluminum 5251
  // (Dave Bellenger version for WaterMod aluminium)
  // Total atom density 0.059693
  MObj.setMaterial(112,"Alum5251",
		   "13027.70c 5.739771e-02 14028.70c 2.307178e-04 "
                   "24000.50c 4.673301e-05 25055.70c 1.474348e-04 "
		   "26054.70c 8.477590e-06 26056.70c 1.330800e-04 "
		   "26057.70c 3.073398e-06 26058.70c 4.090129e-07 "
		   "22046.70c 4.188076e-06 22047.70c 3.776883e-06 "
		   "22048.70c 3.742363e-05 22049.70c 2.746363e-06 "
		   "22050.70c 2.629604e-06 29063.70c 2.644224e-05 "
		   "29065.70c 1.179672e-05 30000.70c 3.714985e-05 "
		   "12024.70c 1.263543e-03 12025.70c 1.599624e-04 "
		   "12026.70c 1.761186e-04","al.20t",MLib);
  setMaterial(MObj);

  // Material #113: Au-In-Cd (75%-0.5%-24.5%); density = 16.3 g/cc
  // J-PARC decoupler
  // Total atom density 0.0591989
  MObj.setMaterial(113,"AuInCd",
		   "79197.70c 3.737725e-02 49113.70c 1.833815e-05 "
		   "49115.70c 4.091246e-04 48000.42c 2.139419e-02",
		   "",MLib);
  setMaterial(MObj);

  // Material #114: D2O + H2O mixture (20% D2O & 80% H2O)    (by VOLUME)
  // Total atom density 0.099796 - 1.0214 grams per cc
  MObj.setMaterial(114,"20D2O/80H2O","1001.70c 5.311190e-02 "
		   "1002.70c 1.324203e-02 8016.70c 0.033442081",
		   "lwtr.01t hwtr.01t",MLib);
  setMaterial(MObj);

  MObj.setMaterial(115,"HalfStainless304",
		   "6000.70c 3.18640e-4 14028.70c 1.70336e-3 "
		   "15031.70c 6.95038e-5 16032.70c 4.47520e-5 "
		   "24000.50c 1.74813e-2 25055.70c 1.74159e-3 "
		   "26054.70c 3.380e-3 26056.70c 5.3455e-2 "
		   "26057.70c 1.282177e-3 28000.50c 8.15128e-3",
		   "",MLib);
  MObj.setDensity(0.042);
  setMaterial(MObj);

  // Material #116: helium liquid
  // Total density 0.125g/cc
  MObj.setMaterial(116,"LiqHelium","2004.70c 0.01882","",MLib);
  setMaterial(MObj);


  // Material #117 Silicon Oxide
  MObj.setMaterial(117,"SiO2",
		   "14028.70c 0.0245002 "
		   "14029.70c 0.00124406 "
		   "14030.70c 0.000820094 "
		   "8016.70c 0.0531292 ","",MLib);
  setMaterial(MObj);

  MObj.setMaterial(118, "Be5H2O",
		   "1001.70c 0.0033422785 "
		   "4009.70c 0.117311225 "
		   "8016.70c 0.00167113925 ",
		   "be.60t lwtr.01t", MLib);
  setMaterial(MObj);

  MObj.setMaterial(119, "Be10H2O",
		   "1001.70c 0.006684557 "
		   "4009.70c 0.11113695 "
		   "8016.70c 0.003342780 ",
		   "be.60t lwtr.01t", MLib);
  setMaterial(MObj);

  // Material #120:
  // Low density tungsten
  MObj.setMaterial(120, "Tungsten_15.1g",
		   "74182.70c  0.265000000 "
		   "74183.70c  0.143100000 "
		   "74184.70c  0.306400000 "
		   "74186.70c  0.284300000 ",
		   "",MLib);
  MObj.setDensity(-15.1);
  setMaterial(MObj);

  // Material #120:
  // Homogeneous mixture of Iron and 10% volume H2O
  MObj.setMaterial(121, "Iron_10H2O",
                   " 1001.70c 0.077534884 "
                   " 8016.70c 0.038767442 "
                   " 26054.70c 0.051652129 "
                   " 26056.70c 0.810827964 "
                   " 26057.70c 0.018725554 "
                   " 26058.70c 0.002492027 ", "lwtr.01t", MLib);
  MObj.setDensity(-7.17);
  setMaterial(MObj);

  // Carston concrete
  // Number density 0.08800 / B4C fraction :
  MObj.setMaterial(122,"CarstonConc",
                   "1001.70c 0.0278123 1002.70c 3.19878e-06 "
                   "5010.70c 0.000130219 5011.70c 0.000524148 "
                   "6000.70c 0.00883308 8016.70c 0.0342097 "
                   "11023.70c 0.000316496 12024.70c 7.52233e-05 "
                   "12025.70c 9.52314e-06 12026.70c 1.0485e-05 "
                   "13027.70c 0.00102942 14028.70c 0.0110701 "
                   "14029.70c 0.000562111 14030.70c 0.000370548 "
                   "16032.70c 9.59317e-05 16033.70c 7.6802e-07 "
                   "16034.70c 4.33527e-06 16036.70c 2.0211e-08 "
                   "17035.70c 8.95621e-07 17037.70c 2.86249e-07 "
                   "19039.70c 0.00037788 19040.70c 4.74082e-08 "
                   "19041.70c 2.72698e-06 20040.70c 0.00231121 "
                   "20042.70c 1.54254e-05 20043.70c 3.21859e-06 "
                   "20044.70c 4.97332e-05 20046.70c 9.53656e-08 "
                   "20048.70c 4.45834e-06 26054.70c 1.03984e-05 "
                   "26056.70c 0.000163233 26057.70c 3.76976e-06 "
                   "26058.70c 5.01685e-07 ",
                   "poly.01t",MLib);
  setMaterial(MObj);


  // Material #123 Parafin Wax:
  MObj.setMaterial(123,"Wax","6000.70c 0.2 "
                   "8016.70c 0.1 1001.70c 0.65 "
                   "14028.70c 0.05","poly.01t",MLib);
  MObj.setDensity(-1.05);
  setMaterial(MObj);

  // # 124 Tungsten at 600K -- density unchanged
  MObj.setMaterial(124,"Tungsten600K",
		   "74182.71c 0.016871 74183.71c 0.00911077 "
		   "74184.71c 0.019507618 74186.71c 0.018100573 ","",MLib);
  // density at 300 K according to the Material handbook.
  // YJL says at 600K we should use the same density (??)
  MObj.setDensity(-19.298);
  setMaterial(MObj);

  // # 125 Zircalloy-2 -- 6.56g/cc
  // NEEDS 0.1% Cr / 1.4% Sn / 0.1% Fe / 0.12% O / 0.05% Ni
  MObj.setMaterial(125,"Zircaloy2",
                   "40090.70c 0.00874443 40091.70c 0.00190695 "
		   "40093.70c 0.00291481 40094.70c 0.0029539 ",
                   "",MLib);
  MObj.setDensity(-6.56);
  setMaterial(MObj);

  // Material #126 Polystyrene [C8H8]
  MObj.setMaterial(126,"Polystyrene","6000.70c 0.5 "
                   "1001.70c 0.5 ","poly.01t",MLib);
  MObj.setDensity(-1.06);
  setMaterial(MObj);

  // Material #127 Invar at room temperature [from K.B]
  MObj.setMaterial(127, "Invar36",
		   " 6000.70c  0.001000000 "
		   " 14028.70c 0.003227805 "
		   " 14029.70c 0.000163975 "
		   " 14030.70c 0.000108220 "
		   " 29063.70c 0.003457501 "
		   " 29065.70c 0.001542499 "
		   " 25055.70c 0.006000000 "
		   " 15031.70c 0.000250000 "
		   " 16032.70c 0.000237476 "
		   " 16033.70c 0.000001875 "
		   " 16034.70c 0.000010625 "
		   " 16036.70c 0.000000024 "
		   " 24050.70c 0.000217250 "
		   " 24052.70c 0.004189450 "
		   " 24053.70c 0.000475050 "
		   " 24054.70c 0.000118250 "
		   " 28058.70c 0.251884530 "
		   " 28060.70c 0.097025471 "
		   " 28061.70c 0.004217629 "
		   " 28062.70c 0.013447651 "
		   " 28064.70c 0.003424721 "
		   " 26054.70c 0.035654500 "
		   " 26056.70c 0.559699400 "
		   " 26057.70c 0.012925900 "
		   " 26058.70c  0.001720200 ", "fe56.12t", MLib);
  MObj.setMXitem(6000, 70, 'c', "h", "06012");
  MObj.setDensity(-8.11);
  setMaterial(MObj);


  // Material #128: SAB - Liquid para-hydrogen (basic)
  //Total atom density 0.041957 -  19 K; 0.07021 grams per cc
  MObj.setMaterial(128,"H2para19K","1001.70c 0.041957","hpara.60t",MLib);
  setMaterial(MObj);

  // Material #129: SAB - Liquid para-hydrogen (basic)
  //Total atom density 0.041957 -  19 K; 0.07021 grams per cc
  MObj.setMaterial(129,"H2ortho19K","1001.70c 0.041957","hortho.60t",MLib);
  setMaterial(MObj);

  // Carston concrete
  // Regular concrete - no B4C
  MObj.setMaterial(130,"RegularCarstonConc",
                   "1001.70c 0.00354518 1002.70c 4.07742e-07 "
                   "8016.70c 0.0450741 11023.70c 0.000645145 "
                   "12024.70c 0.000107881 12025.70c 1.36576e-05 "
                   "12026.70c 1.5037e-05 13027.70c 0.00192657 "
                   "14028.70c 0.0150756 14029.70c 0.000765504 "
                   "14030.70c 0.000504626 16032.70c 9.82716e-05 "
                   "16033.70c 7.86752e-07 16034.70c 4.44101e-06 "
                   "16036.70c 2.0704e-08 17037.70c 9.08816e-07 "
                   "17037.70c 2.90466e-07 19039.70c 0.000759079 "
                   "19040.70c 9.52327e-08 19041.70c 5.47791e-06 "
                   "20040.70c 0.00241901 20042.70c 1.61448e-05 "
                   "20043.70c 3.36871e-06 20044.70c 5.20528e-05 "
                   "20046.70c 9.98135e-08 20048.70c 4.66628e-06 "
                   "26054.70c 1.7002e-05 26056.70c 0.000266895 "
                   "26057.70c 6.16376e-06 26058.70c 8.20284e-07",
                   "lwtr.01t",MLib);
  setMaterial(MObj);

  // Carston concrete
  // Regular concrete - with B4C
  MObj.setMaterial(131,"RegCarstonConcB4C",
                   "1001.70c 5.50969e-05 1002.70c 6.33687e-09  "
                   "5010.70c 0.0250581 5011.70c 0.100862  "
                   "6000.70c 0.000163366 8016.70c 0.000700512  "
                   "11023.70c 1.00264e-05 12024.70c 1.67662e-06  "
                   "12025.70c 2.12257e-07 12026.70c 2.33695e-07  "
                   "13027.70c 2.99414e-05 14028.70c 0.000234296  "
                   "14029.70c 1.1897e-05 14030.70c 7.84257e-06  "
                   "16032.70c 1.52727e-06 16033.70c 1.22272e-08  "
                   "16034.70c 6.90193e-08 16036.70c 3.21768e-10  "
                   "17037.70c 1.41242e-08 17037.70c 4.51424e-09  "
                   "19039.70c 1.17971e-05 19040.70c 1.48004e-09  "
                   "19041.70c 8.51342e-08 20040.70c 3.75946e-05  "
                   "20042.70c 2.50913e-07 20043.70c 5.23543e-08  "
                   "20044.70c 8.0897e-07 20046.70c 1.55124e-09  "
                   "20048.70c 7.25203e-08 26054.70c 2.64234e-07  "
                   "26056.70c 4.1479e-06 26057.70c 9.57932e-08  ",
                   "lwtr.01t",MLib);
  setMaterial(MObj);

  // He3 for detectors [1bar]
  MObj.setMaterial(132,"He3_1Bar","2003.70c 2.45e-5","",MLib);
  setMaterial(MObj);

  // He3 for detectors [10bar]
  MObj.setMaterial(133,"He3_10Bar","2003.70c 2.45e-4","",MLib);
  setMaterial(MObj);

  // Material #134: liquid N2
  // Total density 0.807g/cc
  MObj.setMaterial(134,"LiqN2","7014.70c 0.034718","",MLib);
  setMaterial(MObj);

  // Skanska concrete
  // Composition received from Skanska
  // Source: MATER.INP from MARS. Material "ESSConc"
  MObj.setMaterial(135,"SkanskaConcrete",
		   " 1001.70c -3.35720233139058521e-03 "
		   " 8016.70c -3.82342797668609513e-01 "
		   " 12024.70c -0.0019 "
		   " 13027.70c -0.0192 "
		   " 14028.70c -0.1251 "
		   " 16032.70c -0.0081 "
		   " 19039.70c -0.0158 "
		   " 20040.70c -0.3927 "
		   " 22048.70c -0.0038 "
		   " 25055.70c -0.0021 "
		   " 26056.70c -0.0444 "
		   " 28058.70c -0.0012 ", "lwtr.01t", MLib);
  MObj.setDensity(-2.35);
  setMaterial(MObj);

  // Material #136 Silver
  // Density 10.49g/cc atomic rho=0.058573
  MObj.setMaterial(136,"Silver","47107.70c 0.043778 "
                   "47109.70c 0.040672 ","",MLib);
  MObj.setDensity(-10.49); // wikipedia
  setMaterial(MObj);

  //
  // Material #137 Hi-DensityPoly:
  MObj.setMaterial(137,"HighDensPoly","6000.70c 0.0333333 "
		   "1001.70c 0.0666666666","poly.01t",MLib);
  MObj.setDensity(-0.97);
  setMaterial(MObj);

  //
  // Material #138 Ammonia [695kg/m^3]
  MObj.setMaterial(138,"Ammonia","7014.70c 0.024801 "
		   "1001.70c 0.074402","orthh.99t",MLib);
  setMaterial(MObj);

  //
  // Material #139 boro-silicate glass (rho=2.24g 75% siO2 12% B2O4 13% Al2O3
  MObj.setMaterial(139,"Borosilicate",
		   "14028.70c 0.0160107 14029.70c 0.000812983  "
		   "14030.70c 0.000535924 5010.70c 0.000663275  "
		   "5011.70c 0.00266976 13027.70c 0.00361079  "
		   "8016.70c 0.0451349 ","",MLib);
  setMaterial(MObj);


  // Material #140: Hydrogen gas for vacuum pipes (Brem production)
  // Total atom density 5.4127e-5 -  300K 0.08988 g/litre
  MObj.setMaterial(140,"H2Gas","1001.70c 5.4127e-5","",MLib);
  setMaterial(MObj);

  // Material #141: Hydrogen gas+carbon+O for vacuum pipes (Brem production)
  // Total atom density 2.4305e-5 Mol/Angstrom -  300K R 100kPa
  // 80% H2  / 10% C / 10% O2
  // Mass density  2.4305e-5 Mol/Angstrom -  300K R 100kPa
  MObj.setMaterial(141,"VacuumResidual",
		   "1001.70c 3.888e-5 "
		   "6000.70c 2.43e-6 "
		   "8016.70c 4.86e-6 ","",MLib);
  setMaterial(MObj);

  // Material Lead glass:
  // PbO 24%  SiO2 64% Na2O 12%
  // density 3.4g/cc [rho=0.056]
  MObj.setMaterial(142,"LeadGlass",
		   "82204.70c 6.93965e-05 82206.70c 0.00119461  "
		   "82207.70c 0.00109547 82208.70c 0.00259741  "
		   "14028.70c 0.0121913 14029.70c 0.000619043  "
		   "14030.70c 0.000408078 11023.70c 0.0049569  "
		   "8016.70c 0.033459 ",
		   "",MLib);
  setMaterial(MObj);

  // Material Nb2 Fe24 B : NbFeB magnet
  // density 7.4g/cc [0.0700 Atom/A^3]
  MObj.setMaterial(143,"NbFeB",
		   "26054.24c 0.00337305 26056.24c 0.0529497  "
		   "26057.24c 0.00122284 26058.24c 0.000162738  "
		   "5010.70c 0.000820283 5011.70c 0.00330174  "
		   "60142.70c 0.00224238 60143.70c 0.00100577  "
		   "60144.70c 0.00196208 60145.70c 0.000684256  "
		   "60146.70c 0.00141798 60148.70c 0.000469911  "
		   "60150.70c 0.000461667 ",
		   "fe56.12t",MLib);
  setMaterial(MObj);

  // Fe2 O 3
  // density 5.2 g/cc
  // generated by MatMCNP
  // and O18 added to O16 due to lack of O18 cross section:
  //   Fe 2 O 3
  // 1
  // iron (III)  oxide
  // 5.2
  // atomic
  // 2
  // nat 26 2
  // nat 8 3
  // 144
  MObj.setMaterial(144,"Fe2O3",
		   " 26054.70c   0.023380 "
		   " 26056.70c   0.367016 "
		   " 26057.70c   0.008476 "
		   " 26058.70c   0.001128 "
		   " 08016.70c   0.599772 "
		   " 08017.70c   0.000228 ",
		   "fe56.12t",MLib);
  MObj.setDensity(-5.2);
  setMaterial(MObj);

  // Generic cable material
  // Reference: material StbTCABL in MARS
  // Mass fractions converted into atomic fractions by table 40
  MObj.setMaterial(145,"StbTCABL",
                   " 1001.70c  3.88760701228E-01 "
                   " 1002.70c  4.47126239451E-05 "
                   " 6000.70c  2.664664e-01      "
                   " 17035.70c 1.00520773169E-01 "
                   " 17037.70c 3.21273836065E-02 "
                   " 29063.70c 1.46695727581E-01 "
                   " 29065.70c 6.53842615705E-02 ","",MLib);
  MObj.setMXitem(6000, 70, 'c', "h", "06012");
  MObj.setDensity(-2.0272);
  setMaterial(MObj);

  // Material #146 Diamond
  // density 3.51g/cc 0.176
  MObj.setMaterial(146,"Diamond", "6012.70c 0.17615 ","",MLib);
  MObj.setDensity(-3.51);
  setMaterial(MObj);

  // ESS Iron
  MObj.setMaterial(147, "Iron",
		   " 26054.70c  0.058450000 "
		   " 26056.70c  0.917540000 "
		   " 26057.70c  0.021190000 "
		   " 26058.70c  0.002820000 ", "fe56.12t", MLib);
  MObj.setDensity(-7.85);
  setMaterial(MObj);

  // Earth: from https://mcnp.lanl.gov/pdf_files/la-ur-13-24293.pdf
  // Density 1.6104
  MObj.setMaterial(148, "Earth",
		   "1001.70c 0.0010213 1002.70c 1.17462e-07  "
		   "8016.70c 0.0245038 11023.70c 0.00099556  "
		   "12024.70c 0.000580795 12025.70c 7.35277e-05  "
		   "12026.70c 8.0954e-05 13027.70c 0.00286048  "
		   "14028.70c 0.0089957 14029.70c 0.00045678  "
		   "14030.70c 0.000301113 19039.70c 0.000904785  "
		   "19040.70c 1.13513e-07 19041.70c 6.52941e-06  "
		   "20040.70c 0.00123824 20042.70c 8.26422e-06  "
		   "20043.70c 1.72437e-06 20044.70c 2.66448e-05  "
		   "20046.70c 5.10925e-08 20048.70c 2.38858e-06  "
		   "26054.70c 0.000102832 26056.70c 0.00161425  "
		   "26057.70c 3.728e-05 26058.70c 4.96128e-06  ",
		   "lwtr.01t",MLib);

  MObj.setDensity(-1.6104);
  setMaterial(MObj);

  // SS304L composition from ESS Design Update WP3
  // Reference: Material Data Compilation 29 Mar 2017
  MObj.setMaterial(149, "Stainless304L",
		   " 6000.70c      0.001366050 "
		   " 14028.70c      0.017958587 "
		   " 14029.70c      0.000912310 "
		   " 14030.70c      0.000602105 "
		   " 15031.70c      0.000794573 "
		   " 16032.70c      0.000486055 "
		   " 16033.70c      0.000003838 "
		   " 16034.70c      0.000021747 "
		   " 16036.70c      0.000000051 "
		   " 24050.70c      0.008683351 "
		   " 24052.70c      0.167449786 "
		   " 24053.70c      0.018987462 "
		   " 24054.70c      0.004726381 "
		   " 25055.70c      0.019910026 "
		   " 26054.70c      0.038864395 "
		   " 26056.70c      0.610087892 "
		   " 26057.70c      0.014089590 "
		   " 26058.70c      0.001875066 "
		   " 28058.70c      0.063434555 "
		   " 28060.70c      0.024434877 "
		   " 28061.70c      0.001062167 "
		   " 28062.70c      0.003386654 "
		   " 28064.70c      0.000862481 ", "fe56.12t", MLib);
  MObj.setMXitem(6000, 70, 'c', "h", "06012");
  MObj.setDensity(-7.85);
  setMaterial(MObj);

  // Material #150 Niodimium
  // Source:
  // https://prod-ng.sandia.gov/techlib-noauth/access-control.cgi/2014/1417693.pdf
  // Table 176 on page 69
  MObj.setMaterial(150,"Neodymium",
		   " 60142.70c 0.271520 "
		   " 60143.70c 0.121740 "
		   " 60144.70c 0.237980 "
		   " 60145.70c 0.082930 "
		   " 60146.70c 0.171890 "
		   " 60148.70c 0.057560 "
		   " 60150.70c 0.056380 ","",MLib);
  MObj.setDensity(0.0292587);
  setMaterial(MObj);

  // was 144
  //Limestone concrete as given by Phil
  // Density = 2.33 g/cm3
  //Number atom fractions
  MObj.setMaterial(151,"LimestoneConcrete",
		   " 01000.70c 0.00723 "
		   " 08000.70c 0.039825 "
		   " 13000.70c 0.000337 "
		   " 14000.70c 0.001554 "
		   " 20000.70c 0.007037 "
		   " 26000.70c 0.000287 "
		   " 16000.70c 8.84e-6 "
		   " 19000.70c 0.000234 "
		   " 22000.70c 1.6e-5 "
		   " 23000.70c 7.65e-6 "
		   " 25000.70c 1.29e-5 "
		   " 28000.70c 5.93e-7 "
		   " 29000.70c 3.94e-7 "
		   " 30000.70c 1.38e-6 "
	    //	   " 37000.70c -0.004 " //Rb cross sections are  missing in FLUKA
		   " 38000.70c 2.56e-6 "
		   " 39000.70c 1.69e-7 "
		   " 40000.70c 1.15e-6 "
		   " 82000.70c 4.35e-8 "
		   " 41000.70c 9.68e-8 ", "lwtr.10t", MLib);

  MObj.setDensity(-2.33);
  setMaterial(MObj);


  // Material # 152 MagnadenseHC from Luca 3.5 g/cm3
  MObj.setMaterial(152, "MagnadenseHC",
		   "01001.70c 1.1079E-02  "
		   "01002.70c 1.2742E-06  "
		   "08016.70c 4.3686E-02  "
		   "08017.70c 1.6641E-05  "
		   "11023.70c 4.2163E-04  "
		   "13027.70c 4.9983E-04  "
		   "14028.70c 3.2452E-03  "
		   "14029.70c 1.6486E-04  "
		   "14030.70c 1.0880E-04  "
		   "15031.70c 2.9934E-04  "
		   "16032.70c 1.8727E-05  "
		   "16033.70c 1.4789E-07  "
		   "16034.70c 8.3788E-07  "
		   "16036.70c 1.9818E-09  "
		   "19039.70c 7.5392E-05  "
		   "19040.70c 9.4960E-09  "
		   "19041.70c 5.4408E-06  "
		   "20040.70c 1.0092E-03  "
		   "20042.70c 6.7355E-06  "
		   "20043.70c 1.4054E-06  "
		   "20044.70c 2.1716E-05  "
		   "20046.70c 4.1617E-08  "
		   "20048.70c 1.9468E-06  "
		   "26054.70c 1.2754E-03  "
		   "26056.70c 2.0022E-02  "
		   "26057.70c 4.6239E-04  "
		   "26058.70c 6.1535E-05  ","lwtr.01t",MLib);
  MObj.setDensity(-3.8);
  setMaterial(MObj);



  //Number atom fractions
  MObj.setMaterial(153,"BorkronNBK7", //Optical Materials Express, Vol. 3 No1 P.69, 1 January 2013
		   " 08000.70c 0.608978 " //O
		   " 14000.70c 0.2307199 " //Si
		   " 05000.70c 0.0653517 " //B
		   " 11000.70c 0.0606038 " //Na
		   " 19000.70c 0.0315574 " //K
		   " 56000.70c 0.0012925 " //Ba
		   " 22000.70c 0.000619549 " //Ti
		   " 20000.70c 0.000876436 " //Ca
                   , "lwtr.10t", MLib);

  MObj.setDensity(-2.4914); //According to R. Boffy thesis on guide substrates
  setMaterial(MObj);

  //Number atom fractions
  MObj.setMaterial(154,"B4CConcrete", //JLab composition from Tsito
		   " 01000.70c      0.008327" //H
		   " 05010.70c       0.0070413"//B10
		   " 05011.70c      0.028165"//B11
		   " 06000.70c       0.0088025"//C12
		   " 08000.70c       0.027883"//O16
		   " 11023.70c       0.0010578"//Na23
		   " 13027.70c       0.0010567"//Al27
		   " 14028.70c       0.010062"//Si28
		   " 20040.70c       0.00089242"//Ca40
		   " 20044.70c       2.81606e-05"//Ca44
		   " 26054.70c       1.2297e-05"//Fe54
		   " 26056.70c     0.00019287"//Fe56
		   " 26057.70c      4.4565e-06"//Fe57
		   " 26058.70c      5.886e-07"//Fe58
                   , "lwtr.10t", MLib);

  MObj.setDensity(-2.19783); //From Tsito
  setMaterial(MObj);


  MObj.setMaterial(155,"PVC", //(C2H3Cl)n
		   " 01000.70c      3 " //H
		   " 06000.70c      2 "//C12
		   " 17000.70c       1 "//Cl
		   , "lwtr.10t", MLib);
  MObj.setDensity(-1.45); //From wikipedia
  setMaterial(MObj);


  MObj.setMaterial(156,"Mirrobor", //B4C rubber from Mirrotron
		   " 01000.70c      0.01" //H
		   " 05000.70c       0.05797"//B
		   " 06000.70c       0.07246"//C
		   " 08000.70c       0.003125"//O
                   , "lwtr.10t", MLib);

  MObj.setDensity(-1.36); //From Tsito
  setMaterial(MObj);

  MObj.setMaterial(157,"SteelS355", //S355 steeel from Valentina
                "  6012.70c      0.008201260271"
		"   6013.30c      0.000088702603 "
		"         13027.70c      0.000615039421"
		"         14028.70c      0.004359299697"
		"         14029.70c      0.000221455809"
		"         14030.70c      0.000146156107"
		"         15031.70c      0.000250024457"
		"         16032.70c      0.000098321002"
		"         16033.70c      0.000000776300"
		"         16034.70c      0.000004399034"
		"         16036.70c      0.000000010351"
		"         22046.70c      0.000009533802"
		"         22047.70c      0.000008597756"
		"         22048.70c      0.000085191746"
		"         22049.70c      0.000006251863"
		"         22050.70c      0.000005986072"
		"         23050.30c      0.000000271467"
		"         23051.30c      0.000108315242"
		"         24050.70c      0.000013867196"
		"         24052.70c      0.000267415078"
		"         24053.70c      0.000030322723"
		"         24054.70c      0.000007547968"
		"         25055.70c      0.015304486247"
		"         26054.70c      0.056657033492"
		"         26056.70c      0.889394260220"
		"         26057.70c      0.020539992125"
		"         26058.70c      0.002733495884"
		"         27059.70c      0.000093861692"
		"         28058.70c      0.000192477584"
		"         28060.70c      0.000074142021"
		"         28061.70c      0.000003222902"
		"         28062.70c      0.000010276023"
		"         28064.70c      0.000002617000"
		"         29063.70c      0.000240775535"
		"         29065.70c      0.000107417574"
		"         41093.70c      0.000059539182"
		"         42092.70c      0.000008515873"
		"         42094.70c      0.000005321700"
		"         42095.70c      0.000009167392"
		"         42096.70c      0.000009617113"
		"         42097.70c      0.000005511967"
		"         42098.70c      0.000013947121"
		"         42100.70c      0.000005575389 "
                , "lwtr.10t", MLib);

  MObj.setDensity(-7.8); //From Valentina & bunker project
  setMaterial(MObj);


  MObj.setMaterial(158,"Lead51121", //B4C rubber from Mirrotron
		   " 82000.70c 0.48198359" //Pb
		   " 51000.70c 8.21288E-06 "//Sb
		   " 33000.70c 1.33476E-05 "//As
		   " 50000.70c 8.42389E-06 " //Sn
		   " 29000.70c 0.001258931 "//Cu
		   " 47000.70c 0.000185408 "//Ag
		   " 83000.70c 0.000119629 "//Bi
		   " 30000.70c 1.52952E-05 "//Zn
		   " 28000.70c 3.40774E-05 "//Ni
		   " 26000.70c 3.58102E-05 "//Fe
		   , "lwtr.10t", MLib);

  MObj.setDensity(-11.2);
  setMaterial(MObj);


 MObj.setMaterial(159,"Nimonic75", //B4C rubber from Mirrotron
		"  6000.70c 0.0125  "//C
		"  24000.70c 0.384615385 "//Cr
		"  29000.70c 0.007874016 "//Cu
		"  26000.70c 0.089285714  "//Fe
		"  25000.70c 0.018181818  "//Mn
		"  14000.70c 0.035714286  "//Si
		"  22000.70c 0.010460251  "//Ti
		"  28000.70c 1.224020443  "//Ni
		  "  27000.70c 0.000169 " //Co, 0.01 wt%
		  , "lwtr.10t", MLib);

  MObj.setDensity(-8.37);
  setMaterial(MObj);




  MObj.setMaterial(160,"SS1.4318",
		  " 26000.70c 1.25375  " //Fe
		 "  24000.70c 0.355769231 "//Cr
		 "  28000.70c 0.136309422 "//Ni
		 "  25000.70c 0.036363636 "//Mn
		 "  14000.70c 0.035714286 "//Si
		 "  7000.70c  0.014285714 "//N
		 "  15000.70c 0.001451613 "//P
		 "  6000.70c 0.0025 "//C
		 "  16000.70c 0.00046875 "//S
		   "  27000.70c 0.000169 " //Co, 0.01 wt%
		   , "lwtr.10t", MLib);

  MObj.setDensity(-7.8);
  setMaterial(MObj);



  MObj.setMaterial(161,"CuCr1Zr",
		   "  14000.70c 0.003571429 " //Si
		   "  24000.70c 0.023076923 "//Cr
		   "  29000.70c 1.548346457 "//Cu
		   "  40000.70c 0.003289474 " //Zr
		   "  26000.70c 0.001428571 " //Fe
		   "  27000.70c 0.000169 " //Co, 0.01 wt%
		     , "lwtr.10t", MLib);

  MObj.setDensity(-8.91);
  setMaterial(MObj);

  MObj.setMaterial(162,"W-MT185",
		   " 74000.70c 0.527747552 " //W
		   " 28000.70c 0.035781223 " //Ni
		   " 26000.70c 0.016114593 " //Fe
		   "  27000.70c 0.000169 " //Co, 0.01 wt%
     , "lwtr.10t", MLib);

  MObj.setDensity(-18.5);
  setMaterial(MObj);


  MObj.setMaterial(163,"Nd2NiO4",
		   " 60000.70c 0.017 " //Nd
		   " 28000.70c 0.0085 " //Ni
		   " 08000.70c 0.0034 " //O
    , "lwtr.10t", MLib);

  MObj.setDensity(-3.5);
  setMaterial(MObj);

  // was 1002 but not a good idea to use numbers
  MObj.setMaterial(164,"LiquidD2",
		   "1002.70c 0.33333333 01005.70c      0.666666667",
		   "PD-J33.20T  OD-J33.20T",MLib);
    MObj.setDensity(-1.63E-01); // 1.63g/cm3
    //   MObj.setDensity(0.050869); //E-24, atom density
  setMaterial(MObj);

  // Material #401: Beryllium solid at 20K
  // Total atom density 0.1187475
  MObj.setMaterial(165,"Be20K","4009.70c 0.1234855","BE-MET.20T",MLib);
  setMaterial(MObj);

  // Stainless steel with 1% (weight) boron content
  // Reference: Compendium of Material Composition Data for Radiation Trans
  //            PNNL-15870Rev1, page 280
  //            plone:doc/misc/pnnl-15870rev1.pdf/view
  MObj.setMaterial(166,"BoronSteel",
		   " 05010.70c 0.009716 "
		   " 05011.70c 0.039110 "
		   " 06000.70c 0.001741 "
		   " 14028.70c 0.008580 "
		   " 14029.70c 0.000436 "
		   " 14030.70c 0.000288 "
		   " 15031.70c 0.000389 "
		   " 16032.70c 0.000233 "
		   " 16033.70c 0.000002 "
		   " 16034.70c 0.000010 "
		   " 24050.70c 0.008297 "
		   " 24052.70c 0.160003 "
		   " 24053.70c 0.018143 "
		   " 24054.70c 0.004516 "
		   " 25055.70c 0.009512 "
		   " 26054.70c 0.038382 "
		   " 26056.70c 0.602516 "
		   " 26057.70c 0.013915 "
		   " 26058.70c 0.001852 "
		   " 28058.70c 0.056068 "
		   " 28060.70c 0.021597 "
		   " 28061.70c 0.000939 "
		   " 28062.70c 0.002993 "
		   " 28064.70c 0.000762 ","fe56.12t",MLib);
  MObj.setMXitem(6000, 70, 'c', "h", "06012");
  MObj.setDensity(-7.87);
  setMaterial(MObj);

  // Steel S235JR
  // Reference: Email from AB 2021-12-08, 0936_001_High-Ni-value.pdf (measured)
  //            The steel sample with the hightest Nickel value used
  //            (to get conservative Cobalt content for residual activation,
  //            see S235JR_Co).
  //            Density calculated from dimensions and mass: 13738000./(10*250*700)

  MObj.setMaterial(167, "S235JR",
		   " 06000.70c 0.000600 "
		   " 25055.70c 0.014900 "
		   " 14028.70c 0.001660 "
		   " 14029.70c 0.000084 "
		   " 14030.70c 0.000056 "
		   " 15031.70c 0.000070 "
		   " 16032.70c 0.000019 "
		   " 16034.70c 0.000001 "
		   " 24050.70c 0.000001 "
		   " 24052.70c 0.000014 "
		   " 24053.70c 0.000002 "
		   " 29063.70c 0.000131 "
		   " 29065.70c 0.000059 "
		   " 28058.70c 0.001784 "
		   " 28060.70c 0.000687 "
		   " 28061.70c 0.000030 "
		   " 28062.70c 0.000095 "
		   " 28064.70c 0.000024 "
		   " 42092.70c 0.000001 "
		   " 42094.70c 0.000001 "
		   " 42095.70c 0.000002 "
		   " 42096.70c 0.000002 "
		   " 42097.70c 0.000001 "
		   " 42098.70c 0.000002 "
		   " 42100.70c 0.000001 "
		   " 13027.70c 0.000440 "
		   " 41093.70c 0.000260 "
		   " 23051.70c 0.000020 "
		   " 22046.70c 0.000016 "
		   " 22047.70c 0.000014 "
		   " 22048.70c 0.000140 "
		   " 22049.70c 0.000010 "
		   " 22050.70c 0.000010 "
		   " 07014.70c 0.000045 "
		   " 05011.70c 0.000002 "
		   " 26054.70c 0.057212 "
		   " 26056.70c 0.898103 "
		   " 26057.70c 0.020741 "
		   " 26058.70c 0.002760 ", "fe56.12t",MLib);
  MObj.setMXitem(6000, 70, 'c', "h", "06012");
  MObj.setDensity(-7.85);
  setMaterial(MObj);

  // Steel S235JR with ~0.5% weight Cobalt content based on its Nickel content
  // See also S235JR and S234JR_Co.inp

  MObj.setMaterial(168, "S235JR_Co",
		   " 06000.70c 0.000599 "
		   " 25055.70c 0.014900 "
		   " 14028.70c 0.001661 "
		   " 14029.70c 0.000084 "
		   " 14030.70c 0.000056 "
		   " 15031.70c 0.000070 "
		   " 16032.70c 0.000020 "
		   " 16034.70c 0.000001 "
		   " 24050.70c 0.000001 "
		   " 24052.70c 0.000014 "
		   " 24053.70c 0.000002 "
		   " 29063.70c 0.000131 "
		   " 29065.70c 0.000058 "
		   " 28058.70c 0.001784 "
		   " 28060.70c 0.000687 "
		   " 28061.70c 0.000030 "
		   " 28062.70c 0.000095 "
		   " 28064.70c 0.000024 "
		   " 42092.70c 0.000002 "
		   " 42094.70c 0.000001 "
		   " 42095.70c 0.000002 "
		   " 42096.70c 0.000002 "
		   " 42097.70c 0.000001 "
		   " 42098.70c 0.000003 "
		   " 42100.70c 0.000001 "
		   " 13027.70c 0.000440 "
		   " 41093.70c 0.000260 "
		   " 23051.70c 0.000020 "
		   " 22046.70c 0.000016 "
		   " 22047.70c 0.000014 "
		   " 22048.70c 0.000140 "
		   " 22049.70c 0.000010 "
		   " 22050.70c 0.000010 "
		   " 07014.70c 0.000044 "
		   " 26054.70c 0.057203 "
		   " 26056.70c 0.897965 "
		   " 26057.70c 0.020738 "
		   " 26058.70c 0.002760 "
		   " 27059.70c 0.000153 ","fe56.12t",MLib);
  MObj.setMXitem(6000, 70, 'c', "h", "06012");
  MObj.setDensity(-7.85);
  setMaterial(MObj);

  return;
}

} // NAMESPACE ModelSupport
