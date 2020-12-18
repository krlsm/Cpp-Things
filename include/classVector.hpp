#pragma once
#include <array> //Store vec data
#include <utility> //Specialize tuple_size and tuple_element
#include <type_traits> //integral_constant
#include <initializer_list> // for assignment with multiple values
#include <assert.h> 
template<typename T, size_t N> class NdimVec {
public:
//Constructors
    NdimVec() {}

    template<typename ...Params> NdimVec(const Params... p) {
        static_assert(sizeof...(p) == N, "No se han proporcionado la cantidad de datos correcta.");
        valores = { static_cast<T>(p)... ,};
    }
//Get Set
    //c++17 std::get
    template<std::size_t Index> std::tuple_element_t<Index, NdimVec> get()  {
        if constexpr(Index<N) return valores[Index];
    }
    //normal get
    T get(size_t coord) {
        size_t pos = 0;
        return valores[coord < N? coord : N];
    }

// //Asignators & Returners
//     auto operator() (void) {
//         return valores;
//     }
// intento suma
    auto operator+ (const NdimVec& vector) -> NdimVec {
        // check dim igual
        NdimVec result();
        for (size_t i = 0; i < vector; i++)
        {
            result[i] =  valores[i] + vector[i];
        }
        return result;
    }
    template<typename _T, std::size_t _N>
    auto operator=(const _T(&l)[_N]){
        static_assert(_N <= N, "No se han proporcionado la cantidad de datos correcta.");
        
        for (size_t i = 0; i < _N; i++)
        {
            _set(i,l[i]);
        }
        

        // for (auto iterator = l.begin(); iterator != l.end() ; iterator++)
        // { 
        //     set(std::distance(l.begin(), iterator),*iterator);
        // }
        return *this;
        
    }

    
    auto operator[] (const size_t index) {
        return valores[index];
    }

//boring set
    void set(const size_t coord, const T value) {
        _set(coord, value);
    }



//Operators
private:
    std::array<T, N> valores;

    inline void _set(const size_t coord, const T value) {
        valores[coord < N ? coord : N] = value;
    }

};

namespace std {
    template <typename T,size_t N> 
    struct tuple_size<::NdimVec<T,N>> 
        : integral_constant<size_t, N>{ };

    template<size_t Index, typename T, size_t N>
    struct tuple_element<Index, ::NdimVec<T, N>> 
        : enable_if <Index < N, T>{ };
}
