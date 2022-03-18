#ifndef PARSER_H
#define PARSER_H

//TODO: check endian https://stackoverflow.com/questions/2100331/c-macro-definition-to-determine-big-endian-or-little-endian-machine
// default is little endian
#include<cstdint>

enum opcode{
	layer_config = 1,
	transfer_config,
	load_store,
	conv,
	pooling,
};
struct __attribute__((__packed__)) base{
	uint64_t empty		:60;
	enum opcode opcode	:4;
};
struct __attribute__((__packed__)) layer_config{
	uint64_t empty		:7;
	uint64_t deq		:1;
	uint64_t stride		:4;
	uint64_t f_num		:11;
	uint64_t f_size		:4;
	uint64_t input_c	:11;
	uint64_t input_h	:11;
	uint64_t input_w	:11;
	enum opcode opcode	:4;
};
struct __attribute__((__packed__)) transfer_config{
	uint64_t empty 		:22;
	uint64_t right_pad	:4;
	uint64_t left_pad	:4;
	uint64_t bot_pad	:4;
	uint64_t top_pad	:4;
	uint64_t channel	:10;
	uint64_t tile_h		:6;
	uint64_t tile_w		:6;
	enum opcode opcode	:4;
};
struct __attribute__((__packed__)) load_store{
	uint64_t empty 		:5;
	uint64_t SRAM_addr	:17;
	uint64_t SRAM_ID	:2;
	uint64_t DRAM_addr	:32;
	uint64_t DEPT		:4;
	enum opcode opcode	:4;
};
struct __attribute__((__packed__)) conv{
	uint64_t empty 		:8;
	uint64_t shift		:4;
	uint64_t L			:1;
	uint64_t ACT		:2;
	uint64_t WSRAM_addr	:7;
	uint64_t Ibank_addr	:4;
	uint64_t Ibank_id	:6;
	uint64_t tile_h		:6;
	uint64_t tile_w		:6;
	uint64_t OSRAM_addr	:12;
	uint64_t DEPT		:4;
	enum opcode opcode	:4;
};
struct __attribute__((__packed__)) pooling{
	uint64_t empty 		:21;
	uint64_t stride 	:4;
	uint64_t pool_size	:4;
	uint64_t type		:3;
	uint64_t tile_h		:6;
	uint64_t tile_w		:6;
	uint64_t OSRAM_addr	:12;
	uint64_t DEPT		:4;
	enum opcode opcode	:4;
};
union instruction{
	uint64_t binary;
	struct base base;
	struct layer_config layer_config;
	struct transfer_config transfer_config;
	struct load_store load_store;
	struct conv conv;
	struct pooling pooling;
};
#endif
