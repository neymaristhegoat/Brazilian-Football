# Brazilian Football - Contributing Guide

## Getting Started

1. Fork the repository
2. Clone your fork
3. Create a feature branch
4. Make your changes
5. Test thoroughly
6. Submit a pull request

## Development Setup

### Prerequisites
- C++17 compatible compiler (GCC 9+, Clang 10+, MSVC 2019+)
- CMake 3.20+
- Python 3.8+ (for build scripts)
- Git

### Building
```bash
# Linux/Mac
python scripts/compile-linux.py --debug

# Windows
python scripts/compile-windows.py --debug
```

### Running Tests
```bash
cd build
ctest --output-on-failure
```

## Code Style

### C++ Guidelines
- Follow modern C++17 practices
- Use smart pointers over raw pointers
- RAII for resource management
- Const-correctness
- Descriptive variable names

### Naming Conventions
- Classes: `PascalCase`
- Functions: `PascalCase`
- Variables: `camelCase`
- Members: `m_PascalCase`
- Constants: `UPPER_SNAKE_CASE`

### File Organization
- Header files: `.h`
- Implementation: `.cpp`
- One class per file
- Matching header/cpp names

## Testing

All new features should include tests:
```cpp
TEST(FeatureName) {
    // Setup
    // Execute
    // Assert
    return true;
}
```

## Documentation

- Document public APIs with comments
- Update README.md for user-facing changes
- Update ARCHITECTURE.md for system changes

## Pull Request Process

1. Update documentation
2. Add tests for new features
3. Ensure all tests pass
4. Follow commit message format
5. Reference related issues

### Commit Message Format
```
[Type] Brief description

Detailed explanation of changes

Fixes #123
```

Types: `[Feature]`, `[Fix]`, `[Refactor]`, `[Docs]`, `[Test]`

## Community

- Be respectful and constructive
- Help others in discussions
- Report bugs with detailed information
- Suggest features with use cases

Thank you for contributing to Brazilian Football!
