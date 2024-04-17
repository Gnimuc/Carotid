# Carotid

[![CI](https://github.com/Gnimuc/Carotid/actions/workflows/CI.yml/badge.svg)](https://github.com/Gnimuc/Carotid/actions/workflows/CI.yml)
[![Documentation](https://img.shields.io/badge/docs-dev-blue.svg)](https://gnimuc.github.io/Carotid)

## Build

```
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/your_install_prefix_dir
cmake --build build --config Release
ctest --Release
```
