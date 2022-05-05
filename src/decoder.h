#ifndef DECODER_H
#define DECODER_H

class Decoder
{
public:
    Decoder();
    ~Decoder();
    int EnabledRow(int address);

private:
    int address;
}