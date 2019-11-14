# Solbit TECHNICAL FEATURES
 **Infrastructure to use solbit**

## Getting Started

### 1. General Information

**1.1. Blockchain description, distinctive features**
> Solbit (SBT) is a sustainable cryptocurrency modeled after Satoshi Nakamoto’s vision for Bitcoin.  
It is a decentralized, peer-to-peer transactional currency designed to offer a solution to the problem posed by the exponential increase in energy consumed by Bitcoin and other proof-of-work currencies.   
Proof-of-work mining is environmentally unsustainable due to the electricity used by high-powered mining hardware.  Solbit utilizes the Tier Protocol, an energy efficient proof-of-stake algorithm inspired by PROECTCOIN/PIVX/DASH, can be mined on any computer, and will never require specialized mining equipment.  
The Tier Protocol offers a simple solution to Bitcoin sustainability issues and provides a faster, more scalable blockchain that is better suited for daily transactional use.
Fast transactions featuring guaranteed zero confirmation transactions, we call it SwiftTX.  Decentralized blockchain voting providing for consensus based advancement of the current Masternode technology used to secure the network and provide the above features, each Masternode is secured with a collateral of 1,000,000 SBT.
- Fast transactions featuring guaranteed zero confirmation transactions, we call it _SwiftTX_.
- Decentralized blockchain voting providing for consensus based advancement of the current Masternode technology used to secure the network and provide the above features, each Masternode is secured with a collateral of 1,000,000 SBT.

**1.2. All available source code repositories**
> Solbit's source code repositories at [github](https://github.com/SolbitManager/Solbit-new)

**1.3. For blockchain forks - Original project name and its version or tag**
> projectcoin(PRJ) 1.3.0

**1.4. Recommendations for integration**
> Same with bitcoin

### 2. Deposits

**2.1. Dockerfile for building and running an RPC node (Base system Ubuntu 18.04)**
> Dockerfile repository at [github](https://github.com/SolbitManager/Solbit-new/blob/master/Dockerfile)
```yml
# 1. use ubuntu 18.04
FROM            ubuntu:18.04
MAINTAINER      admin@solbit.tech
RUN             apt-get -y update
RUN             apt-get -y install curl
RUN             apt-get -y install software-properties-common

# 2. solbit release lastest download
RUN             mkdir /root/solbit && cd /root/solbit && curl -L https://github.com/SolbitManager/Solbit-new/releases/download/v1.3.0.0/solbit-1.3.0.0-arm-linux-gnu-ubuntu.18.0.4.tar.gz
RUN             mkdir /root/.solbit && cd /root/solbit &&  mv solbit.conf /root/.solbit/ && chmod 755 solbit*
RUN             cd /root/solbit && chmod 755 solbit*


# 3. install dependancy
RUN             apt-get -y install build-essential
RUN             apt-get -y install libtool autotools-dev autoconf
RUN             apt-get -y install libssl-dev libboost-all-dev
RUN             add-apt-repository -y ppa:bitcoin/bitcoin
RUN             apt-get -y update
RUN             apt-get install -y libdb4.8-dev libdb4.8++-dev
RUN             apt-get install -y libssl1.0-dev
RUN             apt-get install -y libminiupnpc-dev
RUN             apt-get install -y libzmq5

# 3. run solbit daemon
RUN             cd /root/solbit && ./solbitd -txindex -daemon
```

**2.2. Dockerfile with an application that syncs blockchain into a database**
> Reference 2.1

**2.3. Code sample for address generation (private key and derived address)**
> sanacoin-cli getnewaddress "account"  
> or  
> sanacoin-cli getaddressesbyaccount "account"  
> [ Not use private key or derived address ]


### 3. Withdrawals
#### 3.1. Code samples (node-js) for

**3.1.1. Preparing raw transaction data (gathering required transaction parameters from the blockchain)**  
```linux
curl --user 'userid:pw' --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "listunspent", "params": [1, 1000] }' -H 'content-type: text/plain;' http://127.0.0.1:10776/
>> {
    "result": [
  		{
  			"txid": "042a4f5d9457911a657acd3bb8a8bbcf92d4bad5618115e771ba8e4cd9e937c0",
  			"vout": 1,
  			"address": "Sc7nFMPNL36bnFd2NDpEvXjtrGWPaPbUWC",
  			"account": "mn1",
  			"scriptPubKey": "2102a0104151e5cd124d3393b299e3e3585d360a77abc2e8f72a58dd947199840eb2ac",
  			"amount": 390.058,
  			"confirmations": 820,
  			"spendable": true
  		},
  		.......		
  		{
  			"txid": "e5b811a862101f63123f7ceff01385c638b7c3dc50ac34c90586b16acaf005b8",
  			"vout": 1,
  			"address": "Sc7nFMPNL36bnFd2NDpEvXjtrGWPaPbUWC",
  			"account": "mn1",
  			"scriptPubKey": "2102a0104151e5cd124d3393b299e3e3585d360a77abc2e8f72a58dd947199840eb2ac",
  			"amount": 240.048,
  			"confirmations": 977,
  			"spendable": true
  		}
  	],
  	"error": null,
  	"id": "curltest"
}	
```
**3.1.2. Generation raw transaction (combining data into a data structure, serializing into a raw transaction)**
```linux
curl --user 'userid:pw' --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "createrawtransaction", "params": [[{"txid":"e5b811a862101f63123f7ceff01385c638b7c3dc50ac34c90586b16acaf005b8","vout":1}], {"SXDV25EnvwxNXTyQrbbt5sWp4vuJH3w9qJ":0.01} ]}'  -H 'content-type: text/plain;' http://127.0.0.1:10776/
>> {
   		"result": "0100000001b805f0ca6ab18605c934ac50dcc3b738c68513f0ef7c3f12631f1062a811b8e50100000000ffffffff0140420f00000000001976a9146cd68a4a7f627b5d1424a2fb21970588de6d3e6d88ac00000000",
   		"error": null,
   		"id": "curltest"
   }
```
**3.1.3. Signing and broadcasting raw transaction)**
```linux
## signrawtransaction
curl --user 'userid:pw' --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "signrawtransaction", "params": ["0100000001b805f0ca6ab18605c934ac50dcc3b738c68513f0ef7c3f12631f1062a811b8e50100000000ffffffff0140420f00000000001976a9146cd68a4a7f627b5d1424a2fb21970588de6d3e6d88ac00000000"] }' -H 'content-type: text/plain;' http://127.0.0.1:10776/
>>"result": {
    "hex": "0100000001b805f0ca6ab18605c934ac50dcc3b738c68513f0ef7c3f12631f1062a811b8e50100000049483045022100a421eb0e31a77eb6dfc5653cc5a7650f7a8071e9c74677e722e0c5349eb76e3a02204353ee7728fed1d047344513580fac2e48d120069c3f64f5da10ae3e7f51902601ffffffff0140420f00000000001976a9146cd68a4a7f627b5d1424a2fb21970588de6d3e6d88ac00000000",
    "complete": true
    },
    "error": null,
    "id": "curltest"
}
		
## sendrwatransaction
curl --user 'userid:pw' --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "sendrawtransaction", "params": ["0100000001b805f0ca6ab18605c934ac50dcc3b738c68513f0ef7c3f12631f1062a811b8e50100000049483045022100a421eb0e31a77eb6dfc5653cc5a7650f7a8071e9c74677e722e0c5349eb76e3a02204353ee7728fed1d047344513580fac2e48d120069c3f64f5da10ae3e7f51902601ffffffff0140420f00000000001976a9146cd68a4a7f627b5d1424a2fb21970588de6d3e6d88ac00000000"] }' -H 'content-type: text/plain;'  http://127.0.0.1:10776/
```

## License

Copyright 2018-2019 SOLBIT Co.,Ltd.
