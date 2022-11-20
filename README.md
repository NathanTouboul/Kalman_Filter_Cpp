# Kalman_Filter_Cpp


Configure with: 
cmake -S . -B build (linux)
cmake -S . -B out\build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release (windows)

Build with 
make -C .out\build

Add boost manually if not found (windows)
SET BOOST_ROOT="<path_to_boost>"
SET BOOST_INCLUDEDIR="<path_to_boost>"
SET BOOST_LIBRARYDIR="<path_to_boost>\lib64-msvc-14.1"