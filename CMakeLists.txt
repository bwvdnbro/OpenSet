################################################################################
# This file is part of OpenSet
# Copyright (C) 2017 Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
#
# OpenSet is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# OpenSet is distributed in the hope that it will be useful,
# but WITOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with OpenSet. If not, see <http://www.gnu.org/licenses/>.
################################################################################

# Make sure we are using a recent version of CMake
cmake_minimum_required(VERSION 2.6)

# Now set the project properties
project(OpenSet)
set(OPENSET_VERSION_MAJOR 0)
set(OPENSET_VERSION_MINOR 1)

# Check required dependencies (we do this as soon as possible)
find_package(GTK2 REQUIRED gtk)
if(NOT GTK2_FOUND)
  message(FATAL_ERROR
          "OpenSet requires the GTK library (version 2 or higher) to compile!")
endif(NOT GTK2_FOUND)
# Add GTK2 specific includes and compiler flags
include_directories(${GTK2_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GTK2_DEFINITIONS}")

# Enable unit testing using CTest
enable_testing()

# Configure the unit tests
add_subdirectory(test)
