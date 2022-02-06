#include "includes.h"
#include "algorithm"

bool mine(block prevBlock, block newBlock, std::vector<transactions> blockTransactions, std::vector<user> &users, std::vector<block> &blockChain)
{

    std::vector<int> numbers;

    int diff = newBlock.Header.diff;

    for (int i = 0; i < diff + 1; i++)
        numbers.push_back(i);
    std::random_shuffle(numbers.begin(), numbers.end());

    for (int i = 0; i < diff; i++)
    {
        std::string tempStr = hash(std::to_string(numbers[i]));
        std::string lole = newBlock.Header.getNonce();
        if (newBlock.Header.hashedNonce() == tempStr)
        {
            return true;
        }
    }
    return false;
}