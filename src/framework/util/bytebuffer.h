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

#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

// PROJECT INCLUDES
//
#include <framework/util/endian.h>
#include <framework/util/ogdef.h>
#include <framework/util/ogtypes.h>

// STL INCLUDES
//
#include <assert.h>
#include <vector>

/**
 * @class ByteBuffer
 * @brief
 */
class ByteBuffer
{
public:
	ByteBuffer() : mReadIndex(0), mWriteIndex(0) { mStorage.reserve( DEFAULT_RESERVE ); }
	ByteBuffer( size_t res ) : mReadIndex(0), mWriteIndex(0) { mStorage.reserve( res ); }
	~ByteBuffer() { }

	const static uint32 DEFAULT_RESERVE = 512;

	// OPERATIONS
	//
	void Clear() { mStorage.clear(); mReadIndex = mWriteIndex = 0; }

	// OPERATORS
	//
	template< typename T > inline ByteBuffer& operator << ( T& value )
	{
		if( mWriteIndex + sizeof(T) > mStorage.capacity() )
			assert( 0 && "Trying to write more then the ByteBuffer will hold!" );

		EndianConvert( value );

		mStorage.resize( mWriteIndex + sizeof(T) );
		memcpy( &mStorage[mWriteIndex], (void*) &value, sizeof(T) );

		mWriteIndex += sizeof(T);
		return *this;
	}

	template< typename T > inline ByteBuffer& operator >> ( T& value )
	{
		if( mReadIndex + sizeof(T) > mStorage.size() )
			assert( 0 && "Trying to read more then the ByteBuffer has!" );

		memcpy( (void*) &value, &mStorage[mReadIndex], sizeof(T) );
		EndianConvert( value );
		mReadIndex += sizeof(T);
		return *this;
	}

	// ACCESS
	//
	uint32 Size() const { return mStorage.size(); }
	uint32 Capacity() const { return mStorage.capacity(); }

	// INQUIRES
	//
	bool Empty() const { return mStorage.empty(); }

protected:
private:
	uint32						mReadIndex;
	uint32						mWriteIndex;
	std::vector<uint8>			mStorage;

};

#endif