# InfiniMap

**Powerful fantasy map creation tool** - Generate beautiful procedural terrain maps with customizable biomes, realistic noise patterns, and smooth zoom controls.

![InfiniMap Demo](https://via.placeholder.com/800x400/4a5568/ffffff?text=InfiniMap+Demo)

## ✨ Features

- **Procedural Terrain Generation**: Uses advanced fractal noise (fBm) to create realistic landscapes
- **Biome System**: Automatic color mapping with distinct biomes (ocean, beach, plains, forest, mountains, snow)
- **High Performance**: Multi-threaded generation and optimized image processing
- **Smooth Zoom**: Mouse wheel zooming with configurable limits
- **Customizable**: Extensive configuration options for noise, colors, and rendering
- **Cross-Platform**: Works on Windows, macOS, and Linux

## 🚀 Quick Start

### Prerequisites

- **Qt6** (6.10.1 or later)
- **CMake** (3.16 or later)
- **C++17 compatible compiler** (GCC 8+, Clang 7+, MSVC 2019+)

### Build Instructions

#### Windows (Recommended)

1. **Install Qt Creator** or Qt maintenance tool from [qt.io](https://www.qt.io/download)
2. **Set environment variable**:
   ```bash
   set QTDIR=C:\Qt\6.10.1\mingw_64  # Adjust path to your Qt installation
   ```
3. **Build with CMake**:
   ```bash
   # Configure
   cmake -B build -S . -G "Ninja" -DCMAKE_PREFIX_PATH="%QTDIR%"

   # Build
   cmake --build build --config Release

   # Run
   ./build/InfiniMap.exe
   ```

#### Linux

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get update
sudo apt-get install qt6-base-dev cmake build-essential

# Build
cmake -B build -S .
cmake --build build --config Release

# Run
./build/InfiniMap
```

#### macOS

```bash
# Install Qt6 via Homebrew
brew install qt6 cmake

# Build
cmake -B build -S .
cmake --build build --config Release

# Run
./build/InfiniMap
```

## 🎮 Usage

### Basic Controls

- **Mouse Wheel**: Zoom in/out
- **Mouse Drag**: Pan around the map
- **Window Resize**: Application adapts to window size

### Configuration

Edit `src/config/Config.h` to customize:

```cpp
// Map dimensions
static constexpr int MapWidth  = 2048;  // Terrain width in pixels
static constexpr int MapHeight = 2048;  // Terrain height in pixels

// Noise parameters
static constexpr float NoiseScale       = 0.55f;  // Feature size (lower = larger features)
static constexpr float NoiseFloor       = 0.272f; // Minimum noise value
static constexpr float NoiseCeil        = 0.714f; // Maximum noise value
static constexpr int   NoiseOctaves     = 5;      // Fractal detail levels
static constexpr float NoisePersistence = 0.6f;   // Detail decay per octave
static constexpr float NoiseBaseFreq    = 0.002f; // Base frequency

// View controls
static constexpr int WindowWidth  = 1600;  // Initial window width
static constexpr int WindowHeight = 900;   // Initial window height
static constexpr double MinZoomScale = 0.1;  // Minimum zoom level
static constexpr double MaxZoomScale = 10.0; // Maximum zoom level
```

## 🏗️ Architecture

### Core Components

```
src/
├── core/           # Main application logic
│   ├── MapScene.*  # Terrain generation and scene management
│   └── MapView.*   # View controls and zoom handling
├── terrain/        # Terrain generation algorithms
│   ├── Noise.*     # Perlin noise and fBm implementation
│   └── BiomeColor.* # Biome color mapping
├── utils/          # Utility functions
│   ├── ImageUtils.* # Image processing and filtering
│   └── Random.*     # Random number generation
└── config/         # Configuration management
    └── Config.h    # Centralized configuration
```

### Key Algorithms

- **Fractal Brownian Motion (fBm)**: Multi-octave noise for realistic terrain
- **Gaussian Blur**: Separable convolution for smooth terrain transitions
- **Biome Mapping**: Height-based color interpolation
- **Parallel Processing**: Multi-threaded terrain generation

## 🔧 Development

### Build Targets

```bash
# Standard build
cmake --build build --config Release

# Deploy Qt libraries (Windows)
cmake --build build --target deploy --config Release

# Install to system
cmake --install build --prefix /usr/local
```

### Development Setup

```bash
# Clone repository
git clone https://github.com/yourusername/infini-map.git
cd infini-map

# Setup build environment (see Build Instructions above)
cmake -B build -S .
cmake --build build --config Debug

# Run tests
ctest --output-on-failure
```

## 🧪 Testing

The project includes comprehensive unit tests for core functionality using Qt Test framework.

### Test Coverage

- **Noise Generation**: Tests for deterministic output, range validation, and statistical properties
- **Biome Coloring**: Tests for color mapping, biome transitions, and input validation
- **Image Processing**: Tests for Gaussian blur with various inputs and edge cases
- **Configuration**: Tests for parameter validation and compile-time assertions

### Test Structure

```
tests/
├── main.cpp              # Test application entry point
├── TestNoise.*           # Noise generation tests
├── TestBiomeColor.*      # Biome color mapping tests
├── TestImageUtils.*      # Image processing tests
└── TestConfig.*          # Configuration validation tests
```

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Commit changes: `git commit -m 'Add amazing feature'`
4. Push to branch: `git push origin feature/amazing-feature`
5. Open a Pull Request

## 📄 License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **Qt Framework**: Cross-platform GUI development
- **Perlin Noise**: Foundation for procedural terrain
- **Fractal Algorithms**: Realistic landscape generation

## 📞 Support

- **Issues**: [GitHub Issues](https://github.com/yourusername/infini-map/issues)
- **Discussions**: [GitHub Discussions](https://github.com/yourusername/infini-map/discussions)

---

**Made with ❤️ for procedural generation enthusiasts**
