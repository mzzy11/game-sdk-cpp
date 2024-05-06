# syntax=docker/dockerfile:1

FROM gcc:12.3.0 AS build-env
WORKDIR /app
RUN curl -fsSL https://xmake.io/shget.text | bash
RUN CURRENT_IP=$(curl -s https://ifconfig.me/ip) \
 && IP_COUNTRY=$(curl -s https://ipinfo.io/$CURRENT_IP/country) \
 && if [ "$IP_COUNTRY" = "CN" ]; then \
      ~/.local/bin/xmake g --proxy_pac=github_mirror.lua --root; \
    fi
COPY . .
RUN ~/.local/bin/xmake f -m release -v -y --root \
 && ~/.local/bin/xmake -v --root

FROM gcr.nju.edu.cn/distroless/cc-debian12
WORKDIR /app
COPY --from=build-env /app/bin/agent .
ENTRYPOINT ["./agent"]
