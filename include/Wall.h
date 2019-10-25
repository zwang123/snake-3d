#ifndef WALL_H
#define WALL_H

#include <irrlicht.h>
#include "CubicShape.h"

class Wall : public CubicShape
{
    public:
        Wall(irr::scene::ISceneManager *, const irr::f32);

    protected:
        static const irr::video::SColor color;

    private:
};

#endif // WALL_H
