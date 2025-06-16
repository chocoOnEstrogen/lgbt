# LGBT Flag Display Tool

A command-line tool that displays various LGBTQ+ pride flags in the terminal using ANSI color codes.

## Features

- Display multiple LGBTQ+ pride flags in the terminal
- Customizable flag dimensions
- Border options
- Reverse flag display
- Comprehensive man page
- Easy installation process
- Support for 14 different pride flags
- Enhanced color support with light and bright variants
- Improved error handling and user feedback

## Installation

### Quick Install

```bash
# Clone the repository
git clone https://github.com/chocoOnEstrogen/lgbt.git
cd lgbt

# Build and install
make
sudo make install
```

### Custom Installation

You can customize the installation location:

```bash
# Install to custom location
sudo make install INSTALL_PREFIX=/usr/local

# Show all options
make help
```

## Usage

```bash
# Display a specific flag
lgbt --flag=trans

# Custom dimensions
lgbt --flag=rainbow --matrix=40x20

# Add border
lgbt --flag=lesbian --border

# Reverse flag display
lgbt --flag=bi --reverse

# List available flags
lgbt --list
```

### Available Flags

- `trans` - Transgender Pride Flag
- `lesbian` - Lesbian Pride Flag
- `rainbow` - Rainbow Pride Flag
- `bi` - Bisexual Pride Flag
- `pan` - Pansexual Pride Flag
- `nonbinary` - Non-binary Pride Flag
- `ace` - Asexual Pride Flag
- `genderfluid` - Genderfluid Pride Flag
- `genderqueer` - Genderqueer Pride Flag
- `intersex` - Intersex Pride Flag
- `aromantic` - Aromantic Pride Flag
- `demisexual` - Demisexual Pride Flag
- `agender` - Agender Pride Flag
- `polyamorous` - Polyamorous Pride Flag

Use `--list` for detailed descriptions of each flag's meaning and symbolism.

## Building from Source

```bash
# Build the project
make

# Build with debug symbols
make dev

# Clean build files
make clean

# Install
make install

# Uninstall
make uninstall
```

## Documentation

Detailed documentation is available in the [docs](./docs) directory:

- [Installation Guide](./docs/installation.md)
- [User Guide](./docs/user-guide.md)
- [Developer Guide](./docs/developer-guide.md)
- [Contributing Guide](./docs/contributing.md)

## Contributing

We welcome contributions! Please see our [Contributing Guide](./docs/contributing.md) for details.

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.

## Acknowledgments

- Thanks to all contributors who have helped make this project better
- Inspired by the need for more LGBTQ+ representation in terminal tools
- Special thanks to the LGBTQ+ community for their support and feedback



