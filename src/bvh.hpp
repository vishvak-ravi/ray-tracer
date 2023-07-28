//
// Created by Vishvak Ravi on 7/13/23.
//

#ifndef RAYTRACER_BVH_HPP
#define RAYTRACER_BVH_HPP

#include "rtweekend.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include <algorithm>

class bvh_node : public hittable {
public:
    aabb box;
    shared_ptr<hittable> left;
    shared_ptr<hittable> right;
public:
    bvh_node();
    bvh_node(const hittable_list& list, double time0, double time1) : bvh_node(list.objects, 0, list.objects.size(), time0, time1) {}
    bvh_node(const std::vector<shared_ptr<hittable>>& src_objects, size_t start, size_t end, double time0, double time1);

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;
};

inline bool box_compare(shared_ptr<hittable> a, shared_ptr<hittable>b, int axis) {
    aabb box_a;
    aabb box_b;
    if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0,0,box_b))
        cerr << "No possible bounding box in bvh_node constructor.\n";
    return (box_a.min()[axis] < box_b.min()[axis]);
}
inline bool box_x_compare(shared_ptr<hittable> a, shared_ptr<hittable> b) {
    return box_compare(a, b, 0);
}
inline bool box_y_compare(shared_ptr<hittable> a, shared_ptr<hittable> b) {
    return box_compare(a, b, 1);
}
inline bool box_z_compare(shared_ptr<hittable> a, shared_ptr<hittable> b) {
    return box_compare(a, b, 2);
}

bool bvh_node::bounding_box(double time0, double time1, aabb& output_box) const {
    output_box = box;
    return true;
}

bool bvh_node::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    if (!box.hit(r, t_min, t_max, rec))
        return false;

    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, t_max, rec);

    return hit_left || hit_right;
}

bvh_node::bvh_node(const vector<shared_ptr<hittable>>& src_objects, size_t start, size_t end, double time0, double time1) {
    auto objects = src_objects;

    int axis = random_int(0, 2);
    auto comparator = axis == 0 ? box_x_compare : axis == 1 ? box_y_compare : box_z_compare;

    int span = end - start;

    if (span == 1) {
        right = left = objects[start];
    }
    if (span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
        }
        else {
            right = objects[start];
            left = objects[start+1];
        }
    }
    else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        int mid = start + span / 2;
        left = make_shared<bvh_node>(objects, start, mid, time0, time1);
        right = make_shared<bvh_node>(objects, mid, end, time0, time1);
    }
    aabb l_box, r_box;

    if (!(left->bounding_box(time0, time1, l_box)) || !(right->bounding_box(time0, time1, r_box)))
        cerr << "No possible bounding box in bvh_constuctor\n";
    box = surrounding_box(l_box, r_box);
}

#endif //RAYTRACER_BVH_HPP
