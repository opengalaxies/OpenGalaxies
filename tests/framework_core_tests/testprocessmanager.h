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

#ifndef TESTPROCESSMANAGER_H
#define TESTPROCESSMANAGER_H

// CPPUNIT INCLUDES
//
#include <cppunit/extensions/HelperMacros.h>

// PROJECT INCLUDES
//
#include <framework/core/processmanager.h>

class TestProcessManager : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TestProcessManager );
	CPPUNIT_TEST( testUpdate );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp( void );
	void tearDown( void );

	void testUpdate( void );
	void testTogglePause( void );

protected:

private:
	boost::shared_ptr< Process >		mRootProcess;
	ProcessManager						mProcessManager;
};

#endif