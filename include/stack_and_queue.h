#include <iostream>
#include <cassert>

using namespace std;

template<typename T>
class Vector
{
protected:
    size_t sz;
    size_t capacity;// максимальное количество элементов до перевыделения памяти
    T* pMem;

public:
    Vector(size_t size = 0)
    {
        sz = size;
        capacity = sz * 2 + 2;
        pMem = new T[capacity];
        if (pMem == nullptr) throw"pMem is nullptr";
    }

    Vector(T* arr, size_t s) : sz(s), capacity(s * 2 + 2)
    {
        assert(arr != nullptr && "Vector requires non-nullptr arg");
        pMem = new T[capacity];
        copy(arr, arr + sz, pMem);
    }

    Vector(const Vector& v)
    {
        sz = v.sz;
        capacity = v.capacity;
        pMem = new T[capacity];
        if (pMem == nullptr) throw("pMem is nullptr");
        copy(v.pMem, v.pMem + sz, pMem);
    }

    ~Vector()
    {
        delete[]pMem;
        pMem = nullptr;
    }

    Vector& operator=(const Vector& v)
    {
        if (this != &v)
        {
            if (sz != v.sz)
            {
                sz = v.sz;
                capacity = v.capacity;
                delete[] pMem;
                T* p = new T[sz];
                if (p == nullptr)
                    throw "pMem is nullptr";
                pMem = p;
                p = nullptr;
            }
            copy(v.pMem, v.pMem + sz, pMem);
        }
        return (*this);
    }

    Vector& operator=(Vector&& v) noexcept
    {
        sz = 0;
        capacity = 0;
        delete[] pMem;
        pMem = nullptr;
        swap(*this, v);
        return (*this);
    }

    friend void swap(Vector& v1, Vector& v2)
    {
        swap(v1.size, v2.size);
        swap(v1.capacity, v2.capacity);
        swap(v1.data, v2.data);
    }

    bool operator==(const Vector& v) const noexcept
    {
        if (sz != v.sz)
            return 0;
        else
            for (size_t i = 0; i < sz; i++)
                if (pMem[i] != v.pMem[i])
                    return 0;
        return 1;
    }

    bool operator!=(const Vector& v) const noexcept
    {
        return !(*this == v);
    }

    void NewMem(size_t newmem) {
        T* tmp = new T[newmem * 2 + 2];
        if (tmp == nullptr)
        {
            throw ("pMem is nullptr");
        }
        copy(pMem, pMem + sz, tmp);
        delete[] pMem;
        pMem = tmp;
        capacity = newmem * 2 + 2;
    }

    bool IsFull() const noexcept {
        return (sz == capacity);
    }

    bool IsEmpty() const noexcept {
        return (sz == 0);
    }

    size_t size() const noexcept { return sz; }
    size_t getcapacity() const noexcept { return capacity; }

    // индексация с контролем
    T& operator [](size_t ind)
    {
        if (ind < 0 || ind >= sz) throw("Incorrect index");
        return pMem[ind];
    }
    const T& operator [](size_t ind) const
    {
        if (ind < 0 || ind >= capacity) throw("Incorrect index");
        return pMem[ind];
    }

    void push_back(T elem)
    {
        if (IsFull())
            NewMem(sz + 1);
        pMem[sz++] = elem;
    }

    void pop_back() {
        if (IsEmpty()) throw "vector is empty";
        --sz;
    }
    void insert(T elem, size_t ind)
    {
        if (ind < 0 || ind >= capacity)
        {
            throw ("index must be greater than 0 and the current size of the vector");
        }
        if (sz == capacity) NewMem(sz + 1);
        for (size_t i = sz; i > ind; i--)
        {
            pMem[i] = pMem[i - 1];
        }
        pMem[ind] = elem;
        ++sz;
    }

    void erase(size_t ind)
    {
        if (ind < 0 || ind >= capacity)
        {
            throw out_of_range("Index must be between 0 and the current size of the vector");
        }
        if (sz == 0)
        {
            throw ("can't erase from empty vector");
        }
        for (size_t i = ind; i < sz; i++)
        {
            pMem[i] = pMem[i + 1];
        }
        --sz;
    }

    void push_front(T elem)
    {
        insert(elem, 0);
    }

    void pop_front()
    {
        erase(0);
    }

    friend istream& operator>>(istream& istr, Vector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const Vector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' ';
        return ostr;
    }
};

template <typename T>
class Stack : private Vector<T>
{
private:
    using Vector<T>::sz;
    using Vector<T>::capacity;
    using Vector<T>::pMem;
public:
    using Vector<T>::push_back;
    using Vector<T>::pop_back;
    using Vector<T>::NewMem;
    using Vector<T>::IsFull;
    using Vector<T>::IsEmpty;
    using Vector<T>::size;
    using Vector<T>::getcapacity;

    Stack() : Vector<T>(0) { };

    void push(T elem)
    {
        push_back(elem);
    }

    void pop()
    {
        pop_back();
    }
    T top()
    {
        if (IsEmpty())
            throw ("stack is empty");
        return pMem[sz - 1];
    }
};

template <typename T>

class Queue : public Vector<T> {
private:
    size_t front;
    size_t back;
    using Vector<T>::sz;
    using Vector<T>::capacity;
    using Vector<T>::pMem;
    using Vector<T>::push_back;
    using Vector<T>::NewMem;
public:
    using Vector<T>::IsFull;
    using Vector<T>::IsEmpty;
    using Vector<T>::size;
    using Vector<T>::getcapacity;

    Queue() : Vector<T>(0), front(0), back(0) { }

    void push(T elem)
    {
        push_back(elem);
        if (back == capacity)
            back = 0;
        else
            ++back;
    }

    void pop()
    {
        if (IsEmpty())
            throw ("queue is empty");
        if (front == capacity)
            front = 0;
        else
            ++front;
        --sz;
    }

    T getFront() const noexcept {
        return pMem[front];
    }

    T getBack() const noexcept {
        if (back == 0)
            return pMem[capacity - 1];
        return pMem[back - 1];
    }

    size_t getBackIndex() const noexcept { return back; }
};


template<typename T>

class Queue_by_two_Stacks : private Vector<Stack<T>>
{
    using Vector<Stack<T>>::pMem;
    size_t sz;
    size_t capacity;
public:
    Queue_by_two_Stacks() : Vector<Stack<T>>(2), sz(0) {}

    size_t size() const noexcept { return sz; }

    size_t getcapacity() const noexcept { return capacity; }

    bool IsFull() const noexcept { return (pMem[0].IsFull() && pMem[1].IsFull()); }

    bool IsEmpty() const noexcept { return (pMem[0].IsEmpty() && pMem[1].IsEmpty()); }

    void push(T elem)
    {
        pMem[1].push(elem);
        ++sz;
    }

    void pop()
    {
        if (pMem[0].IsEmpty())
        {
            while (!pMem[1].IsEmpty())
            {
                T tmp = pMem[1].top();
                pMem[0].push(tmp);
                pMem[1].pop();
            }
            pMem[0].pop();
        }
        else
            pMem[0].pop();
        --sz;
    }

    T front()
    {
        if (!pMem[1].IsEmpty())
        {
            T tmp{ };
            while (!pMem[1].IsEmpty())
            {
                tmp = pMem[1].top();
                pMem[1].pop();
            }
            return tmp;
        }
        if (!pMem[0].IsEmpty())
            return pMem[0].top();
        return 0;
    }

    T back()
    {
        if (!pMem[0].IsEmpty())
        {
            T tmp{ };
            while (!pMem[0].IsEmpty())
            {
                tmp = pMem[0].top();
                pMem[0].pop();
            }
            return tmp;
        }
        if (!pMem[1].IsEmpty())
            return pMem[1].top();
        return 0;
    }
};
