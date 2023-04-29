//
// Created by Mali Abramovitch on 20/04/2023.
//

#ifndef INC_01_RC_H
#define INC_01_RC_H

template<class T>
class RC {
    T* data;
    int count;
public:
    //Methods
    explicit RC(T d); //required copy C'tor for T.
    ~RC();
    int getCount();
    void setCount(int nc);
    void operator++();
    void operator--();

};

template<class T>
RC<T>::RC(T d): data(T(&d)), count(0){}

template<class T>
RC<T>::~RC() {
    delete data;
}

template<class T>
int RC<T>::getCount() {
    return count;
}

template<class T>
void RC<T>::setCount(int nc) {
    count = nc;
}

template<class T>
void RC<T>::operator++() {
    ++count;
}

template<class T>
void RC<T>::operator--() {
    --count;
}

#endif //INC_01_RC_H
