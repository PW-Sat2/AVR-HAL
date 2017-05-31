#ifndef HAL_LIBS_ARRAY_H_
#define HAL_LIBS_ARRAY_H_

#include <stddef.h>
#include <algorithm>
#include <cstring>
#include <type_traits>
#include <utility>
#include "hal/libs/span.h"
#include "hal_assert.h"

namespace hal {
namespace libs {

template<typename T, size_t N>
class array {
 public:
    static_assert(N > 0, "array size must be positive");
    // type definitions
    typedef typename std::remove_reference<T>::type value_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    // iterator support
    iterator begin() {
        return elems;
    }
    const_iterator begin() const {
        return elems;
    }
    iterator end() {
        return elems + N;
    }
    const_iterator end() const {
        return elems + N;
    }

    // operator[]
    reference operator[](size_type i) {
        return elems[i];
    }
    const_reference operator[](size_type i) const {
        return elems[i];
    }

    // at() with range check
    reference at(size_type i) {
        rangecheck(i);
        return elems[i];
    }
    const_reference at(size_type i) const {
        rangecheck(i);
        return elems[i];
    }

    // front() and back()
    reference front() {
        return elems[0];
    }
    constexpr const_reference front() const {
        return elems[0];
    }
    reference back() {
        return elems[N - 1];
    }
    const_reference back() const {
        return elems[N - 1];
    }

    // size is constant
    static constexpr size_type size() {
        return N;
    }
    static constexpr bool empty() {
        return false;
    }
    enum { static_size = N };

    // direct access to data (read-only)
    const T* data() const {
        return elems;
    }

    // use array as C array (direct read/write access to data)
    T* data() {
        return elems;
    }

    // assignment with type conversion
    template<typename T2>
    array<T, N>& operator=(const array<T2, N>& rhs) {
        for (size_type i = 0; i < static_size; ++i) {
            memcpy(elems[0], rhs.data(), static_size * sizeof(T));
        }
        return *this;
    }

    // assign one value to all elements
    /*constexpr */ void assign(const T& value) {
        for (size_type i = 0; i < static_size; ++i) {
            elems[i] = value;
        }
    }

    // get array view to this array
    span<T> as_span() {
        return make_span(elems, N);
    }
    const span<const T> as_span() const {
        return make_span(elems, N);
    }

    T elems[N];  // fixed-size array of elements of type T

 private:
    // check range (may be private because it is static)
    static void rangecheck(size_type i) {
        if (i >= size()) {
            fail_due_to_error("array<>: index out of range");
        }
    }
};

// comparisons
template<class T, size_t N>
inline bool operator==(const array<T, N>& x, const array<T, N>& y) {
    return (memcmp(x.data(), y.data(), x.size() * sizeof(T)) == 0);
}

template<class T, size_t N>
inline bool operator!=(const array<T, N>& x, const array<T, N>& y) {
    return !(x == y);
}

// global swap()
template<class T, size_t N>
inline void swap(array<T, N>& x, array<T, N>& y) noexcept {
    x.swap(y);
}

}  // namespace libs
}  // namespace hal

#endif  // HAL_LIBS_ARRAY_H_
