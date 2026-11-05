# External Dependencies

This directory should contain external libraries used by the project.

## Required Libraries

### Graphics
- **GLFW** (3.3+): Window and input
- **GLEW** or **GLAD**: OpenGL loader
- **GLM** (0.9.9+): Math library

### Audio
- **OpenAL** or **miniaudio**: Audio playback
- **libsndfile**: Audio file loading

### Networking
- **Enet**: Reliable UDP networking

### Asset Loading
- **stb_image**: Image loading
- **Assimp**: 3D model loading
- **nlohmann/json**: JSON parsing

### Physics (Optional)
- **Bullet Physics**: 3D physics simulation

## Installation

Libraries can be installed via:
- System package manager (apt, brew, vcpkg)
- Manual compilation
- Git submodules

Example structure:
```
external/
├── include/
│   ├── GLFW/
│   ├── glm/
│   ├── AL/
│   └── ...
└── lib/
    ├── libglfw3.a
    ├── libopenal.so
    └── ...
```

## License Notes

All external libraries have their own licenses. Check each library's license before distribution.
