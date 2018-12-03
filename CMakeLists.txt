# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

get_filename_component(DEV_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

set(PROJECT_ROOT "${DEV_ROOT}/")

set(SUBMODULE_ROOT "${IDF_PATH}/esp_mqtt")

set(MAIN_SRCS main/smartled.c)

set(EXTRA_COMPONENT_DIRS "${EXTRA_COMPONENT_DIRS} ${SUBMODULE_ROOT}")
set(BUILD_COMPONENTS "${BUILD_COMPONENTS} espmqtt")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(smartled)
