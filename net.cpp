#include "net.h"

#include <iostream>
#include <algorithm>
#include <random>


std::default_random_engine rng = std::default_random_engine{};

mat sigmoid(const mat& z) {
	mat new_mat = z;
	for (int i = 0; i < new_mat.h(); i++) {
		new_mat[i][0] = 1.0f / (1.0f + exp(-new_mat[i][0]));
	}
	return new_mat;
}

mat sigmoid_prime(const mat& z) {
	return sigmoid(z) * (sigmoid(z) * -1 + 1);
}

mat net::feedforward(mat a) {
	for (int i = 0; i < weights.size(); i++) {
		a = sigmoid(weights[i] * a + bias[i]);
	}
	return a;
}

void net::SGD(Training_Data& training_data, int epochs, int mini_batch_size, float eta, const Test_Data& test_data) {
	int n_test = 0;
	if (!test_data.empty()) {
		n_test = test_data.size();
	}

	int n = training_data.size();
	for (int i = 0; i < epochs; i++) {
		std::shuffle(std::begin(training_data), std::end(training_data), rng);
		for (int k = 0; k < n; k += mini_batch_size) {
			Batch batch;
			for (int c = k; c < k + mini_batch_size; c++) {
				batch.push_back(training_data[c]);
			}
			update_mini_batch(batch, eta);
		}

		if (!test_data.empty()) {
			std::cout << "Epoch {" << i << "}: {" << evaluate(test_data) << "} / {" << n_test << "}" << std::endl;
		}
		else {
			std::cout << "Epoch {" << i << "} complete." << std::endl;
		}
	}
}

void net::update_mini_batch(const Batch& batch, float eta) {
	std::vector<mat> nabla_w = weights;
	std::vector<mat> nabla_b = bias;
	for (auto& nw : nabla_w) {
		nw.zeros();
	}
	for (auto& nb : nabla_b) {
		nb.zeros();
	}

	for (auto& data : batch) {
		std::pair<std::vector<mat>, std::vector<mat>> delta_nabla = backprop(data);
		for (int itr = 0; itr < weights.size(); itr++) {
			nabla_w[itr] = nabla_w[itr] + delta_nabla.second[itr];
		}

		for (int itr = 0; itr < weights.size(); itr++) {
			nabla_b[itr] = nabla_b[itr] + delta_nabla.first[itr];
		}
	}

	for (int itr = 0; itr < weights.size(); itr++) {
		weights[itr] = weights[itr] - nabla_w[itr] * (eta / batch.size());
		// std::cout << (nabla_w[itr] * (eta / batch.size()))[0][0] << std::endl;
		bias[itr] = bias[itr] - nabla_b[itr] * (eta / batch.size());
		// std::cout << (nabla_b[itr] * (eta / batch.size()))[0][0] << std::endl;
	}
}

int net::evaluate(const Test_Data& test_data) {
	int test_result = 0;
	for (auto& data : test_data) {
		mat temp = feedforward(data.first);
		float max = 0;
		int ans = 0;
		for (int i = 0; i < 10; i++) {
			if (temp[i][0] > max) {
				max = temp[i][0];
				ans = i;
			}
		}
		temp.zeros();
		temp[ans][0] = 1;

		if (temp == data.second) {
			test_result += 1;
		}
	}
	return test_result;
}

mat net::cost_derivative(const mat& output_activations, const mat& y) {
	return output_activations - y;
}

std::pair<std::vector<mat>, std::vector<mat>> net::backprop(const std::pair<mat, mat>& data) {
	std::vector<mat> nabla_w = weights;
	std::vector<mat> nabla_b = bias;
	for (auto& nw : nabla_w) {
		nw.zeros();
	}
	for (auto& nb : nabla_b) {
		nb.zeros();
	}
	mat activation = data.first;
	std::vector<mat> activations;
	activations.push_back(activation);
	std::vector<mat> zs;

	for (int itr = 0; itr < weights.size(); itr++) {
		mat z = weights[itr] * activation + bias[itr];
		zs.push_back(z);
		activation = sigmoid(z);
		activations.push_back(activation);
	}

	mat delta = cost_derivative(activations[activations.size() - 1], data.second) * sigmoid_prime(zs[zs.size() - 1]);
	nabla_b[nabla_b.size() - 1] = delta;
	nabla_w[nabla_w.size() - 1] = delta * activations[activations.size() - 2].transpose();

	for (int i = weights.size() - 2; i >= 1; i--) {
		mat z = zs[i - 1];
		mat sp = sigmoid_prime(z);
		delta = (weights[i + 1].transpose() * delta) * sp;
		nabla_b[i] = delta;
		nabla_w[i] = delta * activations[i - 1].transpose();
	}
	return std::pair<std::vector<mat>, std::vector<mat>>{nabla_b, nabla_w};
}
