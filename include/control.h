#ifndef CONTROL_H
#define CONTROL_H

#include <unordered_map>
#include <SDL_keycode.h>

class Control {
private:
    std::unordered_map<SDL_Keycode, bool> keys;
    std::unordered_map<Uint8, bool> mouse_btns;
public:
    int SetKey(SDL_Keycode key, bool state);
    int SetMouseBtn(Uint8 btn, bool state);
    bool CheckKey(SDL_Keycode key);
    bool CheckMouseBtn(Uint8 btn);
};

#endif