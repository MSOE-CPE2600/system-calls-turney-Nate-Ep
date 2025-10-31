/**
* @file info.c
* @author Nathan Eppler <epplern@msoe.edu>
* @date 30 October 2025
* @brief
*
* Course: CPE 2600
* Section: 111
* Due: 3 November 2025
*
* To Compile: make info
* To Run: ./info
*/

#include <time.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    struct timespec time;
    struct utsname sys_info;
    int num_procs;
    int page_size;
    long avail_mem;
    long total_mem;

    clock_gettime(CLOCK_REALTIME, &time);
    uname(&sys_info);
    num_procs = get_nprocs();
    page_size = getpagesize();
    avail_mem = sysconf(_SC_AVPHYS_PAGES) * page_size;
    total_mem = sysconf(_SC_PHYS_PAGES) * page_size;
    
    printf("The current time is: %ld\n", time.tv_nsec);
    printf("System Network Name: %s\n", sys_info.nodename);
    printf("Opperating System Name: %s\n", sys_info.sysname);
    printf("OS Version: %s\n", sys_info.version);
    printf("OS Release: %s\n", sys_info.release);
    printf("Number of processors: %d\n", num_procs);
    printf("Total memory: %ld Bytes\n", total_mem);
    printf("Availible memory: %ld Bytes\n", avail_mem);

    return 0;
}