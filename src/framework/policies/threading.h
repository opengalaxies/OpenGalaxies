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

#ifndef THREADING_H
#define THREADING_H

// BOOST INCLUDES
//
#include <boost/thread/mutex.hpp>

// PROJECT INCLUDES
//
#include <framework/util/ogdef.h>
#include <framework/util/ogtypes.h>

/**
 * @class SingleThreaded
 * @brief Stub Locking Policy
 */
template< class T >
class OG_API SingleThreaded
{
public:
	class Lock : boost::noncopyable
	{
		Lock( SingleThreaded<T>& obj ) { }
		~Lock() { }
	};
};

/**
 * @class ClassLevelLockable
 * @brief Class-Level Locking Policy
 *
 * Provides threading synchronization protection on a class-level. This means that the mutex
 * supplied inside the lock is on a class-level (one instance per class).
 * 
 * These should be used on widely used fast-classes to conserve space.
 * 
 * A moderate performance hit may occure depending on whether or not another thread is trying to access a different
 * object of the same class type. Under this circumstance, even though the each object is a seperate instance, it will still lock
 * because they share the same mutex instance.
 * 
 * Hense it is important to only use this type of lock on classes that perform fast operations. A size hit in most circumstances
 * is more acceptable then a performance hit. If this is the case, use ObjectLevelLockable.
 */
template< class T >
class OG_API ClassLevelLockable : private boost::noncopyable
{
public:
	class Lock : private boost::noncopyable
	{
	public:
		Lock() { mLockable.lock(); }
		Lock( ClassLevelLockable<T>& obj ) { mLockable.unlock(); }
		~Lock() { }

	private:
		static boost::mutex			mLockable;
	};

};

/**
 * @class ObjectLevelLockable
 * @brief Object-Level Locking Policy
 *
 * Provides threading synchronization protection on an object-level. This means that the mutex
 * supplied inside the lock is on an object-level (one instance per object).
 */
template< class T >
class OG_API ObjectLevelLockable : private boost::noncopyable
{
public:
	class Lock : private boost::noncopyable
	{
	public:
		friend class ObjectLevelLockable;

		Lock( ObjectLevelLockable<T>& obj ) : mLockableRef( obj.mLockable ) {  mLockableRef.lock(); }
		~Lock() { mLockableRef.unlock(); }

	private:
		boost::mutex&			mLockableRef;

	};

private:
	boost::mutex				mLockable;
};


#endif