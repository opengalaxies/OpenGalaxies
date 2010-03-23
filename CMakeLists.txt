# OpenGalaxies - A Star Wars Galaxies PreCU Server Emulator
#
# Copyright (c) 2009 OpenGalaxies <http://www.opengalaxies.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.

CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )

PROJECT( OpenGalaxies )

# Version Information
SET( OG_VERSION_MAJOR 0 )
SET( OG_VERSION_MINOR 1 )
SET( OG_VERSION_BUILD 0 )
SET( OG_VERSION_STAGE "Pre-Alpha" )
SET( OG_VERSION_EXTRA "" )
SET( OG_VERSION "${OG_VERSION_MAJOR}.${OG_VERSION_MINOR}.${OG_VERSION_BUILD}" )

# Build Type
# SET( CMAKE_BUILD_TYPE "Release" )
SET( CMAKE_BUILD_TYPE "Debug" )

# Install
IF( OG_VERSION_EXTRA STREQUAL "" )
	SET( INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/${OG_VERSION}" CACHE PATH "Install Path" )
ELSE( ${OG_VERSION_EXTRA} STREQUAL "" )
	SET( INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/${OG_VERSION}-${OG_VERSION_EXTRA}" CACHE PATH "Install Path" )
ENDIF( OG_VERSION_EXTRA STREQUAL "" )

# Build Options
OPTION( BUILD_PLUGINS "Build provided plugins." OFF )
OPTION( UNIT_TESTING OFF )

# Modify Directories
SET( CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/build/cmake/modules
)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OpenGalaxies_BINARY_DIR}/bin CACHE PATH "Directory for all binary output." )
SET( CMAKE_ARHCIVE_OUTPUT_DIRECTORY ${OpenGalaxies_BINARY_DIR}/lib CACHE PATH "Directory for all static archive output." )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OpenGalaxies_BINARY_DIR}/lib CACHE PATH "Directory for all library output." )

# Find packages
FIND_PACKAGE( Boost REQUIRED )
FIND_PACKAGE( Qt4 4.5.0 )

# Configuration
INCLUDE( CheckPlatform )
INCLUDE( CheckEndianness )
INCLUDE( CheckInOutBuildSource )
INCLUDe( DefineTargetSuffixes )

CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/include/config.h )

# Default include directories
#
# include - This is where public headers reside. These are used for the development
# of third-party plugins, services and tools. (API)
#
# ${CMAKE_CURRENT_BINARY_DIR}/include - This is where config.h resides, so each
# build can have different configurations
INCLUDE_DIRECTORIES( src ${CMAKE_BINARY_DIR}/include ${Boost_INCLUDE_DIRS} external/include )

# Library Directories
#
LINK_DIRECTORIES( ${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS} )
IF( WIN32 )
	IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
		LINK_DIRECTORIES( ${LINK_DIRECTORIES} "${CMAKE_SOURCE_DIR}/external/lib/win32/debug" )
	ELSEIF( CMAKE_BUILD_TYPE STREQUAL "Release" )
		LINK_DIRECTORIES( ${LINK_DIRECTORIES} "{CMAKE_SOURCE_DIR}external/lib/win32/release" )
	ENDIF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
ENDIF( WIN32 )

IF( OG_PLATFORM EQUAL OG_PLATFORM_LINUX )
	IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
		LINK_DIRECTORIES( ${LINK_DIRECTORIES} "${CMAKE_SOURCE_DIR}/external/lib/linux/debug" )
	ELSEIF( CMAKE_BUILD_TYPE STREQUAL "Release" )
		LINK_DIRECTORIES( ${LINK_DIRECTORIES} "{CMAKE_SOURCE_DIR}external/lib/linux/release" )
	ENDIF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
ENDIF( OG_PLATFORM EQUAL OG_PLATFORM_LINUX )

IF( OG_PLATFORM EQUAL OG_PLATFORM_FREEBSD )
	IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
		LINK_DIRECTORIES( ${LINK_DIRECTORIES} "${CMAKE_SOURCE_DIR}/external/lib/freebsd/debug" )
	ELSEIF( CMAKE_BUILD_TYPE STREQUAL "Release" )
		LINK_DIRECTORIES( ${LINK_DIRECTORIES} "{CMAKE_SOURCE_DIR}external/lib/freebsd/release" )
	ENDIF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
ENDIF( OG_PLATFORM EQUAL OG_PLATFORM_FREEBSD )

ADD_SUBDIRECTORY( src )

IF( UNIT_TESTING )
	INCLUDE( CTest )
	ENABLE_TESTING()
	ADD_SUBDIRECTORY( tests )
ENDIF( UNIT_TESTING )

IF( BUILD_PLUGINS )
	ADD_SUBDIRECTORY( plugins )
ENDIF( BUILD_PLUGINS )

