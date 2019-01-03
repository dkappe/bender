//
// Created by dkappe on 9/7/18.
//

#ifndef LC0_GOODIES_H
#define LC0_GOODIES_H


#include "string.h"
#include <fstream>
#include <queue>
#include <mutex>



class goodies {
public:
    goodies();

    virtual ~goodies();

    static void FillQ();

    static std::string Pop();
    static std::string PopFen();

private:

    static const std::string epds[];
    static std::mutex qlock_;
    static std::queue<std::string> queue_;

};


#endif //LC0_GOODIES_H
