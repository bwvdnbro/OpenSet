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
 * @file Card.cpp
 *
 * @brief Card implementation.
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 */

#include "Card.hpp"

/**
 * @brief Empty constructor.
 */
Card::Card()
    : _number_of_symbols(0), _colour(CardProperties::CARDCOLOUR_COUNTER),
      _symbol(CardProperties::CARDSYMBOL_COUNTER),
      _fill(CardProperties::CARDFILL_COUNTER) {}

/**
 * @brief Constructor.
 *
 * @param number_of_symbols Number of symbols on the card (1-3).
 * @param colour Colour of the card (CARDCOLOUR_RED, CARDCOLOUR_BLUE,
 * CARDCOLOUR_GREEN).
 * @param symbol Symbol type (CARDSYMBOL_OVAL, CARDSYMBOL_RHOMBUS,
 * CARDSYMBOL_WIGGLE).
 * @param fill Fill type (CARDFILL_EMPTY, CARDFILL_STRIPES, CARDFILL_FULL).
 */
Card::Card(unsigned char number_of_symbols, CardProperties::CardColour colour,
           CardProperties::CardSymbol symbol, CardProperties::CardFill fill)
    : _number_of_symbols(number_of_symbols), _colour(colour), _symbol(symbol),
      _fill(fill) {}

/**
 * @brief Get the number of symbols on the card.
 *
 * @return Number of symbols on the card.
 */
unsigned char Card::get_number_of_symbols() const { return _number_of_symbols; }

/**
 * @brief Get the colour of the card.
 *
 * @return CardColour of the card.
 */
CardProperties::CardColour Card::get_colour() const { return _colour; }

/**
 * @brief Get the symbol on the card.
 *
 * @return CardSymbol of the card.
 */
CardProperties::CardSymbol Card::get_symbol() const { return _symbol; }

/**
 * @brief Get the fill type of the card.
 *
 * @return CardFill of the card.
 */
CardProperties::CardFill Card::get_fill() const { return _fill; }
