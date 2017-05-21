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
 * @file Window.cpp
 *
 * @brief Window implementation.
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 */

#include "Window.hpp"
#include "../engine/Card.hpp"
#include "../engine/CardManager.hpp"

#include <cmath>

/**
 * @brief CardExposeEvent (empty) constructor.
 */
Window::CardExposeEvent::CardExposeEvent() : _window(NULL), _index(0) {}

/**
 * @brief CardExposeEvent constructor.
 *
 * @param window Pointer to the active window instance.
 * @param index Index of the card that is being exposed.
 */
Window::CardExposeEvent::CardExposeEvent(Window *window, unsigned char index)
    : _window(window), _index(index) {}

/**
 * @brief Get the Window instance that contains the exposed card.
 *
 * @return Pointer to the active window instance.
 */
Window *Window::CardExposeEvent::get_window() const { return _window; }

/**
 * @brief Get the index of the exposed card.
 *
 * @return Index of the exposed card.
 */
unsigned char Window::CardExposeEvent::get_index() const { return _index; }

/**
 * @brief Constructor.
 *
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @param size_x Horizontal initial size of the window (in pixels).
 * @param size_y Vertical initial size of the window (in pixels).
 * @param title Title for the window.
 * @param card_manager CardManager that contains information about the cards.
 */
Window::Window(int &argc, char **argv, unsigned int size_x, unsigned int size_y,
               std::string title, CardManager &card_manager)
    : _card_manager(card_manager) {
  // initialize GTK
  gtk_init(&argc, &argv);

  // create the underlying window
  _window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // set the initial size of the window
  gtk_window_set_default_size(GTK_WINDOW(_window), size_x, size_y);

  // set the title of the window
  gtk_window_set_title(GTK_WINDOW(_window), title.c_str());

  // connect the window delete event to the delete function for this window
  g_signal_connect(_window, "delete-event", G_CALLBACK(delete_event), this);

  GtkWidget *vbox = gtk_vbox_new(TRUE, 0);
  GtkWidget *hbox[3];
  hbox[0] = gtk_hbox_new(TRUE, 0);
  hbox[1] = gtk_hbox_new(TRUE, 0);
  hbox[2] = gtk_hbox_new(TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox[0], TRUE, TRUE, 10);
  gtk_box_pack_start(GTK_BOX(vbox), hbox[1], TRUE, TRUE, 10);
  gtk_box_pack_start(GTK_BOX(vbox), hbox[2], TRUE, TRUE, 10);

  gtk_container_add(GTK_CONTAINER(_window), vbox);
  gtk_widget_show(vbox);
  gtk_widget_show(hbox[0]);
  gtk_widget_show(hbox[1]);
  gtk_widget_show(hbox[2]);

  for (unsigned char ix = 0; ix < 6; ++ix) {
    for (unsigned char iy = 0; iy < 3; ++iy) {
      _aspect_frames[3 * ix + iy] =
          gtk_aspect_frame_new(NULL, 0.5, 0.5, 1. / std::sqrt(2.), FALSE);

      gtk_container_add(GTK_CONTAINER(hbox[iy]), _aspect_frames[3 * ix + iy]);

      _cards[3 * ix + iy] = gtk_drawing_area_new();
      gtk_widget_set_size_request(_cards[3 * ix + iy], 100, 100);
      _card_expose_events[3 * ix + iy] = CardExposeEvent(this, 3 * ix + iy);
      g_signal_connect(G_OBJECT(_cards[3 * ix + iy]), "expose_event",
                       G_CALLBACK(card_expose_event),
                       &_card_expose_events[3 * ix + iy]);

      gtk_container_add(GTK_CONTAINER(_aspect_frames[3 * ix + iy]),
                        _cards[3 * ix + iy]);

      gtk_widget_show(_cards[3 * ix + iy]);
    }
  }

  for (unsigned int i = 0; i < 12; ++i) {
    gtk_widget_show(_aspect_frames[i]);
  }
}

/**
 * @brief Show the window and (optionally) enter the main GTK loop.
 *
 * In real applications, you always want to enter the main GTK loop, because
 * otherwise the application will just exit. However, this behaviour is useful
 * for
 * testing purposes, when you don't want to actually use the window, but just
 * want
 * to test if it is set up correctly.
 *
 * @param start_application Enter the main GTK loop after the window has been
 * shown (default: true)?
 */
void Window::show(bool start_application) {
  // show the window
  gtk_widget_show(_window);

  if (start_application) {
    // enter the main GTK loop
    gtk_main();
  }
}

/**
 * @brief Draw a rectangle with rounded edges.
 *
 * @param cr cairo_t instance to use for drawing.
 * @param origin_x Upper left corner of the rectangle: horizontal position.
 * @param origin_y Upper left corner of the rectangle: vertical position.
 * @param side_x Width: horizontal size of the rectangle.
 * @param side_y Height: vertical size of the rectangle.
 * @param r Radius used for round corners.
 */
void Window::draw_rounded_rectangle(cairo_t *cr, double origin_x,
                                    double origin_y, double side_x,
                                    double side_y, double r) {

  cairo_new_sub_path(cr);
  cairo_arc(cr, origin_x + side_x - r, origin_y + r, r, -0.5 * M_PI, 0.);
  cairo_arc(cr, origin_x + side_x - r, origin_y + side_y - r, r, 0.,
            0.5 * M_PI);
  cairo_arc(cr, origin_x + r, origin_y + side_y - r, r, 0.5 * M_PI, M_PI);
  cairo_arc(cr, origin_x + r, origin_y + r, r, M_PI, 1.5 * M_PI);
  cairo_close_path(cr);
}

/**
 * @brief Draw an oval.
 *
 * @param cr cairo_t instance to use for drawing.
 * @param origin Coordinates of the center of the oval.
 * @param size Side lenghts of the oval.
 */
void Window::draw_oval(cairo_t *cr, double origin[2], double size[2]) {
  draw_rounded_rectangle(cr, origin[0] - 0.5 * size[0],
                         origin[1] - 0.5 * size[1], size[0], size[1],
                         0.5 * size[1]);
}

/**
 * @brief Draw a rhombus.
 *
 * @param cr cairo_t instance to use for drawing.
 * @param origin Coordinates of the center of the rhombus.
 * @param size Side lengths of the rhombus.
 */
void Window::draw_rhombus(cairo_t *cr, double origin[2], double size[2]) {
  cairo_new_sub_path(cr);
  cairo_move_to(cr, origin[0] - 0.5 * size[0], origin[1]);
  cairo_line_to(cr, origin[0], origin[1] - 0.5 * size[1]);
  cairo_line_to(cr, origin[0] + 0.5 * size[0], origin[1]);
  cairo_line_to(cr, origin[0], origin[1] + 0.5 * size[1]);
  cairo_line_to(cr, origin[0] - 0.5 * size[0], origin[1]);
  cairo_close_path(cr);
}

/**
 * @brief Draw a wiggly shape.
 *
 * @param cr cairo_t instance to use for drawing.
 * @param origin Coordinates of the center of the wiggly shape.
 * @param size Side lenghts of the wiggly shape.
 */
void Window::draw_wiggle(cairo_t *cr, double origin[2], double size[2]) {
  cairo_new_sub_path(cr);
  cairo_move_to(cr, origin[0] - 0.5 * size[0], origin[1]);
  cairo_curve_to(cr, origin[0] - 0.5 * size[0], origin[1] - 0.25 * size[1],
                 origin[0] - 0.25 * size[0], origin[1] - 0.5 * size[1],
                 origin[0], origin[1] - 0.25 * size[1]);
  cairo_curve_to(cr, origin[0] + 0.25 * size[0], origin[1],
                 origin[0] + 0.5 * size[0], origin[1] - 1. * size[1],
                 origin[0] + 0.5 * size[0], origin[1]);
  cairo_curve_to(cr, origin[0] + 0.5 * size[0], origin[1] + 0.25 * size[1],
                 origin[0] + 0.25 * size[0], origin[1] + 0.5 * size[1],
                 origin[0], origin[1] + 0.25 * size[1]);
  cairo_curve_to(cr, origin[0] - 0.25 * size[0], origin[1],
                 origin[0] - 0.5 * size[0], origin[1] + 1. * size[1],
                 origin[0] - 0.5 * size[0], origin[1]);
  cairo_close_path(cr);
}

/**
 * @brief Draw the given shape.
 *
 * @param cr cairo_t instance to use for drawing.
 * @param shape CardSymbol to draw.
 * @param origin Coordinates of the center of the shape.
 * @param size Side lengths of the shape.
 */
void Window::draw_shape(cairo_t *cr, CardProperties::CardSymbol shape,
                        double origin[2], double size[2]) {
  switch (shape) {
  case CardProperties::CARDSYMBOL_OVAL:
    draw_oval(cr, origin, size);
    break;
  case CardProperties::CARDSYMBOL_RHOMBUS:
    draw_rhombus(cr, origin, size);
    break;
  case CardProperties::CARDSYMBOL_WIGGLE:
    draw_wiggle(cr, origin, size);
    break;
  }
}

/**
 * @brief Set the drawing colour.
 *
 * @param cr cairo_t instance that will be affected.
 * @param colour CardColour to set.
 */
void Window::set_drawing_colour(cairo_t *cr,
                                CardProperties::CardColour colour) {
  switch (colour) {
  case CardProperties::CARDCOLOUR_RED:
    cairo_set_source_rgb(cr, 1, 0, 0);
    break;
  case CardProperties::CARDCOLOUR_BLUE:
    cairo_set_source_rgb(cr, 0, 1, 0);
    break;
  case CardProperties::CARDCOLOUR_GREEN:
    cairo_set_source_rgb(cr, 0, 0, 1);
    break;
  }
}

/**
 * @brief Draw the card with the given index.
 *
 * @param index Index of a card in the card grid.
 */
void Window::draw_card(unsigned char index) {
  int width, height;
  width = _cards[index]->allocation.width;
  height = _cards[index]->allocation.height;
  cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(_cards[index]));

  cairo_set_source_rgb(cr, 1, 1, 1);
  draw_rounded_rectangle(cr, 0, 0, width, height, 20.);
  cairo_fill(cr);

  double shape_size[2];
  shape_size[0] = 0.5 * width;
  shape_size[1] = 0.5 * shape_size[0];

  double shape_origin[2];
  shape_origin[0] = 0.5 * width;

  const Card &card = _card_manager.get_card(index);
  int num_shape = card.get_number_of_symbols();
  CardProperties::CardSymbol shape_type = card.get_symbol();
  CardProperties::CardColour colour_type = card.get_colour();
  int fill_type = 2 - static_cast<int>(card.get_fill());

  cairo_surface_t *texture =
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 10, 10);
  cairo_t *tcr = cairo_create(texture);
  set_drawing_colour(tcr, colour_type);
  cairo_rectangle(tcr, fill_type * 5, 0, 10, 10);
  cairo_fill(tcr);
  cairo_destroy(tcr);
  cairo_pattern_t *pattern = cairo_pattern_create_for_surface(texture);

  double shape_spacing = height / (num_shape + 1.);
  for (int i = 0; i < num_shape; ++i) {
    shape_origin[1] = (i + 1) * shape_spacing;

    draw_shape(cr, shape_type, shape_origin, shape_size);
    cairo_set_source(cr, pattern);
    cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
    cairo_fill_preserve(cr);
    set_drawing_colour(cr, colour_type);
    cairo_stroke(cr);
  }

  cairo_pattern_destroy(pattern);
  cairo_surface_destroy(texture);

  cairo_destroy(cr);
}

/**
 * @brief Event called when the window is closed by the user.
 *
 * @param widget Window that was closed.
 * @param event Delete event that triggered this callback.
 * @param gpointer Extra data: pointer to the Window instance that wraps the
 * window.
 */
void Window::delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
  gtk_main_quit();
}

/**
 * @brief Event called when a card is exposed (becomes visible).
 *
 * @param widget Card that is exposed.
 * @param event GDK expose event.
 * @param data Extra data passed on to this event: a pointer to the Window
 * instance
 * and the index of the card that is exposed.
 * @return FALSE, because we have handled the event and it should not be
 * propagated
 * further.
 */
gboolean Window::card_expose_event(GtkWidget *widget, GdkEventExpose *event,
                                   gpointer data) {
  CardExposeEvent *card_expose_event = static_cast<CardExposeEvent *>(data);
  card_expose_event->get_window()->draw_card(card_expose_event->get_index());
  return FALSE;
}
