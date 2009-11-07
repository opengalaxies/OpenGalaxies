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

#include "testprocessmanager.h"
#include "testprocess.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TestProcessManager );

void
TestProcessManager::setUp( void )
{
	mRootProcess = boost::shared_ptr< Process >( new TestProcess("RootProcess") );
	mRootProcess->SetNext( boost::shared_ptr< Process >( new TestProcess("ChildProcess") ) );
	mProcessManager.Attach( mRootProcess );
}

void
TestProcessManager::tearDown( void )
{
}

void
TestProcessManager::testUpdate( void )
{
	// Simulate a clock.
	for(int x = 0; x < 10; x++)
		mProcessManager.Update( x );
}

void
TestProcessManager::testTogglePause( void )
{
	mRootProcess->TogglePause();
}