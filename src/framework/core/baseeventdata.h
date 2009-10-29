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

#ifndef BASEEVENTDATA_H
#define BASEEVENTDATA_H

// PROJECT INCLUDES
//
#include <framework/core/ieventdata.h>
#include <framework/util/ogdef.h>
#include <framework/util/ogtypes.h>

/**
 * @class BaseEventData
 * @brief A basic implementation of the IEventData interface.
 *
 * This class is a basic <b>non-concrete</b> implementation of the IEvenData interface.
 * Any game events you wish to create, can inheirt from this class and implement the pure virtual
 * functions to create a concrete implementation that can be used with the EventManager.
 *
 * @note This class is based off of the BaseEventData class form "Game Coding Complete: Third Edition" by Mike McShaffry.
 */
class OG_API BaseEventData : public IEventData
{
public:
	BaseEventData( const float timeStamp = 0.0f );
	virtual ~BaseEventData();

	// OPERATIONS
	//
	virtual void Serialize( std::ostream &out ) const { }

	// ACCESS
	//
	float GetTimeStamp( void ) const { return mTimeStamp; }

protected:
	const float mTimeStamp;
};

#endif