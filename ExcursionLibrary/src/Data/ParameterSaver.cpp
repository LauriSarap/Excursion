#include "bgpch.h"
#include <fstream>
#include "ParameterSaver.h"
#include "Core/Layer.h"

namespace Data
{
    void SaveWeightsAndBiases(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path, const FileType& fileType)
    {
        switch (fileType)
        {
        case FileType::txt:
            SaveAsTxt(layers, filename, path);
            break;
            
        case FileType::hdf5:
            break;

        case FileType::json:
            break;

        default:
            std::cerr << "Invalid file type specified." << std::endl;
            return;
        }
    }

    void SaveAsTxt(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path)
    {
        std::ofstream file(filename + ".txt");

        for (size_t i = 0; i < layers.size(); ++i)
        {
            file << "Layer " << i << "\n";
            file << "Weights:\n";
            for (int r = 0; r < layers[i]->weights.rows(); ++r)
            {
                for (int c = 0; c < layers[i]->weights.cols(); ++c)
                {
                    file << layers[i]->weights(r, c) << " ";
                }
                file << "\n";
            }
            file << "Biases:\n";
            for (int r = 0; r < layers[i]->biases.rows(); ++r)
            {
                for (int c = 0; c < layers[i]->biases.cols(); ++c)
                {
                    file << layers[i]->biases(r, c) << " ";
                }
                file << "\n";
            }
            file << "\n";
        }

        file.close();
    }

    void LoadWeightsAndBiases(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path, const FileType& fileType)
    {
        switch (fileType)
        {
        case FileType::txt:
            LoadFromTxt(layers, filename, path);
            break;

        case FileType::hdf5:
            break;

        case FileType::json:
            break;

        default:
            std::cerr << "Invalid file type specified." << std::endl;
            return;
        }
    }

    void LoadFromTxt(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path)
    {
        std::ifstream file(filename + ".txt");
        if (!file.is_open())
        {
            std::cerr << "Could not open file." << std::endl;
            return;
        }

        std::string line;
        int currentLayer  = -1;
        bool readingWeights = false;
        bool readingBiases = false;
        int number_row = 0;
        
        while (std::getline(file, line))
        {
            std::cout << "Reading line: " << line << std::endl;
            if (line.empty())
            {
                continue;
            }
            if (line.find("Layer") != std::string::npos)
            {
                // Parse layer index
                currentLayer = std::stoi(line.substr(6));
                readingWeights = false;
                readingBiases = false;
            }
            else if (line == "Weights:")
            {
                readingWeights = true;
                readingBiases = false;
                number_row = 0;
            }
            else if (line == "Biases:")
            {
                readingWeights = false;
                readingBiases = true;
                number_row = 0;
            }
            else if (readingWeights)
            {
                std::istringstream iss(line);
                std::vector<double> values;
                double value;
                while (iss >> value) {
                    values.push_back(value);
                }
                
                size_t colCount = layers[currentLayer]->weights.cols();

                if (values.size() != colCount) {
                    std::cerr << "Mismatch in number of weights for Layer " << currentLayer << std::endl;
                    return;
                }

                for (int c = 0; c < colCount; ++c)
                {
                    layers[currentLayer]->weights(number_row, c) = values[c]; //TODO Change as this writes directly to the matrix. Should be private.
                }

                number_row++;
            }
            else if (readingBiases)
            {
                std::istringstream iss(line);
                std::vector<double> values;
                double value;

                if (!iss.good()) {
                    std::cerr << "Input stream is not in a good state." << std::endl;
                }
                
                while (iss >> value) {
                    values.push_back(value);
                }

                size_t colCount = layers[currentLayer]->biases.cols();
                
                
                if (values.size() != colCount) {
                    std::cerr << "Mismatch in number of biases for Layer " << currentLayer << std::endl; 
                    return;
                }

                for (int c = 0; c < colCount; ++c)
                {
                    layers[currentLayer]->biases(number_row, c) = values[c]; //TODO 2 Change as this writes directly to the matrix. Should be private.
                }

                number_row++;
            }
        }
        file.close();
    }
}
