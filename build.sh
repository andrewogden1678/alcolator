# build application instance
cd build   
cmake ..
cmake --build . --config Release --clean-first

# copy dependencies
cp ../Alcolator.db Release
cp ../include/sqlite3/sqlite3.dll Release
