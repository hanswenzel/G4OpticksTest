cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name G4OpticksTest)
project(${name} VERSION 0.1.0)
include(OpticksBuildOptions)

if(POLICY CMP0077)  # see note/issues/cmake-3.13.4-FindCUDA-warnings.rst
    cmake_policy(SET CMP0077 OLD)
endif()


find_package( G4OK CONFIG REQUIRED )
set(SOURCES
ColorReader.cc
ConfigurationManager.cc
ConfigurationManagerMessenger.cc
Ctx.cc
DetectorConstruction.cc
EventAction.cc
G4.cc
L4Cerenkov.cc
L4Scintillation.cc
OpHit.cc
PhotonSD.cc
PhysicsList.cc
PrimaryGeneratorAction.cc
RunAction.cc
SensitiveDetector.cc
SteppingAction.cc
TrackerSD.cc
TrackInfo.cc
TrackingAction.cc
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
#file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#set(libsuffix .so)
add_executable(${name} ${name}.cc ${SOURCES})

target_link_libraries(${name} Opticks::G4OK )
target_compile_definitions( ${name} 
  PRIVATE 
      WITH_OPTICKS
 )

install(TARGETS ${name} DESTINATION lib)



