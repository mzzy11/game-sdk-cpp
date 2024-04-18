# syntax=docker/dockerfile:1

FROM gcc:12.3.0 AS build-env

WORKDIR /usr/local/src/app

RUN curl -fsSL https://xmake.io/shget.text | bash

COPY . .

RUN ~/.local/bin/xmake f -m release -v -y --root \
 && ~/.local/bin/xmake -v --root

FROM gcr.io/distroless/cc-debian12

COPY --from=build-env /usr/local/src/app/bin/agent /

ENTRYPOINT ["/agent"]
