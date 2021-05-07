#include "mat.h"

#include <random>

// Seed with a real random value, if available
std::random_device r;

// Choose a random mean between -1 and 1
std::default_random_engine e1(r());
std::normal_distribution<float> normal_dist(0.0f, 0.5f);

void mat::randomize() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			matrix[i][j] = normal_dist(e1);
		}
	}
}

mat mat::transpose() {
	mat new_mat(w(), h());
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			new_mat[i][j] = matrix[j][i];
		}
	}
	return new_mat;
}

void mat::zeros() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			matrix[i][j] = 0.0f;
		}
	}
}

void mat::release() {
	if (matrix != nullptr) {
		delete[] matrix;
	}
}