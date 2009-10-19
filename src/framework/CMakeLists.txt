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

# Gather sources and headers.
FILE( GLOB_RECURSE SOURCES *.cc )
FILE( GLOB_RECURSE HEADERS *.h )

ADD_LIBRARY( framework STATIC ${SOURCES} ${HEADERS} )
SET_TARGET_PROPERTIES( framework PROPERTIES LINKER_LANGUAGE CXX )
