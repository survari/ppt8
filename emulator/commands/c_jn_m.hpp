#ifndef C_JN_M_HPP
#define C_JN_M_HPP

#include <string>
#include "../command/command.hpp"
#include "../runtime/runtime.hpp"
#include "../std/functions.hpp"
#include "../std/std.hpp"

class Jn_M : public Command
{
public:
    uint8_t getOpcode() override
    {
        return 107;
    }

    int getLength() override
    {
        return 2;
    }

    int run(std::vector<uint8_t> args, Runtime* runtime) override // jn_m <aa>
    {
        if ((int) runtime->getHX()->getComplete16bit() != 0)
        {
            uint16_t a = ppt8_std::combine_8bit_to_16bit(args[0], args[1]);

            uint8_t high = runtime->getMemory()->getValueFromAddress(a);
            uint8_t low = runtime->getMemory()->getValueFromAddress(a+1);

            runtime->PROGRAMM_INDEX = ppt8_std::combine_8bit_to_16bit(high, low) - 1;
        }

        return 0;
    }
};

#endif