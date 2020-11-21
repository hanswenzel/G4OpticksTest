
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name G4OpticksTest)
project(${name} VERSION 0.1.0)
include(OpticksBuildOptions)

if(POLICY CMP0077)  # see note/issues/cmake-3.13.4-FindCUDA-warnings.rst
    cmake_policy(SET CMP0077 OLD)
endif()


find_package( G4OK CONFIG REQUIRED )
find_package( GGeo CONFIG REQUIRED )
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir3='${dir}'")
endforeach()
#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT REQUIRED)

# ROOT version 6 required
if(ROOT_FOUND)
  STRING(REGEX MATCH "6.*" VERSION6MATCH ${ROOT_VERSION})
  if(NOT VERSION6MATCH)
    message(FATAL_ERROR "${name} requires ROOT 6")
  endif()
endif()

# Include ROOT's CMake functions for dictionary generation
include("${ROOT_DIR}/RootMacros.cmake")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include
  ${ROOT_INCLUDE_DIRS}
  ${OPTICKS_PREFIX}/include/G4OK/
  ${OPTICKS_PREFIX}/include/GGEO/
  ${OPTICKS_PREFIX}/include/OpticksCore/
  ${OPTICKS_PREFIX}/externals/plog/include/
  ${PROJECT_SOURCE_DIR}/include
  ${Geant4_INCLUDE_DIR}
  ${ROOT_INCLUDE_DIRS}
  )

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc ) 
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB detectors ${PROJECT_SOURCE_DIR}/gdml/*.gdml)
file(GLOB schemas ${PROJECT_SOURCE_DIR}/gdml/*.xsd)
file(GLOB scripts ${PROJECT_SOURCE_DIR}/scripts/*)
file(GLOB macros ${PROJECT_SOURCE_DIR}/*.mac)


#----------------------------------------------------------------------------
# Generate dictionaries, add ROOT libraries properties
#
REFLEX_GENERATE_DICTIONARY(G4OpticksTestClasses include/G4OpticksTestClasses.hh SELECTION xml/selection.xml)
add_library(G4OpticksTestClassesDict SHARED ${sources} G4OpticksTestClasses.cxx)
set(libsuffix .so)
set(ROOT_LIBRARY_PROPERTIES ${ROOT_LIBRARY_PROPERTIES} SUFFIX ${libsuffix})
set_target_properties(G4OpticksTestClassesDict PROPERTIES ${ROOT_LIBRARY_PROPERTIES})
target_link_libraries(G4OpticksTestClassesDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

add_executable(${name} ${name}.cc ${sources} ${headers})
#add_library(G4OpticksTestClassesDict SHARED ${sources})
target_link_libraries(${name} Opticks::G4OK ${ROOT_LIBRARIES})

add_executable(readHits readHits.cc  ${sources} ${headers})
target_link_libraries(readHits G4OpticksTestClassesDict  Opticks::G4OK ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

link_directories( ${ROOT_LIBRARY_DIR} )
target_compile_definitions( ${name} 
  PRIVATE 
      WITH_OPTICKS
 )
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir2='${dir}'")
endforeach()
#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
#include_directories(${PROJECT_SOURCE_DIR}/include
#                    ${Geant4_INCLUDE_DIR}
#                    ${ROOT_INCLUDE_DIRS})


install(TARGETS ${name} DESTINATION bin)
install(FILES ${detectors} ${schemas}  ${scripts} ${macros} DESTINATION bin)
install(TARGETS G4OpticksTestClassesDict DESTINATION bin)
install(TARGETS readHits DESTINATION bin)
install(FILES ${PROJECT_BINARY_DIR}/G4OpticksTestClasses_rdict.pcm DESTINATION bin)

