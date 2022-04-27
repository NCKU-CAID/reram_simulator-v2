#ifndef PARSER_H_
#define PARSER_H_

// TODO: check endian
// https://stackoverflow.com/questions/2100331/c-macro-definition-to-determine-big-endian-or-little-endian-machine
// default is little endian
#include <cstdint>
#define OP_MASK 0xfC00000000000000LL

enum opcode {
    layer_config = 0x0000000000000000LL,
    transfer_config = 0x0400000000000000LL,
    load = 0x0800000000000000LL,
    store = 0x0C00000000000000LL,
    conv = 0x1000000000000000LL,
    pooling = 0x1400000000000000LL,
};
struct __attribute__((__packed__)) layer_config {
    uint64_t reserved2 : 7;
    uint64_t shift : 6;
    uint64_t input_c : 11;
    uint64_t input_h : 9;
    uint64_t input_w : 9;
    uint64_t reserved1 : 2;
    uint64_t add_bias : 1;
    uint64_t do_reg : 1;
    uint64_t ACT : 4;
    uint64_t stride : 4;
    uint64_t f_size : 4;
    uint64_t opcode : 6;
};
struct __attribute__((__packed__)) transfer_config {
    uint64_t reserved : 2;
    uint64_t batch : 11;
    uint64_t channel : 11;
    uint64_t height : 9;
    uint64_t width : 9;
    uint64_t right_pad : 4;
    uint64_t left_pad : 4;
    uint64_t bot_pad : 4;
    uint64_t top_pad : 4;
    uint64_t opcode : 6;
};
struct __attribute__((__packed__)) load {
    uint64_t SRAM_addr : 19;
    uint64_t SRAM_ID : 3;
    uint64_t DRAM_addr : 32;
    uint64_t DEPT : 4;
    uint64_t opcode : 6;
};
struct __attribute__((__packed__)) store {
    uint64_t SRAM_addr : 19;
    uint64_t SRAM_ID : 3;
    uint64_t DRAM_addr : 32;
    uint64_t DEPT : 4;
    uint64_t opcode : 6;
};
struct __attribute__((__packed__)) conv {
    uint64_t empty : 2;
    uint64_t L : 1;
    uint64_t WSRAM_addr : 10;
    uint64_t add_psum : 1;
    uint64_t ISRAM_addr : 10;
    uint64_t tile_h : 9;
    uint64_t tile_w : 9;
    uint64_t OSRAM_addr : 12;
    uint64_t DEPT : 4;
    uint64_t opcode : 6;
};
struct __attribute__((__packed__)) pooling {
    uint64_t empty : 14;
    uint64_t stride : 5;
    uint64_t pool_size : 5;
    uint64_t tile_h : 9;
    uint64_t tile_w : 9;
    uint64_t OSRAM_addr : 12;
    uint64_t DEPT : 4;
    uint64_t opcode : 6;
};
#endif // PARSER_H_
