#ifndef SPHERICALSHAPE_H
#define SPHERICALSHAPE_H

#include <irrlicht.h>
#include <utility>
#include "ISceneNodeUniquePointer.h"


class SphericalShape
: public ISceneNodeUniquePointerNS::UniquePointerBase
    <irr::scene::IMeshSceneNode>
{
    public:
        using base_type =
            ISceneNodeUniquePointerNS::UniquePointerBase
            <irr::scene::IMeshSceneNode>;
        template <typename ...Args>
        explicit SphericalShape(irr::scene::ISceneManager *smgr = nullptr,
                                Args &&... args)
        noexcept : base_type(
        smgr?smgr->addSphereSceneNode(std::forward<Args>(args)...):nullptr)
        {}

        template <typename ...Args>
        explicit SphericalShape(irr::scene::ISceneManager *smgr,
                            const irr::video::SColor &color,
                            Args &&... args)
        noexcept : SphericalShape(smgr, std::forward<Args>(args)...)
        {
            if (*this && (*this)->getMaterialCount())
                (*this)->getMaterial(0).AmbientColor = color;
        }

        template <typename ...Args>
        explicit SphericalShape(irr::scene::ISceneManager *smgr,
                            irr::video::SColor &&color,
                            Args &&... args)
        noexcept : SphericalShape(smgr, std::forward<Args>(args)...)
        {
            if (*this && (*this)->getMaterialCount())
                (*this)->getMaterial(0).AmbientColor = std::move(color);
        }
};


#endif // SPHERICALSHAPE_H
