clear
rm -rf build
mkdir -p build
cd build
cmake ..
make -j8
./compiler ../example/src/main.cpp --out-dir=../example/build

