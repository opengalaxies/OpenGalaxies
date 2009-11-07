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

#ifndef SINGLETON_H
#define SINGLETON_H

// ECT INCLUDES
//
#include <assert.h>

/**
 * @class Singleton
 * @brief A template class used to create single-instance global classes.
 */
template< class T >
class Singleton
{
public:
	Singleton() { if(!mSingleInstance) msSingleInstance = static_cast< T* >( this ); }
	virtual ~Singleton() { msSingleInstance = 0; }

	// OPERATIONS
	//
	T& GetRef( void ) { assert( msSingleInstance ); return *msSingleInstance; }
	T* GetPtr( void ) { return msSingleInstance; }

protected:
private:
	static T*			msSingleInstance;
};

#endif