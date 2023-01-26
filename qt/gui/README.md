# Cpp GUI with Qt5

Learning through books like:
```
Prentice Hall - CPlusPlus GUI Programming With QT4 (adapting everything to qt5)
No Starch - QT
```
And other resources.

# Requirements

Qt5 (used 5.12.0 for dev)

C++14/17 compiler (used gcc 9 - will probably use c++17 features)

CMake > 3.14 (could go lower)

# Building
```bash
mkdir build && \
cmake -GNinja -S. -Bbuild -DQt5_ROOT:PATH=<qt5_path>
```

# Running
```bash
./sheets
```