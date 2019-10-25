#include "Apple.h"

const irr::video::SColor      Apple::appleColor (255, 0, 255, 0);
constexpr irr::f32            Apple::appleRadius;

SphericalShape Apple::random_block() const
{
    auto pos     = random_position();
    bool overlap = true;
    while (overlap) {
        auto p = snake.getBody().cbegin();
        auto pe = snake.getBody().cend();
        for (;p != pe; ++p) {
            if (pos.equals((*p)->getPosition(), TOL)) {
                pos = random_position();
                break;
            }
        }
        overlap = !(p == pe);
    }
    return generate_block(pos);
}
