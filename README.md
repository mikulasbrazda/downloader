# Downloader

A simple multithreaded command-line tool to download files from URLs using C++ and curl.

## Features

- Multithreaded downloading
- User-friendly command-line interface
- Output files saved to a specified directory

## Requirements

- C++20 or newer compiler
- [CMake](https://cmake.org/) (version 3.10 or newer recommended)
- [curl](https://curl.se/) command-line tool installed and available in your system PATH

## Build Instructions (with CMake)

1. Clone the git repository
2. Go to project's root folder and create build directory
   ```
   mkdir build
   cd build
   ```
3. Run CMake to configure the project:
   ```
   cmake ..
   ```
4. Build the project:
   ```
   cmake --build .
   ```
   This will generate the `downloader` executable in the `build` directory.

## Usage

1. Run the program:
   ```
   ./downloader.exe
   ```
2. Enter URLs to download files. Type `quit` to exit.

## Notes

- Make sure `curl` is installed and accessible from the command line.
- Downloaded files will be saved in the output directory specified by `OUTPUT_DIR` in the code.

## License