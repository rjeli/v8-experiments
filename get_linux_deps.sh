#!/bin/bash
set -euo pipefail

mkdir -p thirdparty/v8

echo fetching deps
curl -L 'https://github.com/blazerod/v8-prebuilt/releases/download/v8.0.426.8/v8-v8.0.426.8-linux.tar.gz' \
    | tar -xzf - -C thirdparty/v8
curl -L 'https://github.com/pmed/v8pp/archive/v1.7.0.tar.gz' \
    | tar -xzf - -C thirdparty
