#pragma once

#include "Settings/Settings.h"
#include "Services/Service.h"

#include <yaml-cpp/yaml.h>
#include <fstream>

namespace Micro
{
    class SettingsService : public Service
    {
        const std::string SETTINGS_DIRECTORY = "Settings";

    public:
        template <typename T>
        bool Save(const T& settings) const
        {
            static_assert(std::is_base_of<Settings, T>::value, "T must be derived from Settings");

            try
            {
                if (!std::filesystem::exists(SETTINGS_DIRECTORY))
                {
                    std::filesystem::create_directory(SETTINGS_DIRECTORY);
                }

                YAML::Node node = YAML::convert<T>::encode(settings);

                std::string filepath = SETTINGS_DIRECTORY + "/" + settings.GetFileName();
                std::ofstream fout(filepath);
                if (!fout.is_open()) return false;

                fout << node;
                return true;
            }
            catch (const YAML::Exception&)
            {
                // TODO: log yaml error
                return false;
            }
            catch (...)
            {
                // TODO: log unknown error
                return false;
            }
        }

        template <typename T>
        bool Load(T& outSettings) const
        {
            static_assert(std::is_base_of<Settings, T>::value, "T must be derived from Settings");

            try
            {
                if (!std::filesystem::exists(SETTINGS_DIRECTORY))
                {
                    std::filesystem::create_directory(SETTINGS_DIRECTORY);
                }

                std::string filepath = SETTINGS_DIRECTORY + "/" + outSettings.GetFileName();
                YAML::Node node = YAML::LoadFile(filepath);
                return YAML::convert<T>::decode(node, outSettings);
            }
            catch (const YAML::Exception&)
            {
                // TODO: log yaml error
                return false;
            }
            catch (...)
            {
                return false;
            }
        }

        template <typename T>
        T LoadOrDefault() const
        {
            T settings{};
            Load(settings);
            return settings;
        }
    };
}  // namespace Micro
