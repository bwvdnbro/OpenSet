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
 * @file testCardManager.cpp
 *
 * @brief Unit test for the CardManager class.
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 */

#include "../engine/CardManager.hpp"

#include <cassert>
#include <iostream>

/**
 * @brief Unit test for the CardManager class.
 *
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @return Exit code: 0 on success.
 */
int main(int argc, char **argv) {
  CardManager card_manager;

  std::vector<Card> deck = card_manager.get_deck();

  assert(deck.size() == 12);
  for (unsigned char card = 0; card < deck.size(); ++card) {
    unsigned char number_of_symbols = deck[card].get_number_of_symbols();
    CardProperties::CardColour colour = deck[card].get_colour();
    CardProperties::CardSymbol symbol = deck[card].get_symbol();
    CardProperties::CardFill fill = deck[card].get_fill();
    std::cout << static_cast<unsigned int>(number_of_symbols) << " "
              << CardProperties::get_card_colour(colour) << " "
              << CardProperties::get_card_symbol(symbol) << " "
              << CardProperties::get_card_fill(fill) << std::endl;
  }

  return 0;
}
