//
// Created by Mali Abramovitch on 18/04/2023.
//

#ifndef INC_01_SMARTPOINTER_H
#define INC_01_SMARTPOINTER_H

template<class T>
class SmartPointer {
    T *pointer;

public:
    explicit SmartPointer(T *realPointer = 0) : pointer(new T(*realPointer)) {};

    ~SmartPointer();

    SmartPointer(const SmartPointer<T> &); //act's like move;

    SmartPointer(SmartPointer<T> &&) = delete;

    SmartPointer<T> &operator=(const SmartPointer<T> &); //act's like move;

    SmartPointer<T> &operator=(SmartPointer<T> &&) = delete;

    T *operator->() const;

    T &operator*() const;

};

template<class T>
SmartPointer<T>::~SmartPointer() {
    delete pointer;
}

template<class T>
SmartPointer<T>::SmartPointer(const SmartPointer<T> &other) :pointer(other.pointer) {
    auto &nonConst = const_cast<SmartPointer<T> &>(other);
    nonConst.pointer = 0;
}

template<class T>
SmartPointer<T> &SmartPointer<T>::operator=(const SmartPointer<T> &other) {
    if (this == &other) return *this;
    delete pointer;
    pointer = other.pointer;
    auto &nonConst = const_cast<SmartPointer<T> &>(other);
    nonConst.pointer = 0;
    return *this;
}

template<class T>
T *SmartPointer<T>::operator->() const {
    return pointer;
}

template<class T>
T &SmartPointer<T>::operator*() const {
    return *pointer;
}

#endif //INC_01_SMARTPOINTER_H
