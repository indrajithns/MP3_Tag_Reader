# MP3 Metadata Editor

MP3 tag reader is a software which will read and display MP3 (ID3) tag information from MP3 files. The software will be desktop based and not web based. All operations will be performed using command line interface. A command-line tool to view and modify the metadata of MP3 files, including title, artist, album, year, genre, and more. This project provides functionality to read, edit, and update the metadata tags of MP3 files, offering an easy way to manage MP3 information.

## Features

- **View MP3 metadata**: Read and display metadata tags such as title, artist, album, genre, etc.
- **Edit MP3 metadata**: Modify specific metadata tags, including title (`-t`), artist (`-a`), album (`-A`), and genre (`-g`).
- **Support for multiple tags**: Modify common MP3 metadata tags such as year (`-y`), comment (`-c`), and genre.
- **Overwrite original file**: After modifying the metadata, the program writes the changes back to the MP3 file.

## Files Overview

### 1. `common.c` / `common.h`
These files contain common utility functions used across the project, such as file handling, metadata reading, and validation. They also define helper functions and macros shared between different parts of the program.

### 2. `edit_tag.c` / `edit.h`
Contains the core functions to modify MP3 metadata:
- **`store_frame_size`**: Writes the size of a metadata frame to the MP3 file.
- **`find_tag_size_pos`**: Finds the position and size of a specific metadata tag.
- **`validate`**: Validates the input operation argument.
- **`do_option`**: Executes the operation to modify the metadata and writes the changes back to the MP3 file.

### 3. `mp3tag.c`
The entry point of the program. It handles user input, checks the desired operation (view metadata, modify metadata, show version, etc.), and invokes the corresponding functions.

### 4. `type.h`
Defines the structures and types used throughout the program:
- **`MP3Info`**: Structure storing information related to the MP3 file, such as file pointers, metadata positions, sizes, and keys.
- Enumerations for `Status` (success or failure) and `OperationType` (help, file operations, metadata modification).

## File Descriptions

### `common.c`

This file implements the common utility functions that are shared across the program. It includes:
- File handling routines.
- Helper functions to read and manipulate MP3 metadata.
- Macros for status codes and operation types.

### `common.h`

This header file declares the functions and constants used in `common.c`. It includes:
- Function prototypes for metadata reading and manipulation.
- Status codes and operation types.

### `edit_tag.c`

This file provides the core functionality for editing MP3 metadata tags. It includes:
- **`store_frame_size`**: Stores the size of a metadata frame in the MP3 file.
- **`find_tag_size_pos`**: Finds the size and position of a specific metadata tag.
- **`validate`**: Checks if the provided operation arguments are valid.
- **`do_option`**: Executes the operation to modify the metadata and writes the changes back to the MP3 file.

### `edit.h`

This header file declares functions for editing MP3 metadata. It provides:
- Prototypes for functions that modify metadata tags, validate arguments, and store frame sizes.

### `mp3tag.c`

The entry point for the MP3 metadata editor program. It processes the user input, determines the operation to be performed (view metadata, modify metadata, etc.), and invokes the corresponding functions. Features:
- **Displays help information** for program usage.
- **Reads and prints MP3 metadata tags**.
- **Allows modification of specific metadata tags**.
- **Prints the current version** of the program.

### `type.h`

Defines the data types and structures used in the MP3 metadata editor program. This includes:
- **`MP3Info`**: A structure storing information related to an MP3 file, such as file pointers, metadata positions, sizes, and keys.
- **Enumerations**: `Status` for function status (success or failure) and `OperationType` for operations (help, file reading, metadata modification).

# MP3 Metadata Editor

The MP3 Metadata Editor is a command-line tool that allows users to view and modify the metadata of MP3 files. It supports editing common metadata tags such as title, artist, album, year, genre, and comment.

## Usage

The MP3 Metadata Editor provides several command-line options to view and modify MP3 file metadata.

### Compilation

To compile the program, run the following commands:

```bash
gcc -o mp3tag mp3tag.c common.c edit_tag.c -lm
```

### Viewing Metadata
To display the metadata of an MP3 file, run:

```bash
./mp3tag -file <filename>
```

This command will show the metadata of the specified MP3 file.

### Modifying Metadata
To modify the metadata of an MP3 file, you can use the following commands:

```bash
./mp3tag -t <new_title> <filename>      # Modify the title
./mp3tag -a <new_artist> <filename>     # Modify the artist
./mp3tag -A <new_album> <filename>      # Modify the album
./mp3tag -y <new_year> <filename>       # Modify the year
./mp3tag -g <new_genre> <filename>      # Modify the genre
./mp3tag -c <new_comment> <filename>    # Modify the comment
```

You can replace `<new_title>`, `<new_artist>`, `<new_album>`, etc., with the new values for each metadata tag.

### Help and Version Information
To display help information about the available options and usage:

```bash
./mp3tag -help
```

To view the current version of the program:

```bash
./mp3tag -version
```

## Example
Here are some example commands:

```bash
# View metadata of an MP3 file
./mp3tag -file song.mp3

# Modify the title of an MP3 file
./mp3tag -t "New Title" song.mp3

# Modify the artist of an MP3 file
./mp3tag -a "New Artist" song.mp3
```

This tool provides an easy way to read and modify the metadata of MP3 files, making it useful for organizing and updating music libraries.

