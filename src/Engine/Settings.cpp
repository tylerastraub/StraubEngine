#include "Settings.h"
#include "FileIO.h"

#include <iostream>
#include <algorithm>

void Settings::loadSettings(std::string path) {
    _settingsPath = path;
    std::vector<std::string> controls = FileIO::readFile(path);
    int lineNumber = 0;
    for(auto line : controls) {
        ++lineNumber;
        // Find = sign using delimeter, map control, etc.
        int commentPos = line.find('#');
        line = line.substr(0, commentPos);
        if(line.empty()) continue;
        int delimiter = line.find('=');
        if(delimiter == std::string::npos) {
            continue;
        }
        std::string declaration = line.substr(0, delimiter);
        declaration.erase(std::remove(declaration.begin(), declaration.end(), ' '), declaration.end());
        std::string value = line.substr(delimiter + 1, std::string::npos);
        value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
        InputEvent input = convertStringToInputEvent(declaration);
        if(value.find("GAMEPAD") != std::string::npos) {
            SDL_GameControllerButton_Extended but = convertStringToButton(value);
            _buttonsMap[input] = but;
            _displayStringMap[input].second = value;
        }
        else {
            SDL_Scancode key = convertStringToScancode(value);
            if(key == SDL_SCANCODE_UNKNOWN) {
                parseSetting(declaration, value);
            }
            else {
                _keysMap[input] = key;
                _displayStringMap[input].first = value;
            }
        }
    }
}

void Settings::saveSettings() {
    std::vector<std::string> settings;
    settings = {
        "# ========== VIDEO SETTINGS CONFIG ==========",
        "RESOLUTION=" + std::to_string(_videoWidth) + "x" + std::to_string(_videoHeight),
        "VIDEO_MODE=" + convertVideoModeToString(),
        "MUSIC=" + convertMusicEnabledToString(),
        "",
        "# ========== KEYBOARD CONTROLS CONFIG ==========",
        "",
        "# To comment lines out, use the # symbol.",
        "# Note that if there are any conflicts, the last occurrence of a keybinding is used.",
        "UP=" + _displayStringMap[InputEvent::UP].first,
        "DOWN=" + _displayStringMap[InputEvent::DOWN].first,
        "LEFT=" + _displayStringMap[InputEvent::LEFT].first,
        "RIGHT=" + _displayStringMap[InputEvent::RIGHT].first,
        "ACTION=" + _displayStringMap[InputEvent::ACTION].first,
        "",
        "# ========== GAMEPAD CONTROLS CONFIG ==========",
        "",
        "# Note that bindings follow the standard XBox controller layout, although there is support for the PS4/PS5 touchbad button.",
        "ACTION=" + _displayStringMap[InputEvent::ACTION].second,
        "",
        "# ========== LIST OF ALL KEY BINDINGS ==========",
        "",
        "# A B C D E F G H I J K L M N O P Q R S T U V W X Y Z",
        "# 1 or !",
        "# 2 or @",
        "# 3 or #",
        "# 4 or $",
        "# 5 or %",
        "# 6 or ^",
        "# 7 or &",
        "# 8 or *",
        "# 9 or (",
        "# 0 or )",
        "# SHIFT or LSHIFT",
        "# RSHIFT",
        "# CAPSLOCK",
        "# TAB",
        "# LCTRL or CTRL",
        "# RCTRL",
        "# LALT or ALT",
        "# RALT",
        "# SPACE",
        "# ENTER or RETURN",
        "# , or <",
        "# . or >",
        "# / or ?",
        "# ; or :",
        "# ' or \"",
        "# [ or {",
        "# ] or }",
        "# | or \\",
        "# BACKSPACE",
        "# - or _",
        "# = or +",
        "# F1 F2 F3 F4 F5 F6 F7 F8 F9 F10 F11 F12 F14 F15 F16 F17 F18 F19 F20 F21 F22 F23 F24",
        "# ` or ~",
        "# HOME PAGEDOWN PAGEUP END DELETE HOME",
        "# ESC or ESCAPE",
        "# LEFTARROW RIGHTARROW UPARROW DOWNARROW",
        "# NUM1 NUM2 NUM3 NUM4 NUM5 NUM6 NUM7 NUM8 NUM9 NUM0 NUMPERIOD",
        "# NUM+ or NUMPLUS",
        "# NUM- or NUMMINUS",
        "# NUM* or NUMSTAR or NUMMULTIPLY",
        "# NUM/ or NUMSLASH or NUMDIVIDE",
        "# NUMENTER or NUMRETURN",
        "",
        "# ========== LIST OF ALL GAMEPAD BINDINGS ==========",
        "",
        "# GAMEPAD_A",
        "# GAMEPAD_X",
        "# GAMEPAD_Y",
        "# GAMEPAD_B",
        "# GAMEPAD_LB",
        "# GAMEPAD_RB",
        "# GAMEPAD_LT",
        "# GAMEPAD_RT",
        "# GAMEPAD_L3",
        "# GAMEPAD_R3",
        "# GAMEPAD_START",
        "# GAMEPAD_SELECT",
        "# GAMEPAD_TOUCHPAD",
    };
    
    FileIO::writeFile(_settingsPath, settings);
}

SDL_Scancode Settings::getScancode(InputEvent input) {
    return _keysMap[input];
}

SDL_GameControllerButton_Extended Settings::getButton(InputEvent input) {
    return _buttonsMap[input];
}

std::string Settings::getStringKeyboardControlForInputEvent(InputEvent input) {
    return _displayStringMap[input].first;
}

std::string Settings::getStringControllerControlForInputEvent(InputEvent input) {
    return _displayStringMap[input].second;
}

void Settings::setSetting(std::string declaration, std::string value) {
    parseSetting(declaration, value);
}

int Settings::getVideoWidth() {
    return _videoWidth;
}

int Settings::getVideoHeight() {
    return _videoHeight;
}

SDL_WindowFlags Settings::getVideoMode() {
    return _videoMode;
}

std::string Settings::getSettingsPath() {
    return _settingsPath;
}

bool Settings::getMusicEnabled() {
    return _musicEnabled;
}

InputEvent Settings::convertStringToInputEvent(std::string s) {
    if(s == "LEFT") {
        return InputEvent::LEFT;
    }
    else if(s == "RIGHT") {
        return InputEvent::RIGHT;
    }
    else if(s == "UP") {
        return InputEvent::UP;
    }
    else if(s == "DOWN") {
        return InputEvent::DOWN;
    }
    else if(s == "JUMP") {
        return InputEvent::JUMP;
    }
    else if(s == "ACTION") {
        return InputEvent::ACTION;
    }

    return InputEvent::NOVAL;
}

SDL_Scancode Settings::convertStringToScancode(std::string s) {
    if(s == "A") {
        return SDL_SCANCODE_A;
    }
    else if(s == "B") {
        return SDL_SCANCODE_B;
    }
    else if(s == "C") {
        return SDL_SCANCODE_C;
    }
    else if(s == "D") {
        return SDL_SCANCODE_D;
    }
    else if(s == "E") {
        return SDL_SCANCODE_E;
    }
    else if(s == "F") {
        return SDL_SCANCODE_F;
    }
    else if(s == "G") {
        return SDL_SCANCODE_G;
    }
    else if(s == "H") {
        return SDL_SCANCODE_H;
    }
    else if(s == "I") {
        return SDL_SCANCODE_I;
    }
    else if(s == "J") {
        return SDL_SCANCODE_J;
    }
    else if(s == "K") {
        return SDL_SCANCODE_K;
    }
    else if(s == "L") {
        return SDL_SCANCODE_L;
    }
    else if(s == "M") {
        return SDL_SCANCODE_M;
    }
    else if(s == "N") {
        return SDL_SCANCODE_N;
    }
    else if(s == "O") {
        return SDL_SCANCODE_O;
    }
    else if(s == "P") {
        return SDL_SCANCODE_P;
    }
    else if(s == "Q") {
        return SDL_SCANCODE_Q;
    }
    else if(s == "R") {
        return SDL_SCANCODE_R;
    }
    else if(s == "S") {
        return SDL_SCANCODE_S;
    }
    else if(s == "T") {
        return SDL_SCANCODE_T;
    }
    else if(s == "U") {
        return SDL_SCANCODE_U;
    }
    else if(s == "V") {
        return SDL_SCANCODE_V;
    }
    else if(s == "W") {
        return SDL_SCANCODE_W;
    }
    else if(s == "X") {
        return SDL_SCANCODE_X;
    }
    else if(s == "Y") {
        return SDL_SCANCODE_Y;
    }
    else if(s == "Z") {
        return SDL_SCANCODE_Z;
    }
    else if(s == "1" || s == "!") {
        return SDL_SCANCODE_1;
    }
    else if(s == "2" || s == "@") {
        return SDL_SCANCODE_2;
    }
    else if(s == "3" || s == "#") {
        return SDL_SCANCODE_3;
    }
    else if(s == "4" || s == "$") {
        return SDL_SCANCODE_4;
    }
    else if(s == "5" || s == "%") {
        return SDL_SCANCODE_5;
    }
    else if(s == "6" || s == "^") {
        return SDL_SCANCODE_6;
    }
    else if(s == "7" || s == "&") {
        return SDL_SCANCODE_7;
    }
    else if(s == "8" || s == "*") {
        return SDL_SCANCODE_8;
    }
    else if(s == "9" || s == "(") {
        return SDL_SCANCODE_9;
    }
    else if(s == "0" || s == ")") {
        return SDL_SCANCODE_0;
    }
    else if(s == "SHIFT" || s == "LSHIFT") {
        return SDL_SCANCODE_LSHIFT;
    }
    else if(s == "RSHIFT") {
        return SDL_SCANCODE_RSHIFT;
    }
    else if(s == "CAPSLOCK") {
        return SDL_SCANCODE_CAPSLOCK;
    }
    else if(s == "TAB") {
        return SDL_SCANCODE_TAB;
    }
    else if(s == "LCTRL" || s == "CTRL") {
        return SDL_SCANCODE_LCTRL;
    }
    else if(s == "RCTRL") {
        return SDL_SCANCODE_RCTRL;
    }
    else if(s == "LALT" || s == "ALT") {
        return SDL_SCANCODE_LALT;
    }
    else if(s == "RALT") {
        return SDL_SCANCODE_RALT;
    }
    else if(s == "SPACE") {
        return SDL_SCANCODE_SPACE;
    }
    else if(s == "ENTER" || s == "RETURN") {
        return SDL_SCANCODE_RETURN;
    }
    else if(s == "," || s == "<") {
        return SDL_SCANCODE_COMMA;
    }
    else if(s == "." || s == ">") {
        return SDL_SCANCODE_PERIOD;
    }
    else if(s == "/" || s == "?") {
        return SDL_SCANCODE_SLASH;
    }
    else if(s == ";" || s == ":") {
        return SDL_SCANCODE_SEMICOLON;
    }
    else if(s == "\'" || s == "\"") {
        return SDL_SCANCODE_APOSTROPHE;
    }
    else if(s == "[" || s == "{") {
        return SDL_SCANCODE_LEFTBRACKET;
    }
    else if(s == "]" || s == "}") {
        return SDL_SCANCODE_RIGHTBRACKET;
    }
    else if(s == "|" || s == "\\") {
        return SDL_SCANCODE_BACKSLASH;
    }
    else if(s == "BACKSPACE") {
        return SDL_SCANCODE_BACKSPACE;
    }
    else if(s == "-" || s == "_") {
        return SDL_SCANCODE_MINUS;
    }
    else if(s == "=" || s == "+") {
        return SDL_SCANCODE_EQUALS;
    }
    else if(s == "F1") {
        return SDL_SCANCODE_F1;
    }
    else if(s == "F2") {
        return SDL_SCANCODE_F2;
    }
    else if(s == "F3") {
        return SDL_SCANCODE_F3;
    }
    else if(s == "F4") {
        return SDL_SCANCODE_F4;
    }
    else if(s == "F5") {
        return SDL_SCANCODE_F5;
    }
    else if(s == "F6") {
        return SDL_SCANCODE_F6;
    }
    else if(s == "F7") {
        return SDL_SCANCODE_F7;
    }
    else if(s == "F8") {
        return SDL_SCANCODE_F8;
    }
    else if(s == "F9") {
        return SDL_SCANCODE_F9;
    }
    else if(s == "F10") {
        return SDL_SCANCODE_F10;
    }
    else if(s == "F11") {
        return SDL_SCANCODE_F11;
    }
    else if(s == "F12") {
        return SDL_SCANCODE_F12;
    }
    else if(s == "F14") {
        return SDL_SCANCODE_F14;
    }
    else if(s == "F15") {
        return SDL_SCANCODE_F15;
    }
    else if(s == "F16") {
        return SDL_SCANCODE_F16;
    }
    else if(s == "F17") {
        return SDL_SCANCODE_F17;
    }
    else if(s == "F18") {
        return SDL_SCANCODE_F18;
    }
    else if(s == "F19") {
        return SDL_SCANCODE_F19;
    }
    else if(s == "F20") {
        return SDL_SCANCODE_F20;
    }
    else if(s == "F21") {
        return SDL_SCANCODE_F21;
    }
    else if(s == "F22") {
        return SDL_SCANCODE_F22;
    }
    else if(s == "F23") {
        return SDL_SCANCODE_F23;
    }
    else if(s == "F24") {
        return SDL_SCANCODE_F24;
    }
    else if(s == "`" || s == "~") {
        return SDL_SCANCODE_GRAVE;
    }
    else if(s == "HOME") {
        return SDL_SCANCODE_HOME;
    }
    else if(s == "PAGEDOWN") {
        return SDL_SCANCODE_PAGEDOWN;
    }
    else if(s == "PAGEUP") {
        return SDL_SCANCODE_PAGEUP;
    }
    else if(s == "END") {
        return SDL_SCANCODE_END;
    }
    else if(s == "DELETE") {
        return SDL_SCANCODE_DELETE;
    }
    else if(s == "HOME") {
        return SDL_SCANCODE_HOME;
    }
    else if(s == "ESC" || s == "ESCAPE") {
        return SDL_SCANCODE_ESCAPE;
    }
    else if(s == "LEFTARROW") {
        return SDL_SCANCODE_LEFT;
    }
    else if(s == "RIGHTARROW") {
        return SDL_SCANCODE_RIGHT;
    }
    else if(s == "UPARROW") {
        return SDL_SCANCODE_UP;
    }
    else if(s == "DOWNARROW") {
        return SDL_SCANCODE_DOWN;
    }
    else if(s == "NUM1") {
        return SDL_SCANCODE_KP_1;
    }
    else if(s == "NUM2") {
        return SDL_SCANCODE_KP_2;
    }
    else if(s == "NUM3") {
        return SDL_SCANCODE_KP_3;
    }
    else if(s == "NUM4") {
        return SDL_SCANCODE_KP_4;
    }
    else if(s == "NUM5") {
        return SDL_SCANCODE_KP_5;
    }
    else if(s == "NUM6") {
        return SDL_SCANCODE_KP_6;
    }
    else if(s == "NUM7") {
        return SDL_SCANCODE_KP_7;
    }
    else if(s == "NUM8") {
        return SDL_SCANCODE_KP_8;
    }
    else if(s == "NUM9") {
        return SDL_SCANCODE_KP_9;
    }
    else if(s == "NUM0") {
        return SDL_SCANCODE_KP_0;
    }
    else if(s == "NUMPERIOD") {
        return SDL_SCANCODE_KP_PERIOD;
    }
    else if(s == "NUM+" || s == "NUMPLUS") {
        return SDL_SCANCODE_KP_PLUS;
    }
    else if(s == "NUM-" || s == "NUMMINUS") {
        return SDL_SCANCODE_KP_0;
    }
    else if(s == "NUM*" || s == "NUMSTAR" || s == "NUMMULTIPLY") {
        return SDL_SCANCODE_KP_MULTIPLY;
    }
    else if(s == "NUM/" || s == "NUMSLASH" || s == "NUMDIVIDE") {
        return SDL_SCANCODE_KP_DIVIDE;
    }
    else if(s == "NUMENTER" || s == "NUMRETURN") {
        return SDL_SCANCODE_KP_ENTER;
    }

    // Default
    return SDL_SCANCODE_UNKNOWN;
}

SDL_GameControllerButton_Extended Settings::convertStringToButton(std::string s) {
    if(s == "GAMEPAD_A") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_A;
    }
    else if(s == "GAMEPAD_X") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_X;
    }
    else if(s == "GAMEPAD_Y") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_Y;
    }
    else if(s == "GAMEPAD_B") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_B;
    }
    else if(s == "GAMEPAD_START") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_START;
    }
    else if(s == "GAMEPAD_SELECT") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_BACK;
    }
    else if(s == "GAMEPAD_LB") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
    }
    else if(s == "GAMEPAD_RB") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
    }
    else if(s == "GAMEPAD_L3") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_LEFTSTICK;
    }
    else if(s == "GAMEPAD_R3") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_RIGHTSTICK;
    }
    else if(s == "GAMEPAD_TOUCHPAD") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_TOUCHPAD;
    }
    else if(s == "GAMEPAD_LT") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_LEFTTRIGGER;
    }
    else if(s == "GAMEPAD_RT") {
        return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_RIGHTTRIGGER;
    }

    return SDL_GameControllerButton_Extended::SDL_CONTROLLER_BUTTON_INVALID;
}

void Settings::parseSetting(std::string declaration, std::string value) {
    if(declaration == "RESOLUTION") {
        int delimeter = value.find('x');
        std::string x = value.substr(0, delimeter);
        x.erase(std::remove(x.begin(), x.end(), ' '), x.end());
        std::string y = value.substr(delimeter + 1);
        y.erase(std::remove(y.begin(), y.end(), ' '), y.end());

        std::pair<int, int> resolution = {std::stoi(x), std::stoi(y)};
        _videoWidth = resolution.first;
        _videoHeight = resolution.second;
    }
    else if(declaration == "VIDEO_MODE") {
        if(value == "WINDOWED") {
            _videoMode = SDL_WINDOW_SHOWN;
        }
        else if(value == "WINDOWED_BORDERLESS") {
            _videoMode = SDL_WINDOW_BORDERLESS;
        }
        else if(value == "FULLSCREEN") {
            _videoMode = SDL_WINDOW_FULLSCREEN;
        }
        else {
            std::cout << "Error: invalid video mode in 'video_settings.cfg'! Video mode: " << value << std::endl;
        }
    }
    else if(declaration == "MUSIC") {
        if(value == "DISABLED") {
            _musicEnabled = false;
        }
        else {
            _musicEnabled = true;
        }
    }
}

std::string Settings::convertVideoModeToString() {
    if(_videoMode == SDL_WINDOW_SHOWN) {
        return "WINDOWED";
    }
    else if(_videoMode == SDL_WINDOW_BORDERLESS) {
        return "WINDOWED_BORDERLESS";
    }
    else if(_videoMode == SDL_WINDOW_FULLSCREEN) {
        return "FULLSCREEN";
    }
    return "WINDOWED";
}

std::string Settings::convertMusicEnabledToString() {
    if(_musicEnabled) return "ENABLED";
    return "DISABLED";
}