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

#ifndef IEVENTMANAGER_H
#define IEVENTMANAGER_H

// BOOST INCLUDES
//
#include <boost/bind.hpp>
#include <boost/function.hpp>

// PROJECT INCLUDES
//
#include <framework/core/ieventdata.h>
#include <framework/util/ogdef.h>
#include <framework/util/ogtypes.h>

// STL INCLUDES
//
#include <string>

// TYPEDEF
//
typedef boost::function< void ( const IEventData& ) > EventHandler;

/**
 * @class IEventManager
 * @brief An EventManager interface.
 *
 * @note This class is based off of the IEventManager class form "Game Coding Complete: Third Edition" by Mike McShaffry.
 */
class OG_API IEventManager
{
public:
	IEventManager( std::string name ) {  }
	virtual ~IEventManager( void ) { }

	// OPERATIONS
	//

	/**
	 * Causes the event manager to dequeue an event by type. If allOfType is set to true, the event manager should
	 * remove all of the events matching the inType.
	 * @param EventType[in] - The type of event we wish to remove.
	 * @param bool[in] - Remove all events of this type?
	 */
	virtual void AbortEvent( const EventType inType, bool allOfType = false ) = 0;

	/**
	 * Adds a listener to the manager. When a event is triggered, listeners will
	 * be informed if the event corresponds with an event the listener is listening for.
	 * @param EventHandler[in] - The function that will be called to handle the event.
	 * @param EventType[in] - The event type we wish the listener to be informed about.
	 */
	virtual void AddListener( const EventHandler fnHandler, const EventType eventType ) = 0;

	/**
	 * Tells the manager to stop informing the target listener about a specific EventType.
	 * @param EventHandler[in] - The function/object which should stop listening for the EventType.
	 * @param EventType[in] - The type of event we wish to no be informed about anymore.
	 */
	virtual void DeleteListener( const EventHandler fnHandler, const EventType eventType ) = 0;

	/**
	 * Adds an event to the Event Queue, that will be triggered on the next Tick(). If you wish
	 * to trigger an event sychronously, see Trigger().
	 * @param IEventDataPtr[in] - The event and its data.
	 */
	virtual void QueueEvent( const IEventDataPtr& inEvent ) = 0;

	/**
	 * Triggers all events in-queue. Optionally, you can limit the amount of CPU time (in milliseconds)
	 * this functions uses by using maxMillisec.
	 * @param maxMillisec[in] - The amount of milliseconds the function should be triggering events in-queue.
	 */
	virtual void Tick( void ) = 0;

	/**
	 * Triggers an event immediately, without waiting for
	 * the next Tick().
	 * @param IEventData[in] - The event and its data.
	 */
	virtual void Trigger( const IEventData& inEvent ) const = 0;

	/**
	 * Validates that an EventType is being listened for. This <b>will not</b> add
	 * the EventType to the list of types being listened for.
	 * @param EventType[in] - The event type to search for.
	 */
	virtual bool ValidateType( const EventType inType ) const = 0;


	/**
	 * Varifies that a type is legally able to be listened for by
	 * the Event Manager.
	 * @param EventType[in] - The event type to check.
	 */
	virtual bool TypeLegal( const EventType inType ) const = 0;
};


#endif