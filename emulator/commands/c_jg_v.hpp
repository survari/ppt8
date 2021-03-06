#ifndef C_JG_V_HPP
#define C_JG_V_HPP

#include <string>
#include <unistd.h>
#include <iostream>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Jg_V : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 102;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override
    {
        if (runtime->DEBUG)
            std::cout << "((JGB " << std::hex << "HX=" << runtime->getHX()->getComplete16bit() << "; " << (int) args[0] << " " << (int) args[1] << " -> " << (int) ppt8_std::combine_8bit_to_16bit(args[0], args[1]) << std::dec << "))" << std::endl;

        if (((int) runtime->getHX()->getComplete16bit()) == 2)
            runtime->PROGRAMM_INDEX = (int) ppt8_std::combine_8bit_to_16bit(args[0], args[1]) - 1;

        if (runtime->DEBUG)
            std::cout << "((JGE " << std::hex << (int) runtime->PROGRAMM_INDEX << std::dec << "))" << std::endl;
        return 0;
    }
};

#endif