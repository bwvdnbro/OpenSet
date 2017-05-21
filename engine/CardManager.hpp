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
 * @file CardManager.hpp
 *
 * @brief Backbone of the game: class that keeps track of which cards are where.
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 */

#ifndef OPENSET_CARDMANAGER_HPP
#define OPENSET_CARDMANAGER_HPP

#include "Card.hpp"
#include "CardProperties.hpp"

#include <vector>

/**
 * @brief Backbone of the game: class that keeps track of which cards are where.
 */
class CardManager {
private:
  /*! @brief Cards. */
  Card _cards[CardProperties::CARDNUMBER_COUNTER *
              CardProperties::CARDCOLOUR_COUNTER *
              CardProperties::CARDSYMBOL_COUNTER *
              CardProperties::CARDNUMBER_COUNTER];

  unsigned char _card_stack[CardProperties::CARDNUMBER_COUNTER *
                            CardProperties::CARDCOLOUR_COUNTER *
                            CardProperties::CARDSYMBOL_COUNTER *
                            CardProperties::CARDNUMBER_COUNTER];

  /*! @brief Main card deck. */
  std::vector<unsigned char> _main_deck;

  /*! @brief Index of the next card that should be added to the deck. */
  unsigned char _next_card;

public:
  CardManager();

  std::vector<Card> get_deck() const;

  const Card &get_card(unsigned char index) const;
};

#endif // OPENSET_CARDMANAGER_HPP
