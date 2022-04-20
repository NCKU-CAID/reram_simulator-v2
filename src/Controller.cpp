#include <bitset>
#include <iostream>
#include "parser.h"
// assume input is hax(without 0x)
// and default is little endian


int main()
{
    while (std::cin.peek() != std::char_traits<char>::eof()) {
        // input
        uint64_t inst;
        std::cin >> std::hex >> inst;
        // use __builtin_bswap64(in) if it's big endian
        // inst = __builtin_bswap64(inst);

        // ex: use base or any type of instruction of opcode to get opcode
        struct layer_config *l = (struct layer_config *) &inst;
        struct transfer_config *t = (struct transfer_config *) &inst;
        struct load_store *s = (struct load_store *) &inst;
        struct conv *c = (struct conv *) &inst;
        struct pooling *p = (struct pooling *) &inst;

        switch (inst & OP_MASK) {
        case layer_config:
            std::cout << "layer_config" << std::endl;
            std::cout << "opcode:" << l->opcode << std::endl;
            std::cout << "input_w:" << l->input_w << std::endl;
            std::cout << "input_h:" << l->input_h << std::endl;
            std::cout << "input_c:" << l->input_c << std::endl;
            std::cout << "f_size:" << l->f_size << std::endl;
            std::cout << "f_num:" << l->f_num << std::endl;
            std::cout << "stride:" << l->stride << std::endl;
            std::cout << "deq:" << l->deq << std::endl;
            std::cout << std::endl;
            break;
        case transfer_config:
            std::cout << "transfer_config" << std::endl;
            std::cout << "opcode:" << t->opcode << std::endl;
            std::cout << "right_pad:" << t->right_pad << std::endl;
            std::cout << "left_pad:" << t->left_pad << std::endl;
            std::cout << "bot_pad:" << t->bot_pad << std::endl;
            std::cout << "top_pad:" << t->top_pad << std::endl;
            std::cout << "channel:" << t->channel << std::endl;
            std::cout << "tile_h:" << t->tile_h << std::endl;
            std::cout << "tile_w:" << t->tile_w << std::endl;
            std::cout << std::endl;
            break;
        case load:
            std::cout << "load" << std::endl;
            std::cout << "opcode:" << s->opcode << std::endl;
            std::cout << "SRAM_addr:" << std::hex << s->SRAM_addr << std::endl;
            std::cout << "SRAM_ID:" << s->SRAM_ID << std::endl;
            std::cout << "DRAM_addr:" << std::hex << s->DRAM_addr << std::endl;
            std::cout << "DEPT:" << s->DEPT << std::endl;
            std::cout << std::endl;
            break;
        case store:
            std::cout << "store" << std::endl;
            std::cout << "opcode:" << s->opcode << std::endl;
            std::cout << "SRAM_addr:" << std::hex << s->SRAM_addr << std::endl;
            std::cout << "SRAM_ID:" << s->SRAM_ID << std::endl;
            std::cout << "DRAM_addr:" << std::hex << s->DRAM_addr << std::endl;
            std::cout << "DEPT:" << s->DEPT << std::endl;
            std::cout << std::endl;
            break;
        case conv:
            std::cout << "conv" << std::endl;
            std::cout << "opcode :" << c->opcode << std::endl;
            std::cout << "shift :" << c->shift << std::endl;
            std::cout << "L :" << c->L << std::endl;
            std::cout << "ACT :" << c->ACT << std::endl;
            std::cout << "WSRAM_addr :" << std::hex << c->WSRAM_addr
                      << std::endl;
            std::cout << "Ibank_addr :" << std::hex << c->Ibank_addr
                      << std::endl;
            std::cout << "Ibank_id :" << c->Ibank_id << std::endl;
            std::cout << "tile_h :" << c->tile_h << std::endl;
            std::cout << "tile_w :" << c->tile_w << std::endl;
            std::cout << "OSRAM_addr :" << std::hex << c->OSRAM_addr
                      << std::endl;
            std::cout << "DEPT :" << c->DEPT << std::endl;
            std::cout << std::endl;
            break;
        case pooling:
            std::cout << "pooling" << std::endl;
            std::cout << "opcode :" << p->opcode << std::endl;
            std::cout << "stride :" << p->stride << std::endl;
            std::cout << "pool_size :" << p->pool_size << std::endl;
            std::cout << "type :" << p->type << std::endl;
            std::cout << "tile_h :" << p->tile_h << std::endl;
            std::cout << "tile_w :" << p->tile_w << std::endl;
            std::cout << "OSRAM_addr :" << std::hex << p->OSRAM_addr
                      << std::endl;
            std::cout << "DEPT :" << p->DEPT << std::endl;
            std::cout << std::endl;
            break;
        default:
            std::cout << "unknown command" << std::endl;
            break;
        }
    }
    return 0;
}
