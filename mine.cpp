#include "includes.h"
#include "algorithm"

bool mine(block prevBlock, block newBlock, std::vector<transactions> blockTransactions, std::vector<user> &users, std::vector<block> &blockChain, int &foundNonce)
{

    std::vector<int> numbers;

    int diff = newBlock.Header.diff;
    
    for (int i = diff; i < diff+20000; i++)
        numbers.push_back(i);
    std::random_shuffle(numbers.begin(), numbers.end());
    for (int i = diff; i < diff+ 20000; i++)
    {
        std::string tempStr = hash(std::to_string(numbers[i]));
        if (newBlock.Header.hashedNonce() == tempStr)
        {
            foundNonce = numbers[i];
            return true;
        }
    }
    return false;
}