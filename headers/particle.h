//
// Created by davidl09 on 9/20/23.
//

#ifndef N_BODY_PARTICLE_H
#define N_BODY_PARTICLE_H

#include <mutex>

#include "vector.h"

namespace phys {

    template<FloatingPoint T>
    struct particle {

        particle(T mass_, vector<3, T> position, vector<3, T> velocity = {0,0,0}, vector<3, T> acceleration = {0,0,0}) : mass(mass_), pos{position}, vel(velocity), acl(acceleration) {}
        particle(const particle& p) : mass(p.mass), pos(p.pos), vel(p.vel), acl(p.acl) {};
        particle(particle&& p) noexcept : mass(std::move(p.mass)), pos(std::move(p.pos)), vel(std::move(p.vel)), acl(std::move(p.acl)) {};

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

        T mass;
        vector<3, T> pos;
        vector<3, T> vel;
        vector<3, T> acl;
    };

} // phys

#endif //N_BODY_PARTICLE_H
