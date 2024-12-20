/*
 * File: common.h
 * Description: This header file declares functions and structures used for 
 *              processing and extracting metadata from MP3 files. It includes
 *              function prototypes for operations like validating input, 
 *              reading metadata, and displaying extracted information.
*/

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "type.h"

// Retrieves information from a text metadata tag in the MP3 file
Status get_info_in_text_tag(MP3Info *mp3Info);

// Prints metadata tags such as title, artist, album, etc., for the MP3 file
Status print_tag_data(MP3Info *mp3Info);

// Reads a metadata tag from the MP3 file
Status get_tag(char *tag, int size, FILE *fptr);

// Loads predefined key tags (e.g., title, artist) into the MP3Info structure
Status load_key_tag(MP3Info *mp3Info);

// Reads and stores the size of the metadata header in the MP3 file
Status mp3_tag_head_size(MP3Info *mp3Info);

// Reads the size of a metadata frame in the MP3 file
Status fram_size(char *size, FILE *fptr);

// Checks for and processes text frames within the MP3 metadata
Status check_for_text_frame(MP3Info *mp3Info);

// Orchestrates the process of finding and processing metadata from the MP3 file
Status find_meta(int argc, char *argv, MP3Info *mp3Info);

// Validates the command-line arguments to ensure they are correct and relevant
Status validate_argv(int argc, char *argv, MP3Info *mp3Info);

// Opens the MP3 file for reading and writing
Status open_file(MP3Info *mp3Info);

// Identifies the type/version of the MP3 metadata (e.g., ID3v2)
Status id_type(MP3Info *mp3Info);

// Prints a help message detailing how to use the program and its options
void print_help();

// Determines the type of operation requested based on command-line arguments
OperationType check_operation(char *argv[]);


#endif

