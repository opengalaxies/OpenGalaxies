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

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

// PROJECT INCLUDES
//
#include <framework/core/ieventmanager.h>
#include <framework/util/singleton.h>

// STL INCLUDES
//
#include <list>
#include <map>
#include <set>

/**
 * @class EventManager
 * @brief A basic concrete IEventManager.
 *
 * This class is <b>not</b> thread-safe. All events queued are garunteed to be executed
 * in the thread Tick() is invoked. For Async Event Managment, @see AsyncEventManager.
 *
 * @note This class is based off of the EventManager class form "Game Coding Complete: Third Edition" by Mike McShaffry.
 */
class OG_API EventManager : public IEventManager, public Singleton< EventManager >
{
public:
	EventManager( std::string name );
	virtual ~EventManager( void );

	// OPERATIONS
	//
	void AbortEvent( const EventType inType, bool allOfType = false );
	void AddListener( const EventHandler fnHandler, const EventType eventType );
	void DeleteListener( const EventHandler fnHandler, const EventType eventType );
	void QueueEvent( const IEventDataPtr& inEvent );
	void Tick( void );
	void Trigger( const IEventData& inEvent ) const;
	bool TypeLegal( const EventType inType ) const;
	bool ValidateType( const EventType inType ) const;

	// ACCESS
	//
	std::string GetName( void ) const { return mName; }

protected:
private:

	typedef std::list< EventHandler >							EventHandlerTable;
	typedef std::map< unsigned long, EventHandlerTable >		EventHandlerMap;
	typedef std::pair< unsigned long, EventHandlerTable >		EventHandlerMapEnt;
	typedef std::list< IEventDataPtr >							EventQueue;

	//
	// We need to double buffer the queuing of events,
	// so events queued by events already queued, will
	// be executed on the next Tick().
	//
	EventQueue				mEventQueues[2];
	uint8					mActiveQueue;
	EventHandlerMap			mEventHandlers;

	std::string mName;
};

#endif