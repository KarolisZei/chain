#pragma once
#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <bits/stdc++.h>
std::string hash(std::string);
std::string genNonce(int);

std::string getTime();

using std::cout;
using std::endl;

class user
{
private:
    std::string privateKey;

public:
    std::string name;
    std::string publicKey;
    uint amount;
    void setPrivateKey(std::string value)
    {
        int hashVal = 0;
        privateKey = hash(value);
        for (int i = 0; i < privateKey.length(); i++)
        {
            hashVal += int(privateKey[i]);
        }
        publicKey = hash(std::to_string(hashVal));
    }
};
class transactions
{
public:
    std::string ID = "0";
    std::string sender;
    std::string reciever;
    int amount;
};
class header
{
private:
    std::string nonce;

public:
    std::string prevBlock;
    std::string timestamp;
    std::string merkleHash;
    int version;
    int diff;
    void setNonce(std::string setNonce) { nonce = setNonce; }
    std::string getNonce() { return nonce; }
    std::string hashedNonce() { return hash(nonce); }
};
class block
{
public:
    header Header;
    std::vector<transactions> Transtacions;
};
bool mine(block prevBlock, block, std::vector<transactions> blockTransactions, std::vector<user> &users, std::vector<block> &blockChain);

block genBlock(block, std::vector<transactions>, std::vector<user> &, std::vector<block> &);
