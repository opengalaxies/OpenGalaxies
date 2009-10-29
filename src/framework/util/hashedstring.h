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

#ifndef HASHEDSTRING_H
#define HASHEDSTRING_H

// PROJECT INCLUDES
//
#include <framework/util/ogdef.h>
#include <framework/util/ogtypes.h>

// STL INCLUDES
//
#include <string>

/**
* @classname HashedString
* @brief A string hashing container.
*
* String hashing envolves taking a ASCII string and performing calculations on it,
* which outputs an integer "hash" or "crc" value.
*
* Using hashed strings for string comparing can in most cases boost performance within a program, because
* there is no character-by-character comparing, but rather one calculation which compares each integer with
* eachother.
*/
class OG_API HashedString
{
public:
	HashedString( void );
	HashedString( std::string input );
	virtual ~HashedString();

	// OPERATIONS
	//
	virtual void* HashString( const std::string input );

	// OPERATORS
	//
	bool operator == ( const HashedString& other );
	bool operator < ( const HashedString& other );

	// ACCESS
	//
	unsigned long GetHashValue() const			{ return reinterpret_cast<unsigned long>(mHashValue); }
	std::string GetString() const				{ return mString; }

protected:

private:
	std::string		mString;
	void*			mHashValue; // Stored as a void* instead of a uint32, so
							// the value will show up in the debugger as
							// a hex-value.

};

#endif