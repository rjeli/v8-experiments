#!/bin/bash
set -euo pipefail

echo fetching prebuilt v8
mkdir -p thirdparty/v8
curl -L 'https://github.com/blazerod/v8-prebuilt/releases/download/v8.0.426.8/v8-v8.0.426.8-linux.tar.gz' \
    | tar -xzf - -C thirdparty/v8
