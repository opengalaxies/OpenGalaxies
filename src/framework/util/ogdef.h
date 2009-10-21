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

#ifndef OGDEF_H
#define OGDEF_H

#include <config.h>

//
// Safe Deletes
//
#define SAFE_DELETE( a ) \
	if(a) { delete a; a = 0; }

#define SAFE_RELEASE( a ) \
	if(a) { a->Release(); a = 0; }

//
// API
//
#if ( OG_PLATFORM == OG_PLATFORM_WIN32 )
#	ifdef OG_EXPORT
#		define OG_API __declspec(dllexport)
#	else
#		define OG_API __declspec(dllimport)
#	endif
#else
#	define OG_API 
#endif

#endif