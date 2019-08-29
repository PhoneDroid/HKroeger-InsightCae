# Try to find OpenFOAM-1.6-ext
# Once done this will define
#
# Fx31_FOUND          - system has foam-extend-3.1 installed

include(OpenFOAMfuncs)

#FIND_PATH(Fx31_DIR NAMES etc/bashrc
FIND_FILE(Fx31_BASHRC NAMES bashrc
  HINTS
  $ENV{HOME}/OpenFOAM/foam-extend-3.1/etc
  $ENV{HOME}/foam/foam-extend-3.1/etc
  /opt/foam/foam-extend-3.1/etc
)
message(STATUS ${Fx31_BASHRC})

SET(Fx31_FOUND FALSE)
IF(Fx31_BASHRC)
  #set(Fx31_BASHRC "${Fx31_DIR}/etc/bashrc")
  GET_FILENAME_COMPONENT(Fx31_ETC_DIR ${Fx31_BASHRC} PATH)
  GET_FILENAME_COMPONENT(Fx31_DIR ${Fx31_ETC_DIR} PATH)

  detectEnvVars(Fx31 WM_PROJECT WM_PROJECT_VERSION WM_OPTIONS METIS_LIB_DIR MESQUITE_LIB_DIR PARMETIS_LIB_DIR SCOTCH_LIB_DIR PARMGRIDGEN_LIB_DIR FOAM_APPBIN FOAM_LIBBIN FOAM_MPI_LIBBIN)

  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-c++FLAGS OUTPUT_VARIABLE Fx31_CXX_FLAGS)
  set(Fx31_CXX_FLAGS "${Fx31_CXX_FLAGS} -DFx31 -DOF16ext -DOF_VERSION=010601 -DOF_FORK_extend")

#  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-WM_OPTIONS OUTPUT_VARIABLE Fx31_WM_OPTIONS)
#  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-METIS_LIB_DIR OUTPUT_VARIABLE Fx31_METIS_LIB_DIR)
#  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-MESQUITE_LIB_DIR OUTPUT_VARIABLE Fx31_MESQUITE_LIB_DIR)
#  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-PARMETIS_LIB_DIR OUTPUT_VARIABLE Fx31_PARMETIS_LIB_DIR)
#  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-SCOTCH_LIB_DIR OUTPUT_VARIABLE Fx31_SCOTCH_LIB_DIR)
#  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-PARMGRIDGEN_LIB_DIR OUTPUT_VARIABLE Fx31_PARMGRIDGEN_LIB_DIR)
#  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-FOAM_APPBIN OUTPUT_VARIABLE Fx31_FOAM_APPBIN)
#  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-FOAM_LIBBIN OUTPUT_VARIABLE Fx31_FOAM_LIBBIN)

#  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/printOFLibs ${Fx31_BASHRC} OUTPUT_VARIABLE Fx31_LIBRARIES)
  detectIncPaths(Fx31)

#  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/printOFincPath ${Fx31_BASHRC} OUTPUT_VARIABLE Fx31_INCLUDE_PATHS)
 setOFlibvar(Fx31
#EulerianInterfacialModels # app #uncommenting this and the others below causes segfault at program ends...
IOFunctionObjects
POD
RBFMotionSolver
autoMesh
barotropicCompressibilityModel
blockMesh
cfMesh
checkFunctionObjects
chemistryModel
coalCombustion
combustionModels
compressibleLESModels
compressibleRASModels
#conjugateHeatTransfer # app
conversion
coupledLduMatrix
dieselSpray
dsmc
dynamicTopoFvMesh
engine
equationReader
errorEstimation
extrudeModel
fieldFunctionObjects
foamCalcFunctions
freeSurface
immersedBoundaryDynamicFvMesh
immersedBoundaryForceFunctionObject
incompressibleLESModels
incompressibleTransportModels
interfaceProperties
kineticTheoryModel
lagrangian
laminarFlameSpeedModels
lduSolvers
#materialModels # deprecated solvers
mesquiteMotionSolver
molecularMeasurements
molecule
multiSolver
phaseModel
randomProcesses
rhoCentralFoam
#rhopSonicFoam #app: BCs
sampling
scotchDecomp
solidModels
solidParticle
systemCall
tecio
userd-foam
userd-newFoam
utilityFunctionObjects
viscoelasticTransportModels
edgeMesh
ODE
reactionThermophysicalModels
lagrangianIntermediate
compressibleTurbulenceModel
fvMotionSolver
tetMotionSolver
immersedBoundaryTurbulence
forces
LESdeltas
LESfilters
potential
topoChangerFvMesh
finiteArea
basicThermophysicalModels
radiation
pdf
liquidMixture
solidMixture
immersedBoundary
incompressibleRASModels
dynamicFvMesh
specie
thermophysicalFunctions
liquids
solids
surfMesh
incompressibleTurbulenceModel
tetFiniteElement
solidBodyMotion
dynamicMesh
finiteVolume
meshTools
decompositionMethods
foam
)
detectDepLib(Fx31 "${Fx31_FOAM_LIBBIN}/libfoam.so" "Pstream")
detectDepLib(Fx31 "${Fx31_FOAM_LIBBIN}/libscotchDecomp.so" "scotch")
detectDepLib(Fx31 "${Fx31_FOAM_LIBBIN}/libmesquiteMotionSolver.so" "mesquite")

  set(Fx31_LIBSRC_DIR "${Fx31_DIR}/src")
  set(Fx31_LIB_DIR "${Fx31_DIR}/lib/${Fx31_WM_OPTIONS}")

  #execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-LINKLIBSO OUTPUT_VARIABLE Fx31_LINKLIBSO_full)
  #execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-LINKEXE OUTPUT_VARIABLE Fx31_LINKEXE_full)
  detectEnvVar(Fx31 LINKLIBSO LINKLIBSO_full)
  detectEnvVar(Fx31 LINKEXE LINKEXE_full)
  string(REGEX REPLACE "^[^ ]+" "" Fx31_LINKLIBSO ${Fx31_LINKLIBSO_full})
  string(REGEX REPLACE "^[^ ]+" "" Fx31_LINKEXE ${Fx31_LINKEXE_full})
  message(STATUS "libso link flags = "  ${Fx31_LINKLIBSO})
  message(STATUS "exe link flags = "  ${Fx31_LINKEXE})
  #execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${Fx31_BASHRC} print-FOAM_MPI_LIBBIN OUTPUT_VARIABLE Fx31_FOAM_MPI_LIBBIN)

  set(Fx31_INSIGHT_INSTALL_BIN "bin/${Fx31_WM_PROJECT}-${Fx31_WM_PROJECT_VERSION}")
  set(Fx31_INSIGHT_INSTALL_LIB "lib/${Fx31_WM_PROJECT}-${Fx31_WM_PROJECT_VERSION}")
  set(Fx31_INSIGHT_BIN "${CMAKE_BINARY_DIR}/${Fx31_INSIGHT_INSTALL_BIN}")
  set(Fx31_INSIGHT_LIB "${CMAKE_BINARY_DIR}/${Fx31_INSIGHT_INSTALL_LIB}")

  list(APPEND INSIGHT_OFES_VARCONTENT "FX31@`find \\\${PATH//:/ } -maxdepth 1 -name insight.bashrc.fx31 -print -quit`#161")
  set(INSIGHT_OF_ALIASES "${INSIGHT_OF_ALIASES}
alias fx31=\"source insight.bashrc.fx31\"
")
  create_script("insight.bashrc.fx31"
"source ${Fx31_BASHRC}

foamClean=$WM_PROJECT_DIR/bin/foamCleanPath
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${Fx31_INSIGHT_LIB}
#- Clean LD_LIBRARY_PATH
cleaned=`$foamClean \"$LD_LIBRARY_PATH\"` && LD_LIBRARY_PATH=\"$cleaned\"
export PATH=$PATH:${Fx31_INSIGHT_BIN}
#- Clean PATH
cleaned=`$foamClean \"$PATH\"` && PATH=\"$cleaned\"
")

  macro (setup_exe_target_Fx31 targetname sources exename includes)
    add_executable(${targetname} ${sources})
    set(allincludes ${includes})
    LIST(APPEND allincludes "${Fx31_INCLUDE_PATHS}")
    #LIST(APPEND allincludes "${Fx31_LIBSRC_DIR}/foam/lnInclude")
    #set_property(TARGET ${targetname} PROPERTY INCLUDE_DIRECTORIES ${allincludes})
    set_target_properties(${targetname} PROPERTIES INCLUDE_DIRECTORIES "${allincludes}")
    set_target_properties(${targetname} PROPERTIES COMPILE_FLAGS ${Fx31_CXX_FLAGS})
    set_target_properties(${targetname} PROPERTIES LINK_FLAGS "${Fx31_LINKEXE} ${LIB_SEARCHFLAGS}")
    set_target_properties(${targetname} PROPERTIES OUTPUT_NAME ${exename})
    set_target_properties(${targetname} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${Fx31_INSIGHT_BIN})
    target_link_libraries(${targetname} 
      #${Fx31_LIB_DIR}/libfoam.so 
      ${Fx31_LIBRARIES}
      #${Fx31_FOAM_MPI_LIBBIN}/libPstream.so 
      #${Fx31_METIS_LIB_DIR}/libmetis.a
#      ${Fx31_PARMETIS_LIB_DIR}/libparmetis.a
      #${Fx31_SCOTCH_LIB_DIR}/libscotch.so
      #${Fx31_SCOTCH_LIB_DIR}/libscotcherr.so
#      ${Fx31_MESQUITE_LIB_DIR}/libmesquite.so 
#       ${Fx31_PARMGRIDGEN_LIB_DIR}/libMGridGen.so
      ${ARGN})
     install(TARGETS ${targetname} RUNTIME DESTINATION ${Fx31_INSIGHT_INSTALL_BIN}  COMPONENT ${INSIGHT_INSTALL_COMPONENT})
  endmacro()
  
  macro (setup_lib_target_Fx31 targetname sources exename includes)
    get_directory_property(temp LINK_DIRECTORIES)
    
    SET(LIB_SEARCHFLAGS "-L${Fx31_LIB_DIR} -L${Fx31_FOAM_MPI_LIBBIN} -L${Fx31_METIS_LIB_DIR} -L${Fx31_PARMETIS_LIB_DIR} -L${Fx31_SCOTCH_LIB_DIR} -L${Fx31_MESQUITE_LIB_DIR}")
    add_library(${targetname} SHARED ${sources})
    set(allincludes ${includes})
    LIST(APPEND allincludes "${Fx31_INCLUDE_PATHS}")
#    LIST(APPEND allincludes "${Fx31_LIBSRC_DIR}/foam/lnInclude")
#    set_property(TARGET ${targetname} PROPERTY INCLUDE_DIRECTORIES ${allincludes})
    set_target_properties(${targetname} PROPERTIES INCLUDE_DIRECTORIES "${allincludes}")
    set_target_properties(${targetname} PROPERTIES COMPILE_FLAGS ${Fx31_CXX_FLAGS})
    set_target_properties(${targetname} PROPERTIES LINK_FLAGS "${Fx31_LINKLIBSO} ${LIB_SEARCHFLAGS}")
    set_target_properties(${targetname} PROPERTIES OUTPUT_NAME ${exename})
    set_target_properties(${targetname} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${Fx31_INSIGHT_LIB})
    target_link_libraries(${targetname} ${Fx31_LIBRARIES} ${ARGN}) 
    install(TARGETS ${targetname} LIBRARY DESTINATION ${Fx31_INSIGHT_INSTALL_LIB}  COMPONENT ${INSIGHT_INSTALL_COMPONENT})
    
    set_directory_properties(LINK_DIRECTORIES ${temp})
  endmacro()
  
  SET(Fx31_FOUND TRUE)
ENDIF(Fx31_BASHRC)
