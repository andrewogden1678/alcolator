# build application instance
cd build   
cmake ..
cmake --build . --config Release

# run application instance
cd Release
start Alcolator.exe