//
// Created by jonas on 13.03.18.
//

#ifndef YET_ANOTHER_ENGINE_COUNTER_HPP
#define YET_ANOTHER_ENGINE_COUNTER_HPP

namespace yae
{
    namespace utils
    {
        template<typename T>
        class counter
        {
        public:
            counter()
            {
                instance_count++;
            }

            counter(const counter<T>& counter)
            {
                instance_count++;
            }

            virtual ~counter()
            {
                instance_count--;
            }

            static unsigned int instance_count;
        };

        template<typename T>
        unsigned int counter<T>::instance_count = 0;
    }
}

#endif //YET_ANOTHER_ENGINE_COUNTER_HPP
