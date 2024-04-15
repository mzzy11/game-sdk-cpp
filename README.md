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
./agent --server <server> --token <token>
```

- `<server>`: The server address of the game. (Default: `ws://localhost:14514`)
- `<token>`: The token of the agent. (Default: ``)

For example:

```bash
./agent --server ws://localhost:14514 --token 1919810
```

## Contributing

Ask questions by creating an issue.

PRs accepted.

## License

CC0-1.0 © THUASTA
