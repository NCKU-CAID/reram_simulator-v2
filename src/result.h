#ifndef RESULT_H
#define RESULT_H

class Result
{
public:
    Result() { power = 0; };
    ~Result();

    float getPower();
    void setPower(float P);
    void storePower(float P);

private:
    float power;
};

float Result::getPower()
{
    return power;
}
void Result::setPower(float P)
{
    power = P;
}
void Result::storePower(float P)
{
    if (P != -1)
        power += P;
}

#endif