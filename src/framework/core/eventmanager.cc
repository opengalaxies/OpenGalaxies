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

// BOOST INCLUDES
//
#include <boost/foreach.hpp>

// PROJECT INCLUDES
//
#include "eventmanager.h"

EventManager* EventManager::gEventManager = NULL;

EventManager::EventManager( std::string name, bool setGlobal )
: IEventManager( name ), mActiveQueue( 0 ), mName( name )
{
	if( setGlobal )
		gEventManager = this;
}

EventManager::~EventManager( void )
{
	mActiveQueue = 0;
}

void
EventManager::AbortEvent( const EventType inType, bool allOfType )
{
	if( !TypeLegal( inType ) || !ValidateType( inType ) )
		return;

	EventHandlerMap::iterator iter = mEventHandlers.find( inType.GetHashValue() );
	if( iter != mEventHandlers.end() )
	{
		// If allOfType is true, clear the list.
		if(allOfType)
			iter->second.clear();
		// Otherwise, pop the last pushed event.
		else
			iter->second.pop_back();
	}
}

void
EventManager::AddListener( const EventHandler fnHandler,  const EventType eventType)
{
	if( !TypeLegal( eventType ) )
		return;

	EventHandlerMap::iterator iter = mEventHandlers.find( eventType.GetHashValue() );

	// Insert a new table if it already dosnt exist.
	if( iter == mEventHandlers.end() )
	{
		iter = mEventHandlers.insert( EventHandlerMapEnt( eventType.GetHashValue(), EventHandlerTable() ) ).first;
	}

	iter->second.push_back( fnHandler );
}

void 
EventManager::DeleteListener( const EventHandler fnHandler, const EventType eventType )
{
	if( !TypeLegal( eventType ) || !ValidateType( eventType ) )
		return;

	EventHandlerMap::iterator iter = mEventHandlers.find( eventType.GetHashValue() );

	if( iter != mEventHandlers.end() )
	{
		for( EventHandlerTable::iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++ )
		{
			if( iter2 == fnHandler )
				mEventHandlers.erase( iter );
		}
	}
}

void
EventManager::QueueEvent( const IEventDataPtr& inEvent )
{
	if( !TypeLegal( inEvent->GetEventType() ) || !ValidateType( inEvent->GetEventType() ) )
		return;

	mEventQueues[mActiveQueue].push_back( inEvent );
}

void
EventManager::Tick( void )
{
	const EventQueue& mEventQueue = mEventQueues[mActiveQueue];
	mActiveQueue = (mActiveQueue + 1) % 2; // Saves us from a couple of if/else statements.
	mEventQueues[mActiveQueue].clear(); // Clear our second buffer to allow for new events.

	BOOST_FOREACH( IEventDataPtr pEvent, mEventQueue )
	{
		if( !pEvent->Validate() )
			break;

		//
		// Process Wildcard Listeners
		//
		EventHandlerMap::const_iterator wcIter = mEventHandlers.find( 0 );
		if( wcIter != mEventHandlers.end() )
		{
			const EventHandlerTable& table = wcIter->second;
			BOOST_FOREACH( EventHandler handler, table )
			{
				handler( *pEvent );
			}
		}

		//
		// Process Normal Listeners
		//
		EventHandlerMap::const_iterator iter = mEventHandlers.find( pEvent->GetEventType().GetHashValue() );
		if( iter != mEventHandlers.end() )
		{
			const EventHandlerTable& table = iter->second;
			BOOST_FOREACH( EventHandler handler, table )
			{
				handler( *pEvent );
			}
		}
	}
}

void
EventManager::Trigger( const IEventData& inEvent ) const
{
	if( !TypeLegal( inEvent.GetEventType() ) || !ValidateType( inEvent.GetEventType() ) )
		return;

	//
	// Process Wildcard Listeners.
	//
	EventHandlerMap::const_iterator wcIter = mEventHandlers.find( 0 );
	if( wcIter != mEventHandlers.end() )
	{
		const EventHandlerTable& table = wcIter->second;
		BOOST_FOREACH( EventHandler handler, table )
		{
			handler( inEvent );
		}
	}

	//
	// Process Normal Listeners.
	//
	EventHandlerMap::const_iterator iter = mEventHandlers.find( inEvent.GetEventType().GetHashValue() );
	if( iter != mEventHandlers.end() )
	{
		const EventHandlerTable& table = iter->second;
		BOOST_FOREACH( EventHandler handler, table )
		{
			handler( inEvent );
		}
	}

	return;
}

bool
EventManager::TypeLegal( const EventType inType ) const
{
	if( inType.GetString().length() == 0 )
		return false;

	return true;
}

bool
EventManager::ValidateType( const EventType inType ) const
{
	EventHandlerMap::const_iterator iter = mEventHandlers.find( inType.GetHashValue() );
	if( iter == mEventHandlers.end() )
	{
		return false;
	}
	
	return true;
}