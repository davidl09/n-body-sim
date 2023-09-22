//
// Created by davidl09 on 9/20/23.
//

#ifndef N_BODY_PARTICLE_H
#define N_BODY_PARTICLE_H

#include <mutex>

#include "vector.h"

namespace phys {

    template <typename T>
    concept FloatingPoint = std::is_floating_point_v<T>;

    template<FloatingPoint T>
    struct particle {
        //big five

        particle(T mass_, vector<3, double> position, vector<3, double> velocity = {{0,0,0}}) : mass(mass_), pos(position), vel(velocity) {}
        particle(const particle& p) : mass(p.mass), pos(p.pos), vel(p.vel) {};
        particle(particle&& p) noexcept : mass(p.mass), pos(p.pos), vel(p.vel) {};

        particle& operator=(const particle& p) {
            mass = p.mass;
            pos = p.pos;
            vel = p.vel;
        };

        particle& operator=(particle&& p) noexcept {
            mass = p.mass;
            pos = p.pos;
            vel = p.vel;
        }

        std::mutex m_lock;
        T mass;
        vector<3, T> pos;
        vector<3, T> vel;
        vector<3, T> acl;
    };

} // phys

#endif //N_BODY_PARTICLE_H
