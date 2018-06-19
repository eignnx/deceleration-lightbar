#ifndef VEC3D_H
#define VEC3D_H

#include "Arduino.h"

struct Vec3D
{
    float x, y, z;

    Vec3D();
    Vec3D(float x, float y, float z);
    float norm() const;
    Vec3D normalized() const;
};

// Special vector creation functions
Vec3D i_hat();
Vec3D j_hat();
Vec3D k_hat();
Vec3D zero_vector();

#endif // VEC3D_H
