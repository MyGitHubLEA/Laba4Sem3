#pragma once
#include "..\..\..\Documents\Laba3Sem3\Sequence.h" 

template <typename T>
class Route
{
private:
    ArraySequence<T> route; 
    template <typename T>
    friend std::ostream& operator <<(std::ostream& out, const Route<T>& route);
public:
    Route() {}

    void Prepend(const T& vertex) 
    {
        route.Prepend(vertex); 
    }

    
    void Add(const T& vertex) 
    {
        route.Append(vertex); 
    }


    T& Get(int index) const 
    {
        return route.Get(index); 
    }

    size_t GetLength() const { 
        return route.GetLength(); 
    }  
};

template <typename T>
std::ostream& operator <<(std::ostream& out, const Route<T>& route)
{
    int L = route.GetLength();
    for (int i = 0; i < L; ++i)
    {
        out << route.Get(i);
        if (i != L - 1) out << " -> ";
    }
    out << std::endl;
    return out;
}


