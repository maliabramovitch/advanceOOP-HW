//
// Created by Mali Abramovitch on 06/05/2023.
//

#ifndef INC_015_VECTOR_H
#define INC_015_VECTOR_H

#include <iostream>
#include <algorithm>
#include <utility>


template<class T>
class Vector {
    T *vector;
    int actualSize;
    int lastElem;
public:
    class IndexOutOfrRange : public std::exception {
        std::string mes;
    public:
        explicit IndexOutOfrRange(std::string m) : mes(std::move(m)) {}

        const char *what() const noexcept override { return mes.c_str(); }
    };

    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
        T *p; // beginning
    public:
        explicit Iterator(const Vector<T> &v) : p(v.vector) {};

        inline Iterator(const Iterator &other) : p(other.p) {};

        Iterator(Iterator &&other) noexcept: p(other.p) {
            other.p = nullptr;
        };

        ~Iterator() { p = nullptr; }

        inline Iterator &operator=(const Iterator &other) {
            if (this != &other) {
                p = other.p;
            }
            return *this;
        };

        Iterator &operator=(Iterator &&other) noexcept {
            if (this != &other) {
                p = other.p;
                other.p = nullptr;
            }
            return *this;
        }

        inline T &operator[](int i) noexcept(false) {
            if (i < 0 || i > lastElem) throw IndexOutOfrRange("Illegal index\n");
            return *(vector + i);
        };

        inline const T &operator[](int i) const noexcept(false) {
            if (i < 0 || i > lastElem) throw IndexOutOfrRange("Illegal index\n");
            return *(vector + i);
        };

        inline Iterator &operator+=(int i) {
            p += i;
            return *this;
        };

        inline Iterator &operator-=(int i) {
            p -= i;
            return *this;
        };

        T &operator->() {
            return *p;
        };

        inline T &operator*() { return *p; }

        inline Iterator &operator++() {
            ++p;
            return *this;
        }

        inline Iterator operator++(int) {
            ++p;
            return *this;
        }

        inline Iterator &operator--() {
            --p;
            return *this;
        }

        inline Iterator operator--(int) {
            --p;
            return *this;
        }

        inline Iterator operator+(int i) const {
            Iterator it(*this);
            it += i;
            return it;
        }

        inline Iterator operator-(int i) const {
            Iterator it(*this);
            it -= i;
            return it;
        }

        inline int operator-(const Iterator &o) const {
            return p - o.p;
        }

        inline bool operator==(const Iterator &other) const { return p == other.p; }

        inline bool operator!=(const Iterator &other) const { return p != other.p; }

        inline bool operator>=(const Iterator &other) const { return p >= other.p; }

        inline bool operator<=(const Iterator &other) const { return p <= other.p; }

        inline bool operator>(const Iterator &other) const { return p > other.p; }

        inline bool operator<(const Iterator &other) const { return p < other.p; }

    };

    /**
     * Default actualSize == 10;
     * @param size
     */
    explicit Vector(int size = 10);

    Vector(const Vector<T> &other);

    Vector(Vector<T> &&other) noexcept;

    ~Vector();

    Vector<T> &operator=(const Vector<T> &other);

    Vector<T> &operator=(Vector<T> &&other) noexcept;

    /**
     * add an element in the last place.
     * @param element
     */
    void pushBack(const T &element);

    /**
     * remove the last element.
     * @param element
     */
    void popBack();

    T &operator[](int i) noexcept(false);

    const T &operator[](int i) const noexcept(false);

    /**
     * clears the vector.
     */
    void clear();

    /**
     * resizes the vector.
     * @param newSize
     */
    void resize(int newSize);

    Vector<T>::Iterator begin() const;

    Vector<T>::Iterator end() const;

    inline int size() const { return lastElem; }

    template<class COMP>
    void sort(COMP cmp);
};

template<class T>
Vector<T>::Vector(int s) {
    vector = new T[s];
    lastElem = 0;
    actualSize = s;
}

template<class T>
Vector<T>::Vector(const Vector<T> &other) : actualSize(other.actualSize), lastElem(other.lastElem) {
    vector = new T[other.actualSize];
    for (int i = 0; i < lastElem; ++i) {
        vector[i] = other.vector[i];
    }
}

template<class T>
Vector<T>::Vector(Vector<T> &&other) noexcept : vector(other.vector), actualSize(other.actualSize),
                                                lastElem(other.lastElem) {
    other.vector = nullptr;
}

template<class T>
Vector<T>::~Vector() {
    delete vector;
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
    if (this != &other) {
        if (actualSize != other.actualSize) {
            delete vector;
            vector = new T[other.actualSize];
            actualSize = other.actualSize;
            lastElem = other.lastElem;
        }
        for (int i = 0; i < lastElem; ++i) {
            vector[i] = other.vector[i];
        }
    }
    return *this;
}

template<class T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept {
    if (this != &other) {
        delete vector;
        vector = other.vector;
        actualSize = other.actualSize;
        lastElem = other.lastElem;
        other.vector = nullptr;
    }
    return *this;
}

template<class T>
void Vector<T>::pushBack(const T &element) {
    if (lastElem == actualSize) {
        T *tmp = new T[2 * actualSize + 1];
        for (int i = 0; i < lastElem; ++i) {
            tmp[i] = vector[i];
        }
        delete vector;
        vector = tmp;
        actualSize = 2 * actualSize + 1;
    }
    vector[lastElem++] = element;
}

template<class T>
void Vector<T>::popBack() {
    if (lastElem > 0) {
        --lastElem;
    }
}

template<class T>
T &Vector<T>::operator[](int i) {
    if (i < 0 || i >= lastElem) {
        throw IndexOutOfrRange("Illegal index\n");
    }
    return vector[i];
}

template<class T>
const T &Vector<T>::operator[](int i) const {
    if (i < 0 || i > lastElem) {
        throw IndexOutOfrRange("Illegal index\n");
    }
    return vector[i];
}


template<class T>
void Vector<T>::resize(int newSize) {
    if (newSize > actualSize) {
        T *tmp = new T[newSize];
        for (int i = 0; i < lastElem; ++i) {
            tmp[i] = vector[i];
        }
        delete vector;
        vector = tmp;
        actualSize = newSize;
    } else if (lastElem > newSize) {
        lastElem = newSize;
    }
}

template<class T>
void Vector<T>::clear() {
    lastElem = 0;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::begin() const {
    return Vector::Iterator(*this);
}

template<class T>
typename Vector<T>::Iterator Vector<T>::end() const {
    Vector::Iterator it(*this);
    it += lastElem;
    return it;
}


template<class T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &v) {
    typedef typename Vector<T>::Iterator Iter;
    os << '<';
    for (Iter b(v.begin()), e(v.end()); b != e; ++b) {
        os << *b;
        if (b != e-1) {
            os << ", ";
        }


    }
    os << '>';
    return os;
}

template<class T>
template<class COMP>
void Vector<T>::sort(COMP cmp) {
    std::sort(begin(), end(), cmp);
}

#endif //INC_015_VECTOR_H
