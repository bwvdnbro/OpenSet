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
 * @file CardProperties.hpp
 *
 * @brief Convenient enums used to name card properties.
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 */

#ifndef OPENSET_CARDPROPERTIES_HPP
#define OPENSET_CARDPROPERTIES_HPP

#include <string>

/**
 * @brief Convenient enums used to name card properties.
 */
namespace CardProperties {

/*! @brief Maximum number of symbols on a card. */
const static unsigned char CARDNUMBER_COUNTER = 3;

/**
 * @brief Card colour.
 */
enum CardColour {
  /*! @brief Red. */
  CARDCOLOUR_RED = 0,
  /*! @brief Blue. */
  CARDCOLOUR_BLUE,
  /*! @brief Green. */
  CARDCOLOUR_GREEN,
  /*! @brief Counter: make sure this element is always last! */
  CARDCOLOUR_COUNTER
};

std::string get_card_colour(CardColour colour);

/**
 * @brief Card symbol.
 */
enum CardSymbol {
  /*! @brief Oval. */
  CARDSYMBOL_OVAL = 0,
  /*! @brief Rhombus. */
  CARDSYMBOL_RHOMBUS,
  /*! @brief Wiggle. */
  CARDSYMBOL_WIGGLE,
  /*! @brief Counter: make sure this element is always last! */
  CARDSYMBOL_COUNTER
};

std::string get_card_symbol(CardSymbol symbol);

/**
 * @brief Card fill.
 */
enum CardFill {
  /*! @brief Empty. */
  CARDFILL_EMPTY = 0,
  /*! @brief Stripes. */
  CARDFILL_STRIPES,
  /*! @brief Full. */
  CARDFILL_FULL,
  /*! @brief Counter: make sure this element is always last! */
  CARDFILL_COUNTER
};

std::string get_card_fill(CardFill fill);
}

#endif // OPENSET_CARDPROPERTIES_HPP
