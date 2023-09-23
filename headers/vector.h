//
// Created by davidl09 on 9/20/23.
//

#ifndef N_BODY_VECTOR_H
#define N_BODY_VECTOR_H

#include <cstddef>
#include <iostream>
#include <array>
#include <vector>
#include <cassert>
#include <cmath>

namespace phys {
    template <size_t ndim, typename T>
    class vector {
    public:
        vector(std::array<T, ndim>&& old) : data(old) {}
        explicit vector(std::array<T, ndim>& old) : data(old) {}

        constexpr vector(const vector& vector1) noexcept : data(vector1.data) {}

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

        constexpr auto dim() {
            return data.size();
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

        constexpr bool operator==(vector& b) {
            for(auto i = 0; i < dim(); i++) {
                if(b[i] != this->data[i]) return false;
            }
            return true;
        }

        constexpr vector operator+(vector& b) const{
            vector ret{{*this}};
            for(auto i = 0; i < ndim; i++) {
                ret[i] += b[i];
            }
            return ret;
        }

        constexpr vector operator-(vector& b) const{
            vector ret{{*this}};
            for(auto i = 0; i < ndim; i++) {
                ret[i] -= b[i];
            }
            return ret;
        }

        vector& operator-() {
            for(auto& v : this->data) {
                v *= -v;
            }
            return *this;
        }

        vector& operator+=(vector& a) {
            for(auto i = 0; i < ndim; i++) {
                data[i] += a[i];
            }
            return *this;
        }

        vector& operator+=(vector&& a) {
            for(auto i = 0; i < ndim; i++) {
                data[i] += a[i];
            }
            return *this;
        }

        vector& operator-=(vector& a) {
            for(auto i = 0; i < ndim; i++) {
                data[i] -= a[i];
            }
            return *this;
        }

        vector operator*(T& a) const{
            vector<ndim, T> ret{*this};
            for(auto v : ret) {
                v *= a;
            }
            return ret;
        }

        vector operator*(T&& a) const{
            vector<ndim, T> ret{*this};
            for(auto v : ret) {
                v *= a;
            }
            return ret;
        }

        vector& operator*=(T& a) {
            for(auto& e : data) {
                e *= a;
            }
            return *this;
        }

        vector& operator*=(T&& a) {
            for(auto& e : data) {
                e *= a;
            }
            return *this;
        }

        vector operator/(T& a) {
            vector ret{*this};
            for(auto& e : ret) {
                e /= a;
            }
            return ret;
        }

        vector operator/(T&& a) {
            vector ret{*this};
            for(auto& e : ret) {
                e /= a;
            }
            return ret;
        }

        vector& operator/=(T& a) {
            for(auto& e : data) {
                e /= a;
            }
            return *this;
        }

        vector& operator/=(const T& a) {
            for(auto& e : data) {
                e /= a;
            }
            return *this;
        }

        constexpr T abs() const{
            return std::sqrt(abs_squared());
        }

        constexpr T abs_squared() const {
            T ret = 0;
            for(auto& e : this->data) {
                ret += std::pow(e, 2);
            }
            return ret;
        }

        constexpr auto unit_v() const {
            vector ret{*this};
            return ret / ret.abs();
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
