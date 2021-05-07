#include "vec.h"

void vec::resize(int size) {
	release();
	vector = new float[size] { 0.0f };
}

void vec::release() {
	if (vector != nullptr) {
		delete[] vector;
	}
}