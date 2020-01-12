//
// Created by jonas on 24.02.2018.
//

#ifndef YET_ANOTHER_ENGINE_FILE_UTILS_HPP
#define YET_ANOTHER_ENGINE_FILE_UTILS_HPP

#include <string>
#include <fstream>

namespace yae
{
    namespace pil
    {
        /**
         * @brief reads a file in a std::string
         *
         * @param path to the file
         * @return the text from the file as an object of type std::string
         */
        static std::string read_file(const std::string& path)
        {
            std::fstream file(path);
            std::string buffer;
            std::string line;

            while (!file.eof())
            {
                std::getline(file, line);
                buffer += line + "\n";
            }

            file.close();

            return buffer;
        }

        /**
         * byte typedef for raw data storage
         */
        using byte = unsigned char;
    }
}
#endif //YET_ANOTHER_ENGINE_FILE_UTILS_HPP
