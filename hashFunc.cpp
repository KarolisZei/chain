#include "includes.h"

#include <stdio.h>
#include <string.h>
int intToAscii(int val) { return '0' + val; }
std::string hash(std::string input)
{

    uint values[8][16];

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            values[i][j] = 0;
        }
    }

    int block = 0, counter = 0;

    for (int i = 0; i < 16; i++)
    {
        if (input.length() > i)
            values[block][counter] = ((int)input[i] * 256) % 126;
        else if (input.length() < i)
            break;

        if (values[block][counter] < 32)
        {
            values[block][counter] += 33;
        }

        counter += 1;

        if (counter == 16)
        {
            block += 1;
            counter = 0;
            if (block == 8)
            {
                block = 0;
            }
        }
    }

    std::vector<char> tempVec{};

    for (size_t i = 0; i < 8; i++)
    {

        block = 0;

        int backCounter = 15;

        uint excess = 1;

        uint tempVal = 1;

        counter = 0;

        for (int j = 0; j < 16; j++)
        {
            while (true)
            {
                values[block][counter] = ((values[block][0] * 127) % 255 + values[block][backCounter]) % 255;

                tempVal += values[block][counter] * values[block][counter] * excess;

                tempVal /= 11;

                values[block][counter] = tempVal;

                int tempCounter = 0;

                for (auto &&i : values[block])
                {
                    if (values[block][tempCounter] > 126)
                    {
                        excess += values[block][tempCounter] / 126 * 5;
                        values[block][tempCounter] %= 126;
                    }

                    values[block][tempCounter] = (i * values[block][counter]) % 126;

                    if (values[block][tempCounter] < 32)
                    {
                        excess += values[block][tempCounter];
                        values[block][tempCounter] += 33;
                    }
                    tempCounter++;
                }

                if (backCounter > 0)
                    backCounter -= 1;

                if (counter == 15)
                {
                    if (block == 7)
                        break;

                    block += 1;

                    values[block][0] = (values[block][0] + (excess * excess) % 126) % 126;

                    if (values[block][0] < 32)
                    {
                        excess += (values[block][0]);
                        values[block][0] += 33;
                    }
                    backCounter = 15;
                    tempVal %= 255;
                    counter = 0;
                }
                counter += 1;
            }
            tempVec.push_back(values[i][j]);
        }
    }
    std::string rez(tempVec.begin(), tempVec.end());

    return rez;
}
