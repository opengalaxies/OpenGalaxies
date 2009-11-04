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

#ifndef ENDIAN_H
#define ENDIAN_H

// PROJECT INCLUDES
//
#include <framework/util/ogdef.h>
#include <framework/util/ogtypes.h>

/**
 * @file endian.h
 * @brief Contains endianness functions.
 *
 * @note The Endian namespace was borrowed from the MaNGOS Project <www.getmangos.com>. Thanks guys.
 */

namespace Endian {

    template<size_t T>
        inline void convert(char *val)
    {
        std::swap(*val, *(val + T - 1));
        convert<T - 2>(val + 1);
    }

    template<> inline void convert<0>(char *) {}
    template<> inline void convert<1>(char *) {}

    template<typename T> inline void apply(T *val)
    {
        convert<sizeof(T)>((char *)(val));
    }

};

#if OG_ENDIANNESS == OG_BIG_ENDIAN 
	template< typename T > inline void EndianConvert( T& value ) { Endian::apply(value); }
	template< typename T > inline void EndianReverse( T& value ) { }
#else
	template< typename T > inline void EndianConvert( T& value ) { }
	template< typename T > inline void EndianReverse( T& value ) { Endian::apply(value); }
#endif

	//
	// uint8 and int8 are types that do not
	// need to be flipped, because they are only one byte!
	//
	inline void EndianConvert( uint8& ) { }
	inline void EnaidnConvert( int8& ) { }
	inline void EndianReverse( uint8& ) { }
	inline void EnaidnReverse( int8& ) { }

#endif