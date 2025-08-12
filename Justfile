reset:
    test -d build && rm -rf build/* || true ;
init: reset
    mkdir -p build;
    cd build && \
    export CXX=clang++; export CC=clang; \
    cmake "../" && make;