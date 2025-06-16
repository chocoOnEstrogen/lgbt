# Developer Guide

This guide is for developers who want to contribute to or modify the LGBT Flag Display Tool.

## Project Structure

```
lgbt/
├── src/
│   ├── app/
│   │   └── main.c      # Main program
│   └── installer/
│       └── main.c      # Installer program
├── resources/
│   └── lgbt.1          # Man page
├── bin/                # Build output
├── docs/              # Documentation
├── Makefile           # Build system
└── .github/
    └── workflows/     # CI/CD
```

## Building

### Prerequisites

- GCC or compatible C compiler
- Make
- Git
- Terminal with 256-color support

### Build Commands

```bash
# Build everything
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

## Adding New Flags

To add a new flag, modify `src/app/main.c`:

1. Add the flag definition to the `flags` array:

```c
Flag flags[] = {
    // ... existing flags ...
    {
        "newflag",           // Flag name
        5,                   // Number of stripes
        {"color1", "color2", "color3", "color4", "color5"},  // Colors
        "New Flag Description - Detailed explanation of the flag's meaning and symbolism"  // Description
    }
};
```

2. Add the colors to the `ansi_colors` array if needed:

```c
const char *ansi_colors[] = {
    // ... existing colors ...
    "\x1b[48;5;XXXm ",  // New color
};
```

3. Add the color mapping in `get_ansi_color`:

```c
const char *color_map[][2] = {
    // ... existing mappings ...
    {"newcolor", ansi_colors[INDEX]},
};
```

## Code Style

- Use 4 spaces for indentation
- Maximum line length: 80 characters
- Use descriptive variable names
- Add comments for complex logic
- Follow C99 standard
- Include detailed flag descriptions
- Use proper error handling

## Testing

1. Build the project:
```bash
make clean
make
```

2. Test the binary:
```bash
./bin/lgbt --list
./bin/lgbt --flag=trans
```

3. Test the installer:
```bash
./bin/installer --help
```

4. Test error handling:
```bash
./bin/lgbt --flag=nonexistent
./bin/lgbt --matrix=invalid
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## Release Process

1. Update version numbers
2. Update documentation
3. Create a release tag
4. Push the tag to trigger the release workflow

## Common Issues

### Build Errors

- Ensure all dependencies are installed
- Check compiler version compatibility
- Verify file permissions
- Check for unused variables
- Verify string handling

### Runtime Errors

- Check terminal compatibility
- Verify color support
- Test with different terminal sizes
- Validate error handling
- Test edge cases

## Performance Considerations

- Keep memory usage minimal
- Optimize color calculations
- Handle large dimensions efficiently
- Validate input early
- Use proper string handling

## Security

- Validate all user input
- Handle file operations safely
- Use secure installation paths
- Check buffer sizes
- Prevent string overflows 