# OpenGalaxies - A Star Wars Galaxies PreCU Server Emulator
#
# Copyright (c) 2009 OpenGalaxies <http://www.opengalaxies.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
#
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.

# Sets standard Target naming conventions.

SET( CMAKE_DEBUG_POSTFIX "_d" )

# For shared libraries built with MSVC, give the prefix
# of "lib". GCC already uses this convention.
#
# This helps distinguish plugins and modules for linked libraries 
# that are required to run the server.
IF( MSVC )
	SET( CMAKE_SHARED_LIBRARY_PREFIX "lib" )
ENDIF( MSVC )