//
// Created by jonas on 03.03.2018.
//

#ifndef YET_ANOTHER_ENGINE_STRING_UTILS_HPP
#define YET_ANOTHER_ENGINE_STRING_UTILS_HPP

#include <regex>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>


namespace yae
{
    namespace pil
    {
        /**
         * std::istream utility to read optional numbers
         */
        template<typename T>
        class expect_number
        {
        public:
            explicit expect_number(T& f)
                    : f(f) {}

        private:
            T& f;

        public:
            friend std::istream& operator>>(std::istream& is, expect_number& en)
            {
                if (std::isdigit(is.peek()))
                {
                    is >> en.f;
                }
                return is;
            }
        };

        /**
         * @brief splits a string on a given regex
         *
         * @param input the string which will be split
         * @param regex to determine the split position
         *
         * @return vector containing the substring afte the split
         */
        inline std::vector<std::string> split(const std::string& input, const std::string& regex)
        {
            std::regex re(regex);
            std::sregex_token_iterator first{input.begin(), input.end(), re, -1}, last;
            return {first, last};
        }
    }
}

#endif //YET_ANOTHER_ENGINE_STRING_UTILS_HPP
