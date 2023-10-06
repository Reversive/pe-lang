# pe-lang

## Table of Contents

- [About](#about)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Running pe-lang](#running-pe-lang)
  - [Example Code](#example-code)
- [Credits](#credits)

## About

pe-lang is a custom programming language created with Bison and Flex. It is designed to analyze PE executables in a simplistic way.

## Features

- Extract basic PE header information (sections, cpu arch, entrypoint)
- Explore sections in detail
- Analyze imports and exports
- Do relational operations
- Use basic control flow structures
- Print results to stdout

## Getting Started

### Prerequisites

* [Bison v3.8.2](https://www.gnu.org/software/bison/)
* [CMake v3.24.1](https://cmake.org/)
* [Flex v2.6.4](https://github.com/westes/flex)
* [GCC v11.1.0](https://gcc.gnu.org/)
* [Make v4.3](https://www.gnu.org/software/make/)

### Installation

To build the project completely, run the following commands in the root of the repository (on Linux):
```
user@machine:path/ $ chmod u+x --recursive script
user@machine:path/$script/build.sh
```
In a Microsoft Windows environment, however, you must run:
```
user@machine:path/ $ script\build.bat
```
Then the generated solution bin\Compiler.sln must be opened with the Microsoft Visual Studio 2022 IDE. The executables that this system builds are placed within the bin\Debug and bin\Release directories, as appropriate.

## Usage
### Running pe-lang
On linux:
```
user@machine:path/ $ script/start.sh program
```
On windows:
```
user@machine:path/ $ script\start.bat program
```
### Example Code
```
PEFile pe = peopen ("file.exe");
for SectionInfo section in pe.sections {
  print "{1} found on address {2} with size {3}",
    section.name,
    section.virtual_address,
    section.virtual_size;
}
```

## Credits
- [@agustin-golmar](https://github.com/agustin-golmar/)
- [@Reversive](https://github.com/Reversive)
