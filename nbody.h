//
// Created by davidl09 on 9/21/23.
//

#ifndef N_BODY_NBODY_H
#define N_BODY_NBODY_H

#include <random>
#include <chrono>

#include "vector.h"
#include "particle.h"

namespace phys {

    class nbodysim {
    public:
        nbodysim
        (size_t num_objects, double dt, uint64_t upper_m_bound, uint64_t lower_m_bound, double G_const = 6.6743e-11, uint64_t pos_rad = 100)
        : delta_t(dt), G(G_const) {

            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count()); //seed random engine
            random_m_gen = std::uniform_real_distribution<>(static_cast<double>(lower_m_bound), static_cast<double>(upper_m_bound));
            random_pos_gen = std::uniform_real_distribution<>(0.0, static_cast<double>(pos_rad));

            data.reserve(num_objects);
            for (auto i = 0; i < num_objects; i++) {
                data.push_back(particle<double>(
                        random_m_gen(generator),
                        {{
                            random_pos_gen(generator),
                            random_pos_gen(generator),
                            random_pos_gen(generator),
                        }}
                        ));
            }
            
        }

        void add_particle(const particle<double>& p) {
            data.emplace_back(p);
        }

        void add_particle(double mass, const vector<3, double>& position, vector<3, double> velocity = {{0,0,0}}) {
            data.emplace_back(mass, position, velocity);

            for (auto i = data.begin(); i != data.end() - 1; i++) {
                pairs.emplace_back(&(*i), &data.back());
            }
        }

        template<typename T>
         void fill_pairwise_vec() noexcept {
            std::vector<std::pair<T, T>> result;
            result.erase();
            result.reserve(data.size() * data.size());

            for(auto i = data.begin(); i != data.end() - 1; i++) {
                for(auto j = data.begin() + std::distance(data.begin(), i) + 1; j != data.end(); j++) {
                    pairs.emplace_back(&(*i), &(*j));
                }
            }

            return result;
        }

    private:
        std::vector<std::pair<particle<double>*, particle<double>*>> pairs;
        std::vector<particle<double>> data;
        double delta_t; //time granularity
        double G; //Gravitational constant

        std::uniform_real_distribution<> random_m_gen;
        std::uniform_real_distribution<> random_pos_gen;
    };

} // phys

#endif //N_BODY_NBODY_H
