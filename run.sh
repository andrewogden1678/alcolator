# build application instance
cd build   
cmake ..
cmake --build . --config Release --clean-first

# run instance
cd Release
start Alcolator.exe