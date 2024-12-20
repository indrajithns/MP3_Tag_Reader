/*
 * File: type.h
 * Description: This header file defines the data types and structures used in the MP3 metadata editor program.
 *              It includes declarations for the `MP3Info` structure, enumerations for status codes and operations,
 *              and constants for managing metadata frames.
 * 
 * Features:
 *   - Defines the `MP3Info` structure for storing MP3 file metadata.
 *   - Enumerates operation types to support program actions like help, file read, and metadata modification.
 *   - Provides constants and typedefs for managing the metadata editor logic.
*/

#ifndef TYPE_H
#define TYPE_H

// Macro defining the size of the frame key array for metadata
#define FRAME_KEY_ARRAY_SIZE 9

// Typedef for unsigned integer for better readability
typedef unsigned uint;

/*
 * Structure: MP3Info
 * Description: Stores information related to an MP3 file, including metadata and file pointers.
*/

typedef struct _mp3Info
{
    char *src_fname;                  // Source file name
    FILE *fptr_src;                   // File pointer for the MP3 file
    uint tag_size;                    // Metadata tag size
    char *arg_key[7];                 // Array for command-line argument keys
    char data;                        // Temporary data storage
    char idv[9];                      // ID3 version string
    char tag_3[3];                    // Temporary storage for 3-character tags
    char tag_4[5];                    // Temporary storage for 4-character tags
    int f_size[FRAME_KEY_ARRAY_SIZE]; // Size of each metadata frame
    int f_pos[FRAME_KEY_ARRAY_SIZE];  // Position of each metadata frame
    char *f_data[FRAME_KEY_ARRAY_SIZE]; // Data for each metadata frame
    char *f_key[FRAME_KEY_ARRAY_SIZE];  // Keys for metadata frames
} MP3Info;

/*
 * Enumeration: Status
 * Description: Represents the status of function calls in the program.
*/

typedef enum
{
    e_failure, // Failure status
    e_success  // Success status
} Status;

/*
 * Enumeration: OperationType
 * Description: Represents the type of operation the program will perform.
*/

typedef enum
{
    e_help,      // Help operation
    e_file,      // File read operation
    e_option,    // Metadata modification operation
    e_ver,       // Version display operation
    e_unsupport  // Unsupported operation
} OperationType;

#endif
