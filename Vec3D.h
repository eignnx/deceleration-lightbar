#ifndef VEC3D_H
#define VEC3D_H

#ifndef sqrt
#define sqrt(x) x
#endif

#ifndef sq
#define sq(x) x
#endif

struct Vec3D
{
    float x, y, z;

    Vec3D();
    Vec3D(float x, float y, float z);

    float norm() const;
    Vec3D normalized() const;
};

// Constructors
Vec3D::Vec3D() : x(0.0), y(0.0), z(0.0) {}
Vec3D::Vec3D(float x, float y, float z) : x(x), y(y), z(z) {}

// Returns the magnitude (euclidean distance, 2-norm) of the vector.
float Vec3D::norm() const
{
    return sqrt(sq(x) + sq(y) + sq(z));
}


//-- Operators --//

// Vector Addition
Vec3D operator+(const Vec3D& u, const Vec3D& v)
{
    Vec3D w(u.x + v.x, u.y + v.y, u.z + v.z);
    return w;
}

// Multiplication by a Scalar
Vec3D operator*(const Vec3D& u, float a)
{
    Vec3D w(u.x * a, u.y * a, u.z * a);
    return w;
}

// Multiplication by a Scalar (Reversed Order)
Vec3D operator*(float a, const Vec3D& u)
{
    return u * a;
}

// Dot Product
float operator*(const Vec3D& u, const Vec3D& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

// Division by a Scalar
Vec3D operator/(const Vec3D& v, float a)
{
    return v * (1.0f / a);
}

// Unary Minus
Vec3D operator-(const Vec3D& v)
{
    return -1.0 * v;
}

// Vector Subtraction
Vec3D operator-(const Vec3D& u, const Vec3D& v)
{
    return u + (-v);
}

// Returns a normalized (unit length) vector pointing in the
// same direction as the original.
Vec3D Vec3D::normalized() const
{
    return *this / norm();
}

// Compound Addition Assignment
Vec3D& operator+=(Vec3D& self, Vec3D& other)
{
    return self = self + other;
}

// Compound Subtraction Assignment
Vec3D& operator-=(Vec3D& self, Vec3D& other)
{
    return self = self - other;
}

// Compound Scalar Multiplication Assignment
Vec3D& operator*=(Vec3D& self, float a)
{
    return self = self * a;
}

// Compound Scalar Division Assignment
Vec3D& operator/=(Vec3D& self, float a)
{
    return self = self / a;
}


// Definitions of Standard Basis Vectors
Vec3D i_hat() { return Vec3D(1, 0, 0); }
Vec3D j_hat() { return Vec3D(0, 1, 0); }
Vec3D k_hat() { return Vec3D(0, 0, 1); }

Vec3D zero_vector() { return Vec3D(); }

#endif // VEC3D_H
