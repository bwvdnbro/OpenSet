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
 * @file CardProperties.cpp
 *
 * @brief Convenience functions to convert CardProperties to human readable
 * strings.
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 */

#include "CardProperties.hpp"

/**
 * @brief Convert a CardColour to a std::string.
 *
 * @param colour CardColour (CARDCOLOUR_RED, CARDCOLOUR_BLUE, CARDCOLOUR_GREEN).
 * @return std::string ("red", "blue", "green").
 */
std::string CardProperties::get_card_colour(CardColour colour) {
  switch (colour) {
  case CARDCOLOUR_RED:
    return "red";
  case CARDCOLOUR_BLUE:
    return "blue";
  case CARDCOLOUR_GREEN:
    return "green";
  default:
    return "unknown";
  }
}

/**
 * @brief Convert a CardSymbol to a std::string.
 *
 * @param symbol CardSymbol (CARDSYMBOL_OVAL, CARDSYMBOL_RHOMBUS,
 * CARDSYMBOL_WIGGLE).
 * @return std::string ("oval", "rhombus", "wiggle").
 */
std::string CardProperties::get_card_symbol(CardSymbol symbol) {
  switch (symbol) {
  case CARDSYMBOL_OVAL:
    return "oval";
  case CARDSYMBOL_RHOMBUS:
    return "rhombus";
  case CARDSYMBOL_WIGGLE:
    return "wiggle";
  default:
    return "unknown";
  }
}

/**
 * @brief Convert a CardFill to a std::string.
 *
 * @param fill CardFill (CARDFILL_EMPTY, CARDFILL_STRIPES, CARDFILL_FULL).
 * @return std::string ("empty", "stripes", "full").
 */
std::string CardProperties::get_card_fill(CardFill fill) {
  switch (fill) {
  case CARDFILL_EMPTY:
    return "empty";
  case CARDFILL_STRIPES:
    return "stripes";
  case CARDFILL_FULL:
    return "full";
  default:
    return "unknown";
  }
}
