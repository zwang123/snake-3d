#include "KeyEventReceiver.h"
//#include <algorithm>
//#include <iterator>

using namespace irr;

KeyEventReceiver::KeyEventReceiver()
: KeyIsDown {false}
{
}

bool KeyEventReceiver::OnEvent(const SEvent &event)
{
    if (event.EventType == EET_KEY_INPUT_EVENT) {
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return true;
    }
    return false;
}

bool KeyEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

// Caveat: find first occurrence!
u32 KeyEventReceiver::keyCode() const
{
    for (u32 i = 0; i != KEY_KEY_CODES_COUNT; ++i)
        if (KeyIsDown[i]) return i;
    return KEY_KEY_CODES_COUNT;
//    return std::find(std::begin(KeyIsDown), std::end(KeyIsDown), true)
//         - KeyIsDown;
}
