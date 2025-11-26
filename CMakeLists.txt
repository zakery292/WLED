# WLED - ESP-IDF Build Configuration
# For building WLED with ESP-IDF instead of PlatformIO
#
# Usage:
#   source ~/esp/esp-idf/export.sh  (or wherever your IDF is)
#   idf.py set-target esp32  (or esp32s3, esp32c3, etc.)
#   idf.py build
#   idf.py flash monitor

cmake_minimum_required(VERSION 3.16)

# Include Arduino as a component before project()
set(EXTRA_COMPONENT_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/components
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(WLED)

