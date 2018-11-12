#ifndef SMTPTR_H
#define SMTPTR_H

template<class T>
class auto_ptr
{
public:
    explicit auto_ptr(T * p = 0): point_place(p) {}
    template<class U>
    auto_ptr(auto_ptr<U>& right) : point_place(right.release()) {}
    ~auto_ptr() { delete point_place; }
    template<class U>
    auto_ptr<T>& operator=(auto_ptr<U> &right)
    {
        if(this != &right){
            reset(right.release());
        }
        return *this;
    }
    T & operator*() const { return *point_place; }
    T * operator->() const { return point_place; }
    T * get() const { return point_place; }
    T * release() {
        T * old = point_place;
        point_place = 0;
        return old;
    }
    void reset(T * p = 0)
    {
        if(point_place != p){
            delete point_place;
            point_place = p;
        }
    }
private:
    T * point_place;
};
#endif // SMTPTR_H
