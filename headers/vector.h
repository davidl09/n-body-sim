//
// Created by davidl09 on 9/20/23.
//

#ifndef N_BODY_VECTOR_H
#define N_BODY_VECTOR_H

#include <cstddef>
#include <array>
#include <vector>
#include <cassert>

namespace phys {
    template <size_t ndim, typename T>
    class vector {
    public:
        vector(std::array<T, ndim>&& old) : data(old) {}
        explicit vector(std::array<T, ndim>& old) : data(old) {}

        enum class dims : char {
            x = 0,
            y,
            z,
            t,
            w,
            v, //more dims usually not necessary
        };

        constexpr auto begin() {
            return data.begin();
        }

        constexpr auto end() {
            return data.end();
        }

        /*
         * std::ostream overload for printing
         */

        friend std::ostream& operator<<(std::ostream& s, vector<ndim, T>& v) {
            s << "[";
            for(auto& e : v) {
                s << " " << e << ",";
            }
            s << "]";
            return s;
        }

        /*
         * OP overloads for dot and cross product, and others
         */

        friend vector operator+(vector& a, vector& b) {
            vector ret{{a}};
            for(auto i = 0; i < ndim; i++) {
                ret[i] += b[i];
            }
            return ret;
        }

        friend vector operator-(vector& a, vector& b) {
            vector<ndim, T> ret;
            for(auto i = 0; i < ndim; i++) {
                ret[i] = a[i] - b[i];
            }
            return ret;
        }

        vector& operator-() {
            for(auto& v : this->data) {
                v *= static_cast<T>(-1);
            }
            return *this;
        }

        vector& operator+=(vector& a) {
            for(auto i = 0; i < ndim; i++) {
                data[i] += a[i];
            }
            return *this;
        }

        constexpr auto& operator[] (dims d) {
            return data[static_cast<size_t>(d)];
        }

        constexpr auto& operator[] (size_t d) {
            return data[d];
        }

    private:
        std::array<T, ndim> data;
    };
}




#endif //N_BODY_VECTOR_H
