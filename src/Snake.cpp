#include <ctime>
#include <cmath>
#include <cstdlib>
#include <random>
#include <stdexcept>
#include "Snake.h"

#ifdef _DEBUG
#include <cassert>
#endif // _DEBUG

using namespace irr;

Snake::Distribution     Snake::distribution;
Snake::RandomEngine     Snake::generator(time(nullptr));
const video::SColor     Snake::blockColor(255, 255, 0, 0);

constexpr irr::f32      Snake::block_size;
//const     irr::f32      Snake::TOL = core::ROUNDING_ERROR_f32;

void Snake::reset()
{

    body.clear();
    //TODO Random initial position
    body.push_back(random_block());


//    int tmp = distribution(generator)%3;
//    switch (tmp) {
//    case 0:
//        direction = core::vector3df(1.f,0.f,0.f);
//        break;
//    case 1:
//        direction = core::vector3df(0.f,1.f,0.f);
//        break;
//    case 2:
//        direction = core::vector3df(0.f,0.f,1.f);
//        break;
//    default:
//        throw std::logic_error("Programming error");
//    }
//    tmp = distribution(generator)%2 ? 1 : -1;
//    direction *= tmp;

    direction = -1.f * vector2direction(body.front()->getPosition());

//    //prev_direction = direction;
    updateDirectionInfo();


    move_every = init_interval;
    acc = 1u;

    last_move = clock::now();
}

bool Snake::is_died() const
{
    //for (const auto &a : body) {
    for (size_type i = 0; i != body.size(); ++i) {
        const auto &a = body[i];
        const auto pos = a->getPosition();
        if (pos.X < -bound || pos.X > bound
         || pos.Y < -bound || pos.Y > bound
         || pos.Z < -bound || pos.Z > bound)
            return true;
        for (size_type j = i + 1; j < body.size(); ++j) {
            if (pos.equals(body[j]->getPosition(), TOL))
                return true;
        }
    }
    return false;
}

#ifdef _DEBUG
#include <iostream>
#include "vectorExt.h"
#endif // _DEBUG

bool Snake::move(const core::vector3df &applePos)
{
    bool rtn = false;
    if (calDuration(last_move) >= move_every) {
        #ifdef _DEBUG
        assert(body.size());
        #endif // _DEBUG
        const auto new_pos = body.back()->getPosition()
                           + direction * movement_step;
        body.push_back(generate_block(new_pos));
        if (new_pos.equals(applePos, TOL)) {
            updateInterval();
            rtn = true;
        } else {
            body.pop_front();
            rtn = false;
        }

        #ifdef _DEBUG
        std::cout << applePos << std::endl;
        std::cout << new_pos  << std::endl;
        #endif // _DEBUG

        updateDirectionInfo();
        last_move = clock::now();
    }
    return rtn;
}

void Snake::changeDirection()
{
    core::vector3df new_direc;
    if (!getKeyDirection(new_direc) ||
        new_direc.equals(prev_inv_direction, TOL)) {
        return;
    }
    immediateMove();
    direction = new_direc;
}

core::vector3df Snake::vector2direction(const core::vector3df &vect)
{
    core::vector3df direct;
    core::vector3df absVect (std::abs(vect.X), std::abs(vect.Y),
                             std::abs(vect.Z));
    if (absVect.X < absVect.Y) {
        if (absVect.Y < absVect.Z)
            direct.Z = sign(vect.Z);
        else
            direct.Y = sign(vect.Y);
    } else if (absVect.X < absVect.Z)
        direct.Z = sign(vect.Z);
    else
        direct.X = sign(vect.X);
    return direct;
}

core::vector3df Snake::vector2direction(const core::vector3df &vect,
                                        const core::vector3df &prev_direct)
{
    core::vector3df direct;
    core::vector3df absVect (std::abs(vect.X), std::abs(vect.Y),
                             std::abs(vect.Z));
    if (std::abs(prev_direct.X) > TOL) {
        if (absVect.Y < absVect.Z)
            direct.Z = sign(vect.Z);
        else
            direct.Y = sign(vect.Y);
    } else if (std::abs(prev_direct.Y) > TOL) {
        if (absVect.X < absVect.Z)
            direct.Z = sign(vect.Z);
        else
            direct.X = sign(vect.X);
    } else {
        if (absVect.X < absVect.Y)
            direct.Y = sign(vect.Y);
        else
            direct.X = sign(vect.X);
    }
    return direct;
}


#ifdef _DEBUG
//#include <iostream>
#endif // _DEBUG

// Has priority
bool Snake::getKeyDirection(core::vector3df &direc) const
{
//    const core::vector3df upVector  = core::vector3df(1,1,1); //camera->getUpVector();
//    const core::vector3df outVector = -1.f * upVector;// camera->getRotation().
//                                             // rotationToDirection();
    const core::vector3df upVector  = camera->getUpVector();
    const core::vector3df outVector = -1.f * camera->getRotation().
                                             rotationToDirection();


    const core::vector3df yVector   = vector2direction(upVector);
    const core::vector3df zVector   = vector2direction(outVector, yVector);
    const core::vector3df xVector   = zVector.crossProduct(yVector);

    #ifdef _DEBUG
//    std::cout << xVector << yVector << zVector << std::endl;
//    std::cout << outVector.X << outVector.Y << outVector.Z << std::endl;
//    std::cout << zVector.X << zVector.Y << zVector.Z << std::endl;
//    std::cout << upVector.X << upVector.Y << upVector.Z << std::endl;
//    std::cout << yVector.X << yVector.Y << yVector.Z << std::endl;
//    std::cout << std::endl;
    #endif // _DEBUG
    if (keyReceiver.IsKeyDown(KEY_KEY_W) ||
        keyReceiver.IsKeyDown(KEY_UP))
        direc = yVector;
    else if (keyReceiver.IsKeyDown(KEY_KEY_S) ||
             keyReceiver.IsKeyDown(KEY_KEY_X) ||
             keyReceiver.IsKeyDown(KEY_DOWN))
        direc = -1.f * yVector;
    else if (keyReceiver.IsKeyDown(KEY_KEY_A) ||
             keyReceiver.IsKeyDown(KEY_LEFT))
        direc = -1.f * xVector;
    else if (keyReceiver.IsKeyDown(KEY_KEY_D) ||
             keyReceiver.IsKeyDown(KEY_RIGHT))
        direc = xVector;
    else if (keyReceiver.IsKeyDown(KEY_KEY_Z) ||
             keyReceiver.IsKeyDown(KEY_KEY_C))
        direc = zVector;
    else if (keyReceiver.IsKeyDown(KEY_KEY_E) ||
             keyReceiver.IsKeyDown(KEY_KEY_Q))
    #ifdef _DEBUG
    {
//        std::cout << __LINE__ << std::endl;
    #endif // _DEBUG
        direc = -1.f * zVector;
    #ifdef _DEBUG
    }
    #endif // _DEBUG
    else
        return false;
    return true;
}
