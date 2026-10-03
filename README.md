# Image2ASCII

A small C++ console application that converts an image into ASCII art. Each pixel is mapped to a character based on its brightness, and the result is printed to the console (optionally in full 24-bit color) and saved to a text file.

## Features

- Converts any image supported by OpenCV (JPG, PNG, BMP, ...) into ASCII art
- **Three character sets** to control level of detail: small, medium and large
- **Two color modes**: plain black & white, or true-color (RGB) output using ANSI escape codes
- Brightness calculated with the standard luminance formula (`0.299·R + 0.587·G + 0.114·B`)
- Saves the plain-text result to `image.txt` alongside printing it in the console

## How it works

1. The image is loaded with OpenCV and resized to **200 × 200** pixels.
2. For every pixel, the RGB values are read and the brightness (0–255) is computed.
3. The brightness is mapped to an index in the active character set, from dark characters (`@`, `#`) to light ones (`.`, space).
4. The character is printed to the console (colored with the pixel's RGB value in RGB mode) and written to `image.txt` (always without color).

### Character sets

| Mode          | Characters                                                                |
|---------------|---------------------------------------------------------------------------|
| `smallSymb`   | `@#*+=-:. `                                                               |
| `mediumSymb`  | `@#W$9876543210?!;:=-,._ ` *(default)*                                    |
| `largeSymb`   | `@$#WmaOzAdzcfvxrjft/\|()1{}[]?-_+~<>i!lI;:,"^`'. `                       |

## Project structure

| File                | Purpose                                                                     |
|---------------------|-----------------------------------------------------------------------------|
| `ASCII_ART_.cpp`    | Entry point: loads the image and starts rendering                           |
| `ASCIIConverter.h/.cpp` | Maps a pixel's brightness to an ASCII character; holds the symbol mode  |
| `Pixel.h`           | `PIXEL` class storing R, G, B and computing brightness                      |
| `Renderer.h/.cpp`   | Resizes the image, loops over pixels, prints to console and writes `image.txt` |
| `ASCII_ART_.vcxproj`| Visual Studio 2022 project file                                             |

## Requirements

- **Windows** (the renderer includes `<windows.h>`)
- **Visual Studio 2022** (platform toolset `v143`, x64)
- **OpenCV** (the project is configured for `opencv_world500`)
- A terminal that supports 24-bit ANSI colors, such as Windows Terminal, for RGB mode

## Getting started

1. **Clone the repository**
   ```bash
   git clone https://github.com/TymurShashok/Image2ASCII.git
   ```
2. **Install OpenCV** and note the folder where it is extracted.
3. **Open `ASCII_ART_.vcxproj`** in Visual Studio and update the project paths to match your machine
   (Project → Properties):
   - *C/C++ → General → Additional Include Directories*: `<opencv>\build\include`
   - *Linker → General → Additional Library Directories*: `<opencv>\build\x64\vc16\lib`
   - *Linker → Input → Additional Dependencies*: `opencv_world500d.lib` (Debug) / `opencv_world500.lib` (Release)

   The repository currently contains absolute paths from the author's machine, so they must be changed.
4. **Add the OpenCV DLL** (`opencv_world500d.dll` / `opencv_world500.dll`) to your `PATH` or next to the built `.exe`.
5. **Place your image** in the project folder and name it `image1.jpg` (or change the filename in `ASCII_ART_.cpp`).
6. **Build and run** (x64, Debug or Release). The ASCII art appears in the console and is saved as `image.txt`.

> Tip: reduce the console font size or zoom out so the 200-character-wide output fits on one line.

## Configuration

Settings are currently set in the source code:

| Setting          | Where                      | Default       | Options                                  |
|------------------|----------------------------|---------------|------------------------------------------|
| Input image      | `ASCII_ART_.cpp`           | `image1.jpg`  | any OpenCV-readable file                 |
| Symbol set       | `ASCIIConverter.h`         | `mediumSymb`  | `smallSymb`, `mediumSymb`, `largeSymb`   |
| Color mode       | `Renderer.h`               | `RGB`         | `BlackWhite`, `RGB`                      |
| Output size      | `Renderer.cpp`             | 200 × 200     | change `new_width` / `new_height`        |

## Known limitations

- Output size is fixed at 200 × 200, which stretches images that are not square, since characters are also taller than they are wide
- Input filename and settings are hard-coded; there is no command-line interface yet
- Windows-only

## Roadmap ideas

- Command-line arguments for input file, size, symbol set and color mode
- Preserve aspect ratio when resizing
- Cross-platform build (CMake)
- Export colored output to HTML or an image

## Author

[Tymur Shashok](https://github.com/TymurShashok)