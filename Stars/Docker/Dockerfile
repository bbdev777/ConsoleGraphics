FROM 10.74.33.15:5000/ubuntu-20.04-dev-image:1.0.1 AS build

ENV DEBIAN_FRONTEND="noninteractive"
ENV TZ="UTC"

####################################################################################################
# Apps
####################################################################################################

RUN mkdir -p /src/ConsoleGraphics
RUN mkdir -p /build-folder
RUN --mount=type=bind,source=.,target=/src/ConsoleGraphics \
    --mount=type=cache,target=/build-folder \
    cd /build-folder \
    && cmake -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        /src/ConsoleGraphics \
    && ninja clean \
    && ninja -j4 \
    && cp -r /build-folder/Stars /Stars \
    && cp -r /build-folder/MatrixColumns /MatrixColumns

FROM 10.74.33.15:5000/ubuntu-20.04-rel-image:1.0.1 AS Release

COPY --from=build /Stars /Stars
COPY --from=build /MatrixColumns /MatrixColumns
