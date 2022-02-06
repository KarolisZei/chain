#include "includes.h"
std::string genNonce(int diff)
{
    std::string nonce = "";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, diff);

    nonce += std::to_string(distr(gen));

    return nonce;
}

struct tree
{
    std::string hashed;
    int horizontal;
    tree *left, *right;
    tree(std::string val)
    {
        hashed = val;
        horizontal = INT32_MAX;
        left = right = NULL;
    }
};

std::string getMerkle(std::vector<transactions> trans)
{

    std::vector<std::string> hashes;

    for (int i = 0; i < trans.size(); i++)
        hashes.push_back(trans[i].ID);

    while (hashes.size() > 1)
    {
        if (hashes.size() % 2 != 0)
            hashes.push_back(hashes.back());
        std::string newMerkle = "";

        std::vector<std::string> tempHash;

        for (int i = 0; i < hashes.size(); i += 2)
        {
            tempHash.push_back(hash(hashes[i] + hashes[i + 1]));
        }

        hashes = tempHash;
    }
    return hashes[0];
}

block genBlock(block prevBlock, std::vector<transactions> blockTransactions, std::vector<user> &users, std::vector<block> &blockChain)
{
    block newBlock;

    transactions newTrans;

    header newHeader;

    newHeader.prevBlock = prevBlock.Header.merkleHash;

    newHeader.timestamp = getTime();

    newHeader.diff = prevBlock.Header.diff + 1000000;

    newHeader.setNonce(genNonce(newHeader.diff));

    std::string lole = newHeader.getNonce();

    newHeader.version = 1;

    newBlock.Header = newHeader;

    if (users.empty())
    {
        blockChain.push_back(newBlock);
        return newBlock;
    }
    cout << endl
         << "New block is found!" << endl;

    cout << endl
         << "New block merkle hash: " << newBlock.Header.merkleHash << endl;
    cout << "New block dificulty: " << newBlock.Header.diff << endl;
    cout << "New block timestamp: " << newBlock.Header.timestamp << endl;
    cout << "New block version: " << newBlock.Header.version << endl;

    for (auto &&i : blockTransactions)
    {
        newBlock.Transtacions.push_back(i);
        for (int j = 0; j < users.size(); j++)
        {
            if (i.sender == users[j].publicKey)
            {
                users[j].amount -= i.amount;
            }
            if (i.reciever == users[j].publicKey)
            {
                users[j].amount += i.amount;
            }
        }
    }

    newBlock.Header.merkleHash = getMerkle(newBlock.Transtacions);

    cout << "New block merkle hash: " << newBlock.Header.merkleHash << endl
         << endl;
    cout << "------------------------------------------------------" << endl;
    blockChain.back() = newBlock;
}