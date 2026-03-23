#pragma once

#include <algorithm>  //for std::max
#include <stdexcept>  // for std::out_of_range

namespace dsac::array {

template <typename T>
class Vector {

private:
    int cap{0};
    int sz{0};
    T* data{nullptr};

public:
    //empty
    Vector() : cap{0}, sz{0}, data{nullptr} {}

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Copying constructor
    Vector(const Vector& src) : cap{src.cap}, sz{src.sz}, data{nullptr} {
        if (cap > 0) {
            data = new T[cap];
            for (int idx = 0; idx < sz; ++idx)
                data[idx] = src.data[idx];
        }
    }

    // Copying assignment
    Vector& operator=(const Vector& src) {
        if (this != &src) {
            delete[] data;
            cap  = src.cap;
            sz   = src.sz;
            data = nullptr;
            if (cap > 0) {
                data = new T[cap];
                for (int idx = 0; idx < sz; ++idx)
                    data[idx] = src.data[idx];
            }
        }
        return *this;
    }

    //capacity
    int capacity() const { return cap; }

    //elements stored
    int size() const { return sz; }

    // True is empty
    bool empty() const { return sz == 0; }

    //element at index when vector is const
    const T& operator[](int i) const { return data[i]; }

    //element at index when vector is non-cons
    T& operator[](int i) { return data[i]; }

    // at function for const
    const T& at(int i) const {
        if (i < 0 || i >= sz)
            throw std::out_of_range("Vector::at — index out of range");
        return data[i];
    }

    // at function for non const
    T& at(int i) {
        if (i < 0 || i >= sz)
            throw std::out_of_range("Vector::at — index out of range");
        return data[i];
    }

    // first element
    const T& front() const {
        if (sz == 0)
            throw std::out_of_range("Vector::front — vector is empty");
        return data[0];
    }

    // first element
    T& front() {
        if (sz == 0)
            throw std::out_of_range("Vector::front — vector is empty");
        return data[0];
    }

    // last element
    const T& back() const {
        if (sz == 0)
            throw std::out_of_range("Vector::back — vector is empty");
        return data[sz - 1];
    }

    // last element
    T& back() {
        if (sz == 0)
            throw std::out_of_range("Vector::back — vector is empty");
        return data[sz - 1];
    }

    // insert at endf
    void push_back(const T& elem) {
        if (sz == cap) {
            reserve(std::max(1, cap * 2));
        }
        data[sz++] = elem;
    }

    // remove rom end
    // also call shrink
    void pop_back() {
        if (sz == 0)
            throw std::out_of_range("Vector::pop_back — vector is empty");
        --sz;
        shrink();
    }

    // insert at index
    void insert(int i, const T& elem) {
        if (i < 0 || i > sz)
            throw std::out_of_range("Vector::insert — index out of range");
        if (sz == cap) {
            reserve(std::max(1, cap * 2));
        }
        for (int cursor = sz; cursor > i; --cursor)
            data[cursor] = data[cursor - 1];
        data[i] = elem;
        ++sz;
    }

    // removes atindex
    // also call shrink
    void erase(int i) {
        if (i < 0 || i >= sz)
            throw std::out_of_range("Vector::erase — index out of range");
        for (int cursor = i; cursor < sz - 1; ++cursor)
            data[cursor] = data[cursor + 1];
        --sz;
        shrink();
    }

    //capacity >= minimum
    void reserve(int minimum) {
        if (minimum <= cap) return;

        int updated_cap  = std::max(minimum, cap * 2);
        T*  updated_data = new T[updated_cap];
        for (int idx = 0; idx < sz; ++idx)
            updated_data[idx] = data[idx];
        delete[] data;
        data = updated_data;
        cap  = updated_cap;
    }

    // called by other functions to reduce cap by half 
    // when sz <= cap/4 
    void shrink() {
        if (cap > 1 && sz <= cap / 4) {
            int reduced_cap  = std::max(1, cap / 2);
            T*  reduced_data = new T[reduced_cap];
            for (int idx = 0; idx < sz; ++idx)
                reduced_data[idx] = data[idx];
            delete[] data;
            data = reduced_data;
            cap  = reduced_cap;
        }
    }

    // explicitly reduce the cap to sz and eep at least 1 slot
    void shrink_to_fit() {
        int fitted_cap  = std::max(1, sz);
        if (fitted_cap == cap) return;
        T*  fitted_data = new T[fitted_cap];
        for (int idx = 0; idx < sz; ++idx)
            fitted_data[idx] = data[idx];
        delete[] data;
        data = fitted_data;
        cap  = fitted_cap;
    }

}; //end class Vector
}//end namespace dsa