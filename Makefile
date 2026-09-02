CXX ?= clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -pthread -O2

MODULES = 01 02 03 04 05 06 07

all: build/m01 build/m02 build/m03 build/m04 build/m05 build/m06 build/m07

build:
	mkdir -p build

build/m01: 01_pointers_references_and_memory/main.cpp | build
	$(CXX) $(CXXFLAGS) $< -o $@

build/m02: 02_oop_and_virtual_tables/main.cpp | build
	$(CXX) $(CXXFLAGS) $< -o $@

build/m03: 03_raii_and_smart_pointers/main.cpp | build
	$(CXX) $(CXXFLAGS) $< -o $@

build/m04: 04_move_semantics_and_rvalues/main.cpp | build
	$(CXX) $(CXXFLAGS) $< -o $@

build/m05: 05_templates_and_stl_containers/main.cpp | build
	$(CXX) $(CXXFLAGS) $< -o $@

build/m06: 06_modern_cpp_lambdas_and_functional/main.cpp | build
	$(CXX) $(CXXFLAGS) $< -o $@

build/m07: 07_multithreading_and_concurrency/main.cpp | build
	$(CXX) $(CXXFLAGS) $< -o $@

test: all
	@echo "🧪 正在依次运行 C++ 7 大核心语法模块..."
	@./build/m01
	@./build/m02
	@./build/m03
	@./build/m04
	@./build/m05
	@./build/m06
	@./build/m07
	@echo "🎉 全部 7 个 C++ 核心语法模块均成功编译并运行通过！"

clean:
	rm -rf build

.PHONY: all test clean
