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

# Output
SET( CMAKE_INSTALL_PREFIX ./ CACHE PATH "Install Path" )
SET( LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "The directory reletive to the install directory where all libraries will be dumped." )

# Build Options
OPTION( BUILD_TESTS "Build Unit-Tests." ON )
OPTION( BUILD_PLUGINS "Build provided plugins." OFF )

# Modify Directories
SET( CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/build/cmake/modules
)

# Configuration
INCLUDE( CheckPlatform )
INCLUDE( CheckEndianness )

# Find packages
FIND_PACKAGE( Boost REQUIRED )
FIND_PACKAGE( Qt4 4.5.0 )

CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_SOURCE_DIR}/src/framework/util/config.h )

# Include Subdirectories for Compiling
ADD_SUBDIRECTORY( src )

IF( BUILD_TESTS )
	ENABLE_TESTING()
	ADD_SUBDIRECTORY( tests )
ENDIF( BUILD_TESTS )

IF( BUILD_PLUGINS )
	ADD_SUBDIRECTORY( plugins )
ENDIF( BUILD_PLUGINS )

