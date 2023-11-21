//
// Created by davidl09 on 9/21/23.
//

#ifndef N_BODY_NBODY_H
#define N_BODY_NBODY_H

#include <random>
#include <chrono>
#include <execution>
#include <algorithm>

#include "vector.h"
#include "particle.h"

using phys::vector<3, double>::dims::x;
using phys::vector<3, double>::dims::y;
using phys::vector<3, double>::dims::z;

namespace phys {

    template<FloatingPoint T>
    class nbodysim {
    public:
        nbodysim
        (size_t num_objects, T dt, uint64_t upper_m_bound, uint64_t lower_m_bound, T G_const = 6.6743e-11, uint64_t pos_rad = 100)
        : delta_t(dt), G(G_const) {

            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count()); //seed random engine
            random_m_gen = std::uniform_real_distribution<>(static_cast<T>(lower_m_bound), static_cast<T>(upper_m_bound));
            random_pos_gen = std::uniform_real_distribution<>(0.0, static_cast<T>(pos_rad));

            data.reserve(num_objects);
            for (auto i = 0; i < num_objects; i++) {
                data.push_back(particle<T>(
                        random_m_gen(generator),
                        {{
                            random_pos_gen(generator),
                            random_pos_gen(generator),
                            random_pos_gen(generator),
                        }}
                        ));
            }

            fill_pairwise_vec();
            
        }

        void add_particle(const particle<T>& p) {
            data.push_back(p);
            for (auto i = data.begin(); i != data.end() - 1; i++) {
                pairs.emplace_back(&(*i), &data.back());
            }
        }

        void run(T seconds) {
            auto num_steps = static_cast<size_t>(seconds / delta_t);
            for(auto i = 0; i < num_steps; i++) {
                calculate_step_st();
            }
        }

        void print() {
            for(auto i = data.begin(); i != data.end(); i++) {
                std::cout << std::distance(data.begin(), i) << " Pos: " << i->pos << "\n";
            }
        }

    private:

        [[nodiscard]] auto force(std::pair<particle<T>*, particle<T>*>& pair) const {
            //F = G*m1*m2/(r^2)
            return G * pair.first->mass * pair.second->mass / (pair.second->pos - pair.first->pos).abs_squared();
        };


        void fill_pairwise_vec() noexcept {
            pairs.erase(pairs.begin(), pairs.end());
            if(pairs.empty()) return;
            for(auto i = data.begin(); i != data.end() - 1; i++) {
                for(auto j = data.begin() + std::distance(data.begin(), i) + 1; j != data.end(); j++) {
                    pairs.emplace_back(&(*i), &(*j));
                }
            }
        }

        void calculate_step_st() {
            auto calculate_force_step = [&](std::pair<particle<T>*, particle<T>*> pair) {
                auto force_magnitude = force(pair);

                // unit distance vector
                auto pos_unit_vector = (pair.second->pos - pair.first->pos).unit_v();
                pos_unit_vector /= pos_unit_vector.abs();

                auto force_1_v = pos_unit_vector * force_magnitude;

                //acceleration
                pair.first->acl += force_1_v * delta_t;
                pair.second->acl -= force_1_v * delta_t;
            };

            //velocity
            auto calculate_vel_step = [&](std::pair<particle<T>*, particle<T>*> pair) {
                pair.first->vel += pair.first->acl * delta_t;
                pair.second->vel += pair.second->acl * delta_t;
            };
            //position
            auto calculate_pos_step = [&](std::pair<particle<T>*, particle<T>*> pair) {
                pair.first->pos += pair.first->vel * delta_t;
                pair.second->pos += pair.second->vel * delta_t;
            };

            std::for_each(std::execution::par_unseq, pairs, calculate_force_step);
            std::for_each(std::execution::par_unseq, pairs, calculate_vel_step);
            std::for_each(std::execution::par_unseq, pairs, calculate_pos_step);
        }

        std::vector<std::pair<particle<T>*, particle<T>*>> pairs;
        std::vector<particle<T>> data;
        T delta_t; //time granularity
        T G; //Gravitational constant

        std::uniform_real_distribution<> random_m_gen;
        std::uniform_real_distribution<> random_pos_gen;
    };

} // phys

#endif //N_BODY_NBODY_H
