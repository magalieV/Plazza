/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Process class
 *
 * File creation = 05.05.20
 * Last modification = 06.05.20
 */

#include "Encapsulation/Process.hpp"

Process::Process()
{
    reini();
}

Process::Process(Process &&pro) noexcept
{
    _pid = pro._pid;
    _pidError = pro._pidError;
    _exitCode = pro._exitCode;
    _running = pro._running;
}

void Process::reini()
{
    _pid = 1;
    _pidError = false;
    _exitCode = -1;
    _running = false;
}

void Process::run(Procedure *procedure)
{
    if (_running)
        return;
    reini();
    _pid = fork();
    _procedure = procedure;
    if (_pid == 0) {
        _exitCode = procedure->run();
        _exit(_exitCode);
    } else if (_pid < 0) {
        _pidError = true;
        _exitCode = 1;
    } else {
        _running = true;
    }
}

int Process::getCode() noexcept
{
    if (_exitCode == -1) {
        waitpid(_pid, &_exitCode, WNOHANG);
        _running = (_exitCode == -1);
    }
    return _exitCode;
}

bool Process::getError() const noexcept
{
    return _pidError;
}

bool Process::wait()
{
    if (_running and !_pidError) {
        waitpid(_pid, &_exitCode, 0);
        _running = false;
        return true;
    }
    return false;
}

bool Process::isRunning()
{
    if (_exitCode == -1) {
        waitpid(_pid, &_exitCode, WNOHANG);
        _running = (_exitCode == -1);
    }
    return _running;
}

bool Process::kill(int killCode)
{
    if (_running and !_pidError) {
        ::kill(_pid, killCode);
        _exitCode = killCode;
        _running = false;
        return true;
    }
    return false;
}