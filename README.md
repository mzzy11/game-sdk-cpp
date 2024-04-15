# C++ Agent Template

THUAI7 agent template in C++

## Install

Before building the project, you need to install [XMake](https://xmake.io) first.

Run the following code to configure the project:

```bash
xmake f -m debug
```

Or in release mode:

```bash
xmake f -m release
```

Then build the project:

```bash
xmake
```

## Usage

If you modify the code, this section may be invalid.

Run the following command to start the agent:

```bash
./agent --host <host> --port <port> --token <token>
```

- `<host>`: The IP address of the server.
- `<port>`: The port of the server.
- `<token>`: The token of the agent.

For example:

```bash
./agent --host 127.0.0.1 --port 8080 --token 114514
```

## Contributing

Ask questions by creating an issue.

PRs accepted.

## License

CC0-1.0 © THUASTA
