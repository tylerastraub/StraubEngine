#pragma once

#include "SpritesheetID.h"
#include "ReadSpeed.h"

#include <string>

struct Dialogue {
    // id/info
    int id = -1;
    int conversationId = -1;
    bool isRoot = false;

    // fields
    std::string speakerName = ""; // leave blank to disable
    SpritesheetID portrait = SpritesheetID::NOVAL; // leave at SpritesheetID::NOVAL to disable
    ReadSpeed readSpeed = ReadSpeed::MEDIUM;
    std::string text = "";

    // outgoing links
    int nextDialogueId = -1;
    int finalDialogueId = -1;
    int nextConversationId = -1;

    bool operator>(const Dialogue& rhs) const {
        return id > rhs.id;
    }
};