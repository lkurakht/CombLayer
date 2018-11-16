# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# compile CXX with g++
CXX_FLAGS = -fPIC -Wconversion -W -Wall -Wextra -Wno-comment -fexceptions -std=c++11 -O2  -fPIC  

CXX_DEFINES = -Dlibloki_EXPORTS

CXX_INCLUDES = -I/home/scionti/CombLayer-Vespa/include -I/home/scionti/CombLayer-Vespa/beamlineInc -I/home/scionti/CombLayer-Vespa/globalInc -I/home/scionti/CombLayer-Vespa/instrumentInc -I/home/scionti/CombLayer-Vespa/scatMatInc -I/home/scionti/CombLayer-Vespa/specialInc -I/home/scionti/CombLayer-Vespa/transportInc -I/home/scionti/CombLayer-Vespa/testInclude -I/home/scionti/CombLayer-Vespa/System/attachCompInc -I/home/scionti/CombLayer-Vespa/System/compWeightsInc -I/home/scionti/CombLayer-Vespa/System/constructInc -I/home/scionti/CombLayer-Vespa/System/constructVarInc -I/home/scionti/CombLayer-Vespa/System/crystalInc -I/home/scionti/CombLayer-Vespa/System/endfInc -I/home/scionti/CombLayer-Vespa/System/flukaPhysicsInc -I/home/scionti/CombLayer-Vespa/System/flukaProcessInc -I/home/scionti/CombLayer-Vespa/System/flukaTallyInc -I/home/scionti/CombLayer-Vespa/System/funcBaseInc -I/home/scionti/CombLayer-Vespa/System/geomInc -I/home/scionti/CombLayer-Vespa/System/inputInc -I/home/scionti/CombLayer-Vespa/System/insertUnitInc -I/home/scionti/CombLayer-Vespa/System/logInc -I/home/scionti/CombLayer-Vespa/System/md5Inc -I/home/scionti/CombLayer-Vespa/System/mersenneInc -I/home/scionti/CombLayer-Vespa/System/monteInc -I/home/scionti/CombLayer-Vespa/System/phitsPhysicsInc -I/home/scionti/CombLayer-Vespa/System/phitsProcessInc -I/home/scionti/CombLayer-Vespa/System/phitsSupportInc -I/home/scionti/CombLayer-Vespa/System/phitsTallyInc -I/home/scionti/CombLayer-Vespa/System/physicsInc -I/home/scionti/CombLayer-Vespa/System/polyInc -I/home/scionti/CombLayer-Vespa/System/processInc -I/home/scionti/CombLayer-Vespa/System/simMCInc -I/home/scionti/CombLayer-Vespa/System/sourceInc -I/home/scionti/CombLayer-Vespa/System/supportInc -I/home/scionti/CombLayer-Vespa/System/tallyInc -I/home/scionti/CombLayer-Vespa/System/visitInc -I/home/scionti/CombLayer-Vespa/System/weightsInc -I/home/scionti/CombLayer-Vespa/System/workInc -I/home/scionti/CombLayer-Vespa/System/worldInc -I/home/scionti/CombLayer-Vespa/System/xmlInc -I/home/scionti/CombLayer-Vespa/Model/bibBuildInc -I/home/scionti/CombLayer-Vespa/Model/bnctBuildInc -I/home/scionti/CombLayer-Vespa/Model/buildInc -I/home/scionti/CombLayer-Vespa/Model/chipInc -I/home/scionti/CombLayer-Vespa/Model/cuBlockInc -I/home/scionti/CombLayer-Vespa/Model/d4cModelInc -I/home/scionti/CombLayer-Vespa/Model/delftInc -I/home/scionti/CombLayer-Vespa/Model/epbBuildInc -I/home/scionti/CombLayer-Vespa/Model/essBuildInc -I/home/scionti/CombLayer-Vespa/Model/essConstructInc -I/home/scionti/CombLayer-Vespa/Model/essLinacInc -I/home/scionti/CombLayer-Vespa/Model/filterInc -I/home/scionti/CombLayer-Vespa/Model/gammaBuildInc -I/home/scionti/CombLayer-Vespa/Model/imatInc -I/home/scionti/CombLayer-Vespa/Model/lensModelInc -I/home/scionti/CombLayer-Vespa/Model/maxivBuildInc -I/home/scionti/CombLayer-Vespa/Model/moderatorInc -I/home/scionti/CombLayer-Vespa/Model/muonInc -I/home/scionti/CombLayer-Vespa/Model/photonInc -I/home/scionti/CombLayer-Vespa/Model/pipeBuildInc -I/home/scionti/CombLayer-Vespa/Model/sinbadBuildInc -I/home/scionti/CombLayer-Vespa/Model/singleItemBuildInc -I/home/scionti/CombLayer-Vespa/Model/snsBuildInc -I/home/scionti/CombLayer-Vespa/Model/t1BuildInc -I/home/scionti/CombLayer-Vespa/Model/t1EngineerInc -I/home/scionti/CombLayer-Vespa/Model/t1UpgradeInc -I/home/scionti/CombLayer-Vespa/Model/t3ModelInc -I/home/scionti/CombLayer-Vespa/Model/zoomInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/beerInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/bifrostInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/commonInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/commonVarInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/cspecInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/dreamInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/estiaInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/freiaInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/heimdalInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/lokiInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/longLokiInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/magicInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/miraclesInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/nmxInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/nnbarInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/odinInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/shortDreamInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/shortNmxInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/shortOdinInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/simpleItemInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/skadiInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/testBeamInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/trexInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/vespaInc -I/home/scionti/CombLayer-Vespa/Model/ESSBeam/vorInc -I/home/scionti/CombLayer-Vespa/Model/MaxIV/balderInc -I/home/scionti/CombLayer-Vespa/Model/MaxIV/commonBeamInc -I/home/scionti/CombLayer-Vespa/Model/MaxIV/cosaxsInc -I/home/scionti/CombLayer-Vespa/Model/MaxIV/maxpeemInc 
