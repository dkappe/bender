//
// Created by dkappe on 9/7/18.
//

#include "goodies.h"
#include "utils/random.h"
#include <string>
#include <sstream>
#include <iostream>

goodies::goodies() {
}

goodies::~goodies() {
}

std::mutex goodies::qlock_;
std::queue<std::string> goodies::queue_;


void goodies::FillQ() {
    qlock_.lock();
    std::fstream infile("startpos.epd");
    std::string s;
    while(getline(infile,s)) {
        queue_.push(s);
    }
    infile.close();
    qlock_.unlock();
    fprintf(stderr, "Read %lu epd's.\n", queue_.size());
}

std::string goodies::PopFen() {
    std::string retval;
    qlock_.lock();
    if (queue_.empty()) {
        retval = std::string();
    } else {
        retval = queue_.front();
        queue_.pop();
    }
    qlock_.unlock();
    return retval;
}

std::string goodies::Pop() {
    std::string retval;
    qlock_.lock();
    if (queue_.empty()) {
        retval = std::string();
    } else {
        retval = queue_.front();
        queue_.pop();
    }
    qlock_.unlock();

    // tack on fen stuff
    int ply = 0;
    if (lczero::Random::Get().GetInt(1,10) > 9) {
        ply = lczero::Random::Get().GetInt(0,99);
        fprintf(stderr, "ply is %d\n", ply);
    } else {
        fprintf(stderr, "No special ply.\n");
    }

    std::ostringstream stringStream;
    stringStream << " " << ply << " 80";

    retval.append(stringStream.str());

    fprintf(stderr, "%s\n", retval.c_str());

    return retval;
}

const std::string goodies::epds[] = {
        "1b1B1k2/5n1p/6p1/PB6/5p2/7P/5PK1/8 w - -",
        "1B1b1k2/5pp1/2P4p/8/P7/6P1/5P1P/6K1 w - -",
        "1B1b1k2/5pp1/7p/3p4/8/3B1NP1/6KP/8 w - -",
        "1B1b1k2/5pp1/7p/3p4/8/5NP1/2B3KP/8 b - -",
        "1B1b1k2/7p/4p2P/3B4/p5P1/1nR2K2/8/8 b - -",
        "1b1B1k2/7p/6p1/PB2n3/5p2/7P/5PK1/8 b - -",
        "1b1B1k2/7p/6p1/PB6/3n1p2/7P/5P2/5K2 w - -",
        "1b1B1k2/7p/6p1/PB6/5p2/5n1P/5P2/5K2 b - -",
        "1B1b1k2/8/1p2P3/p1p2K2/P1P5/1P5p/8/8 w - -",
        "1b1B1k2/8/8/1P1Kp3/3p1p2/3B4/P5PP/8 w - -",
        "1B1b1R2/6pp/2P1k3/4p3/3p4/7P/6P1/7K b - -",
        "1B1b2k1/1p1P3p/6p1/8/4p1P1/7P/4K1P1/8 w - -",
        "1b1B2k1/1r4pp/8/8/8/1b4P1/1P2R3/R5K1 b - -",
        "1B1b2k1/2p1P1p1/8/3P4/4PP1p/7P/6K1/8 b - -",
        "1B1b2k1/2p3p1/4P3/3P4/4PP1p/7P/6K1/8 w - -",
        "1B1b2k1/3P4/1pb2p1P/5B2/1PK4P/8/8/8 w - -",
        "1B1b2k1/3P4/7p/1p6/2p3P1/2P2p2/1P6/5K2 w - -",
        "1B1b2k1/5n2/8/3Q2P1/3P2P1/2r2NK1/8/q7 b - -",
        "1B1b2k1/5p2/1p5p/1P4p1/6P1/4PK1P/8/8 b - -",
        "1B1b2k1/5pp1/2P4p/8/P7/6P1/5P1P/6K1 b - -",
        "1B1b2k1/5pp1/7p/3p4/8/3B1NP1/6KP/8 b - -",
        "1b1B2k1/6p1/3Np3/2P4p/2K5/8/1rb5/4R3 w - -",
        "1b1B2k1/6p1/3Np3/2P4p/8/2K5/1rb5/4R3 b - -",
        "1b1B2k1/6p1/3Np3/2P4p/8/2K5/r1b5/4R3 w - -",
        "1B1b2k1/8/1p4P1/2p2K2/2P1N3/1P2P3/n7/8 w - -",
        "1B1b2k1/p7/1p4P1/1P1p1p1K/3P4/2P5/8/8 w - -",
        "1b1B2r1/3R1p2/4p3/1B1pP3/5k1p/8/7K/8 w - -",
        "1B1b2r1/8/R2p4/1N1P3k/4pp2/8/6P1/5K2 b - -"
};
