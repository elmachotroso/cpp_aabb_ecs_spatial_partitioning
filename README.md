# C++ AABB + Entity-Component System + Spatial Partitioning

Author: Andrei Victor  
https://github.com/elmachotroso/cpp_aabb_ecs_spatial_partitioning

A C++ Project on the implementation of AABB collision of Entities with tests on Naivette +
Spatial Paritioning (via Grid Buckets).

Current Status: WIP Spatial Partitioning is still slow compared to Naivette approach. I need to
conduct more checks on implementation to make it truly fast.
___  
## Tech Stack
* Visual Studio Code
* CMake
* Make
* GoogleTest (GTest)
* C++20
___
## Usage
This project relies on a CPP Template based on CMake + Make + GoogleTest.  
Suggested way of building and running the program.

### Windows
```cmd
// Generate Projects -- will build the project based on Make (not Visual Studio)
generate_projects.bat

// Compile + Link the project to produce release builds of app.exe and app_test.exe in ./bin/Release/
build_release.bat

// This will execute the app_test.exe that expects to show unit tests of Rectangle2D and
// Entity Component System
test_release.bat

// This is the proper way of running the application to showcase collision tests
./bin/Release/app.exe ./res/entityblueprints.txt
```

### MacOS / Unix shell
```/bin/bash
// Generate Projects -- will build the project based on Make (not Visual Studio)
./generate_projects.sh

// Compile + Link the project to produce release builds of app.exe and app_test.exe in ./bin/Release/
./build_release.sh

// This will execute the app_test.exe that expects to show unit tests of Rectangle2D and
// Entity Component System
./test_release.sh

// This is the proper way of running the application to showcase collision tests
./bin/Release/app ./res/entityblueprints.txt
```
