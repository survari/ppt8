#ifndef C_JE_R_HPP
#define C_JE_R_HPP

#include <string>
#include <unistd.h>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Je_R : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 97;
    }

    int getLength() override
    {
        return 1;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override
    {
        if (runtime->DEBUG)
            std::cout << "((JEB " << std::hex << "HX=" << runtime->getHX()->getComplete16bit() << "; " << (int) args[0] << " " << (int) args[1] << " -> " << (int) ppt8_std::combine_8bit_to_16bit(args[0], args[1]) << std::dec << "))" << std::endl;

        if (((int) runtime->getHX()->getComplete16bit()) == 0)
            runtime->PROGRAMM_INDEX = (int) runtime->getRegisterByID(args[0])->getComplete16bit() - 1;

        if (runtime->DEBUG)
            std::cout << "((JEE " << std::hex << (int) runtime->PROGRAMM_INDEX << std::dec << "))" << std::endl;
        return 0;
    }
};

#endif