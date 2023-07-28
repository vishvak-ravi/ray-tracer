//
// Created by Vishvak Ravi on 7/8/23.
//

#ifndef RAYTRACER_HITTABLE_HPP
#define RAYTRACER_HITTABLE_HPP

#include "rtweekend.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "aabb.hpp"

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    double u;
    double v;
    double t;
    bool front_face; //true iff ray is outside the shape

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() {};
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
    virtual bool bounding_box(double t0, double t1, aabb& output_box) const = 0;
};

#endif //RAYTRACER_HITTABLE_HPP
