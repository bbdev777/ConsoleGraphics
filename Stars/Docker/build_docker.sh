#!/bin/bash

set -e

VERSION="1.0.1"

export DOCKER_BUILDKIT=1

docker build --no-cache --progress=plain  -t 10.74.33.15:5000/stars:"${VERSION}" -f ./Dockerfile ../
docker push 10.74.33.15:5000/stars:"${VERSION}"
