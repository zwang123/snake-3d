#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <irrlicht.h>

class EventReceiver : public irr::IEventReceiver
{
    public:
        EventReceiver();
        bool OnEvent(const irr::SEvent &) override;

    protected:
        enum EMOUSE_CODE {
            LMOUSE = 0, RMOUSE = 2,
            MMOUSE = 1, WHEEL = 3,
            EMOUSE_CODE_COUNT = 4};

        bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
        bool MouseIsDown[EMOUSE_CODE_COUNT];
        bool MouseIsShift;
};

#endif // EVENTRECEIVER_H
