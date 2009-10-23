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
* String hasing envolves taking a ASCII string, performing calculations on it,
* which outputs an integer "hash" or "crc" value of that string.
*
* Using hashed strings instead of normal string for string comparing, you can in most cases
* cause better performance within a program. Because you are not having to compare each character
* in the string.
*/
class OG_API HashedString
{
public:
	HashedString( std::string input );
	virtual ~HashedString();

	// OPERATIONS
	//
	virtual void* HashString( std::string input );

	// OPERATORS
	//
	bool operator == ( HashedString& other );
	bool operator < (HashedString& other );

	// ACCESS
	//
	CRC GetIdent() const			{ return reinterpret_cast<CRC>(mIdent); }

protected:

private:
	std::string		mString;
	void*			mIdent; // Stored as a void* instead of a uint32, so
							// the value will show up in the debugger as
							// a hex-value.

};

#endif