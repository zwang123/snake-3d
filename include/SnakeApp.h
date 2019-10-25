#ifndef SNAKEAPP_H
#define SNAKEAPP_H

#include <irrlicht.h>
#include "KeyEventReceiver.h"

class SnakeApp
{
    public:
        //SnakeApp();
        int run(int, char**);

    protected:
        irr::video::E_DRIVER_TYPE         driverType = irr::video::EDT_NULL;

        irr::IrrlichtDevice              *device = nullptr;
        irr::core::dimension2d<irr::u32>  windowSize;
        KeyEventReceiver                  keyReceiver;

        //irr::core::vector3df              playSize =
        //irr::core::vector3df              (1000.f, 1000.f, 1000.f);
        irr::f32                          playSize = 100.f; // 50.f
        static constexpr irr::u32         key_delay = 100u;

        static constexpr unsigned         init_score_incr = 1u;
        unsigned                          score = 0u;
        unsigned                          score_incr = 1u;

    private:
};

#endif // SNAKEAPP_H
