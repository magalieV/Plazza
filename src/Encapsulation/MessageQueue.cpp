/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Encapsulation fo message queue
 *
 * File creation = 04.05.20
 * Last modification = 04.05.20
 */

#include "Encapsulation/MessageQueue.hpp"

/*
template <typename STRUCT>
MessageQueue<STRUCT>::MessageQueue(const std::string &key, int keyNumber)
{
    _key = key;
    _keyNumber = keyNumber;
}

template <typename STRUCT>
MessageQueue<STRUCT>::~MessageQueue()
{
    key_t keyMessage;
    int msgid;
    STRUCT info;

    keyMessage = ftok(_key.c_str(), _keyNumber);
    if (keyMessage == -1)
        return;
    msgid = msgget(keyMessage, 0666 | IPC_CREAT);
    if (msgid == -1)
        return;
    msgctl(msgid, IPC_RMID, NULL);
}

template <typename STRUCT>
bool MessageQueue<STRUCT>::sendMessage(const STRUCT &info)
{
    key_t keyMessage;
    int msgid;

    keyMessage = ftok(_key.c_str(), _keyNumber);
    if (keyMessage == -1)
        return false;
    msgid = msgget(keyMessage, 0666 | IPC_CREAT);
    if (msgid == -1)
        return false;
    return msgsnd(msgid, &info, sizeof(info), 0) != 1;
}

template <typename STRUCT>
STRUCT MessageQueue<STRUCT>::getInfo(STRUCT &info)
{
    key_t keyMessage;
    int msgid;

    keyMessage = ftok(_key.c_str(), _keyNumber);
    if (keyMessage == -1)
        return info;
    msgid = msgget(keyMessage, 0666 | IPC_CREAT);
    if (msgid == -1)
        return info;
    return msgrcv(msgid, &info, sizeof(info), 1, 0) != -1;
}*/