#!/bin/bash
script_path=$( cd "$(dirname "${BASH_SOURCE}")" ; pwd -P )
curr_path="$PWD"
cd "$script_path"
cd ..
# the -DBoost_DEBUG is for cmake to find the boost library path on OSX
cmake -DBoost_DEBUG=ON
make web_crawler_server
echo
echo

IP=127.0.0.1
PORT=8080
THREAD=20
./web_crawler_server $IP $PORT $THREAD .
cd "$curr_path"
