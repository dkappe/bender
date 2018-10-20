//
// Created by dkappe on 9/7/18.
//

#ifndef LC0_EPDQUEUE_H
#define LC0_EPDQUEUE_H


#include "string.h"
#include <fstream>
#include <queue>
#include <mutex>



class epdqueue {
public:
    epdqueue();

    virtual ~epdqueue();

    static void FillQ();

    static std::string Pop();

private:

    static const std::string epds[];
    static std::mutex qlock_;
    static std::queue<std::string> queue_;

};


#endif //LC0_EPDQUEUE_H
