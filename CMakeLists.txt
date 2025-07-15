# Versión mínima de CMake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(SolarSim)

# Buscamos Geant4 y le pedimos que active TODOS los drivers de UI y VIS que encuentre.
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# Definir directorios
include_directories(${PROJECT_SOURCE_DIR}/include)

# --- Lista completa de todos los archivos fuente del proyecto ---
set(PROJECT_SOURCES
  SolarSim.cc
  src/ActionInitialization.cc
  src/DetectorConstruction.cc
  src/EventAction.cc
  src/PrimaryGeneratorAction.cc
  src/RunAction.cc
  src/SensitiveDetector.cc
  src/Run.cc
  src/SteppingAction.cc
  src/TrackingAction.cc
)

# Creamos UN SOLO ejecutable
add_executable(SolarSim ${PROJECT_SOURCES})

# Enlazamos las librerías de Geant4
target_link_libraries(SolarSim ${Geant4_LIBRARIES})

# Mensaje para el usuario
message(STATUS "Compilando con soporte de visualización y conteo de procesos.")
