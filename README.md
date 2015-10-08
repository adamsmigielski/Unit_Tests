# Unit_Tests
Unit tests framework for C++.

Build system
CMake - Unit_Tests project is added to environment with single static library.
It does not require any configuration.
Global settings should be set before Unit_Tests is added.

Requirements
Depends on Utilities library available here: https://github.com/adamsmigielski/Utilities.git

Usage
1. Create project that will build tested module as static library.
2. Create project that will build test executable.
3. The following definition should be added to projects 1 and 2:
	
	TARGET_COMPILE_DEFINITIONS (TESTED_MODULE_UT PUBLIC UNIT_TESTS_ENABLE)
	
4. Executable 2 should be linked with Unit_Tests and library 1.
