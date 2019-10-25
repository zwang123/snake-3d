#ifndef APPLE_H
#define APPLE_H

#include <irrlicht.h>
#include "Snake.h"
#include "SphericalShape.h"

class Apple
{
    public:
        using Distribution = Snake::Distribution;
        using RandomEngine = Snake::RandomEngine;


        static constexpr irr::f32 movement_step = Snake::movement_step;
        static constexpr irr::f32 appleRadius   = Snake::block_size * .5;
        static constexpr irr::f32 TOL           = Snake::TOL;


        Apple(irr::scene::ISceneManager    * const smgr,
              const Snake                        & snake)
        : smgr(smgr)
        , snake(snake)
        , bound(snake.getHalfBoundary())
        , point(snake.getNumGridPoints())
        {reset();}

        const SphericalShape &getApple() const {return apple;}

        void reset() { apple = random_block(); }

    private:

        static constexpr Distribution      &distribution = Snake::distribution;
        static constexpr RandomEngine      &generator    = Snake::generator;
        static const irr::video::SColor     appleColor;
        //static irr::IRandomizer randomizer;

        irr::scene::ISceneManager   * const smgr;
        const Snake                       & snake;
        const irr::f32                      bound;
        const irr::u32                      point;

        SphericalShape                      apple;



        irr::core::vector3df random_position() const
        {
            return irr::core::vector3df(
                distribution(generator)%point * movement_step - bound,
                distribution(generator)%point * movement_step - bound,
                distribution(generator)%point * movement_step - bound);
        }

        SphericalShape generate_block(const irr::core::vector3df &pos) const
        {
            return SphericalShape(smgr, appleColor, appleRadius,
                                  16, nullptr, -1, pos);
        }

        SphericalShape generate_block(const irr::f32 x, const irr::f32 y,
                                      const irr::f32 z) const
        {
            return generate_block(irr::core::vector3df(x, y, z));
        }

        SphericalShape random_block() const;
};

#endif // APPLE_H
