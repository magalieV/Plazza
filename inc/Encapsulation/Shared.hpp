/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Shared data
 *
 * File creation = 06.05.20
 * Last modification = 06.05.20
 */

#ifndef __SHARED__
#define __SHARED__

#include <iostream>

namespace plazza
{
    class Shared
    {
        public:
            Shared();
            int getData() const;
            std::string getMessage() const;
            void setMessage(const std::string &message);
            void setData(int data);

        private:
            int _data;
            std::string _message;
    };
}

#endif //__SHARED__