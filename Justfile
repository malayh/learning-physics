installdeps:
    mkdir -p build; 
    conan install . --output-folder=build/dependencies --build=missing \
        -c tools.system.package_manager:mode=install

init:
    cmake --preset conan-release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build:
    cmake --build build --preset conan-release