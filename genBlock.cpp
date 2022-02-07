#include "includes.h"
std::string genNonce(int diff)
{
    std::string nonce = "";

    std::random_device rd;
    std::mt19937 gen(rd());
    if (diff - 20000 > 0)
    {
        std::uniform_int_distribution<> distr(0, diff);
        nonce += std::to_string(distr(gen));
    }
    else
    {
        std::uniform_int_distribution<> distr(diff, diff + 20000);

        nonce += std::to_string(distr(gen));
    }

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

block genBlock(block prevBlock, std::vector<transactions> blockTransactions, std::vector<user> &users, std::vector<block> &blockChain, int &foundNonce)
{
    block newBlock;

    transactions newTrans;

    header newHeader;

    newHeader.prevBlock = prevBlock.Header.merkleHash;

    newHeader.timestamp = getTime();

    newHeader.diff = prevBlock.Header.diff + 20000;

    newHeader.setNonce(genNonce(newHeader.diff));

    std::string lole = newHeader.getNonce();

    newHeader.version = 1;

    newBlock.Header = newHeader;

    if (users.empty())
    {
        return newBlock;
    }
    newBlock.Header.prevBlock = prevBlock.Header.merkleHash;
    newBlock.Header.foundNonce = foundNonce;
    cout << endl
         << "New block is found!" << endl;

    cout << endl;
    cout << "New block dificulty: " << newBlock.Header.diff << endl;
    cout << "New block timestamp: " << newBlock.Header.timestamp << endl;
    cout << "New block version: " << newBlock.Header.version << endl;
    cout << "Nonce: " << newBlock.Header.foundNonce << endl;
    cout << "Previuos block hash: " << newBlock.Header.prevBlock << endl;

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

    std::string cont;
    cout << "Do you want to print the transactions in this block?[Y/N]";
    while (std::cin >> cont)
    {
        if (cont == "y" || cont == "Y" || cont == "n" || cont == "N")
            break;
        cout << "Please enter a valid input![Y/N]";
    }
    if (cont == "Y" || cont == "y")
    {

        cout << "Printing transactions!" << endl;

        for (auto &&i : blockTransactions)
        {
            cout << endl
                 << "------------------------------------------------------" << endl
                 << endl;
            cout << "ID: " << i.ID << endl;
            cout << "Trans ammount: " << i.amount << endl;
            cout << "Trans reciever: " << i.reciever << endl;
            cout << "Trans sender: " << i.sender << endl;
        }
    }

    blockChain.push_back( newBlock);
}