/*
 * File: edit_tag.c
 * Description: This file provides functions to modify the metadata of MP3 files.
 *              It includes functionalities to validate input arguments, locate and
 *              update specific metadata tags, and overwrite the original file with
 *              the modified metadata.
 * Functions:
 *   - store_frame_size: Stores the size of a metadata frame in the MP3 file.
 *   - find_tag_size_pos: Finds the size and position of a specific metadata tag.
 *   - validate: Checks if the provided operation arguments are valid.
 *   - do_option: Performs the specified operation to modify the metadata and writes
 *                the changes back to the MP3 file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "type.h"
#include "edit.h"

// Stores the size of a metadata frame
Status store_frame_size(FILE *fptr, int size)
{
    int i;
    char *value = (char *)&size;
    for (i = 3; i >= 0; i--)
    {
        fwrite((value + i), 1, 1, fptr);
    }
    return e_success;
}

// Finds the size and position of a specific tag in the MP3 file
Status find_tag_size_pos(char *Tag, int *pos, int *size, MP3Info *mp3Info)
{
    int i;
    for (i = 0; i < 9; i++)
    {
        if (!strcmp(mp3Info->f_key[i], Tag))
        {
            *size = mp3Info->f_size[i] - 1;
            *pos = mp3Info->f_pos[i];
            return e_success;
        }
    }
    return e_failure;
}

// Validates the provided operation argument
Status validate(char *argv)
{
    char opt[7][3] = {"-t", "-T", "-a", "-A", "-y", "-c", "-g"};
    int i;
    for (i = 0; i < 7; i++)
    {
        if (!strcmp(argv, opt[i]))
        {
            return e_success;
        }
    }
    return e_failure;
}

// Performs the specified operation to modify MP3 metadata
Status do_option(int argc, char *argv[], MP3Info *mp3Info)
{
    int i;
    char *string;
    uint length, f_pos;

    // Validate argument count
    if (argc <= 2)
    {
        return e_failure;
    }

    // Validate operation type
    if (validate(argv[1]) == e_failure)
    {
        return e_failure;
    }

    // Extract metadata from MP3 file
    if (find_meta(argc, argv[argc - 1], mp3Info) == e_failure)
    {
        return e_failure;
    }

    // Open a temporary file for modification
    FILE *fptr_dest = fopen("sample_1.mp3", "wb+");
    fseek(mp3Info->fptr_src, 0L, SEEK_SET);

    char opt[7][3] = {"-t", "-T", "-a", "-A", "-y", "-c", "-g"};

    // Determine the operation and find tag position and size
    for (i = 0; i < 7; i++)
    {
        if (!strcmp(argv[1], opt[i]))
        {
            string = argv[2];
            if (find_tag_size_pos(mp3Info->f_key[i], &f_pos, &length, mp3Info) == e_failure)
                return e_failure;
            break;
        }
    }

    // Copy initial data up to the tag position
    for (i = 0; i < f_pos - 7; i++)
    {
        fread(&mp3Info->data, 1, 1, mp3Info->fptr_src);
        fwrite(&mp3Info->data, 1, 1, fptr_dest);
    }

    int a = 0;
    // Handle additional bytes for "COMM" tag
    if (!strcmp(argv[1], "-c"))
        a = 4;

    // Store the new frame size
    store_frame_size(fptr_dest, a + strlen(string) + 1);
    fseek(mp3Info->fptr_src, 4, SEEK_CUR);

    // Copy additional space after the size
    for (i = 0; i < 3 + a; i++)
    {
        fread(&mp3Info->data, 1, 1, mp3Info->fptr_src);
        fwrite(&mp3Info->data, 1, 1, fptr_dest);
    }

    // Write the new string
    for (i = 0; i < strlen(string); i++)
    {
        fwrite(&string[i], 1, 1, fptr_dest);
    }
    fseek(mp3Info->fptr_src, length - a, SEEK_CUR);

    // Copy remaining data from source to destination
    while (fread(&mp3Info->data, 1, 1, mp3Info->fptr_src) > 0)
    {
        fwrite(&mp3Info->data, 1, 1, fptr_dest);
    }

    // Copy data back to the original file
    rewind(mp3Info->fptr_src);
    rewind(fptr_dest);
    while (fread(&mp3Info->data, 1, 1, fptr_dest) > 0)
    {
        fwrite(&mp3Info->data, 1, 1, mp3Info->fptr_src);
    }

    return e_success;
}
