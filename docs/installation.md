# Installation Guide

This guide covers various methods to install the LGBT Flag Display Tool.

## Prerequisites

- Git
- GCC or compatible C compiler
- Make
- Sudo privileges (for system-wide installation)

## Quick Installation

The simplest way to install the tool:

```bash
# Clone the repository
git clone https://github.com/chocoOnEstrogen/lgbt.git
cd lgbt

# Build the project
make

# Install
sudo make install
```

This will install the tool to the default locations:
- Binary: `/usr/bin/lgbt`
- Man page: `/usr/share/man/man1/lgbt.1`

## Custom Installation

You can customize the installation location using the `INSTALL_PREFIX` variable:

```bash
# Install to /usr/local
sudo make install INSTALL_PREFIX=/usr/local
```

This will install to:
- Binary: `/usr/local/bin/lgbt`
- Man page: `/usr/local/share/man/man1/lgbt.1`

## Uninstallation

To remove the installed files:

```bash
# Using make
sudo make uninstall

# Or manually
sudo rm /usr/bin/lgbt
sudo rm /usr/share/man/man1/lgbt.1
```

## Troubleshooting

### Permission Denied

If you encounter permission errors, ensure you have sudo privileges and try:

```bash
sudo make install
```

### Missing Dependencies

If you're missing required tools, install them:

```bash
# Debian/Ubuntu
sudo apt-get install build-essential git

# Fedora
sudo dnf install gcc make git

# Arch Linux
sudo pacman -S base-devel git
```

### Installation Verification

After installation, verify the tool is working:

```bash
# Check if the binary is in PATH
which lgbt

# Test the tool
lgbt --list
``` 