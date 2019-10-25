#include "EventReceiver.h"

using namespace irr;

EventReceiver::EventReceiver()
: KeyIsDown {false}
, MouseIsDown {false}
, MouseIsShift (false)
{
}

bool EventReceiver::OnEvent(const SEvent &event)
{
    if (event.EventType == EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    if (event.EventType == EET_MOUSE_INPUT_EVENT) {
        MouseIsDown[LMOUSE] = event.MouseInput.isLeftPressed();
        MouseIsDown[MMOUSE] = event.MouseInput.isMiddlePressed();
        MouseIsDown[RMOUSE] = event.MouseInput.isRightPressed();
        MouseIsShift = event.MouseInput.Shift;
    }
    /*
        switch(event.MouseInput.Event)
        {
        case EMIE_LMOUSE_PRESSED_DOWN:
            MouseIsDown[0] = true;
            break;
        case EMIE_RMOUSE_PRESSED_DOWN:
            MouseKeys[2] = true;
            break;
        case EMIE_MMOUSE_PRESSED_DOWN:
            MouseKeys[1] = true;
            break;
        case EMIE_LMOUSE_LEFT_UP:
            MouseKeys[0] = false;
            break;
        case EMIE_RMOUSE_LEFT_UP:
            MouseKeys[2] = false;
            break;
        case EMIE_MMOUSE_LEFT_UP:
            MouseKeys[1] = false;
            break;
        case EMIE_MOUSE_MOVED:
            MousePos = CursorControl->getRelativePosition();
            break;
        case EMIE_MOUSE_WHEEL:
        case EMIE_LMOUSE_DOUBLE_CLICK:
        case EMIE_RMOUSE_DOUBLE_CLICK:
        case EMIE_MMOUSE_DOUBLE_CLICK:
        case EMIE_LMOUSE_TRIPLE_CLICK:
        case EMIE_RMOUSE_TRIPLE_CLICK:
        case EMIE_MMOUSE_TRIPLE_CLICK:
        case EMIE_COUNT:
            return false;
        }
	return true;*/
    return false;
}
