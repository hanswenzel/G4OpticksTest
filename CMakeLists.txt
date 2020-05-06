cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name G4OpticksTest)
project(${name} VERSION 0.1.0)
include(OpticksBuildOptions)

if(POLICY CMP0077)  # see note/issues/cmake-3.13.4-FindCUDA-warnings.rst
    cmake_policy(SET CMP0077 OLD)
endif()


find_package( G4OK CONFIG REQUIRED )


include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB detectors ${PROJECT_SOURCE_DIR}/gdml/*.gdml)
file(GLOB schemas ${PROJECT_SOURCE_DIR}/gdml/*.xsd)

add_executable(${name} ${name}.cc ${sources} ${headers})

target_link_libraries(${name} Opticks::G4OK )
target_compile_definitions( ${name} 
  PRIVATE 
      WITH_OPTICKS
 )

install(TARGETS ${name} DESTINATION bin)
install(FILES ${detectors} ${schemas}   DESTINATION bin)

