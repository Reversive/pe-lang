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
* [Python v3.9](https://www.python.org/)
* [Pipenv](https://pypi.org/project/pipenv/)

### Installation

To build the project completely, run the following commands in the root of the repository (on Linux):
```
user@machine:pe-lang/ $ chmod u+x --recursive script
user@machine:pe-lang/$script/build.sh
```
In a Microsoft Windows environment, however, you must run:
```
user@machine:pe-lang/ $ script/build.bat
```
Then the generated solution bin\Compiler.sln must be opened with the Microsoft Visual Studio 2022 IDE. The executables that this system builds are placed within the bin\Debug and bin\Release directories, as appropriate.

## Usage
### Running pe-lang
On linux:
```
user@machine:pe-lang/ $ script/start.sh program
```
On windows:
```
user@machine:pe-lang/ $ script/start.bat program
```
This will build a `generated.py` file under the `output` folder. To run the generated file, run the following commands:
```
user@machine:pe-lang/output/ $ pipenv install
user@machine:pe-lang/output/ $ pipenv run python generated.py
```
### Example Code
```
main {
    PEFile pe = peopen("./binaries/setup.exe");
    for (PEImport import in pe.imports)
    {
        print import.dll;
        for (PEFunction function in import.functions)
        {
            print "\t", function.address, function.name;
        }
    }
    
}
```

## Credits
- [@agustin-golmar](https://github.com/agustin-golmar/)
- [@Reversive](https://github.com/Reversive)
