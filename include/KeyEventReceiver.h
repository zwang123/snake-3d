#ifndef KEYEVENTRECEIVER_H
#define KEYEVENTRECEIVER_H

#include <irrlicht.h>

class KeyEventReceiver : public irr::IEventReceiver
{
    public:
        KeyEventReceiver();
        bool OnEvent(const irr::SEvent &) override;
        bool IsKeyDown(irr::EKEY_CODE) const;
        irr::u32 keyCode() const;

    protected:
        bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif // KEYEVENTRECEIVER_H
