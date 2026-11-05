# Brazilian Football - Build & Run Guide

## Quick Start

### 1. Install Dependencies

#### Linux (Ubuntu/Debian)
```bash
./scripts/install-dependencies.sh
```

Or manually:
```bash
sudo apt-get install build-essential cmake libglfw3-dev libglew-dev libglm-dev libopenal-dev libsndfile1-dev python3
```

#### macOS
```bash
brew install cmake glfw glew glm openal-soft libsndfile python3
```

#### Windows
Install via vcpkg or manually:
- Visual Studio 2019+ with C++ tools
- CMake 3.20+
- Download GLFW, GLEW, GLM from their websites

### 2. Build the Project

#### Linux/macOS
```bash
./setup.sh
```

Or manually:
```bash
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

#### Windows
```bash
python scripts/compile-windows.py
```

### 3. Run the Demo

```bash
./bin/BrazilianFootball
```

## What You'll See

The demo scene includes:
- ✅ Rotating colored cubes
- ✅ Bouncing sphere
- ✅ Grid of animated cubes
- ✅ Green ground plane
- ✅ Rotating camera view
- ✅ Real-time lighting

## Controls

- **ESC** - Exit demo

## Troubleshooting

### "Failed to initialize GLFW"
- Make sure GLFW is installed
- On Linux, you may need: `sudo apt-get install libglfw3-dev`

### "Failed to load shaders"
- Run from project root directory: `./bin/BrazilianFootball`
- Shaders must be at: `assets/shaders/basic.vert` and `basic.frag`

### Black screen
- Check OpenGL support: `glxinfo | grep "OpenGL version"` (Linux)
- Minimum OpenGL 4.1 required

### Build errors
- Ensure all dependencies are installed
- Try: `rm -rf build && mkdir build && cd build && cmake ..`

## Development

### Running Tests
```bash
cd build
ctest --output-on-failure
```

### Debug Build
```bash
python scripts/compile-linux.py --debug
```

### Clean Build
```bash
python scripts/compile-linux.py --clean
```

## Next Steps

After confirming the graphics engine works:
1. Implement input system for player control
2. Add football pitch model
3. Create player character rendering
4. Implement ball physics
5. Add game logic

See `docs/ARCHITECTURE.md` for system details.
