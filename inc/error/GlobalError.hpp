/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Global error of plazza
 *
 * File creation = 01.05.20
 * Last modification = 02.05.20
 */

#ifndef __GLOBAL_ERROR__
#define __GLOBAL_ERROR__

#include <iostream>

namespace plazza {
    class GlobalError : public std::exception {
        public:
            GlobalError(const std::string &message,
                        const std::string &component = "Unknown");
            std::string const &getComponent() const;
            virtual ~GlobalError() noexcept {};
            const char *what() const noexcept override;

        private:
            std::string _message;
            std::string _componement;
    };
}

#endif //__GLOBAL__ERROR__