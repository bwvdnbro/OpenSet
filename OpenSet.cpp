/*******************************************************************************
 * This file is part of OpenSet
 * Copyright (C) 2017 Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 *
 * OpenSet is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenSet is distributed in the hope that it will be useful,
 * but WITOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with OpenSet. If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

/**
 * @file OpenSet.cpp
 *
 * @brief Main program.
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 */

#include "engine/CardManager.hpp"
#include "visuals/Window.hpp"

/**
 * @brief Main program.
 *
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @return Exit code: 0 on success.
 */
int main(int argc, char **argv){
  CardManager card_manager;
  Window window(argc, argv, 200, 200, "Test window", card_manager);

  window.show();

  return 0;
}
