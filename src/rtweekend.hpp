//
// Created by Vishvak Ravi on 7/8/23.
//

#ifndef RAYTRACER_RTWEEKEND_HPP
#define RAYTRACER_RTWEEKEND_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <random>

//Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utilities
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    //Returns random in [0,1)
    return min + (max - min)*random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}

inline int random_int(int low, int up) {
    return static_cast<int>(random_double(low, up+1));
}

#include "ray.hpp"
#include "vec3.hpp"

#endif //RAYTRACER_RTWEEKEND_HPP
