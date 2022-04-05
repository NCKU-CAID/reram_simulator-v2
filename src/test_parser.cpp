#include <bitset>
#include <iostream>
#include "parser.h"
// assume input is hax(without 0x)
// and default is little endian


int main()
{
    while (std::cin.peek() != std::char_traits<char>::eof()) {
        // input
        // use __builtin_bswap64(in) if it's big endian
        uint64_t inst;
        std::cin >> std::hex >> inst;

        // ex: use base or any type of instruction of opcode to get opcode
        struct layer_config *l = (struct layer_config *) &inst;

        switch (inst & OP_MASK) {
        case layer_config:
            std::cout << std::endl;
            std::cout << l->opcode << std::endl;
            std::cout << l->input_w << std::endl;
            std::cout << l->input_h << std::endl;
            std::cout << l->input_c << std::endl;
            std::cout << l->f_size << std::endl;
            std::cout << l->f_num << std::endl;
            std::cout << l->stride << std::endl;
            std::cout << l->deq << std::endl;
            std::cout << std::endl;
            break;
        case transfer_config:
            break;
        case load_store:
            break;
        case conv:
            break;
        case pooling:
            break;
        default:
            break;
        }
    }
    return 0;
}
