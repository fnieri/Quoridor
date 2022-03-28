MAKEFLAGS += --silent

all: build test

.PHONY: setup
setup:
	cmake -B build -DCMAKE_BUILD_TYPE=Debug -Wno-dev

.PHONY: build
build:
	cmake --build build -j 8
	echo -e "\e[32m== SUCCESSFUL BUILDING! ==\e[0m\n"

.PHONY: test
test:
	ctest --test-dir build --output-on-failure
	echo -e "\e[32m== SUCCESSFUL TESTING! ==\e[0m\n"
