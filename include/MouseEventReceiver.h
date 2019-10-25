#ifndef MOUSEEVENTRECEIVER_H
#define MOUSEEVENTRECEIVER_H

#include <irrlicht.h>

class MouseEventReceiver : public irr::IEventReceiver
{
    public:
        MouseEventReceiver();
        bool OnEvent(const irr::SEvent &) override;

    protected:
        enum EMOUSE_CODE {
            LMOUSE = 0, RMOUSE = 2,
            MMOUSE = 1, WHEEL = 3,
            EMOUSE_CODE_COUNT = 4};

        bool MouseIsDown[EMOUSE_CODE_COUNT];
        bool MouseIsShift;
};

#endif // MOUSEEVENTRECEIVER_H
