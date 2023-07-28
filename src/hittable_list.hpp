//
// Created by Vishvak Ravi on 7/8/23.
//

#ifndef RAYTRACER_HITTABLE_LIST_HPP
#define RAYTRACER_HITTABLE_LIST_HPP

#include "hittable.hpp"

#include <vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
    vector<shared_ptr<hittable>> objects;
public:
    hittable_list() {};
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    bool bounding_box(double t0, double t1, aabb& output_box) const override;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

bool hittable_list::bounding_box(double t0, double t1, aabb &output_box) const {
    if (objects.empty()) { return false; }

    bool first_object = true;

    aabb temp_box;
    for (const auto& object : objects) {
        if (!object->bounding_box(t0, t1, temp_box)) return false;
        output_box = surrounding_box(temp_box, object);
        first_object = false;
    }
    output_box = temp_box;
    return true;
}

#endif //RAYTRACER_HITTABLE_LIST_HPP
