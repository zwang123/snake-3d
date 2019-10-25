#ifndef SNAKE_H
#define SNAKE_H

#include <cmath>
#include <chrono>
#include <deque>
#include <irrlicht.h>
#include <random>
#include "CubicShape.h"
#include "KeyEventReceiver.h"

class Snake
{
    public:
        using Distribution = std::uniform_int_distribution<int>;
        using RandomEngine = std::default_random_engine;

        using body_type = std::deque<CubicShape>;
        using size_type = body_type::size_type;

        using clock = std::chrono::high_resolution_clock;
        using duration = std::chrono::microseconds;
        using interval_t = duration::rep;
        // TODO use internal clock!
//        using interval_t = irr::u32;

///////////////////////////////////////////////////////////////////////////////

        static constexpr irr::f32   movement_step = 10.0f;
        static constexpr irr::f32   block_size    = 10.0f;
        static constexpr interval_t init_interval = 524288;
        static constexpr irr::f32   TOL           = 1.e-4f;
        static Distribution         distribution;
        static RandomEngine         generator;

///////////////////////////////////////////////////////////////////////////////

        Snake(irr::scene::ISceneManager    * const smgr,
              const KeyEventReceiver             & keyReceiver,
              irr::scene::ICameraSceneNode * const camera,
              const irr::f32                       playSize)
        : smgr(smgr)
        , keyReceiver(keyReceiver)
        , camera(camera)
        , bound ((playSize - block_size) * .5 + TOL)
        , point(static_cast<irr::u32>(bound * 2.f / movement_step) + 1)
        {reset();}

        const body_type &getBody() const {return body;}

        interval_t getMoveInterval() const {return move_every;}

        unsigned accelerationRate() const
        {return acc;}

        irr::f32 getHalfBoundary() const {return bound;}
        irr::u32 getNumGridPoints() const {return point;}

///////////////////////////////////////////////////////////////////////////////

        void reset();
        bool is_died() const;
        bool move(const irr::core::vector3df &);
        void changeDirection();

    private:
        static constexpr size_type           growEvery = 5;
        static const irr::video::SColor      blockColor;
        //static irr::IRandomizer randomizer;

///////////////////////////////////////////////////////////////////////////////

        static interval_t calDuration(const clock::time_point &ref)
        {
            return std::chrono::duration_cast<duration>
                (clock::now()-ref).count();
        }

        static irr::f32 sign(const irr::f32 x)
        {
            return std::signbit(x) ? -1.f : 1.f;
        }

        static irr::core::vector3df
        vector2direction(const irr::core::vector3df &);

        static irr::core::vector3df
        vector2direction(const irr::core::vector3df &,
                         const irr::core::vector3df &);

///////////////////////////////////////////////////////////////////////////////

        irr::scene::ISceneManager    * const smgr;
        const KeyEventReceiver             & keyReceiver;
        irr::scene::ICameraSceneNode * const camera;
        const irr::f32                       bound;
        const irr::u32                       point;


        body_type            body;
        irr::core::vector3df direction, prev_inv_direction;
        interval_t           move_every;
        unsigned             acc;
        clock::time_point    last_move;

///////////////////////////////////////////////////////////////////////////////

        void updateDirectionInfo()
        {
            prev_inv_direction = -1.f * direction;
        }

        void updateInterval()
        {
            if (body.size() % growEvery == 1) {
                move_every = init_interval / (++acc);
//                move_every = init_interval / (acc*=2);
            }
        }

        void immediateMove()
        {
            last_move -= duration(move_every);
        }

        CubicShape generate_block(const irr::core::vector3df &pos) const
        {
            return CubicShape(smgr, blockColor, block_size, nullptr, -1, pos);
        }

        CubicShape generate_block(const irr::f32 x, const irr::f32 y,
                                  const irr::f32 z) const
        {
            return generate_block(irr::core::vector3df(x, y, z));
        }

        CubicShape random_block() const
        {
            return generate_block(
                       distribution(generator)%point * movement_step - bound,
                       distribution(generator)%point * movement_step - bound,
                       distribution(generator)%point * movement_step - bound);
        }

        bool getKeyDirection(irr::core::vector3df &) const;
};


#endif // SNAKE_H
