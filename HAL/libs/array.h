#ifndef HAL_LIBS_ARRAY_H_
#define HAL_LIBS_ARRAY_H_

#include <stddef.h>
#include "hal_assert.h"

namespace hal {
namespace libs {

template<typename T, size_t N>
class array {
 public:
    // type definitions
    typedef T value_type;
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
    static constexpr size_type max_size() {
        return N;
    }
    enum {
        static_size = N
    };

    // swap (note: linear complexity in N, constant for given instantiation)
    void swap(array<T, N>& y) {
        for (size_type i = 0; i < static_size; ++i) {
            T x = y[i];
            y[i] = elems[i];
            elems[i] = x;
        }
    }

    // direct access to data (read-only)
    const T* data() const {
        return elems;
    }

    // use array as C array (direct read/write access to data)
    T* data() {
        return elems;
    }

    // assignment with type conversion
    template <typename T2>
    array<T, N>& operator= (const array<T2, N>& rhs) {
        for (size_type i = 0; i < static_size; ++i) {
            memcpy(elems[0], rhs.data(), static_size * sizeof(T));
        }
        return *this;
    }

    // assign one value to all elements
    void assign(const T& value) {
        for (size_type i = 0; i < static_size; ++i) {
            elems[i] = value;
        }
    }

 private:
    T elems[N];    // fixed-size array of elements of type T

    // check range (may be private because it is static)
    static void rangecheck(size_type i) {
        if (i >= size()) {
            fail_due_to_error("array<>: index out of range");
        }
    }
};

template<typename T>
class array<T, 0> {
 public:
    // type definitions
    typedef T value_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    // iterator support
    iterator begin() {
        return reinterpret_cast<iterator>(&c);
    }
    const_iterator begin() const {
        return reinterpret_cast<const_iterator>(&c);
    }
    iterator end() {
        return reinterpret_cast<iterator>(&c);
    }
    const_iterator end() const {
        return reinterpret_cast<const_iterator>(&c);
    }

    // at() with range check
    reference at(size_type i) {
        fail_due_to_error("");
    }
    const_reference at(size_type i) const {
        fail_due_to_error("<0>: index out of range");
    }

    // size is constant
    static size_type size() {
        return 0;
    }
    static bool empty() {
        return true;
    }
    static size_type max_size() {
        return 0;
    }
    enum {
        static_size = 0
    };

    // swap
    void swap(array<T, 0>& y) {
        //  could swap value of c, but value is not part of documented array state
    }

    // direct access to data
    const T* data() const {
        return NULL;
    }
    T* data() {
        return NULL;
    }

    // assignment with type conversion
    template<typename T2>
    array<T, 0>& operator=(const array<T2, 0>& rhs) {
        return *this;
    }

    //  Calling these operations are undefined behaviour for 0-size arrays,
    //  but Library TR1 requires their presence.
    // operator[]
    [[noreturn]] reference operator[](size_type i) {
        makes_no_sense();
    }

    [[noreturn]] const_reference operator[](size_type i) const {
        makes_no_sense();
    }

    // front() and back()
    [[noreturn]] reference front() {
        makes_no_sense();
    }

    [[noreturn]] const_reference front() const {
        makes_no_sense();
    }

    [[noreturn]] reference back() {
        makes_no_sense();
    }

    [[noreturn]] const_reference back() const {
        makes_no_sense();
    }

 private:
    char c;  // to ensure different array intances return unique values for begin/end

    // helper for operations that have undefined behaviour for 0-size arrays,
    //  assert( false ); added to make lack of support clear
    [[noreturn]] static void makes_no_sense() {
        fail_due_to_error("array<0>: index out of range");
    }
};

// comparisons
template<class T, size_t N>
bool operator==(const array<T, N>& x, const array<T, N>& y) {
    if (memcmp(x.data(), y.data(), x.size()*sizeof(T)) == 0) {
        return true;
    }
    return false;
}
template<class T, size_t N>
bool operator!=(const array<T, N>& x, const array<T, N>& y) {
    return !(x == y);
}

// global swap()
template<class T, size_t N>
inline void swap(array<T, N>& x, array<T, N>& y) {
    x.swap(y);
}

}  // namespace libs
}  // namespace hal

#endif  // HAL_LIBS_ARRAY_H_
