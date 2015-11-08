#!/bin/bash
if [ "$#" -ne 4 ]; then
  echo -e "\033[31mIllegal number of parameters\033[0m"
  echo "Usage: run_http_client.sh MONE HOSTNAME PORT URI"
  echo "Example: run_http_client.sh sync localhost 8080 abc" 
  exit 1
fi

if [[ "$1" != "sync" && "$1" != "async" ]]; then
  echo -e "\033[31mIllegal mode:\033[0m"
  echo "Available mode: sync, async"
  exit 1
fi

script_path=$( cd "$(dirname "${BASH_SOURCE}")" ; pwd -P )
curr_path="$PWD"
cd "$script_path"
cd ..
# the -DBoost_DEBUG is for cmake to find the boost library path on OSX
cmake -DBoost_DEBUG=ON
make http_client_sync
echo
echo

if [[ "$1" == "sync" ]]; then
  make http_client_sync
  CMD="./http_client_sync $2 $3 $4"
else
  make http_client_async
  CMD="./http_client_async $2 $3 $4"
fi

echo -e "\033[33mRunning http request using command:\033[0m"
echo -e "\033[32m$CMD\033[0m"
eval $CMD
cd "$curr_path"
