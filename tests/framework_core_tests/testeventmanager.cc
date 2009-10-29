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

#include "testevent.h"
#include "testeventmanager.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestEventManager );

void
TestEventManager::setUp( void )
{
	mEventManager.AddListener( boost::bind( &TestEventManager::HandleEvent, this, _1 ), EventType("ClientPermissionsMessage") );
}

void
TestEventManager::tearDown( void )
{
	mEventManager.DeleteListener( boost::bind( &TestEventManager::HandleEvent, this, _1 ), EventType("ClientPermissionsMessage") );
}

void
TestEventManager::testQueue( void )
{
	mEventManager.QueueEvent( boost::shared_ptr<IEventData>( new TestEvent() ) );
	mEventManager.Tick();
}

void
TestEventManager::testTrigger( void )
{
	mEventManager.Trigger( boost::shared_ptr<IEventData>( new TestEvent() ) );
}

void
TestEventManager::HandleEvent( const EventPtr &pEvent )
{
	std::cout << "Event [" << pEvent->GetEventType().GetString() << "] was triggered.";
}