#include <iostream>
#include <chrono>
#include <fstream>

#include "net.h"

unsigned char** read_mnist_images(const std::string& full_path, int number_of_images);
unsigned char* read_mnist_labels(const std::string& full_path, int number_of_labels);

int main() {
	std::vector<int> sizes{ 784, 30, 10 };
	net network = net(sizes);
	Training_Data training_datas;
	Test_Data test_datas;

    std::cout << "reading training data..." << std::endl;
    unsigned char** datas = read_mnist_images("train-images.idx3-ubyte", 5000);
    unsigned char* labels = read_mnist_labels("train-labels.idx1-ubyte", 5000);
    for (int i = 0; i < 5000; i++) {
        mat data(784, 1);
        mat label(10, 1);
        switch ((int)labels[i])
        {
        case 0:
            label[0][0] = 1;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 1:
            label[0][0] = 0;
            label[1][0] = 1;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 2:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 1;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 3:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 1;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 4:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 1;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 5:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 1;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 6:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 1;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 7:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 1;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 8:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 1;
            label[9][0] = 0;
            break;
        case 9:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 1;
            break;
        }
        for (int j = 0; j < 784; j++) {
            data[j][0] = (float)datas[i][j];
        }
        std::pair<mat, mat> training_data(data, label);
        training_datas.push_back(training_data);
    }
    delete[] datas;
    delete[] labels;

    std::cout << "reading test data..." << std::endl;
    datas = read_mnist_images("t10k-images.idx3-ubyte", 10000);
    labels = read_mnist_labels("t10k-labels.idx1-ubyte", 10000);
    for (int i = 0; i < 10000; i++) {
        mat data(784, 1);
        mat label(10, 1);
        switch ((int)labels[i])
        {
        case 0:
            label[0][0] = 1;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 1:
            label[0][0] = 0;
            label[1][0] = 1;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 2:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 1;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 3:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 1;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case '4':
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 1;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 5:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 1;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case '6':
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 1;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 7:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 1;
            label[8][0] = 0;
            label[9][0] = 0;
            break;
        case 8:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 1;
            label[9][0] = 0;
            break;
        case 9:
            label[0][0] = 0;
            label[1][0] = 0;
            label[2][0] = 0;
            label[3][0] = 0;
            label[4][0] = 0;
            label[5][0] = 0;
            label[6][0] = 0;
            label[7][0] = 0;
            label[8][0] = 0;
            label[9][0] = 1;
            break;
        }
        for (int j = 0; j < 784; j++) {
            data[j][0] = (float)datas[i][j];
        }
        std::pair<mat, mat> test_data(data, label);
        test_datas.push_back(test_data);
    }
    delete[] datas;
    delete[] labels;

	std::cout << "start training..." << std::endl;
	network.SGD(training_datas, 30, 10, 1.0, test_datas);
	return 0;
}

unsigned char** read_mnist_images(const std::string& full_path, int number_of_images) {
    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
    };

    std::ifstream file(full_path, std::ios::binary);

    if (file.is_open()) {
        int magic_number = 0, n_rows = 0, n_cols = 0;

        file.read((char*)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if (magic_number != 2051) throw std::runtime_error("Invalid MNIST image file!");

        file.read((char*)&number_of_images, sizeof(number_of_images)), number_of_images = reverseInt(number_of_images);
        file.read((char*)&n_rows, sizeof(n_rows)), n_rows = reverseInt(n_rows);
        file.read((char*)&n_cols, sizeof(n_cols)), n_cols = reverseInt(n_cols);

        int image_size = n_rows * n_cols;

        unsigned char** _dataset = new unsigned char* [number_of_images];
        for (int i = 0; i < number_of_images; i++) {
            _dataset[i] = new unsigned char[image_size];
            file.read((char*)_dataset[i], image_size);
        }
        return _dataset;
    }
    else {
        throw std::runtime_error("Cannot open file `" + full_path + "`!");
    }
}

unsigned char* read_mnist_labels(const std::string& full_path, int number_of_labels) {
    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
    };

    typedef unsigned char uchar;

    std::ifstream file(full_path, std::ios::binary);

    if (file.is_open()) {
        int magic_number = 0;
        file.read((char*)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if (magic_number != 2049) throw std::runtime_error("Invalid MNIST label file!");

        file.read((char*)&number_of_labels, sizeof(number_of_labels)), number_of_labels = reverseInt(number_of_labels);

        uchar* _dataset = new uchar[number_of_labels];
        for (int i = 0; i < number_of_labels; i++) {
            file.read((char*)&_dataset[i], 1);
        }
        return _dataset;
    }
    else {
        throw std::runtime_error("Unable to open file `" + full_path + "`!");
    }
}