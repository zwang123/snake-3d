#include "Wall.h"

using namespace irr;

const video::SColor Wall::color (255, 75, 75, 75);

Wall::Wall(scene::ISceneManager *smgr, irr::f32 size)
: CubicShape(smgr, color, size, nullptr, -1, core::vector3df(0.f, 0.f, 0.f))
{
    if (*this) (*this)->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}
