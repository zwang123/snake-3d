#ifndef CAMERA_H
#define CAMERA_H

#include <irrlicht.h>
#include <utility>
#include "ISceneNodeUniquePointer.h"

class KeyEventReceiver;

class Camera
//: public ISceneNodeUniquePointerNS::UniquePointerBase

//         <irr::scene::ICameraSceneNode>
{
    public:
        using camera_ptr =
            ISceneNodeUniquePointerNS::UniquePointerBase
            <irr::scene::ICameraSceneNode>;

        template <typename ...Args>
        explicit Camera(irr::scene::ISceneManager *smgr,
                        const KeyEventReceiver    &keyReceiver,
                        Args                  &&...args)
        noexcept : camera(
        smgr?smgr->addCameraSceneNodeMaya(std::forward<Args>(args)...):nullptr)
        , keyReceiver(keyReceiver)
        {}

    protected:
        const camera_ptr         camera;
        const KeyEventReceiver & keyReceiver;

};

#endif // CAMERA_H
