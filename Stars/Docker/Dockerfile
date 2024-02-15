FROM 10.74.33.15:5000/ubuntu-20.04-dev-image:1.0.1 AS build

ENV DEBIAN_FRONTEND="noninteractive"
ENV TZ="UTC"

RUN apt-get install libncurses5-dev libncursesw5-dev

####################################################################################################
# Apps
####################################################################################################

RUN mkdir -p /src/ConsoleGraphics
RUN mkdir -p /build-folder

RUN --mount=type=bind,source=./Sources/glm/,target=/src/ConsoleGraphics/Stars/Sources/glm \
    --mount=type=cache,target=/build-folder \
    cd /build-folder \
    && cmake \
        -DGLM_BUILD_TESTS=OFF \
        -DBUILD_SHARED_LIBS=OFF \
        -B build /src/ConsoleGraphics/Stars/Sources/glm/ \
&& cmake --build build -- all \
&& cmake --build build -- install

RUN --mount=type=bind,source=.,target=/src/ConsoleGraphics \
    --mount=type=cache,target=/build-folder \
    cd /build-folder \
    && cmake -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        /src/ConsoleGraphics \
    && ninja clean \
    && ninja -j4 \
    && cp -r /build-folder/Stars /Stars \
    && cp -r /build-folder/MatrixColumns /MatrixColumns \
    && cp -r /build-folder/Flame /Flame

FROM 10.74.33.15:5000/ubuntu-20.04-rel-image:1.0.1 AS Release

COPY --from=build /Stars /Stars
COPY --from=build /MatrixColumns /MatrixColumns
COPY --from=build /Flame /Flame
