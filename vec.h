#pragma once
class vec {
public:
	vec() {
		vector = nullptr;
	}

	vec(int size) {
		vector = new float[size] { 0.0f };
	}

	~vec() {
		release();
	}

	inline float& operator[](int j) { return vector[j]; }

	void resize(int size);

private:
	float* vector;

	void release();
};