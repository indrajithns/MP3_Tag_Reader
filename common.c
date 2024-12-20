/*
 * File: common.c
 * Description: This file provides functionalities to extract and manage metadata
 *              from MP3 files. It includes functions to validate input, open files,
 *              parse metadata tags, and display the extracted information.
 * Functions:
 *   - find_meta: Main function to process the MP3 file and extract metadata.
 *   - print_tag_data: Prints the extracted MP3 metadata in a readable format.
 *   - check_for_text_frame: Identifies and processes text frames in the MP3 file.
 *   - get_info_in_text_tag: Extracts and stores metadata information from a tag.
 *   - get_tag: Reads a specific tag from the MP3 file.
 *   - load_key_tag: Loads predefined metadata keys for processing.
 *   - mp3_tag_head_size: Reads the header size of the MP3 metadata.
 *   - fram_size: Reads the size of a metadata frame.
 *   - id_type: Identifies the MP3 version from its header.
 *   - open_file: Opens the specified MP3 file for reading.
 *   - validate_argv: Validates command-line arguments to ensure proper input.
 *   - print_help: Displays help information for using the application.
 *   - check_operation: Determines the type of operation based on user input.
*/


#include <stdio.h>
#include <string.h>
#include "common.h"
#include "type.h"

// Main function to find and process MP3 metadata
Status find_meta(int argc, char *argv, MP3Info *mp3Info) {
    // Validate command-line arguments
    if (validate_argv(argc, argv, mp3Info) == e_failure) {
        fprintf(stderr, "Validate_Argv Function Failed\n");
        return e_failure;
    }

    // Open the MP3 file
    if (open_file(mp3Info) == e_failure) {
        fprintf(stderr, "Open_File Function Failed\n");
        return e_failure;
    }

    // Identify MP3 version
    if (id_type(mp3Info) == e_failure) {
        fprintf(stderr, "Id_Type Function Failed\n");
        return e_failure;
    }

    // Read tag header size
    if (mp3_tag_head_size(mp3Info) == e_failure) {
        fprintf(stderr, "MP3_Tag_Head_Size Function Failed\n");
        return e_failure;
    }

    // Load metadata keys
    if (load_key_tag(mp3Info) == e_failure) {
        fprintf(stderr, "Load_Key_Tag Function Failed\n");
        return e_failure;
    }

    // Check and process text frames
    if (check_for_text_frame(mp3Info) == e_failure) {
        fprintf(stderr, "Check_For_Text_Frame Function Failed\n");
        return e_failure;
    }

    return e_success;
}

// Prints extracted MP3 metadata
Status print_tag_data(MP3Info *mp3Info) {
    printf("\n\n");
    printf("=================================================================\n");
    printf("File\t: %s\n", mp3Info->src_fname);
    printf("Version\t: %s\n", mp3Info->idv);
    printf("=================================================================\n");
    printf("Title\t: %s\n", mp3Info->f_data[0]);
    printf("Artist\t: %s\n", mp3Info->f_data[2]);
    printf("Album\t: %s\n", mp3Info->f_data[3]);
    printf("Year\t: %s\n", mp3Info->f_data[4]);
    printf("Genre\t: %s\n", mp3Info->f_data[6]);
    printf("Comment\t: %s\n", mp3Info->f_data[5]);
    printf("Image\t: %s %s\n", mp3Info->f_data[8], mp3Info->f_data[8] + strlen(mp3Info->f_data[8]) + 2);
    printf("=================================================================\n\n");
    return e_success;
}

// Checks for text frames in the MP3 file
Status check_for_text_frame(MP3Info *mp3Info) {
    char ch;
    while (ftell(mp3Info->fptr_src) < mp3Info->tag_size + 10) {
        fread(&ch, 1, 1, mp3Info->fptr_src);
        if ((ch == 'T') || (ch == 'C') || ch == 'A') {
            get_tag(mp3Info->tag_4, 4, mp3Info->fptr_src);
            get_info_in_text_tag(mp3Info);
        }
    }
    return e_success;
}

// Extracts metadata information from a tag
Status get_info_in_text_tag(MP3Info *mp3Info) {
    int i = 0;
    while (i < 9) {
        if (!strcmp(mp3Info->tag_4, mp3Info->f_key[i])) {
            fram_size((char *)&mp3Info->f_size[i], mp3Info->fptr_src);
            fseek(mp3Info->fptr_src, 3L, SEEK_CUR);
            mp3Info->f_pos[i] = ftell(mp3Info->fptr_src);

            char *array = (char *)malloc(mp3Info->f_size[i] - 1);
            fread(array, mp3Info->f_size[i] - 1, 1, mp3Info->fptr_src);

            for (int j = 0; j < mp3Info->f_size[i] - 1; j++) {
                if ((array[j] == 0 && array[j] > 127) && strcmp(mp3Info->tag_4, "APIC"))
                    array[j] = 127;
            }

            mp3Info->f_data[i] = array;
            return e_success;
        }
        i++;
    }
    return e_failure;
}

// Reads tag from the file
Status get_tag(char *tag, int size, FILE *fptr) {
    fseek(fptr, -1L, SEEK_CUR);
    fread(tag, 1, size, fptr);
    return e_success;
}

// Loads metadata keys into the array
Status load_key_tag(MP3Info *mp3Info) {
    mp3Info->f_key[0] = "TIT2";  // Title
    mp3Info->f_key[1] = "TRCK";  // Track
    mp3Info->f_key[2] = "TPE1";  // Artist
    mp3Info->f_key[3] = "TALB";  // Album
    mp3Info->f_key[4] = "TYER";  // Year
    mp3Info->f_key[5] = "COMM";  // Comment
    mp3Info->f_key[6] = "TCON";  // Genre
    mp3Info->f_key[7] = "TIME";  // Time
    mp3Info->f_key[8] = "APIC";  // Image
    return e_success;
}

// Reads tag header size
Status mp3_tag_head_size(MP3Info *mp3Info) {
    fseek(mp3Info->fptr_src, 6L, SEEK_SET);
    fram_size((char *)&mp3Info->tag_size, mp3Info->fptr_src);
    return e_success;
}

// Reads frame size from the file
Status fram_size(char *size, FILE *fptr) {
    for (int i = 3; i >= 0; i--) {
        fread((size + i), 1, 1, fptr);
    }
    return e_success;
}

// Identifies MP3 version
Status id_type(MP3Info *mp3Info) {
    char buff[3];
    fread(buff, 3, 1, mp3Info->fptr_src);

    char mv;
    fread(&mv, 1, 1, mp3Info->fptr_src);
    if (!strcmp(buff, "ID3")) {
        mv += 48;
        sprintf(mp3Info->idv, "%s.%c", "ID3 v2", mv);
        return e_success;
    }

    return e_success;
}

// Opens the MP3 file
Status open_file(MP3Info *mp3Info) {
    if ((mp3Info->fptr_src = fopen(mp3Info->src_fname, "rb+")) == NULL) {
        perror("fopen");
        return e_failure;
    }
    return e_success;
}

// Validates command-line arguments
Status validate_argv(int argc, char *argv, MP3Info *mp3Info) {
    if ((strrchr(argv, '.') != NULL) && (strcmp(strrchr(argv, '.'), ".mp3"))) {
        fprintf(stderr, "Please input an MP3 file\n");
        return e_failure;
    }
    mp3Info->src_fname = argv;
    return e_success;
}

// Prints help information
void print_help() {
    printf("Usage: ./a.out -[tYaAycg] \"value\" file.mp3\n");
    printf("       ./a.out -v\n\n");
    printf("  -t   Modifies a Title Tag\n");
    printf("  -T   Modifies a Track Tag\n");
    printf("  -a   Modifies an Artist Tag\n");
    printf("  -A   Modifies an Album Tag\n");
    printf("  -y   Modifies a Year Tag\n");
    printf("  -c   Modifies a Comment Tag\n");
    printf("  -g   Modifies a Genre Tag\n");
    printf("  -h   Displays help info\n");
    printf("  -v   Prints version info\n");
}

// Checks the operation type
OperationType check_operation(char *argv[]) {
    if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) 
        return e_help;
    
    if (!strcmp(argv[1], "-v")) 
        return e_ver;

    if (argv[1][0] != '-')
        return e_file;

    if (argv[1][0] == '-' && argv[1][1] != '-')
        return e_option;

    return e_unsupport;
}
