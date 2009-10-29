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

#ifndef IEVENTLISTENER_H
#define IEVENTLISTENER_H

// BOOST INCLUDES
//
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

// PROJECT INCLUDES
//
#include <framework/core/ieventdata.h>
#include <framework/util/ogdef.h>
#include <framework/util/ogtypes.h>

// STL INCLUDES
//
#include <string>

/**
 * @class IEventListener
 * @brief Listens for incoming events from the EventManager.
 *
 * Events need to go somewhere, and this is where. Classes that need to listen
 * for events needs to inherit and implement the pure virtual functions of this interface.
 *
 * @note This class is based off of the IEventListener class form "Game Coding Complete: Third Edition" by Mike McShaffry.
 */
class OG_API IEventListener
{
public:
	explicit IEventListener() { }
	virtual ~IEventListener() { }

	// ACCESS
	//
	virtual std::string GetName( void ) const = 0;
};

typedef boost::shared_ptr<IEventListener> EventListenerPtr;
typedef void (IEventListener::*	EventHandler)( const EventPtr& );

#endif