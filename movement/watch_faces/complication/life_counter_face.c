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

#include <stdlib.h>
#include <string.h>
#include "life_counter_face.h"
#include "watch.h"

void life_counter_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr) {
    (void) settings;
    (void) watch_face_index;
    if (*context_ptr == NULL) {
        *context_ptr = malloc(sizeof(life_counter_state_t));
        memset(*context_ptr, 0, sizeof(life_counter_state_t));        
    }
}

void life_counter_face_activate(movement_settings_t *settings, void *context) {
    (void) settings;
    (void) context;

    // Initialize state if there wasn't one before.
    life_counter_state_t *state = (life_counter_state_t *)context;
    // if(state->active_life_ctr != &state->life_counter_p1 || state->active_life_ctr != &state->life_counter_p2) {
        state->life_counter_p1 = 20;
        state->life_counter_p2 = 20;
        state->active_life_ctr = &state->life_counter_p1;
    // }
}

bool life_counter_face_loop(movement_event_t event, movement_settings_t *settings, void *context) {
    (void) settings;

    life_counter_state_t *state = (life_counter_state_t *)context;

    switch (event.event_type) {
        // Press light, decrement counter
        case EVENT_LIGHT_BUTTON_UP:
            if (*state->active_life_ctr == 0) {
                (*state->active_life_ctr)=20; //reset counter index
            } else {
                (*state->active_life_ctr)--; // decrement counter index
            }
            print_life_counter(state);
            break;
        // Press alarm, increment counter
        case EVENT_ALARM_BUTTON_UP:
            (*state->active_life_ctr)++; // increment counter index
            if (*state->active_life_ctr>99) { //0-99
                (*state->active_life_ctr)=0; //reset counter index
            }
            print_life_counter(state);
            break;
        // Reset Life
        case EVENT_ALARM_LONG_PRESS:
            (*state->active_life_ctr)=20; // reset counter index
            print_life_counter(state);
            break;
        case EVENT_MODE_BUTTON_UP:
            movement_move_to_next_face();
            break;
        // Change player
        case EVENT_MODE_LONG_PRESS:
            change_player(state);
            print_life_counter(state);
            break;
        case EVENT_LIGHT_LONG_PRESS:
            movement_illuminate_led();
            break;
        case EVENT_ACTIVATE:
            print_life_counter(state);
            break;
        case EVENT_TIMEOUT:
            // ignore timeout, we want to display life entire game.
            break;
        default:
            break;
    }

    return true;
}

void change_player(life_counter_state_t *state) {
    if(state->active_life_ctr != &state->life_counter_p1) {
        state->active_life_ctr = &state->life_counter_p1;
    } else {
        state->active_life_ctr = &state->life_counter_p2;
    }
}

// print counter index at the center of display.
void print_life_counter(life_counter_state_t *state) {
    char buf[14];
    sprintf(buf, "LF1   %02d", *state->active_life_ctr); // center of LCD display
    watch_display_string(buf, 0);
}

void life_counter_face_resign(movement_settings_t *settings, void *context) {
    (void) settings;
    (void) context;
}
