# SPDX-FileCopyrightText: 2019 - 2023 Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required( VERSION 3.21 )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

cmake_policy(SET CMP0010 NEW)

project( blackchocobo VERSION 1.16.0.0 DESCRIPTION "Final Fantasy 7 Save Editor")
# Get the version from git if it's a git repository
IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
  FIND_PACKAGE(Git)
  IF(GIT_FOUND)
    EXECUTE_PROCESS(
      COMMAND ${GIT_EXECUTABLE} describe --long --match v*
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE GITREV
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
      string(REGEX MATCH [0-9]+ MAJOR ${GITREV})
      string(REGEX MATCH \\.[0-9]+ MINOR ${GITREV})
      string(REPLACE "." "" MINOR ${MINOR})
      string(REGEX MATCH [0-9]+\- PATCH ${GITREV})
      string(REPLACE "-" "" PATCH ${PATCH})
      string(REGEX MATCH \-[0-9]+\- TWEAK ${GITREV})
      string(REPLACE "-" "" TWEAK ${TWEAK})
      set(CMAKE_PROJECT_VERSION_MAJOR ${MAJOR})
      set(CMAKE_PROJECT_VERSION_MINOR ${MINOR})
      set(CMAKE_PROJECT_VERSION_PATCH ${PATCH})
      set(CMAKE_PROJECT_VERSION_TWEAK ${TWEAK})
      set(CMAKE_PROJECT_VERSION "${MAJOR}.${MINOR}.${PATCH}.${TWEAK}")
  ENDIF(GIT_FOUND)
  ELSE()
ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)

#Clean up version Number
set(BC_VERSION "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}")
if(NOT CMAKE_PROJECT_VERSION_PATCH EQUAL 0)
    string(APPEND BC_VERSION ".${CMAKE_PROJECT_VERSION_PATCH}")
endif()
if(NOT CMAKE_PROJECT_VERSION_TWEAK EQUAL 0)
    string(APPEND BC_VERSION "-${CMAKE_PROJECT_VERSION_TWEAK}")
endif()
MESSAGE(STATUS "PROJECT VERSION ${BC_VERSION}")
add_definitions(-DBC_VERSION="${BC_VERSION}")

set(QT_DEFAULT_MAJOR_VERSION 6 CACHE STRING "" FORCE)
set(REQUIRED_QT_VERSION 6.2.0)
set(REQUIRED_FF7TK_VERSION 1.2.0.5)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

#Set Deployed Binary Name
if(WIN32 OR APPLE)
    set(BIN_NAME "Black_Chocobo")
else()
    set(BIN_NAME "blackchocobo")
endif()

find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS Core)
get_target_property(qmake_executable Qt6::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${qmake_executable}" DIRECTORY)
if(WIN32 OR APPLE)
    if(WIN32)
        set(deployqtapp windeployqt)
    elseif(APPLE)
        set(deployqtapp macdeployqt)
    endif()
    find_program(PLATFORMDEPLOYQT ${deployqtapp} HINTS "${_qt_bin_dir}")
endif()

add_subdirectory(deploy)
add_subdirectory(icons)
add_subdirectory(qhexedit)
add_subdirectory(src)
add_subdirectory(translations)
