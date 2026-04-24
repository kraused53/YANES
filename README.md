# YANES
Yet Another NES emulator written in C++


Build CMake System
```
cmake -S . -B build
```

Build using CMake - Standard
```
cmake --build build -j
```

Build using CMake - Speedy
```
cmake --build build --config Release -j
```

Run Tests
```
ctest --test-dir build --output-on-failure
```