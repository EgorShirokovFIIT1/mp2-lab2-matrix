﻿#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<class T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if ((sz <= 0) || (sz >= MAX_VECTOR_SIZE))
            throw out_of_range("Vector size should be correct");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        sz = 0;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        if (pMem != nullptr)
            delete[]pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (v != *this) {
            if (pMem != nullptr)
                delete[] pMem;
            sz = v.sz;
            pMem = new T[sz];
            for (size_t i = 0; i < sz; i++) {
                pMem[i] = v.pMem[i];
            }
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        sz = 0;
        swap(*this, v);
        return *this;
    }
    size_t getSize() const noexcept
    {
        return sz;
    }

    // индексация
    T& operator[](size_t ind)
    {
        if ((ind >= sz) || (ind < 0))
            throw invalid_argument("Index should be correct");
        else
            return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if ((ind >= sz) || (ind < 0))
            throw invalid_argument("Index should be correct");
        else
            return pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind)
    {
        if ((ind >= sz) || (ind < 0))
            throw invalid_argument("Index should be correct");
        else
            return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if ((ind >= sz) || (ind < 0))
            throw invalid_argument("Index should be correct");
        else
            return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        bool flag = true;
        if (sz == v.sz) {
            for (size_t i = 0; i < sz; i++) {
                if (pMem[i] != v.pMem[i]) {
                    flag = false;
                    break;
                }
            }
        }
        else
            flag = false;
        return flag;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        bool flag = false;
        if (sz == v.sz) {
            for (size_t i = 0; i < sz; i++) {
                if (pMem[i] != v.pMem[i]) {
                    flag = true;
                    break;
                }
            }
        }
        else
            flag = true;
        return flag;
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector<T> a(sz);
        for (size_t i = 0; i < sz; i++) {
            a.pMem[i] = pMem[i] + val;
        }
        return a;
    }
    TDynamicVector operator-(double val)
    {
        TDynamicVector<T> a(sz);
        for (size_t i = 0; i < sz; i++) {
            a.pMem[i] = pMem[i] - val;
        }
        return a;
    }
    TDynamicVector operator*(double val)
    {
        TDynamicVector<T> a(sz);
        for (size_t i = 0; i < sz; i++) {
            a.pMem[i] = pMem[i] * val;
        }
        return a;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz == v.sz) {
            TDynamicVector<T> a(sz);
            for (size_t i = 0; i < sz; i++) {
                a.pMem[i] = pMem[i] + v.pMem[i];
            }
            return a;
        }
        else throw invalid_argument("Different size!");
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        
        if (sz == v.sz) {
            TDynamicVector<T> a(sz);
            for (size_t i = 0; i < sz; i++) {
                a.pMem[i] = pMem[i] - v.pMem[i];
            }
            return a;
        }
        else throw invalid_argument("Different size!");
    }

    //скалярное произведение
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz == v.sz)
        {
            T sp = 0;
            for (size_t i = 0; i < sz; i++)
            {
                sp += pMem[i] * v.pMem[i];
            }
            return sp;
        }
        else throw invalid_argument("Different size!");
    }
    
    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        swap(lhs.sz, rhs.sz);
        swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& in, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            in >> v.pMem[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            out << v.pMem[i] << ' ';
        return out;
    }

    
};



template<class T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if ((s <= 0) || (s > 1000))
            throw invalid_argument("Size should be correct!");
        else
            for (size_t i = 0; i < s; i++) {
                pMem[i] = TDynamicVector<T>(s);
            }
    }
    TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& m) : TDynamicVector<TDynamicVector<T>>(m) {}

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        bool flag = true;
        if (sz == m.sz) {
            for (size_t i = 0; i < m.sz; i++)
            {
                for (size_t j = 0; j < m.sz; j++)
                {
                    if (pMem[i][j] != m.pMem[i][j])
                        flag = false;
                }
            }
        }
        else flag = false;
        return flag;
    }
    bool operator!=(const TDynamicMatrix& m) const noexcept 
    {
        bool flag = false;
        if (sz == m.sz) {
            for (size_t i = 0; i < m.sz; i++)
            {
                for (size_t j = 0; j < m.sz; j++)
                {
                    if (pMem[i][j] != m.pMem[i][j])
                        flag = true;
                }
            }
        }
        else flag = true;
        return flag;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix m(sz);
        for (size_t i = 0; i < sz; i++) {
            m.pMem[i] = pMem[i] * val;
        }
        return m;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        TDynamicVector<T> v1(sz);
        for (size_t i = 0; i < sz; i++) {
            T sp = 0;
            for (size_t j = 0; j < sz; j++) {
                sp += pMem[i][j] * v[j];
            }
            v1[i] = sp;
            sp = 0;
        }
        return v1;
    }

    // матрично-матричные операции
    
   /* TDynamicMatrix& operator=(const TDynamicMatrix& m) {
        if (*this != m)
        {
            if (sz != m.sz)
            {
                if (pMem != nullptr)
                    delete[]pMem;
                sz = m.sz;
                pMem = new TDynamicVector<T>(sz);
            }
            for (size_t i = 0; i < sz; i++) {
                pMem[i] = m.pMem[i];
            }
        }
        return *this;
    }
    */
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        return TDynamicVector<TDynamicVector<T>> :: operator+(m);
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        return TDynamicVector<TDynamicVector<T> > :: operator-(m);
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (m.sz == sz) {
            TDynamicMatrix a(sz);
            for (size_t i = 0; i < sz; i++) {
                for (size_t j = 0; j < sz; j++) {
                    T tmp = 0;
                    for (size_t k = 0; k < sz; k++) {
                        tmp += pMem[i][k] * m.pMem[k][j];
                    }
                    a.pMem[i][j] = tmp;
                }
            }
            return a;
        }
        else throw invalid_argument("Incorrect matrix size!");
    }

    // ввод/вывод
    friend istream& operator>>(istream& in, TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++) {
            in >> m.pMem[i];
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, const TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++) {
            out << m.pMem[i] << endl;
        }
        return out;
    }
};

#endif