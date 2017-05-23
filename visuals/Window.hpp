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
 * @file Window.hpp
 *
 * @brief Abstract representation of the game window.
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 */

#ifndef OPENSET_WINDOW_HPP
#define OPENSET_WINDOW_HPP

#include "../engine/CardProperties.hpp"

#include <gtk/gtk.h>
#include <string>

class CardManager;

/**
 * @brief Abstract representation of the game window.
 */
class Window {
private:
  /**
   * @brief Private inner class used to represent card exposure events.
   */
  class CardExposeEvent {
  private:
    /*! @brief Pointer to the active window instance. */
    Window *_window;

    /*! @brief Index of the card that is being exposed. */
    unsigned char _index;

  public:
    CardExposeEvent();
    CardExposeEvent(Window *window, unsigned char index);

    Window *get_window() const;
    unsigned char get_index() const;
  };

private:
  /*! @brief Wrapped GTK window. */
  GtkWidget *_window;

  /*! @brief Wrapped GTK aspect frames that contain cards (used to hide or show
   *  cards). */
  GtkWidget *_aspect_frames[18];

  /*! @brief Wrapped GTK drawing areas used to draw the actual cards. */
  GtkWidget *_cards[18];

  /*! @brief CardManager that contains information about the cards. */
  CardManager &_card_manager;

  /*! @brief CardExposeEvents for the cards. */
  CardExposeEvent _card_expose_events[18];

public:
  Window(int &argc, char **argv, unsigned int size_x, unsigned int size_y,
         std::string title, CardManager &card_manager);

  void show(bool start_application = true);

private:
  static void draw_rounded_rectangle(cairo_t *cr, double origin_x,
                                     double origin_y, double side_x,
                                     double side_y, double r);
  static void draw_oval(cairo_t *cr, double origin[2], double size[2]);
  static void draw_rhombus(cairo_t *cr, double origin[2], double size[2]);
  static void draw_wiggle(cairo_t *cr, double origin[2], double size[2]);
  static void draw_shape(cairo_t *cr, CardProperties::CardSymbol shape,
                         double origin[2], double size[2]);
  static void set_drawing_colour(cairo_t *cr,
                                 CardProperties::CardColour colour);

  void draw_card(unsigned char index);
  void card_clicked(unsigned char index);

  static void delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
  static gboolean card_expose_event(GtkWidget *widget, GdkEventExpose *event,
                                    gpointer data);
  static gboolean card_click_event(GtkWidget *widget, GdkEvent *event,
                                   gpointer data);
};

#endif // OPENSET_WINDOW_HPP
