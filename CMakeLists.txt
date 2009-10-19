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

# Install
SET( CMAKE_INSTALL_PREFIX ./ CACHE PATH "Install Path" )
SET( LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "The directory reletive to the install directory where all libraries will be dumped." )

# Build Options
OPTION( BUILD_TESTS "Build Unit-Tests." ON )
OPTION( BUILD_PLUGINS "Build provided plugins." OFF )

# Modify Directories
SET( CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/build/cmake/modules
)

# Find packages
FIND_PACKAGE( Boost REQUIRED )
FIND_PACKAGE( Qt4 4.5.0 )

# Configuration
INCLUDE( CheckPlatform )
INCLUDE( CheckEndianness )
INCLUDE( CheckInOutBuildSource )
INCLUDe( DefineTargetSuffixes )

CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/config.h )

# Set default output directories. These can be overwritten in lower CMakeLists.txts if needed.
SET( LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib )
SET( LIBRARY_OUTPUT_DIRECTORY "./" )
SET( ARCHIVE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib )
SET( ARCHIVE_OUTPUT_DIRECTORY "./" )
SET( RUNTIME_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin )

# Add some default include directories
#
# src - This is where private headers reside.
#
# include - This is where public headers reside. These are used for the development
# of third-party plugins, services and tools. (API)
#
# ${CMAKE_CURRENT_BINARY_DIR}/include - This is where config.h resides, so each
# build can have different configurations
INCLUDE_DIRECTORIES( src include ${CMAKE_CURRENT_BINARY_DIR}/include )

# Include Subdirectories for Compiling
ADD_SUBDIRECTORY( src )

IF( BUILD_TESTS )
	ENABLE_TESTING()
	ADD_SUBDIRECTORY( tests )
ENDIF( BUILD_TESTS )

IF( BUILD_PLUGINS )
	ADD_SUBDIRECTORY( plugins )
ENDIF( BUILD_PLUGINS )

