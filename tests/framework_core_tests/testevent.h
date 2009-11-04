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

#ifndef TESTEVENT_H
#define TESTEVENT_H

// PROJECT INCLUDES
//
#include <framework/core/baseeventdata.h>

class TestEvent : public BaseEventData
{
public:
	TestEvent( void )
		: mEventType("ClientPermissionsMessage"), AllowZone( 0 ), AllowCharacterCreation( 0 ), AllowUnlimitedCharacterCreation( 0 )
	{
	}

	TestEvent(uint8 allowZone, uint8 allowCharacterCreation, uint8 allowUnlimitedCharacterCreation)
		: mEventType("ClientPermissionsMessage"), AllowZone( allowZone ), AllowCharacterCreation( allowCharacterCreation ), AllowUnlimitedCharacterCreation( allowUnlimitedCharacterCreation )
	{
	}

	TestEvent( std::istream& in )
		: mEventType("ClientPermissionsMessage")
	{
	}

	~TestEvent() { }

	const EventType& GetEventType() const { return mEventType; }

	uint8 AllowCharacterCreation;
	uint8 AllowZone;
	uint8 AllowUnlimitedCharacterCreation;

	void Serialize( ByteBuffer& archv ) const
	{
		archv << AllowZone;
		archv << AllowCharacterCreation;
		archv << AllowUnlimitedCharacterCreation;
	}

	void Deserialize( ByteBuffer& archv ) const
	{
		archv >> AllowZone;
		archv >> AllowCharacterCreation;
		archv >> AllowUnlimitedCharacterCreation;
	}

protected:
private:
	EventType	mEventType;
};

#endif