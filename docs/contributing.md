# Contributing Guide

Thank you for your interest in contributing to the LGBT Flag Display Tool! This guide will help you get started.

## Code of Conduct

Please read and follow our [Code of Conduct](../.github/CODE_OF_CONDUCT.md).

## Getting Started

1. Fork the repository
2. Clone your fork:
   ```bash
   git clone https://github.com/YOUR_USERNAME/lgbt.git
   cd lgbt
   ```
3. Add the upstream repository:
   ```bash
   git remote add upstream https://github.com/chocoOnEstrogen/lgbt.git
   ```

## Development Workflow

1. Create a new branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. Make your changes

3. Test your changes:
   ```bash
   make clean
   make
   ./bin/lgbt --list
   ```

4. Commit your changes:
   ```bash
   git commit -m "feat: add new feature"
   ```

5. Push to your fork:
   ```bash
   git push origin feature/your-feature-name
   ```

6. Create a Pull Request

## Pull Request Guidelines

1. Update documentation if needed
2. Add tests if applicable
3. Follow the existing code style
4. Keep commits focused and atomic
5. Write clear commit messages

## Commit Message Format

Follow the [Conventional Commits](https://www.conventionalcommits.org/) format:

```
<type>(<scope>): <description>

[optional body]

[optional footer]
```

Types:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes
- `refactor`: Code refactoring
- `test`: Adding tests
- `chore`: Maintenance tasks

## Adding New Features

1. Discuss the feature in an issue first
2. Create a new branch
3. Implement the feature
4. Add tests if applicable
5. Update documentation
6. Submit a pull request

## Bug Reports

When reporting bugs, please include:

1. Steps to reproduce
2. Expected behavior
3. Actual behavior
4. System information
5. Terminal type and version

## Feature Requests

When requesting features, please include:

1. Use case
2. Expected behavior
3. Any relevant examples
4. Potential implementation ideas

## Code Review Process

1. All pull requests require review
2. At least one approval needed
3. All tests must pass
4. Documentation must be updated
5. Code style must be followed

## Development Setup

### Required Tools

- GCC or compatible C compiler
- Make
- Git
- A terminal that supports ANSI colors

### Building

```bash
# Build the project
make

# Build with debug symbols
make dev

# Clean build files
make clean
```

### Testing

```bash
# Run basic tests
./bin/lgbt --list
./bin/lgbt --flag=trans

# Test installer
./bin/installer --help
```

## Documentation

- Keep documentation up to date
- Add comments for complex code
- Update README if needed
- Document new features

## Release Process

1. Update version numbers
2. Update changelog
3. Create release tag
4. Push tag to trigger release workflow

## Questions?

Feel free to open an issue for any questions or concerns. 