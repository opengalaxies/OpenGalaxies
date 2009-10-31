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

#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

// BOOST INCLUDES
//
#include <boost/shared_ptr.hpp>

// PROJECT INCLUDES
//
#include <framework/core/process.h>
#include <framework/util/ogdef.h>
#include <framework/util/ogtypes.h>

// STL INCLUDES
//
#include <list>

/**
* @classname ProcessManager
* @brief A container and manager for Processes.
*
* Holds and maintains the updating of Processes. Once a process is considered to be dead, the ProcessManager
* will clean it up accordingly.
*
* @note This class was based off of the CProcessManager class from "Game Coding Complete: Third Edition" by Mike McShaffry.
* @see Process
*/
class OG_API ProcessManager
{
	typedef std::list< boost::shared_ptr<Process> > ProcessList;
public:
	ProcessManager( void );
	virtual ~ProcessManager( void );

	// OPERATIONS
	//
	void Attach( boost::shared_ptr<Process> pProcess );
	void Update( int deltaMilliseconds );

	// INQUIRES
	//
	bool HasProcesses()	{ return mProcesses.empty(); }

protected:
	ProcessList		mProcesses;

private:

	// OPERATIONS
	//
	void Detach( boost::shared_ptr<Process> pProcess );

};

#endif