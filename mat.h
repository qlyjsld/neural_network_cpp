// This is a matrix class designed for neural network usage
#pragma once
#include "vec.h"

class mat {
public:
	mat(int h, int w)
		: height(h), width(w)
	{
		matrix = new vec[height];
		for (int i = 0; i < height; i++) {
			matrix[i].resize(width);
		}
	}

	mat(const mat& other) {
		height = other.height;
		width = other.width;

		matrix = new vec[height];
		for (int i = 0; i < height; i++) {
			matrix[i].resize(width);
			for (int j = 0; j < width; j++) {
				matrix[i][j] = other.matrix[i][j];
			}
		}
	}

	mat& operator=(const mat& other) {
		if (this != &other) {
			release();
			height = other.height;
			width = other.width;

			matrix = new vec[height];
			for (int i = 0; i < height; i++) {
				matrix[i].resize(width);
				for (int j = 0; j < width; j++) {
					matrix[i][j] = other.matrix[i][j];
				}
			}
		}
		return *this;
	}

	mat(mat&& other) noexcept {
		height = other.height;
		width = other.width;
		matrix = other.matrix;
		other.matrix = nullptr;
	}

	mat& operator=(mat&& other) noexcept {
		if (this != &other) {
			release();
			height = other.height;
			width = other.width;
			matrix = other.matrix;
			other.matrix = nullptr;
		}
		return *this;
	}

	~mat() {
		release();
	}

	inline int h() const { return height; };
	inline int w() const { return width; };

	inline vec& operator[](int i) const { return matrix[i]; }

	mat operator+(const mat& other) const {
		mat new_mat(h(), w());
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				new_mat[i][j] = matrix[i][j] + other[i][j];
			}
		}
		return new_mat;
	}

	mat operator+(float other) const {
		mat new_mat(*this);
		for (int i = 0; i < h(); i++) {
			for (int j = 0; j < w(); j++) {
				new_mat[i][j] = new_mat[i][j] + other;
			}
		}
		return new_mat;
	}

	mat& operator+=(const mat& other) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				matrix[i][j] += other[i][j];
			}
		}
		return *this;
	}

	mat operator-(const mat& other) const {
		mat new_mat(h(), w());
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				new_mat[i][j] = matrix[i][j] - other[i][j];
			}
		}
		return new_mat;
	}

	mat& operator-=(const mat& other) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				matrix[i][j] -= other[i][j];
			}
		}
		return *this;
	}

	mat operator*(const mat& other) const {
		mat new_mat(h(), other.w());
		for (int k = 0; k < w(); k++) {
			for (int i = 0; i < new_mat.h(); i++) {
				for (int j = 0; j < new_mat.w(); j++) {
					new_mat[i][j] += matrix[i][k] * other[k][j];
				}
			}
		}
		return new_mat;
	}

	mat operator*(float other) const {
		mat new_mat(*this);
		for (int i = 0; i < h(); i++) {
			for (int j = 0; j < w(); j++) {
				new_mat[i][j] = new_mat[i][j] * other;
			}
		}
		return new_mat;
	}

	mat& operator*=(const mat& other) {
		mat new_mat(h(), other.w());
		for (int k = 0; k < w(); k++) {
			for (int i = 0; i < new_mat.h(); i++) {
				for (int j = 0; j < new_mat.w(); j++) {
					new_mat[i][j] += matrix[i][k] * other[k][j];
				}
			}
		}
		this->release();
		return new_mat;
	}

	bool operator==(const mat& other) const {
		for (int i = 0; i < h(); i++) {
			for (int j = 0; j < w(); j++) {
				if (matrix[i][j] != other[i][j]) {
					return false;
				}
			}
		}
		return true;
	}


	void randomize(); // flags for methods of randomizing coming soon
	mat transpose();
	void zeros();

private:
	int height;
	int width;

	vec* matrix;

	void release();
};
