#include <iostream>
#include <array>
#include <math.h> 

namespace aline{  

    template<typename T,std::size_t N>
    class Vector
    {
       std::array<T, N> vector;

    public:

        //Constructor

        //Constructs a vector filled with zeros.
        Vector() {
            vector = std::array<T, N>();
        }


        /* Constructs a vector with the values given as arguments.Fills up with zeros if less
        than N arguments are given.Throws runtime_error if more than N arguments are given.*/
        Vector(std::initializer_list<T> l) {
            vector = std::array<T, N>();
            if (l.size() > N)
                throw std::runtime_error("Index out of range");
            int i = 0;
            for (auto it = l.begin(); it != l.end(); ++it) {
                vector[i] = *it;
                i++;
            }       
        }

        //Constructs a copy of the vector given as argument.
        Vector(const Vector<T, N>& v) {
            vector = std::array<T, N>();
            vector = v.vector;
        }

 

        //Methods
        

        //The element indexed by the given argument. Throws runtime_error if the index is out of range.
        T at(std::size_t index) const {
            if (index >= N || index < 0)
                throw std::runtime_error("Index out of range");
            return vector[index];
        }

        //Subscripting (the as at(), but does not throw an exception).
        inline const T& operator[](std::size_t index) const {
            return vector[index];
        }

        //Subscripting permitting assignment.
        inline T& operator[](std::size_t index) {
            return vector[index];
        }

        //Vector addition and assignment.
        Vector<T, N>& operator+=(const Vector<T, N>& v) {
            for (std::size_t i = 0; i <= N; ++i)
                vector[i] += v.vector[i];
            return *this;
        }
    };

    

    

    //Function

    /*The cross product of two vectors.Uses only the first 3 elements(zero the others in
    the result).Throws runtime_error if the vectors have less than 3 elements.*/
    template<typename T, std::size_t N>
    Vector<T, N> cross(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        Vector<T, N> v;
        if (N < 3)
            throw std::runtime_error("Vector have less than 3 elements");

        v[0] = v1[1] * v2[2] - v1[2] * v2[1]; // 1*5 - 2*4 = 5-8 = -3
        v[1] = v1[2] * v2[0] - v1[0] * v2[2]; // 2*3 - 
        v[2] = v1[0] * v2[1] - v1[1] * v2[0];
        return v;
    }

    //The dot product of two vectors.
    template<typename T, std::size_t N>
    T dot(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        T res = 0;
        for (std::size_t i = 0; i < N; i++)
            res += v1[i] * v2[i];
        return res;
    }

    /*Tests if the vector contains NAN(not a number) values. (It is sometimes useful when
    the result of a computation does not exist, e.g.division by zero).*/
    template<typename T, std::size_t N>
    bool isnan(const Vector<T, N>& v) {
        for (std::size_t i = 0; i < N; i++)
            if (v[i] != v[i])
                return true;
        return false;
    }

    //Tests if the vector is a unit vector.
    template<typename T, std::size_t N>
    inline bool is_unit(const Vector<T, N>& v) {
        return round(norm(v));
    }

    /*Tests if two vectors contain nearly equal values. Two values are nearly equal when
    they are very close, with respect to their magnitudes. For example, 1.0000001 can be
    considered nearly equal to 1, whereas 1.234 is not nearly equal to 1.242. However,
    because of their magnitude, 67329.234 can be considered nearly equal to 67329.242 */
    template<typename T, std::size_t N>
    bool nearly_equal(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        const float epsilon = std::numeric_limits<float>::epsilon();
        for (std::size_t i = 0; i < N; ++i) {
            T max = std::max(v1[i], v2[i]);
            if (max != 0) {
                if (std::abs(v1[i] - v2[i]) / max > epsilon) {
                    return false;
                }
            }  
        }
        return true;
    }
    
    //Tests if two vectors contain the same values.
    template<typename T, std::size_t N>
    bool operator==(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        for (std::size_t i = 0; i < N; i++)
            if (v1[i] != v2[i])
                return false;
        return true;
    }
    // USE NEARLY_EQUAL WHEN IMPLEMENTED

    //Tests if two vectors contain different values.
    template<typename T, std::size_t N>
    bool operator!=(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        for (std::size_t i = 0; i < N; i++)
            if (v1[i] == v2[i])
                return false;
        return true;
    }
    // USE NEARLY_EQUAL WHEN IMPLEMENTED

    //Output operator.
    template<typename T, std::size_t N>
    std::ostream &operator<<(std::ostream& out, const Vector<T, N> v) {
        out << v[0];
        for (std::size_t i = 1; i < N; ++i)
            out << ", " << v[i];
        return out;
    }

    //The sum of two vectors.
    template<typename T, std::size_t N>
    Vector<T, N> operator+(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        Vector<T, N> v;
        for (std::size_t i = 0; i < N; i++)
            v[i] = v1[i] + v2[i];
        return v;
    }

    //The negation of a vector.
    template<typename T, std::size_t N>
    Vector<T, N> operator-(const Vector<T, N>& v) {
        const T i = -1;
        return i * v;
    }

    //The subtraction of two vectors.
    template<typename T, std::size_t N>
    Vector<T, N> operator-(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        Vector<T, N> v;
        for (std::size_t i = 0; i < N; i++)
            v[i] = v1[i] - v2[i];
        return v;
    }

    //The product of a scalar and a vector.
    template<typename T, std::size_t N>
    Vector<T, N> operator*(const T& s, const Vector<T, N>& v) {
        Vector<T, N> nv;
        for (std::size_t i = 0; i < N; i++)
            nv[i] = v[i] * s;
        return nv;
    }

    //The product of a vector and a scalar.
    template<typename T, std::size_t N>
    Vector<T, N> operator*(const Vector<T, N>& v, const T& s) {
        Vector<T, N> nv;
        for (std::size_t i = 0; i < N; i++)
            nv[i] = v[i] * s;
        return nv;
    }
    
    //The dot product of two vectors.
    template<typename T, std::size_t N>
    inline T operator*(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        return dot(v1, v2);
    }

    //The division of a vector by a scalar (same as the multiplication by 1s ).
    template<typename T, std::size_t N>
    Vector<T, N> operator/(const Vector<T, N>& v, const T& s) {
        Vector<T, N> nv;
        for (std::size_t i = 0; i < N; i++)
            nv[i] = v[i] / s;
        return nv;
    }

    //A string representation of a vector.
    template<typename T, std::size_t N>
    std::string to_string(const Vector<T, N>& v) {
        std::string s;
        s.append("(");
        s.append(std::to_string(v[0]));
        for (std::size_t i = 1; i < N; i++) {
            s.append(", ");
            s.append(std::to_string(v[i]));
        }
        s.append(")");
        return s;
    }

    //The vector normalized.
    template<typename T, std::size_t N>
    inline Vector<T, N> unit_vector(const Vector<T, N>& v) {
        return v / norm(v);
    }

    //The norm (magnitude) of the vector.
    template<typename T, std::size_t N>
    inline T norm(const Vector<T, N>& v) {
        return sqrt(dot(v, v));
    }

    //The square of the norm(magnitude) of the vector.
    template<typename T, std::size_t N>

    inline T sq_norm(Vector<T, N>& v) {
        return sqrt(norm(v));
    }

}