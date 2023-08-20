#pragma once

#include "SpritesheetID.h"
#include "Dialogue.h"

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

using json = nlohmann::json;
using Conversation = std::vector<Dialogue>;

class DialogueParser {
public:
    DialogueParser() = default;
    ~DialogueParser() = default;

    void openJson(std::string filePath);

    Conversation getConversation(int conversationId);

private:
    ReadSpeed convertStringToReadSpeed(std::string s);

    json _data;

    /**
     * Hash table of conversations accessed using conversationId.
     */
    std::unordered_map<int, Conversation> _conversations;

};