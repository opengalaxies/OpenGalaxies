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

#include "testbytebuffer.h"

// STL INCLUDES
//
#include <assert.h>

CPPUNIT_TEST_SUITE_REGISTRATION( TestByteBuffer );

TestByteBuffer::TestByteBuffer( void )
{
}

TestByteBuffer::~TestByteBuffer( void )
{
}

void
TestByteBuffer::setUp( void )
{
}

void
TestByteBuffer::tearDown( void )
{
}

void
TestByteBuffer::testBasicTypes( void )
{
	int8 _sint8 = -256;
	int16 _sint16 = -512;
	int32 _sint32 = -1024;
	int64 _sint64 = -2048;
	uint8 _suint8 = 256;
	uint16 _suint16 = 512;
	uint32 _suint32 = 1024;
	uint64 _suint64 = 2048;
	std::string _string("Ascii");
	std::wstring _wstring((wchar_t*)"Unicode");

	mBuffer << _sint8;
	mBuffer << _sint16;
	mBuffer << _sint32;
	mBuffer << _sint64;
	mBuffer << _suint8;
	mBuffer << _suint16;
	mBuffer << _suint32;
	mBuffer << _suint64;
	mBuffer << _string;
	mBuffer << _wstring;

	mBuffer >> _sint8;
	mBuffer >> _sint16;
	mBuffer >> _sint32;
	mBuffer >> _sint64;
	mBuffer >> _suint8;
	mBuffer >> _suint16;
	mBuffer >> _suint32;
	mBuffer >> _suint64;
	mBuffer >> _string;
	mBuffer >> _wstring;
}

void TestByteBuffer::testClear( void )
{
	std::wstring _string((wchar_t*)"Hello!");
	mBuffer << _string;
	mBuffer.Clear();

	if( !mBuffer.Empty() )
		assert( 0 && "Buffer was more than the size of 0 after a Clear()." );
}