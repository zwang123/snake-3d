#ifndef CUBICSHAPE_H
#define CUBICSHAPE_H

#include <irrlicht.h>
#include <utility>
#include "ISceneNodeUniquePointer.h"


class CubicShape
: public ISceneNodeUniquePointerNS::UniquePointerBase
    <irr::scene::IMeshSceneNode>
{
    public:
        using base_type =
            ISceneNodeUniquePointerNS::UniquePointerBase
            <irr::scene::IMeshSceneNode>;
        template <typename ...Args>
        explicit CubicShape(irr::scene::ISceneManager *smgr = nullptr,
                            Args &&... args)
        noexcept : base_type(
        smgr?smgr->addCubeSceneNode(std::forward<Args>(args)...):nullptr)
        {}

        template <typename ...Args>
        explicit CubicShape(irr::scene::ISceneManager *smgr,
                            const irr::video::SColor &color,
                            Args &&... args)
        noexcept : CubicShape(smgr, std::forward<Args>(args)...)
        {
            if (*this && (*this)->getMaterialCount())
                (*this)->getMaterial(0).AmbientColor = color;
        }

        template <typename ...Args>
        explicit CubicShape(irr::scene::ISceneManager *smgr,
                            irr::video::SColor &&color,
                            Args &&... args)
        noexcept : CubicShape(smgr, std::forward<Args>(args)...)
        {
            if (*this && (*this)->getMaterialCount())
                (*this)->getMaterial(0).AmbientColor = std::move(color);
        }
};


#endif // CUBICSHAPE_H
