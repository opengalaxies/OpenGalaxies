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

// BOOST INCLUDES
//
#include <boost/shared_ptr.hpp>

// PROJECT INCLUDES
//
#include <framework/util/endian.h>
#include <framework/util/ogdef.h>
#include <framework/util/ogtypes.h>

// STL INCLUDES
//
#include <assert.h>
#include <vector>

// EXCEPTIONS
//
class ByteBufferOverflowException : public std::exception
{
public:
	ByteBufferOverflowException() { }
	virtual ~ByteBufferOverflowException() { }
};

class ByteBufferOverrunException : public std::exception
{
public:
	ByteBufferOverrunException() { }
	virtual ~ByteBufferOverrunException() { }
};

/**
 * @class ByteBuffer
 * @brief An archive for a sequence of bytes.
 * 
 * A ByteBuffer can be used to store/serialize a sequence of bytes, which can be read back
 * later (in the same order).
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

	/**
	 * @brief Writes an array of bytes to the buffer.
	 */
	void MemCpy( char* buffer, uint16 len )
	{
		if( mWriteIndex + len > mStorage.capacity() )
			throw ByteBufferOverflowException();

		mStorage.resize( mWriteIndex + len );
		memcpy( &mStorage[mWriteIndex], buffer, len );
		mWriteIndex += len;
	}

	// OPERATORS
	//

	/**
	 * @brief Writes the value to the buffer.
	 * This operator will take the value passed to it and write it in byte form to the archive.
	 * If the user tries to write more than the buffer can contain, it will throw a ByteBufferOverflowException.
	 */
	template< typename T > inline ByteBuffer& operator << ( T& value )
	{
		if( mWriteIndex + sizeof(T) > mStorage.capacity() )
			throw ByteBufferOverflowException();

		EndianConvert( value );

		mStorage.resize( mWriteIndex + sizeof(T) );
		memcpy( &mStorage[mWriteIndex], (void*) &value, sizeof(T) );

		mWriteIndex += sizeof(T);
		return *this;
	}

	/**
	 * @brief Read a value from the buffer.
	 * This operator will read a sequence of bytes from the buffer corresponding to
	 * the size of T. In which it will copy the result into the passed reference of T.
	 */
	template< typename T > inline ByteBuffer& operator >> ( T& value )
	{
		if( mReadIndex + sizeof(T) > mStorage.size() )
			throw ByteBufferOverrunException();

		memcpy( (void*) &value, &mStorage[mReadIndex], sizeof(T) );
		EndianConvert( value );
		mReadIndex += sizeof(T);
		return *this;
	}

	// ACCESS
	//
	uint32 Size() const { return mStorage.size(); }
	uint32 Capacity() const { return mStorage.capacity(); }
	const std::vector<uint8>& Contents() const { return mStorage; }

	// INQUIRES
	//
	bool Empty() const { return mStorage.empty(); }

protected:
private:
	uint32						mReadIndex;
	uint32						mWriteIndex;
	std::vector<uint8>			mStorage;

};

typedef boost::shared_ptr< ByteBuffer >	pByteBuffer;

#endif