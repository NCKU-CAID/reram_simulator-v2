#include <bitset>
#include <cstdlib>
#include <iostream>

#include "parser.h"
void init();

FILE *fptr;
int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " instruction_file SRAM_file"
                  << std::endl;
        return 1;
    }

    init();


    uint64_t inst;
    while (fscanf(fptr, "%lu", &inst) != EOF) {
        struct layer_config *l = (struct layer_config *) &inst;
        struct transfer_config *t = (struct transfer_config *) &inst;
        struct load_store *s = (struct load_store *) &inst;
        struct conv *c = (struct conv *) &inst;
        struct pooling *p = (struct pooling *) &inst;
        switch (inst & OP_MASK) {
        case layer_config:
            std::cout << "opcode:" << l->opcode << std::endl;
            break;
        case transfer_config:
            break;
        case load:
            break;
        case store:
            break;
        case conv:
            break;
        case pooling:
            break;
        default:
            std::cout << "parse failed!!! no such instruction" << std::endl;
            // return 2;
        }
    }
    return 0;
}

void init()
{
    // new ???
}
