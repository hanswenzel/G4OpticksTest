cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name G4OpticksTest)
project(${name} VERSION 0.1.0)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

option(WITH_ROOT "Build example with ROOT" ON)
option(WITH_G4OPTICKS "Build example with OPTICKS" ON)

if(WITH_G4OPTICKS)
include(OpticksBuildOptions)
if(POLICY CMP0077)  # see note/issues/cmake-3.13.4-FindCUDA-warnings.rst
    cmake_policy(SET CMP0077 OLD)
  endif()
 find_package( G4OK CONFIG REQUIRED )
endif()

if(WITH_ROOT)
  find_package(ROOT REQUIRED)

# ROOT version 6 required
if(ROOT_FOUND)
  STRING(REGEX MATCH "6.*" VERSION6MATCH ${ROOT_VERSION})
  if(NOT VERSION6MATCH)
    message(FATAL_ERROR "${name} requires ROOT 6")
  endif()
endif()
# Include ROOT's CMake functions for dictionary generation
#  since root6.20, the file is renamed and included by default, so include
#  only when we find the *old* name
if(EXISTS "${ROOT_DIR}/modules/RootNewMacros.cmake")
   include("${ROOT_DIR}/modules/RootNewMacros.cmake")
endif()

#----------------------------------------------------------------------------
# G4OpticksTest requires shared libraries
#
if(NOT Geant4_shared_FOUND)
  message(FATAL_ERROR "G4OpticksTest must use shared libraries")
endif()
#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIRS})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
#----------------------------------------------------------------------------
# Generate dictionaries, add ROOT libraries properties
#
REFLEX_GENERATE_DICTIONARY(G4OpticksTestClasses include/G4OpticksTestClasses.hh SELECTION xml/selection.xml)
add_library(G4OpticksTestClassesDict SHARED ${sources} G4OpticksTestClasses.cxx)
set(libsuffix .so)
set(ROOT_LIBRARY_PROPERTIES ${ROOT_LIBRARY_PROPERTIES} SUFFIX ${libsuffix})
set_target_properties(G4OpticksTestClassesDict PROPERTIES ${ROOT_LIBRARY_PROPERTIES})
target_link_libraries(G4OpticksTestClassesDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
endif()


file(GLOB detectors ${PROJECT_SOURCE_DIR}/gdml/*.gdml)
file(GLOB schemas ${PROJECT_SOURCE_DIR}/gdml/*.xsd)
file(GLOB scripts ${PROJECT_SOURCE_DIR}/scripts/*)
file(GLOB macros ${PROJECT_SOURCE_DIR}/macros/*.mac)

add_executable(${name} ${name}.cc ${sources} ${headers})
target_compile_definitions( ${name} PRIVATE WITH_G4OPTICKS WITH_ROOT)
target_link_libraries(${name}  G4OpticksTestClassesDict Opticks::G4OK ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

if(WITH_ROOT)
add_executable(readHits readHits.cc  ${sources} ${headers})
target_link_libraries(readHits G4OpticksTestClassesDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
link_directories( ${ROOT_LIBRARY_DIR} )
endif()

install(TARGETS ${name} DESTINATION bin)
install(FILES ${detectors} ${schemas}  ${scripts} ${macros} DESTINATION bin)
if(WITH_ROOT)
  install(TARGETS G4OpticksTestClassesDict DESTINATION bin)
  install(TARGETS readHits DESTINATION bin)
  install(FILES ${PROJECT_BINARY_DIR}/G4OpticksTestClasses_rdict.pcm DESTINATION bin)
endif()
