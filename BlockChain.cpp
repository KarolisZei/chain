#include "includes.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <vector>
//g++ 
std::vector<transactions> genTransactions(std::vector<user> users)
{
    srand(time(NULL));

    transactions tempTrans;

    std::vector<user> tempUsers;

    for (int i = 0; i < 1000; i++)
    {
        tempUsers.push_back(users[i]);
    }

    std::vector<transactions> trans;
    uint tempSender, tempReciever, sum;
    for (int i = 0; i < 10000; i++)
    {

        tempSender = rand() % 1000;
        tempReciever = rand() % 1000;

        while (tempSender == tempReciever)
            tempSender = rand() % 1000;

        sum = tempUsers[tempSender].amount * (rand() % 50) / 100;

        tempUsers[tempSender].amount -= sum;
        if (tempUsers[tempSender].amount < 0)
            continue;

        tempUsers[tempReciever].amount += sum;

        tempTrans.amount = sum;

        tempTrans.sender = tempUsers[tempSender].publicKey;
        tempTrans.reciever = tempUsers[tempReciever].publicKey;
        std::string check = hash(hash(tempTrans.reciever + tempTrans.sender + std::to_string(tempTrans.amount)));
        tempTrans.ID = check;

        trans.push_back(tempTrans);

        // tempHeader.amount =
        // tempHeader.sender
        // tempHeader.reciever
    }
    for (int i = 0; i < 10000; i++)
    {
        std::string check = hash(hash(trans[i].reciever + trans[i].sender + std::to_string(trans[i].amount)));
        if (trans[i].ID != check)
            trans.erase(trans.begin() + i);
    }

    return trans;
}

std::vector<user> genUsers()
{
    srand(time(NULL));
    std::vector<user> users;
    user tempUser;
    std::string userName, publicHash, balance;
    for (int i = 0; i < 1000; i++)
    {
        userName = "name" + std::to_string(i + 1);
        tempUser.name = userName;
        std::string tempKey = hash(hash(std::to_string(rand() % 100000)));
        tempUser.setPrivateKey(tempKey);
        tempUser.publicKey = hash(hash(tempKey));
        tempUser.amount = (rand() % 900 + 100);
        users.push_back(tempUser);
    }
    return users;
}
std::string getTime()
{
    std::time_t t = std::time(0);

    char *dt = ctime(&t);

    time_t rawtime;
    struct tm *ptm;

    time(&rawtime);

    ptm = gmtime(&rawtime);

    std::string tempTime = "TimeStamp: " + std::to_string((ptm->tm_hour) % 24) + ":" + std::to_string(ptm->tm_min);

    return tempTime;
}
block genesisBlock(std::vector<user> &users)
{
    block genesis;

    header genHeader;

    transactions genTrans;

    genHeader.prevBlock = "";
    genHeader.timestamp = getTime();
    genHeader.setNonce(genNonce(10));
    genHeader.version = 1;
    genHeader.diff = 10;
    //"dd+dX44dXdXn5Xp3;;Y:::::z@;3*;dU51=5%==B%%B1 !<\\7=BB=B=B=BB`#'L'jUs^C^^s^U\"CsCU.chhhhhhhh:h0H=nZ.5%|lJ51lJ3lXX2zHZ-HPB4:T*f;|.Zj*"
    int send = rand() % 1000 + 1, get;
    std::string sender = users[send].publicKey;
    get = rand() % 1000 + 1;
    while (send == get)
        get = rand() % 1000 + 1;

    std::string reciever = users[get].publicKey;

    genTrans.sender = sender;
    genTrans.reciever = reciever;
    genTrans.amount = 50;

    users[get].amount += 50;
    users[send].amount -= 50;

    genTrans.ID = hash(hash(genTrans.reciever + genTrans.sender + std::to_string(genTrans.amount)));

      bc::hash_list tx_hashes;

    char * temp = new char[65];
    for (int j = 0; j < 65; j++)
    {
        genTrans.ID.append(&temp[j]);
        // temp[j] = genTrans.ID[j];
    }
    
    const char c[65] = {*temp};

    tx_hashes.push_back(bc::hash_literal(c));
    
    const bc::hash_digest merkle_root = create_merkle(tx_hashes);
    
    genHeader.merkleHash =  bc::encode_base16(merkle_root);

    genesis.Transtacions.push_back(genTrans);

    genesis.Header = genHeader;

    return genesis;
}
int main()
{

    printf("Creating users... ");
    cout << endl;
    std::vector<user> users = genUsers();
    printf("Users created, Creating transaction pool... ");
    cout << endl;
    std::vector<transactions> trans = genTransactions(users);
    cout << endl;
    printf("Transaction pool created, Creating genesis block...");

    // std::cout<<hash(1);

    std::vector<block> blockChain;
    std::vector<transactions> temp100;
    blockChain.push_back(genesisBlock(users));
    cout << endl;
    printf("genBlock details: ");
    cout << endl
         << "genBlock merkle hash: " << blockChain.back().Header.merkleHash << endl;
    cout << "genBlock dificulty: " << blockChain.back().Header.diff << endl;
    cout << "genBlock timestamp: " << blockChain.back().Header.timestamp << endl;
    cout << "genBlock version: " << blockChain.back().Header.version << endl;
    cout << "genBlock nonce: " << genNonce(1) << endl;

    cout << endl;

    cout << "genBlock trans values:" << endl;
    cout << "genBlock trans ammount: " << blockChain.back().Transtacions.back().amount << endl;
    cout << "genBlock trans sender: " << blockChain.back().Transtacions.back().sender << endl;
    cout << "genBlock trans reciever: " << blockChain.back().Transtacions.back().reciever << endl;
    cout << "genBlock trans ID: " << blockChain.back().Transtacions.back().ID << endl;

    std::vector<user> emptyUsers;

    int foundNonce = 0;

    for (int i = 0; i < 100; i++)
    {
        temp100.push_back(trans[i]);
    }
    trans.erase(trans.begin(), std::next(trans.begin(), 100));

    for (int i = 0; i < 10; i++)
    {
        block newBlock = genBlock(blockChain.back(), temp100, emptyUsers, blockChain, foundNonce);
        
        bool checked = mine(blockChain[i], newBlock, temp100, users, blockChain, foundNonce);
        
        if (checked)
        {
            temp100.clear();
            for (int j = 0; j < 100; j++)
            {
                temp100.push_back(trans[j]);
            }
            trans.erase(trans.begin(), std::next(trans.begin(), 100));
            genBlock(blockChain.back(), temp100, users, blockChain, foundNonce);
        }
        else
            i--;
        if (trans.empty())
        {
            trans = genTransactions(users);
        }
    }

    return 0;
}
