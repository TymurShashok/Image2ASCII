# Image2ASCII

[![Build](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/TymurShashok/Image2ASCII/actions)
[![License](https://img.shields.io/badge/License-MIT-brightgreen)](https://github.com/TymurShashok/Image2ASCII/blob/main/LICENSE)
[![Release](https://img.shields.io/badge/Release-v1.0.6-blue)](https://github.com/TymurShashok/Image2ASCII)

A small C++ console application that converts an image into ASCII art. Each pixel is mapped to a character based on its brightness, and the result is printed to the console (optionally in full 24-bit color) and saved to a text file.

> Note: Image2ASCII is tested only on Windows 10 x64.

## Features

- Converts any image supported by OpenCV (JPG, PNG, BMP, ...) into ASCII art
- **Command-line interface**: choose the input file, character set, color mode and output size without recompiling
- **Three character sets** to control level of detail: small, medium and large
- **Two color modes**: plain black & white, or true-color (RGB) output using ANSI escape codes
- **Aspect-ratio compensation**: every second pixel row is skipped, because characters are about twice as tall as they are wide
- Brightness calculated with the standard luminance formula (`0.299·R + 0.587·G + 0.114·B`)
- Saves the plain-text result to `image.txt` alongside printing it in the console
- **CMake build** (CMake 3.16+, C++17); OpenCV DLLs are copied next to the executable automatically on Windows

## Usage

```
Image2ASCII <image> [--symbols small|medium|large] [--color rgb|bw] [--width N] [--height N] [--original]
```

The first argument is always the image path. Options can follow in any order.

| Option                              | Description                                                  | Default  |
|-------------------------------------|--------------------------------------------------------------|----------|
| `<image>`                           | Path to the input image (first argument)                     | `image.jpg` (when run with no arguments) |
| `--symbols small\|medium\|large`    | Character set used for the output                            | `medium` |
| `--color rgb\|bw`                   | `rgb` = 24-bit color, `bw` = plain text (`BW` also accepted) | `rgb`    |
| `--width N`                         | Target width in pixels (= characters per line)               | `100`    |
| `--height N`                        | Target height in pixels before row skipping                  | `100`    |
| `--original`                        | Keep the original image size (no resizing)                   | off      |

### Examples

```bash
# Defaults: looks for image.jpg, medium symbols, RGB color
Image2ASCII

# Large character set, black & white
Image2ASCII photo.png --symbols large --color bw

# Resize to a given size (see the note on resizing below)
Image2ASCII photo.png --symbols small --color rgb --width 120 --height 60
```

> **Resizing note:** the image is currently resized only when the program receives at least 8 command-line arguments (including the program name), i.e. when `--width` and `--height` are passed together with at least one more option. Otherwise the original image size is used. See [Known limitations](#known-limitations).

## How it works

1. The image is loaded with OpenCV (`IMREAD_COLOR`) and, if requested, resized to the given width and height.
2. The image is scanned row by row, skipping every second row to compensate for the height of characters.
3. For every pixel, the RGB values are read and the brightness (0–255) is computed.
4. The brightness is mapped to an index in the active character set, from dark characters (`@`, `#`) to light ones (`.`, space).
5. The character is printed to the console (colored with the pixel's RGB value in RGB mode) and written to `image.txt` (always without color).

### Character sets

| Mode     | Characters                                                                |
|----------|---------------------------------------------------------------------------|
| `small`  | `@#*+=-:. `                                                               |
| `medium` | `@#W$9876543210?!;:=-,._ ` *(default)*                                    |
| `large`  | `@$#WmaOzAdzcfvxrjft/\|()1{}[]?-_+~<>i!lI;:,"^`'. `                       |

## Project structure

| File                    | Purpose                                                                          |
|-------------------------|----------------------------------------------------------------------------------|
| `Image2ASCII.cpp`       | Entry point: parses arguments, loads the image and starts rendering              |
| `Config.h`              | `config` struct: defaults and command-line argument parsing                      |
| `ASCIIConverter.h/.cpp` | Maps a pixel's brightness to an ASCII character for the selected symbol set      |
| `Pixel.h`               | `PIXEL` class storing R, G, B and computing brightness                           |
| `Renderer.h/.cpp`       | Loops over pixels, prints to console (with ANSI colors) and writes `image.txt`   |
| `CMakeLists.txt`        | CMake build configuration                                                        |
| `.github/workflows/`    | GitHub Actions workflow (build badge)                                            |

## Requirements

- **Windows** (the renderer includes `<windows.h>`)
- **CMake 3.16+** and a C++17 compiler (Visual Studio 2022 / MSVC recommended)
- **OpenCV** (the author builds against OpenCV 5.0, `opencv_world500`)
- A terminal that supports 24-bit ANSI colors, such as Windows Terminal, for RGB mode

## Getting started

1. **Clone the repository**
   ```bash
   git clone https://github.com/TymurShashok/Image2ASCII.git
   cd Image2ASCII
   ```
2. **Install OpenCV** and note the folder where it is extracted.
3. **Set the OpenCV path** in `CMakeLists.txt`. The file currently contains an absolute path from the author's machine, so change this line to match yours:
   ```cmake
   set(OpenCV_DIR "<opencv>/build/x64/vc16/lib")
   ```
4. **Configure and build**
   ```bash
   cmake -S . -B build
   cmake --build build --config Release
   ```
   Alternatively, open the project folder in Visual Studio 2022, which supports CMake projects directly.
5. **Run it.** On Windows the required OpenCV DLLs are copied next to the executable after the build.
   ```bash
   build\Release\Image2ASCII.exe image.jpg --symbols medium --color rgb
   ```
   The ASCII art appears in the console and is saved as `image.txt`.

> Tip: reduce the console font size or zoom out so wide output fits on one line.

## Known limitations

- The image is resized only when at least 8 arguments are passed; `--original` does not currently change this behavior
- `--width` and `--height` are not validated (invalid or missing values are not reported)
- `--height` is applied before every second row is skipped, so the number of text lines is smaller than the value you pass
- The OpenCV path in `CMakeLists.txt` is hard-coded and must be edited manually
- Windows-only (`<windows.h>` is used to enable ANSI colors)

## Roadmap ideas

- Reliable resizing logic and argument validation
- Preserve the aspect ratio automatically when only one of width/height is given
- Cross-platform support (remove the `<windows.h>` dependency, find OpenCV without a hard-coded path)
- Export colored output to HTML or an image

## Author

[Tymur Shashok](https://github.com/TymurShashok)