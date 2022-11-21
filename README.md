# BinaryMeshFormat
## Build
```bash
cmake -S . -B build/Release -DCMAKE_BUILD_TYPE=Release
cmake --build build/Release
```
## CLI tool usage
```bash
build/Release/BMF_convert o2b a.obj a.bmf
build/Release/BMF_convert b2o a.bmf a.obj
```
