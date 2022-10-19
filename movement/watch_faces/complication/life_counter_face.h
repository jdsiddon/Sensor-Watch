/*
 * MIT License
 *
 * Copyright (c) 2022 Shogo Okamoto
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef LIFE_COUNTER_FACE_H_
#define LIFE_COUNTER_FACE_H_

#include "movement.h"

// Life counter face is designed to count the amount of life a player has remaining in the game of Magic the Gathering.
typedef struct {
    int8_t *active_life_ctr;
    int8_t life_counter_p1;
    int8_t life_counter_p2;
} life_counter_state_t;


void life_counter_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr);
void life_counter_face_activate(movement_settings_t *settings, void *context);
bool life_counter_face_loop(movement_event_t event, movement_settings_t *settings, void *context);
void life_counter_face_resign(movement_settings_t *settings, void *context);

void change_player(life_counter_state_t *state);
void print_life_counter(life_counter_state_t *state);

#define life_counter_face ((const watch_face_t){ \
    life_counter_face_setup, \
    life_counter_face_activate, \
    life_counter_face_loop, \
    life_counter_face_resign, \
    NULL, \
})

#endif // LIFE_COUNTER_FACE_H_
