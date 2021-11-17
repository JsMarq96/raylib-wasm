#!/usr/bin/env bash

cd emsdk
git checkout main

./emsdk install latest
./emsdk activate latest

source ./emsdk_env.sh

echo 'source "emsdk/emsdk_env.sh"' >> $HOME/.bash_profile
