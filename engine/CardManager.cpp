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
 * @file CardManager.cpp
 *
 * @brief CardManager implementation.
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 */

#include "CardManager.hpp"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>

/**
 * @brief Utility class used for index sorting the card weight array.
 */
class CardSorter {
private:
  /*! @brief Pointer to the card weight array. */
  int *_weights;

public:
  /**
   * @brief Constructor.
   *
   * @param weights Pointer to the card weights array.
   */
  CardSorter(int *weights) : _weights(weights) {}

  /**
   * @brief Sort function.
   *
   * @param a Index of element A.
   * @param b Index of element B.
   * @return True if the weight for element A is smaller than that for element
   * B.
   */
  bool operator()(const unsigned char a, const unsigned char b) {
    return _weights[a] < _weights[b];
  }
};

/**
 * @brief Constructor.
 */
CardManager::CardManager() : _num_clicked(0) {
  // initialize the random generator
  srand(time(NULL));

  // array that will be used to randomly shuffle the cards
  int card_order_weights[CardProperties::CARDNUMBER_COUNTER *
                         CardProperties::CARDCOLOUR_COUNTER *
                         CardProperties::CARDSYMBOL_COUNTER *
                         CardProperties::CARDFILL_COUNTER];

  // create the cards
  unsigned char card_index = 0;
  for (unsigned char number_of_symbols = 1;
       number_of_symbols <= CardProperties::CARDNUMBER_COUNTER;
       ++number_of_symbols) {
    for (int colour = 0; colour < CardProperties::CARDCOLOUR_COUNTER;
         ++colour) {
      for (int symbol = 0; symbol < CardProperties::CARDSYMBOL_COUNTER;
           ++symbol) {
        for (int fill = 0; fill < CardProperties::CARDFILL_COUNTER; ++fill) {
          _cards[card_index] =
              Card(number_of_symbols,
                   static_cast<CardProperties::CardColour>(colour),
                   static_cast<CardProperties::CardSymbol>(symbol),
                   static_cast<CardProperties::CardFill>(fill));
          card_order_weights[card_index] = rand();
          _card_stack[card_index] = card_index;
          ++card_index;
        }
      }
    }
  }

  // argument sort the card_order_weights array; this effectively shuffles the
  // cards
  CardSorter sorter(card_order_weights);
  std::sort(&_card_stack[0], &_card_stack[0] + card_index, sorter);

  // set up the main deck
  _main_deck.resize(12, 0);
  for (unsigned char card = 0; card < 12; ++card) {
    _main_deck[card] = _card_stack[card];
  }
  _next_card = 13;
}

/**
 * @brief Get the cards that are currently in the main deck.
 *
 * @return Cards that are currently in the main deck.
 */
std::vector<Card> CardManager::get_deck() const {
  std::vector<Card> deck;
  for (unsigned char card = 0; card < _main_deck.size(); ++card) {
    deck.push_back(_cards[_main_deck[card]]);
  }
  return deck;
}

/**
 * @brief Get a reference to the card with the given index.
 *
 * @param index Index of a card on the main deck.
 * @return constant reference to that card.
 */
const Card &CardManager::get_card(unsigned char index) const {
  return _cards[_main_deck[index]];
}

/**
 * @brief Click the card with the given index.
 */
void CardManager::click_card(unsigned char index) {
  unsigned char i = 0;
  while (i < _num_clicked && _clicked[i] != index) {
    ++i;
  }
  if (i == _num_clicked) {
    assert(i < 3);
    // new card was clicked
    _clicked[_num_clicked] = index;
    _cards[_main_deck[index]].click();
    ++_num_clicked;
  } else {
    // clicked card was clicked again
    _cards[_main_deck[index]].unclick();
    unsigned char j = i + 1;
    while (j < _num_clicked) {
      _clicked[i] = _clicked[j];
      ++i;
      ++j;
    }
    --_num_clicked;
  }

  if (_num_clicked == 3) {
    check_set();
  }
}

/**
 * @brief Check if the clicked cards make up a set, and if so, remove it.
 */
void CardManager::check_set() {
  if (is_set(_cards[_main_deck[_clicked[0]]], _cards[_main_deck[_clicked[1]]],
             _cards[_main_deck[_clicked[2]]])) {
    unsigned char next_clicked = 0;
    while (_next_card < 81 && next_clicked < 3) {
      _main_deck[_clicked[next_clicked]] = _card_stack[_next_card];
      ++next_clicked;
      ++_next_card;
    }
  } else {
    _cards[_main_deck[_clicked[0]]].unclick();
    _cards[_main_deck[_clicked[1]]].unclick();
    _cards[_main_deck[_clicked[2]]].unclick();
  }
  _num_clicked = 0;
}

/**
 * @brief Check if the three given cards make up a set.
 *
 * @param card1 First card.
 * @param card2 Second card.
 * @param card3 Third card.
 * @return True if the three cards make up a set.
 */
bool CardManager::is_set(Card &card1, Card &card2, Card &card3) {
  bool colour_set = (card1.get_colour() == card2.get_colour() &&
                     card1.get_colour() == card3.get_colour()) ||
                    (card1.get_colour() != card2.get_colour() &&
                     card1.get_colour() != card3.get_colour() &&
                     card2.get_colour() != card3.get_colour());
  bool symbol_set = (card1.get_symbol() == card2.get_symbol() &&
                     card1.get_symbol() == card3.get_symbol()) ||
                    (card1.get_symbol() != card2.get_symbol() &&
                     card1.get_symbol() != card3.get_symbol() &&
                     card2.get_symbol() != card3.get_symbol());
  bool fill_set = (card1.get_fill() == card2.get_fill() &&
                   card1.get_fill() == card3.get_fill()) ||
                  (card1.get_fill() != card2.get_fill() &&
                   card1.get_fill() != card3.get_fill() &&
                   card2.get_fill() != card3.get_fill());
  bool num_set =
      (card1.get_number_of_symbols() == card2.get_number_of_symbols() &&
       card1.get_number_of_symbols() == card3.get_number_of_symbols()) ||
      (card1.get_number_of_symbols() != card2.get_number_of_symbols() &&
       card1.get_number_of_symbols() != card3.get_number_of_symbols() &&
       card2.get_number_of_symbols() != card3.get_number_of_symbols());
  return colour_set && symbol_set && fill_set && num_set;
}
