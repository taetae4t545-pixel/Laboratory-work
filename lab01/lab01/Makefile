# Сборка практической работы. Проверенный путь сборки — этот Makefile.
#   make          тесты с санитайзерами (основной режим)
#   make bench    тесты и программы из apps/ с -O2 без санитайзеров
#   make apps     программы из apps/ с санитайзерами
#   make clean

CXX  ?= g++
STD  ?= -std=c++17
WARN := -Wall -Wextra -Wpedantic
SAN  := -fsanitize=address,undefined -fno-omit-frame-pointer
INC  := -Iinclude -I../common

SRC     := $(wildcard src/*.cpp)
TESTSRC := $(wildcard tests/*.cpp)
APPSRC  := $(wildcard apps/*.cpp)
APPS_D  := $(patsubst apps/%.cpp,build/%,$(APPSRC))
APPS_R  := $(patsubst apps/%.cpp,build-release/%,$(APPSRC))
HDRS    := $(wildcard include/*.hpp) $(wildcard ../common/*.hpp)

.PHONY: all test bench apps apps-release clean
all: test

build/tests: $(SRC) $(TESTSRC) $(HDRS)
	@mkdir -p build
	$(CXX) $(STD) $(WARN) -g $(SAN) $(INC) $(SRC) $(TESTSRC) -o $@

test: build/tests
	@echo "--- тесты с санитайзерами ---"
	@ASAN_OPTIONS=detect_leaks=1 ./build/tests

build-release/tests: $(SRC) $(TESTSRC) $(HDRS)
	@mkdir -p build-release
	$(CXX) $(STD) $(WARN) -O2 -DNDEBUG $(INC) $(SRC) $(TESTSRC) -o $@

bench: build-release/tests $(APPS_R)
	@echo "--- сборка для замеров готова, каталог build-release/ ---"

build/%: apps/%.cpp $(SRC) $(HDRS)
	@mkdir -p build
	$(CXX) $(STD) $(WARN) -g $(SAN) $(INC) $< $(SRC) -o $@

build-release/%: apps/%.cpp $(SRC) $(HDRS)
	@mkdir -p build-release
	$(CXX) $(STD) $(WARN) -O2 $(INC) $< $(SRC) -o $@

apps: $(APPS_D)
apps-release: $(APPS_R)

clean:
	rm -rf build build-release
