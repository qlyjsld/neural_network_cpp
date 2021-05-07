#pragma once
#include <vector>
#include "mat.h"

typedef std::vector<std::pair<mat, mat>> Training_Data;
typedef std::vector<std::pair<mat, mat>> Test_Data;
typedef std::vector<std::pair<mat, mat>> Batch;

mat sigmoid(const mat& z);
mat sigmoid_prime(const mat& z);

class net {
public:
	net(const std::vector<int>& sizes)
		: sizes(sizes)
	{
		num_layers = sizes.size();

		/* weights is an array of matrices
		* row represents the output neuron
		* col represents the input neuron
		* weights are initialize with normal distribution */
		for (int i = 0; i < sizes.size() - 1; i++) {
			weights.push_back(mat(sizes[i + 1], sizes[i]));
			weights[i].randomize();
		}

		/* bias is a 2D array
		* row represents the layer - 1
		* col represents the neuron */
		for (int i = 0; i < sizes.size() - 1; i++) {
			bias.push_back(mat(sizes[i + 1], 1));
			bias[i].randomize();
		}
	}

	~net() {}

	mat feedforward(mat a);
	void SGD(Training_Data& training_data, int epochs, int mini_batch_size, float eta, const Test_Data& test_data);
	void update_mini_batch(const Batch& batch, float eta);
	int evaluate(const Test_Data& test_data);
	mat cost_derivative(const mat& output_activations, const mat& y);
	std::pair<std::vector<mat>, std::vector<mat>> backprop(const std::pair<mat, mat>& data);

	int num_layers;
	std::vector<int> sizes;
	std::vector<mat> weights;
	std::vector<mat> bias;
};
