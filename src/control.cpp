#include <unordered_map>
#include <SDL_keycode.h>

#include "control/control.h"

int Control::SetKey(SDL_Keycode key, bool state) {
    this->keys[key] = state;

    return 0;
}

int Control::SetMouseBtn(Uint8 btn, bool state) {
    this->mouse_btns[btn] = state;

    return 0;
}

bool Control::CheckKey(SDL_Keycode key) {
    if (this->keys[key]) {
        return true;
    }
    return false;
}

bool Control::CheckMouseBtn(Uint8 btn) {
    if (this->mouse_btns[btn]) {
        return this->mouse_btns[btn];
    }
    return false;
}
