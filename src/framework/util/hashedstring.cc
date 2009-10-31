/*
    OpenGalaxies PreCU Server - A Star Wars Galaxies Pre-Combat Upgrade Server.
    Copyright (C) 2009  OpenGalaxies (www.opengalaxies.org)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "crctable.h"
#include "hashedstring.h"

HashedString::HashedString( )
: mString( "NULL" ), mHashValue( 0 )
{
}

HashedString::HashedString( std::string input )
: mString( input ), mHashValue( HashString( input ) )
{
}

HashedString::~HashedString( void )
{
}

void*
HashedString::HashString( const std::string input )
{
	uint32 length = input.length();
	CRC crc = 0xFFFFFFFF;

	for(uint16 counter = 0; counter < length; counter++)
		crc = CrcTable[input[counter] ^ (crc >> 24)] ^ (crc << 8);

	return reinterpret_cast<void*>(~crc);
}

bool
HashedString::operator ==( const HashedString &other )
{
	return ( GetHashValue() == other.GetHashValue() );
}

bool
HashedString::operator <( const HashedString &other )
{
	return ( GetHashValue() < other.GetHashValue() );
}

