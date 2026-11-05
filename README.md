# 🇧🇷 Brazilian Football

### A stylized, low-poly football game with high-detail environments.

Brazilian Football is a 3D association football game built with **C++ and a custom engine**. Combining a distinctive low-poly art style with detailed environments and immersive gameplay, the project aims to deliver a unique football experience.

Built with performance and cross-platform compatibility in mind, Brazilian Football features a custom C++ game engine, a dedicated desktop launcher, and custom development tools.

Experience football in a stylized world. Build your team, step onto the pitch, and play.

<p align="left">
  <a href="https://github.com/neymaristhegoat/brazilian-football/releases"><img src="https://img.shields.io/github/v/release/neymaristhegoat/brazilian-football?style=flat-square&label=RELEASE" alt="Latest Release"></a>
  <a href="https://github.com/neymaristhegoat/brazilian-football/releases"><img src="https://img.shields.io/github/downloads/neymaristhegoat/brazilian-football/total?style=flat-square&label=DOWNLOADS" alt="Downloads"></a>
  <a href="https://github.com/neymaristhegoat/brazilian-football"><img src="https://img.shields.io/github/stars/neymaristhegoat/brazilian-football?style=flat-square&label=STARS" alt="Stars"></a>
  <a href="https://github.com/neymaristhegoat/brazilian-football/issues"><img src="https://img.shields.io/github/issues/neymaristhegoat/brazilian-football?style=flat-square&label=ISSUES" alt="Issues"></a>
</p>

---

## ⚽ Features

- **Low-Poly Graphics** — A distinctive stylized art direction with detailed environments.
- **Custom Engine** — A purpose-built C++ game engine powering gameplay and rendering.
- **Desktop Launcher** — A dedicated launcher built with TypeScript, HTML, and CSS.
- **Cross-Platform** — Designed to support Windows, Linux, and macOS.
- **Build Automation** — Python scripts for compilation, testing, and development workflows.

## 🛠️ Built With

| Technology | Usage |
|:---|:---|
| C++ | Core game engine |
| Custom Engine | Game systems and rendering |
| TypeScript | Launcher functionality |
| HTML5 / CSS3 | Launcher interface |
| Python | Build scripts and testing |
| CMake / Make | Build configuration |
| GCC / Clang | C++ compilation |

## 📥 Download

The easiest way to get Brazilian Football is through the official GitHub Releases page.

**[Download Brazilian Football](https://github.com/neymaristhegoat/brazilian-football/releases)**

Installation packages and compiled builds for supported platforms are published there.

## 🔧 Building From Source

### Requirements

- C++ compiler (GCC or Clang)
- CMake or GNU Make
- Python
- Node.js and npm (for launcher development)

### Clone the Repository

```bash
git clone https://github.com/neymaristhegoat/brazilian-football.git
cd brazilian-football
```

### CMake

```bash
cmake -S . -B build
cmake --build build --config Release
```

### Make

```bash
make
```

### GCC

```bash
g++ -std=c++17 src/*.cpp -o brazilian-football
```

### Clang

```bash
clang++ -std=c++17 src/*.cpp -o brazilian-football
```

*Note: Direct compiler commands may require additional source files, include paths, platform-specific linker flags, and engine dependencies. CMake is recommended.*

## 🖥️ Launcher Development

The Brazilian Football launcher uses TypeScript, HTML, and CSS.

```bash
cd launcher
npm install
```

Use the development and build commands defined in the launcher's `package.json`.

## 🧪 Testing & Build Tools

Python is used for automated compilation workflows, development utilities, and testing.

```bash
python -m pip install pytest
python -m pytest
```

Additional build scripts are located in the project's `scripts/` directory.

## 🌍 Supported Platforms

| Platform | Build Support |
|:---|:---|
| Windows | Planned / Supported |
| Linux | Planned / Supported |
| macOS | Planned / Supported |

Precompiled installation files are distributed through [GitHub Releases](https://github.com/neymaristhegoat/brazilian-football/releases).

## 🤝 Contributing

Contributions, suggestions, and bug reports are welcome.

1. Fork the repository.
2. Create a branch for your changes.
3. Make your modifications.
4. Test your changes.
5. Submit a pull request.

## 🐛 Issues & Feedback

Found a bug or have a suggestion?

[Open an Issue](https://github.com/neymaristhegoat/brazilian-football/issues)

---

<p align="center">
  <b>🇧🇷 Brazilian Football</b><br>
  A different perspective on the beautiful game.
  <br><br>
  <a href="https://github.com/neymaristhegoat/brazilian-football">Repository</a> ·
  <a href="https://github.com/neymaristhegoat/brazilian-football/releases">Releases</a> ·
  <a href="https://github.com/neymaristhegoat/brazilian-football/issues">Issues</a>
</p>