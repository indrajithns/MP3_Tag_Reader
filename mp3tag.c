/*
 * File: mp3tag.c
 * Description: This is the entry point for the MP3 metadata editor program. 
 *              The program allows users to view or modify MP3 metadata 
 *              such as title, artist, album, year, genre, etc.
 * 
 * Features:
 *   - Displays help information for program usage.
 *   - Reads and prints MP3 metadata tags.
 *   - Allows modification of specific metadata tags.
 *   - Prints the current version of the program.
 * 
 * Functions:
 *   - main: Handles user input, determines the operation, and invokes 
 *           corresponding functions for metadata operations.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "common.h"
#include "type.h"
#include "edit.h"

// Main function: Entry point for the MP3 metadata editor
int main(int argc, char *argv[])
{
    MP3Info mp3Info; // Structure to hold MP3 metadata information

    if (argc > 1)
    {
        // Determine the operation based on the input arguments
        switch (check_operation(argv))
        {
            case e_help: // Help option
                print_help();
                break;

            case e_file: // Display metadata of an MP3 file
                if (find_meta(argc, argv[1], &mp3Info) == e_success)
                    print_tag_data(&mp3Info);
                break;

            case e_option: // Perform metadata modification
                if (do_option(argc, argv, &mp3Info) == e_failure)
                {
                    print_help();
                }
                break;

            case e_ver: // Display version information
                printf("Version 1.1\n");
                break;

            default: // Invalid option
                printf("Invalid Option !!! '%s'\n", argv[1]);
                print_help();
                break;
        }
    }
    else
    {
        // No valid input arguments provided
        printf("Invalid Option !!!\n");
        print_help();
    }
}
