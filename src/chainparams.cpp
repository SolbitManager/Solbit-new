// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2019 The Solbit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>
#include <limits>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("00000379ac7a9c9a2d0caf0de4229202ff35ff0d81b868ed26f9e38186a76467"))
                              ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1568092034, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1568092034,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1568092034,
    0,
    100};


class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa8;
        pchMessageStart[1] = 0x22;
        pchMessageStart[2] = 0xc4;
        pchMessageStart[3] = 0xc4;
        vAlertPubKey = ParseHex("04324656a6e3ab11ef480da2ef2cce01f289145e7264ceba1650e3869744fde779e9e29544a4fa1b5d28edb1aae541b9176740e055b0af2584b159147d385cb8d5");

        nDefaultPort = 9555;
        //org
        //bnProofOfWorkLimit = ~uint256(0) >> 20;
        //bnStartWork = ~uint256(0) >> 24;
        //custom
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        bnStartWork = ~uint256(0) >> 20;

        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetSpacing = 1 * 30;  // Solbit: 0.5 minute after 750K
        nTargetSpacingSlowLaunch = 1 * 60; // before block 750k
        // nAntiInstamineTime = 50; // 720 blocks with 1 reward for instamine prevention
        nMaturity = 228;
        nMasternodeCountDrift = 3;
        // nMaxMoneyOut = 80000000 * COIN;        
        nMaxMoneyOut = 3000000000 * COIN;

        nStartMasternodePaymentsBlock = 200;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 2000;
        nModifierUpdateBlock = std::numeric_limits<decltype(nModifierUpdateBlock)>::max();

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        // const char* pszTimestamp = "the new yoek times - New Russian Hacking Targeted Republican Groups, Microsoft Says";
        const char* pszTimestamp = "Premier League champions have first billion euro squad, says study";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        //txNew.vout[0].scriptPubKey = CScript() << ParseHex("044a001040da79684a0544c2254eb6c896fae95a9ea7b51d889475eb57ab2051f1a5858cac61ae400e90ea08015263ad40c65d36f0edf19e996972e7d2cbd13c15") << OP_CHECKSIG;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0404e0d731dc889ba419387cc62138e1f8fbba1cbb86363146910dd8aaa952e86d0a98e160281edb11e1947dbd08a37fd7e1178a25a7c43914da3075ec0f6d9572") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1568092034;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 5177791;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("00000379ac7a9c9a2d0caf0de4229202ff35ff0d81b868ed26f9e38186a76467"));
        assert(genesis.hashMerkleRoot == uint256("e68e10b5b8d9330217897b6f84f558f9c56acd975d187353298ac35d47fbb4ed"));

        vSeeds.push_back(CDNSSeedData("54.180.128.176", "54.180.128.176"));
        vSeeds.push_back(CDNSSeedData("13.124.78.235", "13.124.78.235"));
        vSeeds.push_back(CDNSSeedData("13.125.199.119", "13.125.199.119"));
        vSeeds.push_back(CDNSSeedData("13.125.34.121", "13.125.34.121"));
        vSeeds.push_back(CDNSSeedData("13.124.56.172", "13.124.56.172"));
        vSeeds.push_back(CDNSSeedData("52.78.122.58", "52.78.122.58"));
        vSeeds.push_back(CDNSSeedData("13.124.218.172", "13.124.218.172"));
        vSeeds.push_back(CDNSSeedData("13.125.239.93", "13.125.239.93"));
        vSeeds.push_back(CDNSSeedData("54.180.151.134", "54.180.151.134"));
        vSeeds.push_back(CDNSSeedData("54.180.134.127", "54.180.134.127"));

        //base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 55); // P
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);    // S
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 8);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 117); // p
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 9984
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x27)(0x00).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0228344aa5b39cc8fed8a8adcf8fe5616584e6b49b2008f47a166f509a51e7ead9";
        //strObfuscationPoolDummyAddress = "PSDj2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        strObfuscationPoolDummyAddress = "SSDj2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = 1568092034; //Wed, 25 Jun 2014 20:36:16 GMT

    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x27;
        pchMessageStart[1] = 0x78;
        pchMessageStart[2] = 0x16;
        pchMessageStart[3] = 0xb9;

        bnProofOfWorkLimit = ~uint256(0) >> 1;
        bnStartWork = bnProofOfWorkLimit;

        //vAlertPubKey = ParseHex("04459DC949A9E2C2E1FA87ED9EE93F8D26CD52F95853EE24BCD4B07D4B7D79458E81F0425D81E52B797ED304A836667A1D2D422CD10F485B06CCBE906E1081FBAC");
        vAlertPubKey = ParseHex("0404e0d731dc889ba419387cc62138e1f8fbba1cbb86363146910dd8aaa952e86d0a98e160281edb11e1947dbd08a37fd7e1178a25a7c43914da3075ec0f6d9572");
        nDefaultPort = 19555;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetSpacing = 1 * 60;  // Solbit: 1 minute
        nLastPOWBlock = std::numeric_limits<decltype(nLastPOWBlock)>::max();
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = std::numeric_limits<decltype(nModifierUpdateBlock)>::max();
        nMaxMoneyOut = 1000000000 * COIN;


        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1568092034;
        genesis.nNonce = 290796;

        hashGenesisBlock = genesis.GetHash();

        //assert(hashGenesisBlock == uint256("0"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("solbit.net", "seed01.solbit.net"));     // Primary DNS Seeder

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 137); // Testnet Solbit addresses start with 'x'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet Solbit script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet Solbit BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet Solbit BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet Solbit BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        //convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0421838CC1407E7B8C0C5F2379DF7EBD395181949CFA55124939B4980D5054A7926F88E3059921A50F0F81C5195E882D9A414EA0835BB89C9BB061511B9F132B31";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1568092034; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;

        bnStartWork = ~uint256(0) >> 20;

        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetSpacing = 1 * 60;        // Solbit: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1568092034;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;

        //assert(hashGenesisBlock == uint256("300552a9db8b2921c3c07e5bbf8694df5099db579742e243daeaf5008b1e74de"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fMineBlocksOnDemand = true;


    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
