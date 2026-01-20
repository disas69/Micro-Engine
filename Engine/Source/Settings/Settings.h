#pragma once

#include <yaml-cpp/yaml.h>
#include <fstream>

namespace Micro
{
    template <typename T>
    struct Settings
    {
        bool Save(const std::string& filepath) const
        {
            try
            {
                YAML::Node node = YAML::convert<T>::encode(static_cast<const T&>(*this));

                std::ofstream fout(filepath);
                if (!fout.is_open()) return false;

                fout << node;
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        bool Load(const std::string& filepath)
        {
            try
            {
                YAML::Node node = YAML::LoadFile(filepath);
                return YAML::convert<T>::decode(node, static_cast<T&>(*this));
            }
            catch (...)
            {
                return false;
            }
        }
    };
}  // namespace Micro
