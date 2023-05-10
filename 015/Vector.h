//
// Created by Mali Abramovitch on 06/05/2023.
//

#ifndef INC_015_VECTOR_H
#define INC_015_VECTOR_H

#include <iostream>
#include <memory>

template<class T>
class Vector {
    std::shared_ptr<T[]> vector;
    int size;
    int lastElem;
public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {

    };
    class IndexOutOfRange : public std::exception {

    };
    class proxy {
        std::shared_ptr<T> element;
    public:
        proxy(T& element) : element(element){};
        operator T() {
            return element;
        }

    };

    Vector(int size = 10);
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other);
    ~Vector() = default;
    Vector<T>& operator=(const Vector<T>& other);
    Vector<T>& operator=(Vector<T>&& other);
    /**
     * add an element in the last place.
     * @param element
     */
    void pushBack(const T& element);

    /**
     * remove the last element.
     * @param element
     */
    void popBack(const T& element);

    T& operator[](int i);
    const proxy& operator[](int i);




};


#endif //INC_015_VECTOR_H
