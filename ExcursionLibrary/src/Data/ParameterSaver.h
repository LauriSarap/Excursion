#pragma once
#include "Core/Layer.h"

namespace Data
{
    enum class FileType
    {
        txt,
        hdf5,
        json
    };
    
    void SaveWeightsAndBiases(
            const std::vector<Layer*>& layers,
            const std::string& filename,
            const std::string& path,
            const FileType& fileType
            );

    void SaveAsTxt(
            const std::vector<Layer*>& layers,
            const std::string& filename,
            const std::string& path
            );

    void LoadWeightsAndBiases(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path, const FileType& fileType);

    void LoadFromTxt(const std::vector<Layer*>& layers, const std::string& filename, const std::string& path);
}
