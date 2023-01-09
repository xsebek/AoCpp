# Advent of Code 2017

To build use these commands:
```sh
conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

Afterwards you can run the tests:
```sh
build/aoctest  # run all tests
```

And the selected day:
```sh
build/aocpp 01
```
