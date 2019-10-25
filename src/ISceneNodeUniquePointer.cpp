#include "ISceneNodeUniquePointer.h"

namespace ISceneNodeUniquePointerNS {
    void deleter (irr::scene::ISceneNode *node)
    {
        if(node) {
            node->remove();
            node->drop();
        }
    }

//
//void f (const std::unique_ptr<irr::scene::ISceneNode, decltype(deleter)*> &)
//{
//    ;
//}
//
//void deff (std::unique_ptr<irr::scene::ISceneNode>)
//{
//    ;
//}
//
//void g ()
//{
//    static std::unique_ptr<irr::scene::IMeshSceneNode, decltype(deleter)*> pimsn(nullptr, deleter);
//    f(std::move(pimsn));
//}
//
//void defg ()
//{
//    std::unique_ptr<irr::scene::IMeshSceneNode> pimsn;
//    deff(std::move(pimsn));
//}

}
