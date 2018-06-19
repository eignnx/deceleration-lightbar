#ifndef GEEMONITOR_HPP
#define GEEMONITOR_HPP

#include "RingBuffer.hpp"
#include "Vec3D.h"
#include <utility>

// The number of vectors to keep for averaging the
// acceleration.
#define AVERAGES_WINDOW_SIZE 3

class GeeMonitor
{
    Vec3D backward;
    RingBuffer<Vec3D, AVERAGES_WINDOW_SIZE> averages;
    float threshold_gees; // in m/s^2

    Vec3D get_average() const;

public:
    GeeMonitor(float threshold_gees, Vec3D& backward);
    bool is_above() const;
    bool is_below() const;
    void update(Vec3D inst_acc);
};

Vec3D GeeMonitor::get_average() const
{
    if (averages.size() == 0) return zero_vector();
    Vec3D total = zero_vector();
    for (auto& acc : averages)
        total += acc;
    return total / ((float) averages.size());
}

GeeMonitor::GeeMonitor(float threshold_gees, Vec3D& backward)
    : threshold_gees(threshold_gees), backward(backward)
{
    averages = RingBuffer<Vec3D, AVERAGES_WINDOW_SIZE>();
}

bool GeeMonitor::is_above() const
{
    return (get_average() * backward) > threshold_gees;
}

bool GeeMonitor::is_below() const { return !is_above(); }

void GeeMonitor::update(Vec3D inst_acc)
{
    averages.push(inst_acc);
}

#endif // GEEMONITOR_HPP
