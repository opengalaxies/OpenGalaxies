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

// PROJECT INCLUDES
//
#include "processmanager.h"

ProcessManager::ProcessManager()
{
}

ProcessManager::~ProcessManager()
{
}

void
ProcessManager::Attach(boost::shared_ptr<Process> pProcess)
{
	mProcesses.push_back( pProcess );
	pProcess->SetAttached( true );
}

void
ProcessManager::Detach(boost::shared_ptr<Process> pProcess)
{
	mProcesses.remove( pProcess );
	pProcess->SetAttached( false );
}

void
ProcessManager::Update(int deltaMilliseconds)
{
	for(ProcessList::iterator i = mProcesses.begin(); i != mProcesses.end(); i++)
	{
		boost::shared_ptr< Process > pProcess(*i);

		if( pProcess->IsDead() ) // Our process is dead-- get rid of it.
		{
			if( pProcess->GetNext() ) // We have a child process, attach it to the manager.
			{
				Attach( pProcess->GetNext() );
				pProcess->SetNext( boost::shared_ptr< Process >((Process*) NULL)); // Nullify our next for the dead process.
			}

			Detach( pProcess );
		}
		else if( !pProcess->IsPaused() )
		{
			pProcess->Update( deltaMilliseconds );
		}
	}
}