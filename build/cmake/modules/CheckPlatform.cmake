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

# This file is responsible to do platform checks. And adding the
# definitions for configuration.

SET( OG_PLATFORM_WIN32 1 )
SET( OG_PLATFORM_UNIX 2 )
SET( OG_PLATFORM_APPLE 3 )

IF( WIN32 )
	SET( OG_PLATFORM OG_PLATFORM_WIN32 )
ELSEIF( UNIX )
	SET( OG_PLATFORM OG_PLATFORM_UNIX )
ELSE( WIN32 )
	MESSAGE( "Platform not supported. Only NT and Unit based Operating Systems are supported." )
ENDIF( WIN32 )
