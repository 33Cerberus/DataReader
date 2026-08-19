# DataReader

A C++ console application for managing a list of people (name, surname, age). Data is loaded from a text file, can be edited interactively, and saved back to a file.

## Features

- Load people records from a text file, skipping and reporting malformed lines
- Interactive menu to add, remove, or edit a person
- Save the current list to a new file
- Basic input validation with error messages on invalid data

## Input Format

Each line: `Name Surname Age`

```
Jan Kowalski 30
Anna Nowak 40
```

Lines with missing, extra, or invalid values are skipped with an error message pointing to the line number.

## Tech Stack

- C++
- Visual Studio (`.sln` / `.vcxproj`)

## Getting Started

### Prerequisites

- Windows + Visual Studio (the project uses `conio.h` / `_getch`, which are Windows-specific)

### Build & Run

1. Open `DataReader.sln` in Visual Studio
2. Build and run the `DataReader` project
3. Enter the path to an input file (e.g. `Input.txt`) when prompted
4. Use the on-screen menu to add / remove / edit entries, then save

---

*This README was generated with the help of Claude.*
