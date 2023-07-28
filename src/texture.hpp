//
// Created by Vishvak Ravi on 7/15/23.
//

#ifndef RAYTRACER_TEXTURE_HPP
#define RAYTRACER_TEXTURE_HPP

#include "rtweekend.hpp"

class texture {
public:
    virtual ~texture() {};
    virtual color value(double u, double v, const point3& p) const = 0;
};

class solid_color : public texture {
public:
    color color_value;
public:
    solid_color();
    solid_color(color c) : color_value(c) {}
    solid_color(double r, double g, double b) : color_value(color(r, g, b)) {}
    virtual color value(double u, double v, const point3& p) const override {
        return color_value;
    }
};


#endif //RAYTRACER_TEXTURE_HPP
