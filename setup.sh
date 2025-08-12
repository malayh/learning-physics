#!/bin/bash
CLANG_VERSION=20

which clang++ && {
    clang++ --version || grep -q "version $CLANG_VERSION" || {
        echo "clang++ already installed but not version $CLANG_VERSION";
        exit 1;
    }
} || {
    echo "clang++ not installed, installing version $CLANG_VERSION";
    wget https://apt.llvm.org/llvm.sh;
    chmod +x llvm.sh;
    sudo ./llvm.sh -n clang++ $CLANG_VERSION;

    install_path=$(which clang++-$CLANG_VERSION);
    if [ -z "$install_path" ]; then
        echo "clang-$CLANG_VERSION not found in PATH";
        exit 1;
    fi
    sudo  ln -s "$install_path" /usr/bin/clang++;
    rm ./llvm.sh;
}

which cmake || {
    echo "cmake not installed, installing version 4.1.0";
    mkdir -p /opt/cmake;
    cd /opt/cmake || exit 1;
    wget https://github.com/Kitware/CMake/releases/download/v4.1.0/cmake-4.1.0-linux-x86_64.sh
    chmod +x cmake-4.1.0-linux-x86_64.sh;
    ./cmake-4.1.0-linux-x86_64.sh  --skip-license --exclude-subdir
    sudo ln -s /opt/cmake/bin/cmake /usr/bin/cmake;
} && {
    echo "cmake installed";
}

which conan || {
    echo "conan not installed, installing";
    wget https://github.com/conan-io/conan/releases/download/2.19.1/conan-2.19.1-amd64.deb
    sudo dpkg -i conan-2.19.1-amd64.deb;
    rm conan-2.19.1-amd64.deb;
    export CC=clang; export CXX=clang++; conan profile detect;

    configfile="$HOME/.conan2/profiles/default";
    test -f "$configfile" || {
        echo "Conan profile was not created!";
        exit 1;
    }

    sed -i 's/^compiler=.*/compiler=clang/' "$configfile";
    sed -i 's/^compiler.version=.*/compiler.version=20/' "$configfile";
    sed -i 's/^compiler.cppstd=.*/compiler.cppstd=gnu23/' "$configfile";
    echo "[conf]" >> "$configfile";
    echo 'tools.build:compiler_executables={"c": "clang", "cpp": "clang++"}' >> "$configfile";


} && {
    echo "conan installed";
}