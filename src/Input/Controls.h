#ifndef CONTROLS_H
#define CONTROLS_H

#include <unordered_map>
#include <SDL.h>
#include <string>

enum Input {
    NOVAL,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    JUMP,
    ACTION,
};

// SDL_GameControllerButton enum with added values for the triggers. Allows the triggers to be used as buttons instead of axises
namespace gamepad {
    enum SDL_GameControllerButton_Extended {
        SDL_CONTROLLER_BUTTON_INVALID = -1,
        SDL_CONTROLLER_BUTTON_A,
        SDL_CONTROLLER_BUTTON_B,
        SDL_CONTROLLER_BUTTON_X,
        SDL_CONTROLLER_BUTTON_Y,
        SDL_CONTROLLER_BUTTON_BACK,
        SDL_CONTROLLER_BUTTON_GUIDE,
        SDL_CONTROLLER_BUTTON_START,
        SDL_CONTROLLER_BUTTON_LEFTSTICK,
        SDL_CONTROLLER_BUTTON_RIGHTSTICK,
        SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
        SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
        SDL_CONTROLLER_BUTTON_DPAD_UP,
        SDL_CONTROLLER_BUTTON_DPAD_DOWN,
        SDL_CONTROLLER_BUTTON_DPAD_LEFT,
        SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
        SDL_CONTROLLER_BUTTON_MISC1,    /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
        SDL_CONTROLLER_BUTTON_PADDLE1,  /* Xbox Elite paddle P1 */
        SDL_CONTROLLER_BUTTON_PADDLE2,  /* Xbox Elite paddle P3 */
        SDL_CONTROLLER_BUTTON_PADDLE3,  /* Xbox Elite paddle P2 */
        SDL_CONTROLLER_BUTTON_PADDLE4,  /* Xbox Elite paddle P4 */
        SDL_CONTROLLER_BUTTON_TOUCHPAD, /* PS4/PS5 touchpad button */
        SDL_CONTROLLER_BUTTON_MAX,
        SDL_CONTROLLER_BUTTON_LEFTTRIGGER,
        SDL_CONTROLLER_BUTTON_RIGHTTRIGGER
    };
};

class Controls {
public:
    Controls() = default;
    ~Controls() = default;

    void loadControls(std::string path);

    SDL_Scancode getScancode(Input input);
    gamepad::SDL_GameControllerButton_Extended getButton(Input input);
    std::string getStringKeyboardControlForInput(Input input);
    std::string getStringControllerControlForInput(Input input);

private:
    Input convertStringToInput(std::string s);
    SDL_Scancode convertStringToScancode(std::string s);
    gamepad::SDL_GameControllerButton_Extended convertStringToButton(std::string s);

    std::unordered_map<Input, SDL_Scancode> _keysMap;
    std::unordered_map<Input, gamepad::SDL_GameControllerButton_Extended> _buttonsMap;
    // How the control for the corresponding input will be displayed. First string is keyboard, second is controller
    std::unordered_map<Input, std::pair<std::string, std::string>> _displayStringMap;
    
};

#endif