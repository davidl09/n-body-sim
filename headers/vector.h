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
#include <type_traits>
#include <cstdint>
#include <algorithm>
#include <ranges>

template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

namespace phys {
    template <size_t ndim, FloatingPoint T>
    class vector {
    public:
        explicit constexpr vector(std::array<T, ndim>&& old) : data(std::move(old)) {}
        explicit constexpr vector(const std::array<T, ndim>& old) : data(old) {}
        constexpr vector(T args...) : data{{args}} {}

        constexpr vector(const vector& old) noexcept : data{old.data} {}
        constexpr vector(vector && old)  noexcept : data(std::move(old.data)) {}

        constexpr vector& operator=(const vector& other) {
            data = other.data;
            return *this;
        };

        constexpr vector& operator=(vector&& old) {
            data = std::move(old.data);
            return *this;
        }


        enum class dims : std::uint8_t {
            x = 0,
            y,
            z,
            t,
            w,
            v, //more dims usually not necessary
        };

        using dims::x;
        using dims::y;
        using dims::z;
        using dims::t;
        using dims::w;
        using dims::v;

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

        constexpr bool operator==(const vector& b) {
            for(auto i = 0; i < dim(); i++) {
                if(b[i] != this->data[i]) return false;
            }
            return true;
        }

        constexpr vector operator+(const vector& b) const{
            vector ret{{*this}};
            for(auto i = 0; i < ndim; i++) {
                ret[i] += b[i];
            }
            return ret;
        }

        constexpr vector operator-(const vector& b) const{
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

        vector& operator-=(vector&& a) {
            for(auto i = 0; i < ndim; i++) {
                data[i] -= a[i];
            }
            return *this;
        }

        vector operator*(T& a) const{
            vector<ndim, T> ret{*this};
            for(auto& v : ret) {
                v *= a;
            }
            return ret;
        }

        vector operator*(T&& a) const{
            vector<ndim, T> ret{*this};
            for(auto& v : ret) {
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

        constexpr vector<3, T> operator*(const vector<3, T>& rhs) {
            static_assert(ndim == 3);
            vector<3, T> result;
            result[x] = this->data[y] * rhs[z] - this->data[z] * data[y];
            result[y] = -(this->data[x] * rhs[z] - this->data[z] * data[x]);
            result[z] = this->data[x] * rhs[y] - this->data[2] * data[x];
            return std::move(result);
        }

        constexpr T dot(const vector& rhs) {
            T result;
            for (auto i = x; i < ndim; i++) {
                result += this->data[i] * rhs[i];
            }
            return std::move(result);
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
