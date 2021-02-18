// This file is generated by the 'optics2var' script from the optics file.
// Namespace(dtl='LinacDTL1', end='D204US', opt='optics.dat', start='quad1213')
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include <complex>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <memory>

#include "Exception.h"
#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "GTKreport.h"
#include "OutputLog.h"
#include "support.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Code.h"
#include "varList.h"
#include "FuncDataBase.h"
#include "PipeGenerator.h"
#include "essLinacVariableSetup.h"

namespace setVariable
{
void
EssLinacMBetaVariables(FuncDataBase &Control)
  /*!
    Create all the PMQ variables
    \param Control :: DataBase
  */
{
  ELog::RegMethod RegA("essVariables[F]","EssLinacMBetaVariables");

  // Beam Pipe

  setVariable::PipeGenerator PipeGen;
  PipeGen.setPipe(62.0,0.0);
  PipeGen.setWindow(62.0,0.0);
  PipeGen.setFlange(62.0,0.0);

  double mbcvtLength = 150.0;
  double quadLength = 35.0;

  int index = 0;
  int indexHEBT = 0;
  int indexHEBT2 = 0;
  
  PipeGen.generatePipe(Control,"LinacMBetaSection0",25.12);
  Control.addVariable("LinacMBetaSection0VoidMat","Air");

  Control.addVariable("LinacMBetaVacuumPipe0Thickness",0.4);
  Control.addVariable("LinacMBetaVacuumPipe0VoidMat","Void");
  Control.addVariable("LinacMBetaVacuumPipe0Length",25.12);
  Control.addVariable("LinacMBetaVacuumPipe0Mat","SS316_PNNL");
  Control.addVariable("LinacMBetaVacuumPipe0InnerRadius",2.855);
  
  double pipeRad = 5.001;
  //--------
  for(int i=1;i<10;i++){
    // Quad
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11),quadLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11)+"VoidMat","Air");
    
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"Length",quadLength);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"VoidMat","Void");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"Thickness",0.4);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"YokeMat","MARS_QXYOKE");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"CoilMat","MARS_QXCOIL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"PipeRad",pipeRad);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+1),73.0);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+1)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+1)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+1)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+1)+"Length",73.0);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+1)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+1)+"InnerRadius",pipeRad);

    // Quad
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+2),quadLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+2)+"VoidMat","Air");
    
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"Length",quadLength);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"VoidMat","Void");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"Thickness",0.4);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"YokeMat","MARS_QXYOKE");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"CoilMat","MARS_QXCOIL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"PipeRad",pipeRad);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+3),25.12);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+3)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+3)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+3)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+3)+"Length",25.12);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+3)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+3)+"InnerRadius",pipeRad);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+4),29.38);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+4)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+4)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+4)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+4)+"Length",29.38);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+4)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+4)+"InnerRadius",4.688);

    // cvt
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+5),mbcvtLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+5)+"VoidMat","Air");

    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"VoidMat","Void");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"Length",mbcvtLength);
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"InnerMat","Niobium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"OuterMat","Titanium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"ThermalMat","Aluminium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"HeliumMat","LiqHelium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"PipeRad",6.79);

    // cvt    
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+6),mbcvtLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+6)+"VoidMat","Air");

    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"VoidMat","Void");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"Length",mbcvtLength);
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"InnerMat","Niobium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"OuterMat","Titanium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"ThermalMat","Aluminium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"HeliumMat","LiqHelium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"PipeRad",6.79);

    // cvt
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+7),mbcvtLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+7)+"VoidMat","Air");

    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"VoidMat","Void");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"Length",mbcvtLength);
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"InnerMat","Niobium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"OuterMat","Titanium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"ThermalMat","Aluminium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"HeliumMat","LiqHelium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"PipeRad",6.79);

    // cvt
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+8),mbcvtLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+8)+"VoidMat","Air");

    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"VoidMat","Void");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"Length",mbcvtLength);
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"InnerMat","Niobium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"OuterMat","Titanium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"ThermalMat","Aluminium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"HeliumMat","LiqHelium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"PipeRad",6.79);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+9),29.38);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+9)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+9)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+9)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+9)+"Length",29.38);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+9)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+9)+"InnerRadius",4.688);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+10),25.12);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+10)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+10)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+10)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+10)+"Length",25.12);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+10)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+10)+"InnerRadius",pipeRad);
    index = i*11+10;
  }
  index = index+1;
  for(int i=index;i<(index+21);i++){
    // Quad
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11),quadLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11)+"VoidMat","Air");
    
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"Length",quadLength);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"VoidMat","Void");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"Thickness",0.4);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"YokeMat","MARS_QXYOKE");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"CoilMat","MARS_QXCOIL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11)+"PipeRad",pipeRad);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+1),73.0);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+1)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+1)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+1)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+1)+"Length",73.0);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+1)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+1)+"InnerRadius",pipeRad);

    // Quad
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+2),quadLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+2)+"VoidMat","Air");
    
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"Length",quadLength);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"VoidMat","Void");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"Thickness",0.4);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"YokeMat","MARS_QXYOKE");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"CoilMat","MARS_QXCOIL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*11+2)+"PipeRad",pipeRad);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+3),25.12);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+3)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+3)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+3)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+3)+"Length",25.12);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+3)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+3)+"InnerRadius",pipeRad);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+4),29.38);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+4)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+4)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+4)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+4)+"Length",29.38);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+4)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+4)+"InnerRadius",5.0314);

    // cvt
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+5),mbcvtLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+5)+"VoidMat","Air");

    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"VoidMat","Void");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"Length",mbcvtLength);
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"InnerMat","Niobium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"OuterMat","Titanium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"ThermalMat","Aluminium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"HeliumMat","LiqHelium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+5)+"PipeRad",8.0);

    // cvt    
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+6),mbcvtLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+6)+"VoidMat","Air");

    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"VoidMat","Void");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"Length",mbcvtLength);
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"InnerMat","Niobium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"OuterMat","Titanium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"ThermalMat","Aluminium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"HeliumMat","LiqHelium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+6)+"PipeRad",8.0);

    // cvt
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+7),mbcvtLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+7)+"VoidMat","Air");

    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"VoidMat","Void");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"Length",mbcvtLength);
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"InnerMat","Niobium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"OuterMat","Titanium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"ThermalMat","Aluminium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"HeliumMat","LiqHelium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+7)+"PipeRad",8.0);

    // cvt
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+8),mbcvtLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+8)+"VoidMat","Air");

    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"VoidMat","Void");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"Length",mbcvtLength);
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"InnerMat","Niobium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"OuterMat","Titanium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"ThermalMat","Aluminium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"HeliumMat","LiqHelium");
    Control.addVariable("LinacMBCVT"+std::to_string(i*11+8)+"PipeRad",8.0);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+9),29.38);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+9)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+9)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+9)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+9)+"Length",29.38);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+9)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+9)+"InnerRadius",5.0314);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*11+10),25.12);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*11+10)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+10)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+10)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+10)+"Length",25.12);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+10)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*11+10)+"InnerRadius",pipeRad);
    indexHEBT = i*11+10;
  }
  indexHEBT = indexHEBT + 1;
 
  for(int i=indexHEBT;i<(indexHEBT+15);i++){

    // Quad
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*4),quadLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*4)+"VoidMat","Air");
    
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4)+"Length",quadLength);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4)+"VoidMat","Void");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4)+"Thickness",0.4);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4)+"YokeMat","MARS_QXYOKE");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4)+"CoilMat","MARS_QXCOIL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4)+"PipeRad",pipeRad);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*4+1),73.0);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*4+1)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*4+1)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*4+1)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*4+1)+"Length",73.0);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*4+1)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*4+1)+"InnerRadius",pipeRad);

    // Quad
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*4+2),quadLength);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*4+2)+"VoidMat","Air");
    
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4+2)+"Length",quadLength);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4+2)+"VoidMat","Void");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4+2)+"Thickness",0.4);
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4+2)+"PipeMat","SS316_PNNL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4+2)+"YokeMat","MARS_QXYOKE");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4+2)+"CoilMat","MARS_QXCOIL");
    Control.addVariable("LinacMBetaQXQuad6"+std::to_string(i*4+2)+"PipeRad",pipeRad);

    // drift
    PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(i*4+3),709.0);
    Control.addVariable("LinacMBetaSection"+std::to_string(i*4+3)+"VoidMat","Air");

    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*4+3)+"Thickness",0.4);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*4+3)+"VoidMat","Void");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*4+3)+"Length",709.0);
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*4+3)+"Mat","SS316_PNNL");
    Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(i*4+3)+"InnerRadius",pipeRad);

    indexHEBT2 = i*4+3;
  }
  indexHEBT2 = indexHEBT2+1;

  // Quad
  PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(indexHEBT2),quadLength);
  Control.addVariable("LinacMBetaSection"+std::to_string(indexHEBT2)+"VoidMat","Air");
  
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2)+"Length",quadLength);
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2)+"VoidMat","Void");
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2)+"Thickness",0.4);
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2)+"PipeMat","SS316_PNNL");
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2)+"YokeMat","MARS_QXYOKE");
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2)+"CoilMat","MARS_QXCOIL");
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2)+"PipeRad",pipeRad);
  
  // drift
  PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(indexHEBT2+1),73.0);
  Control.addVariable("LinacMBetaSection"+std::to_string(indexHEBT2+1)+"VoidMat","Air");
  
  Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(indexHEBT2+1)+"Thickness",0.4);
  Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(indexHEBT2+1)+"VoidMat","Void");
  Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(indexHEBT2+1)+"Length",73.0);
  Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(indexHEBT2+1)+"Mat","SS316_PNNL");
  Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(indexHEBT2+1)+"InnerRadius",pipeRad);
  
  // Quad
  PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(indexHEBT2+2),quadLength);
  Control.addVariable("LinacMBetaSection"+std::to_string(indexHEBT2+2)+"VoidMat","Air");
    
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2+2)+"Length",quadLength);
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2+2)+"VoidMat","Void");
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2+2)+"Thickness",0.4);
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2+2)+"PipeMat","SS316_PNNL");
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2+2)+"YokeMat","MARS_QXYOKE");
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2+2)+"CoilMat","MARS_QXCOIL");
  Control.addVariable("LinacMBetaQXQuad6"+std::to_string(indexHEBT2+2)+"PipeRad",pipeRad);
  
  // drift
  PipeGen.generatePipe(Control,"LinacMBetaSection"+std::to_string(indexHEBT2+3),87.15);
  Control.addVariable("LinacMBetaSection"+std::to_string(indexHEBT2+3)+"VoidMat","Air");
  
  Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(indexHEBT2+3)+"Thickness",0.4);
  Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(indexHEBT2+3)+"VoidMat","Void");
  Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(indexHEBT2+3)+"Length",87.15);
  Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(indexHEBT2+3)+"Mat","SS316_PNNL");
  Control.addVariable("LinacMBetaVacuumPipe"+std::to_string(indexHEBT2+3)+"InnerRadius",pipeRad); 
  
  return;
}
}
    
