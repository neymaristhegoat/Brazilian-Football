# Brazilian Football - Development Tools

This directory contains development tools and utilities.

## Tools

### Model Converter
Converts 3D models to engine format
```bash
./tools/model_converter input.fbx output.bfm
```

### Texture Packer
Packs multiple textures into atlases
```bash
./tools/texture_packer --input textures/ --output atlas.png
```

### Scene Editor
Visual scene editor (GUI tool)
```bash
./tools/scene_editor
```

### Asset Baker
Pre-processes and optimizes assets
```bash
./tools/asset_baker --input assets/ --output cooked/
```

### Network Simulator
Tests networking under various conditions
```bash
./tools/network_sim --latency 100 --packet-loss 5
```
