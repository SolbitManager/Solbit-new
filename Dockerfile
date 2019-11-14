# 1. use ubuntu 18.04

FROM       ubuntu:18.04

MAINTAINER admin@solbit.tech

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



# 3. run sanacoin daemon

RUN             cd /root/solbit && ./solbitd -txindex -daemon
