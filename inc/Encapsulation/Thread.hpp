/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Encapsulation for mutex
 *
 * File creation = 07.05.20
 * Last modification = 07.05.20
 */

#ifndef __THREAD__
#define __THREAD__

extern "C" {
    #include <pthread.h>
}

#include <csignal>
#include <functional>
#include <atomic>
#include <type_traits>
#include <optional>
#include <iostream>
#include <cstring>

template<typename RETURN, bool V, typename ...ARGS>
class ThreadSerialization;

template<typename RETURN, typename ...ARGS>
class ThreadSerialization<RETURN, true, ARGS...>
{
    private:
        struct ProcedureInformation {
            std::function<RETURN(void)> _function;
            std::atomic_bool *_running;
            std::atomic_bool *_return;
            RETURN *_value;
        };
        std::atomic_bool _running;
        std::atomic_bool _return;
        pthread_t _thread;
        RETURN _value;
        ProcedureInformation _procedureInfo;
    public:
        ThreadSerialization() = delete;
        ThreadSerialization(const ThreadSerialization &) = delete;
        ThreadSerialization(ThreadSerialization &&) = delete;
        ThreadSerialization &operator=(const ThreadSerialization &) = delete;
        ThreadSerialization &operator=(ThreadSerialization &&) = delete;
        ThreadSerialization(std::function<RETURN(ARGS...)> function, ARGS &&... args)
        {
            _running = false;
            _return = false;
            auto procedure = [](void *arg) -> void * {
                ProcedureInformation *procedureInfo = static_cast<ProcedureInformation *>(arg);
                int tmp;

                pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &tmp);
                pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &tmp);
                *(procedureInfo->_running) = true;
                *(procedureInfo->_value) = procedureInfo->_function();
                *(procedureInfo->_running) = false;
                *(procedureInfo->_return) = true;
                return nullptr;
            };
            _procedureInfo = ProcedureInformation{std::bind(function, args...), &_running, &_return, &_value};
            pthread_create(&_thread, NULL, procedure, &_procedureInfo);
        }
        ~ThreadSerialization()
        {
            if (!_running)
                pthread_join(_thread, NULL);
        }
        void cancel()
        {
            if (_running) {
                pthread_cancel(_thread);
                pthread_join(_thread, NULL);
            }
            _running = false;
        }
        void join()
        {
            pthread_join(_thread, NULL);
        }
        void detach()
        {
            pthread_detach(_thread);
        }
        bool isRunning() const noexcept
        {
            return _running;
        }
        std::optional<RETURN> getThreadValue() const noexcept
        {
            if (_running || !_return)
                return std::nullopt;
            return _value;
        }
};

template<typename RETURN, typename ...ARGS>
class ThreadSerialization<RETURN, false, ARGS...>
{
    private:
        struct ProcedureInformation {
            std::function<void(void)> _function;
            std::atomic_bool *_running;
            std::atomic_bool *_return;
        };
        std::atomic_bool _return;
        std::atomic_bool _running;
        pthread_t _thread;
        ProcedureInformation _procedureInfo;
    public:
        ThreadSerialization() = delete;
        ThreadSerialization(const ThreadSerialization &) = delete;
        ThreadSerialization(ThreadSerialization &&) = delete;
        ThreadSerialization &operator=(const ThreadSerialization &) = delete;
        ThreadSerialization &operator=(ThreadSerialization &&) = delete;
        ThreadSerialization(std::function<RETURN(ARGS...)> function, ARGS &&... args)
        {
            _return = false;
            _running = false;
            auto procedure = [](void *arg) -> void * {
                ProcedureInformation *procedureInfo = static_cast<ProcedureInformation *>(arg);
                int tmp;

                pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &tmp);
                pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &tmp);
                *(procedureInfo->_running) = true;
                procedureInfo->_function();
                *(procedureInfo->_running) = false;
                *(procedureInfo->_return) = true;
                return nullptr;
            };
            _procedureInfo = ProcedureInformation{std::bind(function, args...), &_running, &_return};
            pthread_create(&_thread, NULL, procedure, &_procedureInfo);
        }
        ~ThreadSerialization()
        {
            if (!_running)
                pthread_join(_thread, NULL);
        }
        void cancel()
        {
            if (_running) {
                pthread_cancel(_thread);
                pthread_join(_thread, NULL);
            }
            _running = false;
        }
        void join()
        {
            pthread_join(_thread, NULL);
        }
        void detach()
        {
            pthread_detach(_thread);
        }
        bool isRunning() const noexcept
        {
            return _running;
        }
};

template<typename RETURN, typename ...ARGS>
using Thread = ThreadSerialization<RETURN,
    (std::is_default_constructible<RETURN>::value &&
    (std::is_copy_constructible<RETURN>::value || std::is_move_assignable<RETURN>::value)),
    ARGS...>;

#endif //__THREAD__