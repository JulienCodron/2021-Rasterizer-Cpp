#include "vector.h"

namespace aline {
	template<typename T, std::size_t M, std::size_t N>
	class Matrix
	{
		Vector<Vector<T,N>, M> matrix;
	
	public:
		//Constructors 

		//Constructs a matrix filled up with zeros.
		Matrix() {
			matrix = Vector<Vector<T, N>, M>();
			for (std::size_t i = 0 ; i < M; ++i) {
				matrix[i] = Vector<T, N>();
			}
		}

		/*Constructs a matrix with the vectors given as arguments.Each vector is one line of the matrix.*/
		Matrix(std::initializer_list<Vector<T, N>> l){
			if (l.size() > M)
				throw std::runtime_error("Index out of range");

			matrix = Vector<Vector<T, N>, M>();
			for (std::size_t i = 0; i < M; ++i) {
				matrix[i] = Vector<T, N>();
			}
			
			size_t i = 0;
			for (auto it = l.begin(); it != l.end(); ++it) {
				for (size_t j = 0; j < N; ++j) {
					matrix[i][j] = (*it)[j];
				}
				++i;
			}
		}
		
		//Constructs a copy of the matrix given as argument.
		Matrix(const Matrix<T, M, N>& m) {
			matrix = Vector<Vector<T, N>, M>();
			for (std::size_t i = 0; i < M ; ++i)
				matrix[i] = Vector<T, N>(m[i]);
		}
			

		//Methods
		/*The line indexed by the given argument.Throws runtime_error if the index is out of range.*/
		Vector<T, N> at(std::size_t i) {
			if (i >= M)
				throw std::runtime_error("Index out of range");
			return matrix[i];
		}
		
		/*The element indexed by the given arguments.Throws runtime_error if the index is out of range.*/
		T at(std::size_t i, std::size_t j) {
			if (i >= M || j >= N)
				throw std::runtime_error("Index out of range");
			return matrix[i][j];
		}
		
		/*Subscripting.*/
		inline const Vector<T, N> operator[](std::size_t i) const {
			return matrix[i];
		}
		
		/*Subscripting permitting assignment.*/
		inline Vector<T, N>& operator[](std::size_t i) {
			return matrix[i];
		}

		/*Matrix addition and assignment.*/
		Matrix<T, M, N>& operator+=(const Matrix<T, M, N>& m) {
			for (std::size_t i = 0; i < M ; ++i)
				matrix[i] += m[i];
			return *this;
		}
	};


	/*Functions :*/
	
	/*The inverse of a matrix.If the matrix is not invertible, returns a NAN(not a number) matrix.*/
	template<typename T, std::size_t M, std::size_t N>
	Matrix<T, M, N> inverse(const Matrix<T, M, N>& m) { 
		Matrix<T, M, N> nm = m;
		Matrix<T, M, N> im = identity_matrix(m);
		std::cout << to_string(m) << std::endl;
		std::cout << to_string(im) << std::endl;
		T greatest_nonzero = 0;
		for (std::size_t j = 0; j < N; ++j) {
			std::cout << std::endl << "BOUCLE : " << j << std::endl;

			std::size_t  line = 0;
			for (std::size_t x = 0; x < M; ++x) {
				for (std::size_t y = 0; y < N; ++y) {
					if (m[x][y] > greatest_nonzero) {
						greatest_nonzero = m[x][y];
						line = x;
					}
				}
			}
			std::cout <<  greatest_nonzero  << " / " << j <<  " / " << line << std::endl;
			if (greatest_nonzero == 0) {
				for (std::size_t x = 0; x < M; ++x) {
					for (std::size_t y = 0; y < N; ++y) {
						im[x][y] = std::numeric_limits<size_t>::quiet_NaN();
					}
				}
				return im;
			}
			if (line != j) {
				std::cout << "AVANT SWAP:" << std::endl;
				std::cout << to_string(m) << std::endl;
				std::cout << to_string(im) << std::endl;
				for (std::size_t x = 0; x < M; ++x) {
					std::swap(nm[line][x], nm[j][x]);
					std::swap(im[line][x], im[j][x]);
				}
				std::cout << "APRES SWAP:" << std::endl;
				std::cout << to_string(m) << std::endl;
				std::cout << to_string(im) << std::endl;
			}
			for (std::size_t x = 0; x < M; ++x) {
				std::cout << "AVANT DIV:" << std::endl;
				std::cout << to_string(m) << std::endl;
				std::cout << to_string(im) << std::endl;
				nm[j][x] = nm[j][x] * (1/greatest_nonzero);
				im[j][x] = im[j][x] * (1/greatest_nonzero);
				std::cout << "APRES DIV:" << std::endl;
				std::cout << to_string(m) << std::endl;
				std::cout << to_string(im) << std::endl;
			}
		}
		return im;
	}

	// Return the identity matrice of the matrice give in parameter
	template<typename T, std::size_t M, std::size_t N>
	Matrix<T, M, N> identity_matrix(const Matrix<T, M, N>& m) {
		Matrix<T, M, N> nm;
		for (std::size_t i = 0; i < M; ++i) 
			for (std::size_t j = 0; j < N; ++j) 
				if (i == j)
					nm[i][j] = 1;
		return nm;
	}
	
	/*Tests if a matrix contains NAN(not a number) values.*/
	template<typename T, std::size_t M, std::size_t N>
	bool isnan(const Matrix<T, M, N>& m) {
		for (std::size_t i = 0; i < M ; ++i)
			if (isnan(m[i]))
				return true;
		return false;
	}
	
	//Tests if two matrices contain the same values.
	template<typename T, std::size_t M, std::size_t N>
	bool operator==(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
		for (std::size_t i = 0; i < M ; ++i)
			if (m1[i] != m2[i])
				return false;
		return true;
	}
	
	//Tests if two matrices contain different elements.
	template<typename T, std::size_t M, std::size_t N>
	bool operator!=(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
		for (std::size_t i = 0; i < M ; ++i)
			if (m1[i] == m2[i])
				return false;
		return true;
	}

	//Output operator.
	template<typename T, std::size_t M, std::size_t N>
	std::ostream &operator<<(std::ostream& out, const Matrix<T, M, N>& m) {
		for (std::size_t i = 0; i < M; ++i) {
			out << m[0][0];
			for (std::size_t j = 1; j < N; ++j)
				out << ", " << m[i][j];
			out << std::endl;
		}
		return out;
	}

	//The sum of two matrices.
	template<typename T, std::size_t M, std::size_t N>
	Matrix<T, M, N> operator+(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
		Matrix<T, M, N> m;
		for (std::size_t i = 0; i < M ; ++i)
			m[i] = m1[i] + m2[i];
		return m;
	}
	
	//The negation of a matrix.
	template<typename T, std::size_t M, std::size_t N>
	Matrix<T, M, N> operator-(const Matrix<T, M, N>& m) {
		Matrix<T, M, N> mn;
		for (std::size_t i = 0; i < M; ++i)
			mn[i] = m[i] * -1;
		return mn;
	}

	//The subtraction of two matrices.
	template<typename T, std::size_t M, std::size_t N>
	Matrix<T, M, N> operator-(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
		Matrix<T, M, N> m;
		for (std::size_t i = 0; i < M ; ++i)
			m[i] = m1[i] - m2[i];
		return m;
	}

	//The product of a scalar and a matrix.
	template<typename T, std::size_t M, std::size_t N>
	Matrix<T, M, N> operator*(const T& s, const Matrix<T, M, N>& m) {
		Matrix<T, M, N> nm;
		for (std::size_t i = 0; i < M ; ++i)
			nm[i] = m[i] * s;
		return nm;
	}

	//The product of a matrixand a scalar.
	template<typename T, std::size_t M, std::size_t N>
	Matrix<T, M, N> operator*(const Matrix<T, M, N>& m, const T& s) {
		Matrix<T, M, N> nm;
		for (std::size_t i = 0; i < M; ++i)
			nm[i] = m[i] * s;
		return nm;
	}

	//The product of a matrix and a vector.
	template<typename T, std::size_t M, std::size_t N>
	Vector<T,M> operator*(const Matrix<T, M, N>& m, const Vector<T, N>& v) {
		Vector<T, M> nv;
		for (std::size_t i = 0; i < M; ++i) {
			T val = 0;
			for (std::size_t j = 0; j < N; ++j)
				val += m[i][j] * v[j];
			nv[i] = val;
		}
		return nv;
	}

	//The product of two matrices.
	template<typename T, std::size_t M, std::size_t N, std::size_t	O >
	Matrix<T, M, O> operator*(const Matrix<T, M, N>& m1, const Matrix<T, N, O>& m2) {
		Matrix<T, M, O> m;
		for (std::size_t i = 0; i < M; ++i)
			for (std::size_t j = 0; j < O; ++j)
				for (std::size_t k = 0; k < N; ++k) {
					m[i][j] += m1[i][k] * m2[k][j];
				}
		return m;
	}
	
	/*The division of a matrix by a scalar(same as the multiplication by 1/s).*/
	template<typename T, std::size_t M, std::size_t N>
	Matrix<T, M, N> operator/(const Matrix<T, M, N>& m, const T& s) {
		return m * (1 / s);
	}

	//A string representation of a matrix.
	template<typename T, std::size_t M, std::size_t N>
	std::string to_string(const Matrix<T, M, N>& m) {
		std::string s;
		s.append("(");
		s.append(to_string(m[0]));
		for (std::size_t i = 1; i < M; ++i) {
			s.append(", ");
			s.append(to_string(m[i]));
		}
		s.append(")");
		return s;
	}

	//The transpose of a matrix.
	template<typename T, std::size_t M, std::size_t N>
	Matrix<T, N, M> transpose(const Matrix<T, M, N>& m) {
		Matrix<T, N, M> nm;
		for (std::size_t i = 0; i < N; ++i) {
			for (std::size_t j = 0; j < M; ++j)
				nm[i][j] = m[j][i];
		}
		return Matrix<T, M, N>(m);
	}

	/*Tests if two matrices contain nearly equal values. Two values are nearly equal when
	they are very close, with respect to their magnitudes. For example, 1.0000001 can be
	considered nearly equal to 1, whereas 1.234 is not nearly equal to 1.242. However,
	because of their magnitude, 67329.234 can be considered nearly equal to 67329.242.1*/
	template<typename T, std::size_t M, std::size_t N>
	bool nearly_equal(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2) {
		for (std::size_t i = 0; i < M ; ++i)
			if(!nearly_equal(m1[i], m2[i]))
				return false;
		return true;
	}
}