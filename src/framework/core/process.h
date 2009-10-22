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

#ifndef IPROCESS_H
#define IPROCESS_H

// BOOST INCLUDES
//
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

// PROJECT INCLUDES
//
#include <framework/util/ogdef.h>
#include <framework/util/ogtypes.h>

/**
 * @classname Process
 * @brief Represents a task, or job that needs to be done over-time.
 *
 * Processes are managed by the ProcessManager, which calles the Update() function
 * of each Process it stores in a round-robin fashion.
 *
 * This gives each process a little CPU time. When a Process has completed
 * its task, it may flag itself to be destroyed on the next Update() by the
 * ProcessManager.
 *
 * Processes can reference Child Processes, that are to be executed next after
 * this Process is finished executing. Example:
 * @code
 *
 * boost::shared_ptr<WalkProcess> walk = new WalkProcess(object, x, y, z);
 * boost::shared_ptr<PerformProcess> perform = new PerformProcess(object, PERFORMANCE_TYPE::EMOTE, "yay");
 * boost::shared_ptr<WaitProcess> wait = new WaitProcess( 3000 );
 * boost::shared_ptr<WalkProcess> walk2 = new WalkProcess(object, x2, y2, z2);
 *
 * walk->SetNext( perform )->SetNext( wait )->SetNext(walk2);
 * processManager->Attach( walk );
 * @endcode
 * 
 * The above example would cause the object to move from point A (x2, y2, z2), to point B (x, y, z), perform an emote, wait 3000 milliseconds,
 * then return to point A (x2, y2, z2) from point B (x, y, z). 
 *
 *
 * @note This class was based off of the CProcess class from "Game Coding Complete: Third Edition" by Mike McShaffry.
 * @see ProcessManager
 */
class OG_API Process : public boost::noncopyable
{
public:
	Process();
	virtual ~Process();

	// OPERATIONS
	//
	virtual void Initialize( void )								{ mIsInitialized = true; }
	virtual void Kill( void )									{ mKill = true; }
	virtual void TogglePause( void )							{ mIsPaused = !mIsPaused; }
	virtual void Update( const uint32 deltaMilliseconds )		{ if(!IsInitialized()) { Initialize(); } }

	// INQUIRIES
	//
	bool IsAttached( void ) const		{ return mIsAttached; }
	bool IsDead( void ) const			{ return mKill; }
	bool IsInitialized( void ) const	{ return mIsInitialized; }
	bool IsPaused( void ) const			{ return mIsPaused; }

	// ACCESS
	//
	boost::shared_ptr<Process> GetNext( void ) const								{ return mNextProcess; }
	boost::shared_ptr<Process> SetNext( boost::shared_ptr<Process> nextProcess )	{ mNextProcess = nextProcess; return mNextProcess; }
	void SetAttached( bool value )													{ mIsAttached = value; }

protected:

private:
	bool							mIsAttached;
	bool							mIsInitialized;
	bool							mIsPaused;
	bool							mKill;
	boost::shared_ptr<Process>		mNextProcess;
	
};

#endif