# PCSC_project

A C++ project for PCSC course, configured for CLion IDE.

## Prerequisites

- CLion IDE (2020.3 or later recommended)
- CMake (3.10 or later)
- C++ compiler with C++17 support (GCC, Clang, or MSVC)

## Getting Started

### For CLion Users

1. Clone this repository:
   ```bash
   git clone https://github.com/leonlhuillier/PCSC_project.git
   ```

2. Open the project in CLion:
   - Launch CLion
   - Select "Open" from the welcome screen
   - Navigate to and select the `PCSC_project` folder
   - CLion will automatically detect the CMakeLists.txt and configure the project

3. Build the project:
   - CLion will prompt to load the CMake project - click "Load"
   - Once loaded, you can build by clicking the hammer icon or using `Build > Build Project`

4. Run the application:
   - Click the green play button or use `Run > Run 'PCSC_project'`

### Building from Command Line

```bash
mkdir build
cd build
cmake ..
make
./PCSC_project
```

## Project Structure

```
PCSC_project/
├── .idea/              # CLion project settings (shared configuration)
├── src/                # Source files
│   └── main.cpp        # Main application entry point
├── CMakeLists.txt      # CMake build configuration
├── .gitignore          # Git ignore rules
└── README.md           # This file
```

## Collaboration Guide

### What's Shared
- Source code in `src/`
- CMakeLists.txt build configuration
- Basic CLion project settings in `.idea/` (e.g., VCS, encoding, CMake profiles)

### What's Not Shared (in .gitignore)
- Personal workspace settings (`.idea/workspace.xml`, `.idea/tasks.xml`, etc.)
- Build artifacts (`cmake-build-*/`, `build/`, object files)
- OS-specific files

### Working Together
1. Always pull latest changes before starting work: `git pull`
2. Commit frequently with meaningful messages
3. Push your changes regularly to share with your partner
4. Communicate about major changes to avoid conflicts

## Contributing

When adding new source files:
1. Add the `.cpp` file to the `src/` directory
2. Update `CMakeLists.txt` to include new source files
3. Commit both the source file and updated CMakeLists.txt