#include "decoder.h"
#include "tile.h"

Decoder::Decoder(){};
Decoder::~Decoder(){};
int Decoder::EnabledRow(int addr, Tile tile, int ID)
{
    int cellBit = tile.cellArray[0][0].numBit;
    int tileSize = tile.size;
    int position;
    switch (ID) {
    case 0:
    case 2:                            // IFM, OFM
        position = addr - 1577058304;  // 0x5e000000
        break;
    case 1:                            // WT
        position = addr - 1593835520;  // 0x5f000000
        break;
    default:
        std::cout << 'The input ID is not allowed' << std::endl;
        break;
    }

    return int(floor(position / tileSize));
}