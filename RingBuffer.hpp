#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <stdlib.h>

template <typename T, size_t N>
class RingBuffer
{
    size_t start, sz;
    T buffer[N] = { 0 };
    
    size_t to_index(size_t nth) const;
    T& first_opening();

public:
    RingBuffer();
    size_t size() const;
    bool is_empty() const;
    bool is_full() const;
    void push(T&& x);
    void push(T x);

    class Iterator
    {
        size_t start, size, current;
        T* buffer;

    public:
        Iterator(size_t start, size_t size, size_t current, T* buffer);
        T& operator*(); // Dereference
        T& operator++(); // Prefix
        T operator++(int); // Postfix
        bool operator==(Iterator& other) const;
        bool operator!=(Iterator& other) const { return !(*this == other); }
    };

    RingBuffer::Iterator begin();
    RingBuffer::Iterator end();
};

template <typename T, size_t N>
size_t RingBuffer<T, N>::to_index(size_t nth) const
{
    return (nth + start) % N;
}

template <typename T, size_t N>
T& RingBuffer<T, N>::first_opening()
{
    return buffer[to_index(sz)];
}

template <typename T, size_t N>
RingBuffer<T, N>::RingBuffer() : start(0), sz(0) {}

template <typename T, size_t N>
size_t RingBuffer<T, N>::size() const { return sz; }

template <typename T, size_t N>
bool RingBuffer<T, N>::is_empty() const { return size() == 0; }

template <typename T, size_t N>
bool RingBuffer<T, N>::is_full() const { return size() == N; }

template <typename T, size_t N>
void RingBuffer<T, N>::push(T&& x)
{
    first_opening() = x;
    if (sz < N) sz++;
    else start++;
}

template <typename T, size_t N>
void RingBuffer<T, N>::push(T x)
{
    first_opening() = x;
    if (sz < N) sz++;
    else start++;
}

template <typename T, size_t N>
RingBuffer<T, N>::Iterator::Iterator(size_t start, size_t size, size_t current, T* buffer)
    : start(start), size(size), current(current), buffer(buffer) {}

template <typename T, size_t N>
typename RingBuffer<T, N>::Iterator RingBuffer<T, N>::begin()
{
    RingBuffer<T, N>::Iterator it(start, size(), 0, buffer);
    return it;
}

template <typename T, size_t N>
typename RingBuffer<T, N>::Iterator RingBuffer<T, N>::end()
{
    RingBuffer<T, N>::Iterator it(start, size(), size(), buffer);
    return it;
}

template <typename T, size_t N>
T& RingBuffer<T, N>::Iterator::operator*()
{
    return buffer[(start + current) % N];
}

template <typename T, size_t N>
const T& RingBuffer<T, N>::Iterator::operator++()
{
    T& ref = buffer[(start + current) % N];
    current++;
    return ref;
}

template <typename T, size_t N>
T RingBuffer<T, N>::Iterator::operator++(int)
{
    T cpy = buffer[(start + current) % N];
    current++;
    return cpy;
}

template <typename T, size_t N>
bool RingBuffer<T, N>::Iterator::operator==(const RingBuffer<T, N>::Iterator& other) const
{
    return current == other.current && start == other.start && size == other.size && buffer == other.buffer;
}

#endif // RINGBUFFER_HPP
