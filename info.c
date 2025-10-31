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
#include <math.h>

int main(int argc, char* argv[])
{
    struct timespec time;
    struct tm *local_time;
    struct utsname sys_info;
    time_t time_seconds;
    int num_procs;
    int page_size;
    long avail_mem;
    long total_mem;

    clock_gettime(CLOCK_REALTIME, &time);
    local_time = localtime(&time.tv_sec);
    time_seconds = local_time->tm_hour*3600 + local_time->tm_min * 60 + local_time->tm_sec;

    uname(&sys_info);
    num_procs = get_nprocs();
    page_size = getpagesize();
    avail_mem = sysconf(_SC_AVPHYS_PAGES) * page_size;
    total_mem = sysconf(_SC_PHYS_PAGES) * page_size;
    
    printf("The current time is: %lu ns\n", (long unsigned)(time_seconds*pow(10,9) + time.tv_nsec));
    printf("System Network Name: %s\n", sys_info.nodename);
    printf("Opperating System Name: %s\n", sys_info.sysname);
    printf("OS Version: %s\n", sys_info.version);
    printf("OS Release: %s\n", sys_info.release);
    printf("Number of processors: %d\n", num_procs);
    printf("Total memory: %ld Bytes\n", total_mem);
    printf("Availible memory: %ld Bytes\n", avail_mem);

    return 0;
}