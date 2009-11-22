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

PROJECT( Framework )

INCLUDE( MacroCreateSubGroupsFromDir )

CREATE_SUBGROUPS_FROM_DIR()

ADD_DEFINITIONS( -DOG_EXPORT )

FILE( GLOB_RECURSE FRAMEWORK_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc )
FILE( GLOB_RECURSE FRAMEWORK_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h )
ADD_LIBRARY( framework SHARED ${FRAMEWORK_SOURCES} ${FRAMEWORK_HEADERS} )
