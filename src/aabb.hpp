//
// Created by Vishvak Ravi on 7/12/23.
//

#ifndef RAYTRACER_AABB_HPP
#define RAYTRACER_AABB_HPP

#include "rtweekend.hpp"
#include "hittable.hpp"

struct hit_record;

class aabb {
public:
    point3 minimum;
    point3 maximum;
public:
    aabb() {}
    aabb(const point3& min, const point3& max) : minimum(min), maximum(max) {}
    ~aabb() {}
    point3 min() const { return minimum; }
    point3 max() const { return maximum; }

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
};

bool aabb::hit(const ray &r, double t_min, double t_max, hit_record& rec) const {
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / r.direction()[a];
        auto t0 = (minimum[a] - r.origin()[a]) * invD;
        auto t1 = (maximum[a] - r.origin()[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}

aabb surrounding_box(const aabb& box1, const aabb& box2) {
    point3 min_point = point3(fmin(box1.min().x(), box2.min().x()),
                              fmin(box1.min().y(), box2.min().y()),
                              fmin(box1.min().z(), box2.min().z()));
    point3 max_point = point3(fmax(box1.max().x(), box2.max().x()),
                              fmax(box1.max().y(), box2.max().y()),
                              fmax(box1.max().z(), box2.max().z()));
    return aabb(min_point, max_point);
}

#endif //RAYTRACER_AABB_HPP
