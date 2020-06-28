# build typescript front-end
cd typescript
tsc --outDir ../assets/ts_compiled

# build application instance
cd ../build   
cmake ..
cmake --build . --config Release

# run application instance
cd Release
start Alcholator.exe