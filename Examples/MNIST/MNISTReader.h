#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include "Dense"

namespace MNIST
{
    typedef uint8_t Pixel;
    typedef uint8_t Label;

    struct MNISTData
    {
        std::vector<Eigen::Matrix<Pixel, Eigen::Dynamic, Eigen::Dynamic>> training_images;
        std::vector<Label> training_labels;
        std::vector<Eigen::Matrix<Pixel, Eigen::Dynamic, Eigen::Dynamic>> test_images;
        std::vector<Label> test_labels;
    };

    inline std::vector<Eigen::Matrix<Pixel, Eigen::Dynamic, Eigen::Dynamic>> read_mnist_image_file(const std::string& path)
    {
        std::ifstream file(path, std::ios::binary);

        if (!file) {
            std::cerr << "Can't open file in: " << path << std::endl;
            return {};
        }

        int32_t magic_number;
        int32_t num_images;
        int32_t num_rows;
        int32_t num_cols;
        
        file.read(reinterpret_cast<char*>(&magic_number), 4);
        file.read(reinterpret_cast<char*>(&num_images), 4);
        file.read(reinterpret_cast<char*>(&num_rows), 4);
        file.read(reinterpret_cast<char*>(&num_cols), 4);

        
        magic_number = _byteswap_ulong(magic_number);
        num_images = _byteswap_ulong(num_images);
        num_rows = _byteswap_ulong(num_rows);
        num_cols = _byteswap_ulong(num_cols);
        

        //std::cout << "magic number = " << magic_number << std::endl;
        //std::cout << "number of images = " << num_images << std::endl;
        //std::cout << "number of rows = " << num_rows << std::endl;
        //std::cout << "number of columns = " << num_cols << std::endl;

        if (magic_number != 0x00000803) {
            std::cerr << "Invalid magic number in file: " << path << std::endl;
            return {};
        }

        std::vector<Eigen::Matrix<Pixel, Eigen::Dynamic, Eigen::Dynamic>> images;
        images.reserve(num_images);

        for (int i = 0; i < num_images; ++i)
        {
            Eigen::Matrix<Pixel, Eigen::Dynamic, Eigen::Dynamic> image(num_rows, num_cols);
            for (int row = 0; row < num_rows; ++row)
            {
                for (int col = 0; col < num_cols; ++col)
                {
                    unsigned char pixel;
                    file.read(reinterpret_cast<char*>(&pixel), 1);
                    image(row, col) = static_cast<Pixel>(pixel);
                }
            }
            images.push_back(image);
        }

        return images;
    }

    inline std::vector<Label> read_mnist_label_file(const std::string& path)
    {
        std::ifstream file(path, std::ios::binary);

        if (!file) {
            std::cerr << "Can't open file in: " << path << std::endl;
            return {};
        }

        int32_t magic_number;
        int32_t num_labels;
        file.read(reinterpret_cast<char*>(&magic_number), 4);
        file.read(reinterpret_cast<char*>(&num_labels), 4);

        magic_number = _byteswap_ulong(magic_number);
        num_labels = _byteswap_ulong(num_labels);

        if (magic_number != 0x00000801) {
            std::cerr << "Invalid magic number in file: " << path << std::endl;
            return {};
        }

        std::vector<Label> labels(num_labels);
        for (int i = 0; i < num_labels; ++i)
        {
            unsigned char label;
            file.read(reinterpret_cast<char*>(&label), 1);
            labels[i] = static_cast<Label>(label);
        }

        return labels;
    }

    inline MNISTData read_mnist_data(const std::string& path)
    {
        MNISTData data;

        std::cout << "Reading MNIST training images.." << std::endl;
        data.training_images = read_mnist_image_file(path + "/train-images.idx3-ubyte");
        std::cout << "Reading MNIST training labels.." << std::endl;
        data.training_labels = read_mnist_label_file(path + "/train-labels.idx1-ubyte");
        std::cout << "Reading MNIST test images.." << std::endl;
        data.test_images = read_mnist_image_file(path + "/t10k-images.idx3-ubyte");
        std::cout << "Reading MNIST test labels.." << std::endl;
        data.test_labels = read_mnist_label_file(path + "/t10k-labels.idx1-ubyte");

        return data;
    }
}
