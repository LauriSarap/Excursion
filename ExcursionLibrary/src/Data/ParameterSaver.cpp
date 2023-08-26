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
            SaveAsHdf5(layers, filename, path);
            break;

        case FileType::json:
            SaveAsJson(layers, filename, path);
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

    void SaveAsJson(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path)
    {
        std::ofstream file(filename + ".json");
        
        file << "{\n";
        for (size_t i = 0; i < layers.size(); ++i)
        {
            if (layers[i]->weights.size() == 0 && layers[i]->biases.size() == 0) {

                file << "  \"Layer_" << i << "\": { }";
                if (i < layers.size() - 1) {
                    file << ",\n";
                } else {
                    file << "\n";
                }
                continue;  // Skip this layer
            }

            file << "  \"Layer_" << i << "\": {\n";
            file << "    \"weights\": [\n";
            for (int r = 0; r < layers[i]->weights.rows(); ++r) {
                file << "      [";
                for (int c = 0; c < layers[i]->weights.cols(); ++c) {
                    file << layers[i]->weights(r, c);
                    if (c < layers[i]->weights.cols() - 1) {
                        file << ", ";
                    }
                }
                file << "]";
                if (r < layers[i]->weights.rows() - 1) {
                    file << ",\n";
                } else {
                    file << "\n";
                }
            }
            file << "    ],\n";  // End of weights array

            // Save biases
            file << "    \"biases\": [\n";
            for (int r = 0; r < layers[i]->biases.rows(); ++r) {
                file << "      [";
                for (int c = 0; c < layers[i]->biases.cols(); ++c) {
                    file << layers[i]->biases(r, c);
                    if (c < layers[i]->biases.cols() - 1) {
                        file << ", ";
                    }
                }
                file << "]";
                if (r < layers[i]->biases.rows() - 1) {
                    file << ",\n";
                } else {
                    file << "\n";
                }
            }
            file << "    ]\n";  // End of biases array

            file << "  }";  // End of Layer object
            if (i < layers.size() - 1) {
                file << ",\n";
            } else {
                file << "\n";
            }
        }
        file << "}\n";

        file.close();
    }

    void SaveAsHdf5(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path)
    {
        
    }


    void LoadWeightsAndBiases(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path, const FileType& fileType)
    {
        switch (fileType)
        {
        case FileType::txt:
            LoadFromTxt(layers, filename, path);
            break;

        case FileType::hdf5:
            LoadFromHdf5(layers, filename, path);
            break;

        case FileType::json:
            LoadFromJson(layers, filename, path);
            break;

        default:
            std::cerr << "Invalid file type specified." << std::endl;
            return;
        }
    }

    void LoadFromTxt(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path)
    {
        std::cout << "Loading model from txt" << std::endl;
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
            //std::cout << "Reading line: " << line << std::endl;
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
                while (iss >> value)
                {
                    values.push_back(value);
                }
                
                size_t colCount = layers[currentLayer]->weights.cols();

                if (values.size() != colCount)
                {
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
                    layers[currentLayer]->biases(number_row, c) = values[c]; //TODO Change as this writes directly to the matrix. Should be private.
                }

                number_row++;
            }
        }
        file.close();
    }

    void LoadFromJson(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path)
    {
        std::cout << "Loading model from json" << std::endl;
        std::ifstream file(filename + ".json");
        if (!file.is_open())
        {
            std::cerr << "Could not open file." << std::endl;
            return;
        }

        std::string line;
        int currentLayer = -1;
        bool readingWeights = false;
        bool readingBiases = false;
        int number_row = 0;

        while (std::getline(file, line))
        {
            //std::cout << "Reading line: " << line << std::endl;
            if (line.empty())
            {
                continue;
            }
            if (line.find("\"Layer_") != std::string::npos)
            {
                // Parse layer index
                size_t numberStart = line.find('_');
                size_t numberEnd = line.find(':');
                if (numberStart != std::string::npos && numberEnd != std::string::npos && numberEnd > numberStart)
                {
                    std::string layerNumberStr = line.substr(numberStart + 1, numberEnd - numberStart - 1);
                    currentLayer = std::stoi(layerNumberStr);
                }
                readingWeights = false;
                readingBiases = false;
            }
            else if (line.find("\"weights\":") != std::string::npos)
            {
                readingWeights = true;
                readingBiases = false;
                number_row = 0;
            }
            else if (line.find("\"biases\":") != std::string::npos)
            {
                readingWeights = false;
                readingBiases = true;
                number_row = 0;
            }
            else if (readingWeights || readingBiases)
            {
                std::istringstream iss(line);
                std::vector<double> values;
                double value;
                char ch;

                while (iss >> ch)
                {
                    if (ch == '[' ||
                        ch == ']' ||
                        ch == ',' ||
                        ch == ' ' ||
                        ch == '{' ||
                        ch == '}'
                        ) continue;
                    iss.putback(ch);
                    iss >> value;
                    //std::cout << value << std::endl;
                    values.emplace_back(value);
                }

                if (values.empty())
                {
                    continue;
                }

                if (readingWeights)
                {
                    size_t colCount = layers[currentLayer]->weights.cols();

                    if (values.size() != colCount && values.empty() == false)
                    {
                        std::cerr << "Mismatch in number of weights for Layer " << currentLayer << std::endl;
                        return;
                    }

                    for (int c = 0; c < colCount; ++c)
                    {
                        layers[currentLayer]->weights(number_row, c) = values[c]; //TODO Change as this writes directly to the matrix. Should be private.
                    }
                }
                else if (readingBiases)
                {
                    size_t colCount = layers[currentLayer]->biases.cols();

                    if (values.size() != colCount && values.empty() == false)
                    {
                        std::cerr << "Mismatch in number of biases for Layer " << currentLayer << std::endl;
                        return;
                    }

                    for (int c = 0; c < colCount; ++c)
                    {
                        layers[currentLayer]->biases(number_row, c) = values[c]; //TODO Change as this writes directly to the matrix. Should be private.
                    }
                }
                number_row++;
            }
        }

        file.close();
    }

    void LoadFromHdf5(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path)
    {
        
    }
}
