cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

find_package(gz-cmake3 REQUIRED)

project(DummySensorSystem)

gz_find_package(gz-plugin2 REQUIRED COMPONENTS register)
set(GZ_PLUGIN_VER ${gz-plugin2_VERSION_MAJOR})

gz_find_package(gz-sim8 REQUIRED)
set(GZ_SIM_VER ${gz-sim8_VERSION_MAJOR})

find_package(gz-sensors8 REQUIRED)
set(GZ_SENSORS_VER ${gz-sensors8_VERSION_MAJOR})

# Use the locally cloned gz-sensors repo instead of fetching
set(GZ_SENSORS_LOCAL_PATH $ENV{HOME}/GSoC/custom-sensors/dummy_sensor)

# Ensure the path exists
if(NOT EXISTS ${GZ_SENSORS_LOCAL_PATH})
  message(FATAL_ERROR "Path ${GZ_SENSORS_LOCAL_PATH} does not exist. Make sure you have cloned gz-sensors correctly.")
endif()

# Add the dummy sensor from the local repository
add_subdirectory(${GZ_SENSORS_LOCAL_PATH} ${CMAKE_BINARY_DIR}/dummy_sensor)

add_library(${PROJECT_NAME} SHARED ${PROJECT_NAME}.cc)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    gz-plugin${GZ_PLUGIN_VER}::gz-plugin${GZ_PLUGIN_VER}
    gz-sim${GZ_SIM_VER}::gz-sim${GZ_SIM_VER}
    gz-sensors${GZ_SENSORS_VER}::gz-sensors${GZ_SENSORS_VER}
    dummy_sensor
)
target_include_directories(${PROJECT_NAME}
    PUBLIC ${GZ_SENSORS_LOCAL_PATH})

