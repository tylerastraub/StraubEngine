#include "DialogueParser.h"

#include <SDL.h>
#include <fstream>
#include <iostream>

void DialogueParser::openJson(std::string filePath) {
    std::ifstream file(SDL_GetBasePath() + filePath);
    _data = json::parse(file);
    
    if(_data.empty()) {
        std::cout << "Error: dialogue file '" << filePath << "' is empty!" << std::endl;
        return;
    }

    for(auto dialogueEntry : _data["dialogueEntries"]) {
        if(dialogueEntry["id"] < 1) continue;
        auto fields = dialogueEntry["fields"];
        auto outgoingLinks = dialogueEntry["outgoingLinks"];

        Dialogue d;
        d.id = dialogueEntry["id"];
        d.conversationId = dialogueEntry["conversationId"];
        d.isRoot = dialogueEntry["isRoot"];
        for(auto field : fields) {
            if(field["name"] == "SPEAKER") {
                if(field["enabled"]) d.speakerName = field["value"];
            }
            else if(field["name"] == "PORTRAIT") {
                if(field["enabled"]) d.portrait = (SpritesheetID) field["value"];
            }
            else if(field["name"] == "READ_SPEED") {
                d.readSpeed = convertStringToReadSpeed(field["value"]);
            }
            else if(field["name"] == "TEXT") {
                d.text = field["value"];
            }
        }
        d.nextDialogueId = outgoingLinks["nextDialogueId"];
        d.finalDialogueId = outgoingLinks["finalDialogueId"];
        d.nextConversationId = outgoingLinks["nextConversationId"];

        _conversations[d.conversationId].push_back(d);
    }
}

ReadSpeed DialogueParser::convertStringToReadSpeed(std::string s) {
    ReadSpeed speed = ReadSpeed::MEDIUM;
    if(s == "SNAIL") {
        speed = ReadSpeed::SNAIL;
    }
    else if(s == "VERY_SLOW") {
        speed = ReadSpeed::VERY_SLOW;
    }
    else if(s == "SLOW") {
        speed = ReadSpeed::SLOW;
    }
    else if(s == "MEDIUM") {
        speed = ReadSpeed::MEDIUM;
    }
    else if(s == "FAST") {
        speed = ReadSpeed::FAST;
    }
    return speed;
}

Conversation DialogueParser::getConversation(int conversationId) {
    return _conversations[conversationId];
}