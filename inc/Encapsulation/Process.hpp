/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Process class
 *
 * File creation = 05.05.20
 * Last modification = 06.05.20
 */

#ifndef __PROCESS_CLASS__
#define __PROCESS_CLASS__

#include <iostream>
#include <csignal>
#include <climits>
#include <cstdlib>

extern "C" {
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
}

#include <functional>
#include "Encapsulation/Procedure.hpp"

class Process
{

    public:
        Process();
        ~Process() = default;
        Process(const Process &) = delete;
        Process(Process &&) noexcept;
        Process &operator=(const Process &) = delete;
        Process &operator=(Process &&) = delete;
        void run(Procedure *procedure);
        bool isRunning();
        bool kill(int killCode = SIGTERM);
        bool wait();
        [[nodiscard]] bool getError() const noexcept;
        [[nodiscard]] int getCode() noexcept;

    private:
        void reini();
        pid_t _pid;
        bool _pidError;
        int _exitCode;
        bool _running;
        Procedure *_procedure;
};

#endif //__PROCESS_CLASS