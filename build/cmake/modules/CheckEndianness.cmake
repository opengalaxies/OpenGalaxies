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

# This file is responsible for checking the endianness of the
# machine and correctly configure the project to build appropriatly.

SET( OG_BIG_ENDIAN 1 )
SET( OG_LITTLE_ENDIAN 2 )
SET( OG_ENDIANNESS 0 ) # default

include( TestBigEndian )

TEST_BIG_ENDIAN( ENDIAN )

if( ${ENDIAN} EQUAL 1 ) # Big Endian
	MESSAGE( "Endianness: Big-Endian" )
	SET( OG_ENDIANNESS OG_BIG_ENDIAN )
else ( ${ENDIAN} EQUAL 1 ) # Little Endian
	MESSAGE( "Endianness: Little-Endian" )
	SET( OG_ENDIANNESS OG_LITTLE_ENDIAN )
endif( ${ENDIAN} EQUAL 1 )