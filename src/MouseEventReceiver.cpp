#include "MouseEventReceiver.h"

using namespace irr;

MouseEventReceiver::MouseEventReceiver()
: MouseIsDown {false}
, MouseIsShift (false)
{
}

bool MouseEventReceiver::OnEvent(const SEvent &event)
{
    if (event.EventType == EET_MOUSE_INPUT_EVENT) {
        MouseIsDown[LMOUSE] = event.MouseInput.isLeftPressed();
        MouseIsDown[MMOUSE] = event.MouseInput.isMiddlePressed();
        MouseIsDown[RMOUSE] = event.MouseInput.isRightPressed();
        MouseIsShift = event.MouseInput.Shift;

        switch(event.MouseInput.Event)
        {
        case EMIE_LMOUSE_PRESSED_DOWN:
            MouseIsDown[LMOUSE] = true;
            break;
        case EMIE_RMOUSE_PRESSED_DOWN:
            MouseIsDown[RMOUSE] = true;
            break;
        case EMIE_MMOUSE_PRESSED_DOWN:
            MouseIsDown[MMOUSE] = true;
            break;
        case EMIE_LMOUSE_LEFT_UP:
            MouseIsDown[LMOUSE] = false;
            break;
        case EMIE_RMOUSE_LEFT_UP:
            MouseIsDown[RMOUSE] = false;
            break;
        case EMIE_MMOUSE_LEFT_UP:
            MouseIsDown[MMOUSE] = false;
            break;
        case EMIE_MOUSE_MOVED:
            //MouseIsShift = true;
            //MousePos = CursorControl->getRelativePosition();
            break;
        case EMIE_MOUSE_WHEEL:
        case EMIE_LMOUSE_DOUBLE_CLICK:
        case EMIE_RMOUSE_DOUBLE_CLICK:
        case EMIE_MMOUSE_DOUBLE_CLICK:
        case EMIE_LMOUSE_TRIPLE_CLICK:
        case EMIE_RMOUSE_TRIPLE_CLICK:
        case EMIE_MMOUSE_TRIPLE_CLICK:
        case EMIE_COUNT:
        default:
            return false;
        }
        return true;
    }
    return false;
}
