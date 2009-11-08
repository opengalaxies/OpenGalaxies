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

#ifndef CHECKING_H
#define CHECKING_H

// STL INCLUDES
//
#include <exception>

/**
 * @brief A Stub Checking Policy.
 */
template< class T >
struct NoChecking
{
	static inline void Check( T* ptr ) { }
};

/**
 * @brief A Checking Policy that will throw an exception on a Null pointer.
 * @throws EnforceNotNull::NullPointerException
 */
template< class T >
struct EnforceNotNull
{
	class NullPointerException : public std::exception
	{
	public:
		NullPointerException( void ) { }
		~NullPointerException( void ) { }
	};

	static inline void Check( T* ptr )
	{
		if(!ptr)
			throw NullPointerException();
	}
};

#endif