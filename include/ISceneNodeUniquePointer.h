#ifndef ISCENENODEUNIQUEPOINTER_H
#define ISCENENODEUNIQUEPOINTER_H

#include <irrlicht.h>
#include <memory>
#include <utility>

namespace ISceneNodeUniquePointerNS {
    void deleter (irr::scene::ISceneNode *);
    template <typename T>
    struct UniquePointerBase
        : public std::unique_ptr<T, decltype(deleter)*>
    {
        using base_type = std::unique_ptr<T, decltype(deleter)*>;
        using typename base_type::pointer;

        UniquePointerBase (pointer p = nullptr) noexcept
        : base_type(p, deleter)
        {if (*this) (*this)->grab();}

        template <typename U>
        UniquePointerBase ( UniquePointerBase<U> &&u ) noexcept
        : base_type(std::move(u), deleter)
        {}
    };
}

using ISceneNodeUniquePointer =
ISceneNodeUniquePointerNS::UniquePointerBase<irr::scene::ISceneNode>;

#endif // ISCENENODEUNIQUEPOINTER_H
