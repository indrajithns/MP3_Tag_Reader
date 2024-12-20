/*
 * File: edit.h
 * Description: This header file declares functions for editing metadata in MP3 files. 
 *              It provides declarations for functions to validate input arguments, 
 *              locate and modify specific metadata tags, and store frame sizes.
*/

#ifndef EDIT_H
#define EDIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "type.h"
#include "edit.h"

// Writes the size of a metadata frame to the MP3 file
Status store_frame_size(FILE *fptr, int size);

// Finds the size and position of a specified metadata tag
Status find_tag_size_pos(char *Tag, int *pos, int *size, MP3Info *mp3Info);

// Checks if the provided operation argument is valid
Status validate(char *argv);

// Validates the input arguments for metadata modification
Status validate_argument(int argc, char *argv[]);

// Executes the specified operation to modify the metadata in the MP3 file
Status do_option(int argc, char *argv[], MP3Info *mp3Info);

#endif

