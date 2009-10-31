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
	if( mProcesses.size() <= 0)
		return;

	/* HACK
	 * As you may have noticed, we need to manually increment the iterator or else it will become
	 * invalid if a process is declared dead.
	 *
	 * There should be serveral standard ways of getting round this while retaining the normal iterator
	 * increment statement in the for statement.
	 */
	for(ProcessList::iterator i = mProcesses.begin(); i != mProcesses.end(); )
	{
		boost::shared_ptr< Process > pProcess(*i);

		if( pProcess->IsDead() ) // Our process is dead-- get rid of it.
		{
			boost::shared_ptr< Process > pNext( pProcess->GetNext() );
			if( pNext ) // We have a child process, attach it to the manager.
			{
				pProcess->SetNext( boost::shared_ptr< Process >((Process*) NULL)); // Nullify our next for the dead process.
				Attach( pNext );
			}

			i++;
			Detach( pProcess );
		}
		else if( !pProcess->IsPaused() )
		{
			pProcess->Update( deltaMilliseconds );
			i++;
		}
	}
}