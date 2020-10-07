
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name G4OpticksTest)
project(${name} VERSION 0.1.0)
include(OpticksBuildOptions)

if(POLICY CMP0077)  # see note/issues/cmake-3.13.4-FindCUDA-warnings.rst
    cmake_policy(SET CMP0077 OLD)
endif()


find_package( G4OK CONFIG REQUIRED )
find_package( GGeo CONFIG REQUIRED )
#----------------------------------------------------------------------------
# Find ROOT (required package)
#
find_package(ROOT REQUIRED)

# ROOT version 6 required
if(ROOT_FOUND)
  STRING(REGEX MATCH "6.*" VERSION6MATCH ${ROOT_VERSION})
  if(NOT VERSION6MATCH)
    message(FATAL_ERROR "P01 requires ROOT 6")
  endif()
endif()

# Include ROOT's CMake functions for dictionary generation
include("${ROOT_DIR}/RootMacros.cmake")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include
                    ${ROOT_INCLUDE_DIRS})


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB detectors ${PROJECT_SOURCE_DIR}/gdml/*.gdml)
file(GLOB schemas ${PROJECT_SOURCE_DIR}/gdml/*.xsd)
file(GLOB macros ${PROJECT_SOURCE_DIR}/*.mac)

add_executable(${name} ${name}.cc ${sources} ${headers})

target_link_libraries(${name} Opticks::G4OK ${ROOT_LIBRARIES})
link_directories( ${ROOT_LIBRARY_DIR} )
target_compile_definitions( ${name} 
  PRIVATE 
      WITH_OPTICKS
 )
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir2='${dir}'")
endforeach()
install(TARGETS ${name} DESTINATION bin)
install(FILES ${detectors} ${schemas}   ${macros} DESTINATION bin)
