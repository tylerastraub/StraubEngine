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
enum class SDL_GameControllerButton_Extended {
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

class Settings {
public:
    Settings() = default;
    ~Settings() = default;

    void loadSettings(std::string path);
    void saveSettings();

    SDL_Scancode getScancode(Input input);
    SDL_GameControllerButton_Extended getButton(Input input);
    std::string getStringKeyboardControlForInput(Input input);
    std::string getStringControllerControlForInput(Input input);

    void setSetting(std::string declaration, std::string value);

    int getVideoWidth();
    int getVideoHeight();
    SDL_WindowFlags getVideoMode();
    std::string getSettingsPath();
    bool getMusicEnabled();

private:
    Input convertStringToInput(std::string s);
    SDL_Scancode convertStringToScancode(std::string s);
    std::string convertScancodeToString(SDL_Scancode code);
    SDL_GameControllerButton_Extended convertStringToButton(std::string s);
    std::string convertButtonToString(SDL_GameControllerButton_Extended button);

    void parseSetting(std::string declaration, std::string value);
    std::string convertVideoModeToString();
    std::string convertMusicEnabledToString();

    std::unordered_map<Input, SDL_Scancode> _keysMap;
    std::unordered_map<Input, SDL_GameControllerButton_Extended> _buttonsMap;
    // How the control for the corresponding input will be displayed. First string is keyboard, second is controller
    std::unordered_map<Input, std::pair<std::string, std::string>> _displayStringMap;
    
    const std::pair<int, int> VALID_RESOLUTIONS[4] = {
        {640, 360},
        {1280, 720},
        {1920, 1080},
        {2560, 1440}
    };

    std::string _settingsPath = "";
    int _videoWidth = 1280;
    int _videoHeight = 720;
    SDL_WindowFlags _videoMode = SDL_WINDOW_BORDERLESS;
    bool _musicEnabled = true;
    
};

#endif