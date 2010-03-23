# OpenGalaxies - A Star Wars Galaxies PreCU Server Emulator
#
# Copyright (c) 2009 OpenGalaxies <http://www.opengalaxies.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.

# 
# Adds a CppUnit test to the project.
#

MACRO( add_cppunit_test test_NAME )
	FILE( GLOB TEST_SOURCES ${test_NAME}/*.cc )
	FILE( GLOB TEST_HEADERS ${test_NAME}/*.h )
	
	ADD_EXECUTABLE( ${test_NAME} ${TEST_SOURCES} ${TEST_HEADERS} )
	TARGET_LINK_LIBRARIES( ${test_NAME} ${ARGN} cppunitd )
	ADD_TEST( ${test_NAME} ${CMAKE_BINARY_DIR}/bin/${test_NAME} )
ENDMACRO( add_cppunit_test test_NAME )