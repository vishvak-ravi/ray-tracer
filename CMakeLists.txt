cmake_minimum_required(VERSION 3.24)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracer src/main.cpp src/vec3.hpp src/color.hpp src/ray.hpp src/hittable.hpp src/sphere.hpp src/hittable_list.hpp src/rtweekend.hpp src/camera.hpp src/material.hpp src/moving_sphere.hpp src/aabb.hpp src/bvh.hpp src/texture.hpp)