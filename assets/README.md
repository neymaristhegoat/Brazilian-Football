# Assets Directory Structure

This directory contains all game assets organized by type.

## Directory Structure

```
assets/
├── models/          # 3D models and meshes
├── textures/        # Texture files (diffuse, normal, etc.)
├── materials/       # Material definitions
├── shaders/         # GLSL shader files
├── audio/           # Audio files
│   ├── music/       # Background music
│   ├── sfx/         # Sound effects
│   └── voice/       # Voice acting
├── fonts/           # UI and game fonts
├── ui/              # UI textures and layouts
├── animations/      # Animation data
├── scenes/          # Scene definitions
└── config/          # Configuration files

```

## Asset Guidelines

### Models
- Low-poly aesthetic: 500-5000 triangles per character
- Environment props: 100-1000 triangles
- LOD levels for performance

### Textures
- Base resolution: 1024x1024 or 2048x2048
- Formats: PNG for UI, DDS/KTX for game textures
- PBR workflow: Albedo, Normal, Metallic, Roughness, AO

### Audio
- Music: OGG format, 44.1kHz
- SFX: WAV format, 44.1kHz
- Compressed for distribution

### Shaders
- Vertex and Fragment shaders in GLSL 330+
- Named with .vert and .frag extensions
