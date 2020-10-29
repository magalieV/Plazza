/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Encapsulation fo message queue
 *
 * File creation = 04.05.20
 * Last modification = 04.05.20
 */

#ifndef __MESSAGE_QUEUE__
#define __MESSAGE_QUEUE__

extern "C"
{
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/msg.h>
    #include <unistd.h>
}

#include <cstring>
#include <cerrno>
#include <iostream>
#include <any>
#include <memory>
#include "plazza_header.hpp"
#include "Pizza/Pizza.hpp"
#include "Encapsulation/Shared.hpp"

struct mesg_buffer {
    long mesg_type;
    int _data;
    char _message[300];
};

class MessageQueue
{
    public:
        MessageQueue(const std::string &key, int keyNumber)
        {
            _key = key;
            _keyNumber = keyNumber;
        }
        ~MessageQueue()
        {

        }
        void deleteQueue()
        {
            key_t keyMessage;
            int msgid;
            plazza::Shared info;

            keyMessage = ftok(_key.c_str(), _keyNumber);
            if (keyMessage == -1)
                return;
            msgid = msgget(keyMessage, 0666 | IPC_CREAT);
            if (msgid == -1)
                return;
            msgctl(msgid, IPC_RMID, NULL);
        }
        bool operator<<(const plazza::Shared &info)
        {
            key_t keyMessage = 0;
            int msgid;

            keyMessage = ftok(".", _keyNumber);
            if (keyMessage == -1) {
                return false;
            }
            msgid = msgget(keyMessage, 0666 | IPC_CREAT);
            if (msgid == -1) {
                return false;
            }
            mesg_buffer test;
            bzero(&test, sizeof(test));
            test.mesg_type = 1;
            test._data = info.getData();
            for (int i = 0; i < info.getMessage().size(); i++)
                test._message[i] = info.getMessage().at(i);
            return msgsnd(msgid, &test, sizeof(test), 0) != -1;
        }
        plazza::Shared getInfo(bool &state, const std::string &pathName, int keyNumber)
        {
            key_t keyMessage;
            int msgid;

            keyMessage = ftok(".", keyNumber);
            if (keyMessage == -1) {
                state = false;
                return plazza::Shared();
            }
            mesg_buffer test;
            test._data = 0;
            msgid = msgget(keyMessage, 0666 | IPC_CREAT);
            if (msgid == -1) {
                state = false;
                return plazza::Shared();
            }
            if (msgrcv(msgid, &test, sizeof(test), 1, 0) == -1) {
                state = false;
                return plazza::Shared();
            }
            state = true;
            plazza::Shared tmp;
            tmp.setData(test._data);
            tmp.setMessage(std::string(test._message));
            return tmp;
        }
    private:
        int _keyNumber;
        std::string _key;
};

#endif //__MESSAGE_QUEUE__
