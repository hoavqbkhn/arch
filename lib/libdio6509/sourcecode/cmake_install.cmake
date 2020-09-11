# Install script for directory: /home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/build")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/libdio6509.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/dataHelper.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/devices.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/eepromHelper.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/iRegAccessor.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/osiBus.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/osiTypes.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/rtsiResetHelper.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tCHInCh.cpp"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tCHInCh.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tCHInChValues.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tChpServices.cpp"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tChpServices.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tChpServicesValues.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tDioPorts.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tDioPortsValues.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tDioRegAccessor.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tPCIe6509.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tPCIe6509Values.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tPfiPorts.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tPfiPortsValues.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tPfiRegAccessor.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tPortHelperFactory.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tPortHelper.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tStaticDio.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tStaticDioValues.h"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tCHInCh.ipp"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tChpServices.ipp"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tDioPorts.ipp"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tPCIe6509.ipp"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tPfiPorts.ipp"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/tStaticDio.ipp"
    "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/dio6509.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/example/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/ttdk/Working/git_repo/casu-c/source_code/framework/libdio6509/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
