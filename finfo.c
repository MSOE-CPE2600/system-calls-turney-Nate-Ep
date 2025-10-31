/**
* @file finfo.c
* @author Nathan Eppler <epplern@msoe.edu>
* @date 30 October 2025
* @brief
*
* Course: CPE 2600
* Section: 111
* Due: 3 November 2025
*
* To Compile: make finfo
* To Run: ./finfo
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

char* get_filetype(mode_t mode);
void get_filepermissions(mode_t mode, char *ret);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Error: expected an input argument\n");
        exit(-1);
    }
    char *path = argv[1];
    struct stat file_info;
    errno = 0;
    int ret_val = stat(path, &file_info);

    if (ret_val == 0) {
        //sucsessfully retrieved file stats
        //print file type
        mode_t mode = file_info.st_mode;
        char *file_type = get_filetype(mode);
        printf("File type: %s\n", file_type);

        //print file permissions in a readable format
        char *permissions = (char*)malloc(3000);
        if (permissions != NULL) {
            get_filepermissions(mode, permissions);
            printf("Permissions: \n%s\n", permissions);
            free(permissions);
        } else {
            printf("Error allocating memory for permissions display\n");
        }

        //print user ID
        printf("Owner UID: %d\n", (int)file_info.st_uid);

        //print size of file in bytes
        printf("File Size: %ld Bytes\n", (long)file_info.st_size);

        //print date and time of last modification, with an easy format to view
        struct timepec ts = file_info.st_mtim;
        
        
    } else {
        printf("Error retrieving file data\n");
        perror("Error: ");
        exit(-1);
    }

    //display file type
    //display owner of the file -- UID is enough
    //display file size in bytes
    //date and time of last modification, easy for viewing
    //if error, print and exit
    return 0;
}

char* get_filetype(mode_t mode) {
    if (S_ISREG(mode)) {
        return "Regular file\n";
    } else if (S_ISDIR(mode)) {
        return "Directory\n";
    } else if (S_ISCHR(mode)) {
        return "Character device\n";
    } else if (S_ISBLK(mode)) {
        return "Block device\n";
    } else if (S_ISFIFO(mode)) {
        return "FIFO/pipe\n";
    } else if (S_ISLNK(mode)) {
        return "Symbolic link\n";
    } else if (S_ISSOCK(mode)) {
        return "Socket";
    } else {
        return "Unknown\n";
    }
}

void get_filepermissions(mode_t mode, char *ret) {
    //get owner permissions
    if (!(mode & (S_IRUSR | S_IWUSR | S_IXUSR))) {
        strcat(ret, "Owner has no perimissions\n");
    } else {
        strcat(ret, "Owner Permissions: ");

        if (mode & S_IRUSR) {
            strcat(ret, "Read -- ");
        }

        if (mode & S_IWUSR) {
            strcat(ret, "Write -- ");
        }

        if (mode & S_IXUSR) {
            strcat(ret, "Execute -- ");
        }

        strcat(ret, "\n");
    }

    if (!(mode & (S_IRGRP | S_IWGRP | S_IXGRP))) {
        strcat(ret, "Group has no perimissions\n");
    } else {
        strcat(ret, "Group Permissions: ");

        if (mode & S_IRGRP) {
            strcat(ret, "Read -- ");
        }

        if (mode & S_IWGRP) {
            strcat(ret, "Write -- ");
        }

        if (mode & S_IXGRP) {
            strcat(ret, "Execute -- ");
        }

        strcat(ret, "\n");
    }

    if (!(mode & (S_IROTH | S_IWOTH | S_IXOTH))) {
        strcat(ret, "Others have no perimissions\n");
    } else {
        strcat(ret, "Others Permissions: ");

        if (mode & S_IROTH) {
            strcat(ret, "Read -- ");
        }

        if (mode & S_IWOTH) {
            strcat(ret, "Write -- ");
        }

        if (mode & S_IXOTH) {
            strcat(ret, "Execute -- ");
        }

        strcat(ret, "\n");
    }
}