# Try to find OpenFOAM-1.6-ext
# Once done this will define
#
# OF16ext_FOUND          - system has OpenFOAM-1.6-ext installed

#FIND_PATH(OF16ext_DIR NAMES etc/bashrc
FIND_FILE(OF16ext_BASHRC NAMES etc/bashrc
  HINTS
  $ENV{HOME}/OpenFOAM/OpenFOAM-1.6-ext
  /opt/OpenFOAM/OpenFOAM-1.6-ext
)
message(STATUS ${OF16ext_BASHRC})

SET(OF16ext_FOUND FALSE)
IF(OF16ext_BASHRC)
  #set(OF16ext_BASHRC "${OF16ext_DIR}/etc/bashrc")
  GET_FILENAME_COMPONENT(OF16ext_ETC_DIR ${OF16ext_BASHRC} PATH)
  GET_FILENAME_COMPONENT(OF16ext_DIR ${OF16ext_ETC_DIR} PATH)

  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${OF16ext_BASHRC} print-c++FLAGS OUTPUT_VARIABLE OF16ext_CXX_FLAGS)
  set(OF16ext_CXX_FLAGS "${OF16ext_CXX_FLAGS} -DOF16ext")

  detectEnvVars(OF16ext WM_PROJECT WM_PROJECT_VERSION WM_OPTIONS METIS_LIB_DIR PARMETIS_LIB_DIR SCOTCH_LIB_DIR MESQUITE_LIB_DIR FOAM_MPI_LIBBIN FOAM_APPBIN FOAM_LIBBIN)

  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/printOFLibs ${OF16ext_BASHRC} OUTPUT_VARIABLE OF16ext_LIBRARIES)
  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/printOFincPath ${OF16ext_BASHRC} OUTPUT_VARIABLE OF16ext_INCLUDE_PATHS)

  set(OF16ext_LIBSRC_DIR "${OF16ext_DIR}/src")
  set(OF16ext_LIB_DIR "${OF16ext_DIR}/lib/${OF16ext_WM_OPTIONS}")
  
  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${OF16ext_BASHRC} print-LINKLIBSO OUTPUT_VARIABLE OF16ext_LINKLIBSO_full)
  execute_process(COMMAND ${CMAKE_SOURCE_DIR}/CMake/getOFCfgVar ${OF16ext_BASHRC} print-LINKEXE OUTPUT_VARIABLE OF16ext_LINKEXE_full)
  string(REGEX REPLACE "^[^ ]+" "" OF16ext_LINKLIBSO ${OF16ext_LINKLIBSO_full})
  string(REGEX REPLACE "^[^ ]+" "" OF16ext_LINKEXE ${OF16ext_LINKEXE_full})
  message(STATUS "libso link flags = "  ${OF16ext_LINKLIBSO})
  message(STATUS "exe link flags = "  ${OF16ext_LINKEXE})

  set(OF16ext_INSIGHT_INSTALL_BIN "bin/${OF16ext_WM_PROJECT}-${OF16ext_WM_PROJECT_VERSION}")
  set(OF16ext_INSIGHT_INSTALL_LIB "lib/${OF16ext_WM_PROJECT}-${OF16ext_WM_PROJECT_VERSION}")
  set(OF16ext_INSIGHT_BIN "${CMAKE_BINARY_DIR}/${OF16ext_INSIGHT_INSTALL_BIN}")
  set(OF16ext_INSIGHT_LIB "${CMAKE_BINARY_DIR}/${OF16ext_INSIGHT_INSTALL_LIB}")

  list(APPEND INSIGHT_OFES_VARCONTENT "OF16ext@`find \\\${PATH//:/ } -maxdepth 1 -name insight.bashrc.of16ext -print -quit`#160")
  set(INSIGHT_OF_ALIASES "${INSIGHT_OF_ALIASES}
alias of16ext=\"source insight.bashrc.of16ext\"
")
  create_script("insight.bashrc.of16ext"
"source ${OF16ext_BASHRC}

foamClean=$WM_PROJECT_DIR/bin/foamCleanPath
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${OF16ext_INSIGHT_LIB}
#- Clean LD_LIBRARY_PATH
cleaned=`$foamClean \"$LD_LIBRARY_PATH\"` && LD_LIBRARY_PATH=\"$cleaned\"
export PATH=$PATH:${OF16ext_INSIGHT_BIN}
#- Clean PATH
cleaned=`$foamClean \"$PATH\"` && PATH=\"$cleaned\"
")

  macro (setup_exe_target_OF16ext targetname sources exename includes)
    add_executable(${targetname} ${sources})
    set(allincludes ${includes})
    LIST(APPEND allincludes "${OF16ext_INCLUDE_PATHS}")
    set_target_properties(${targetname} PROPERTIES INCLUDE_DIRECTORIES "${allincludes}")
    set_target_properties(${targetname} PROPERTIES COMPILE_FLAGS ${OF16ext_CXX_FLAGS})
    set_target_properties(${targetname} PROPERTIES LINK_FLAGS "${OF16ext_LINKEXE} ${LIB_SEARCHFLAGS}")
    set_target_properties(${targetname} PROPERTIES OUTPUT_NAME ${exename})
    set_target_properties(${targetname} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OF16ext_INSIGHT_BIN})
    target_link_libraries(${targetname} 
      #${OF16ext_LIB_DIR}/libOpenFOAM.so 
      ${OF16ext_LIBRARIES}
      ${OF16ext_FOAM_MPI_LIBBIN}/libPstream.so 
      #${OF16ext_METIS_LIB_DIR}/libmetis.a
      ${OF16ext_PARMETIS_LIB_DIR}/libparmetis.so
      ${OF16ext_SCOTCH_LIB_DIR}/libscotch.so
      ${OF16ext_MESQUITE_LIB_DIR}/libmesquite.so
      ${ARGN})
     install(TARGETS ${targetname} RUNTIME DESTINATION ${OF16ext_INSIGHT_INSTALL_BIN} COMPONENT ${INSIGHT_INSTALL_COMPONENT})
  endmacro()
  
  macro (setup_lib_target_OF16ext targetname sources exename includes)
    get_directory_property(temp LINK_DIRECTORIES)

    set(allincludes ${includes})
    LIST(APPEND allincludes "${OF16ext_INCLUDE_PATHS}")
    
    SET(LIB_SEARCHFLAGS "-L${OF16ext_LIB_DIR} -L${OF16ext_FOAM_MPI_LIBBIN} -L${OF16ext_METIS_LIB_DIR} -L${OF16ext_PARMETIS_LIB_DIR} -L${OF16ext_SCOTCH_LIB_DIR} -L${OF16ext_MESQUITE_LIB_DIR}")
    add_library(${targetname} SHARED ${sources})
    set_target_properties(${targetname} PROPERTIES INCLUDE_DIRECTORIES "${allincludes}")
    set_target_properties(${targetname} PROPERTIES COMPILE_FLAGS ${OF16ext_CXX_FLAGS})
    set_target_properties(${targetname} PROPERTIES LINK_FLAGS "${OF16ext_LINKLIBSO} ${LIB_SEARCHFLAGS}")
    set_target_properties(${targetname} PROPERTIES OUTPUT_NAME ${exename})
    set_target_properties(${targetname} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${OF16ext_INSIGHT_LIB})
    target_link_libraries(${targetname} ${OF16ext_LIBRARIES} ${ARGN}) 
    install(TARGETS ${targetname} LIBRARY DESTINATION ${OF16ext_INSIGHT_INSTALL_LIB} COMPONENT ${INSIGHT_INSTALL_COMPONENT})
    
    set_directory_properties(LINK_DIRECTORIES ${temp})
  endmacro()
  
  SET(OF16ext_FOUND TRUE)
ENDIF(OF16ext_BASHRC)
