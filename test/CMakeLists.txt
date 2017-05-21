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

### Convenient macros to automate unit test generation #########################
### Do not touch the code below unless you know what you're doing! #############

# Add a new unit test
# A new target with the test sources is constructed, and a CTest test with the
# same name is created. The new test is also added to the global list of test
# contained in the check target
macro(add_unit_test)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES LIBS)
    cmake_parse_arguments(TEST "${options}" "${oneValueArgs}"
                               "${multiValueArgs}" ${ARGN})
    message(STATUS "generating " ${TEST_NAME})
    add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_SOURCES})
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                          ${PROJECT_BINARY_DIR}/test)
    target_link_libraries(${TEST_NAME} ${TEST_LIBS})

    set(TESTCOMMAND ${TEST_NAME})
    add_test(NAME ${TEST_NAME}
             WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
             COMMAND ${TESTCOMMAND})

    set(TESTNAMES ${TESTNAMES} ${TEST_NAME})
endmacro(add_unit_test)

### Actual unit test generation ################################################
### Add new unit tests below ###################################################

## CardManager test
set(TESTCARDMANAGER_SOURCES
    testCardManager.cpp

    ../engine/Card.cpp
    ../engine/Card.hpp
    ../engine/CardManager.cpp
    ../engine/CardManager.hpp
    ../engine/CardProperties.cpp
    ../engine/CardProperties.hpp
)
add_unit_test(NAME testCardManager
              SOURCES ${TESTCARDMANAGER_SOURCES})

## Window test
set(TESTWINDOW_SOURCES
    testWindow.cpp

    ../engine/Card.cpp
    ../engine/Card.hpp
    ../engine/CardManager.cpp
    ../engine/CardManager.hpp
    ../engine/CardProperties.cpp
    ../engine/CardProperties.hpp
    ../visuals/Window.cpp
    ../visuals/Window.hpp
)
add_unit_test(NAME testWindow
              SOURCES ${TESTWINDOW_SOURCES}
              LIBS ${GTK2_LIBRARIES})

### Done adding unit tests. Create the 'make check' target #####################
### Do not touch these lines unless you know what you're doing! ################
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
                        DEPENDS ${TESTNAMES})
