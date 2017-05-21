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
 * @file Card.hpp
 *
 * @brief Single card in the game.
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 */

#ifndef OPENSET_CARD_HPP
#define OPENSET_CARD_HPP

#include "CardProperties.hpp"

/**
 * @brief Single card in the game.
 */
class Card {
private:
  /*! @brief Number of symbols on the card. */
  unsigned char _number_of_symbols;

  /*! @brief Card colour. */
  CardProperties::CardColour _colour;

  /*! @brief Symbol type. */
  CardProperties::CardSymbol _symbol;

  /*! @brief Fill type. */
  CardProperties::CardFill _fill;

public:
  Card();
  Card(unsigned char number_of_symbols, CardProperties::CardColour colour,
       CardProperties::CardSymbol symbol, CardProperties::CardFill fill);

  unsigned char get_number_of_symbols() const;
  CardProperties::CardColour get_colour() const;
  CardProperties::CardSymbol get_symbol() const;
  CardProperties::CardFill get_fill() const;
};

#endif // OPENSET_CARD_HPP
