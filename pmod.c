/**
* @file pmod.c
* @author Nathan Eppler <epplern@msoe.edu>
* @date 30 October 2025
* @brief Modifies the program's priority to be less important.
*
* Course: CPE 2600
* Section: 111
* Due: 3 November 2025
*
* To Compile: make pmod
* To Run: ./pmod
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>

int main(int argc, char* argv[])
{
    struct timespec time;
    pid_t pid = getpid();
    int priority;

    errno = 0;
    //check if pid is valid
    priority = getpriority(PRIO_PROCESS, pid);
    //errno is less than or equal to zero, valid priority value

    if (errno <= 0) {
        printf("Pid: %d\n", pid);
        priority += 10;

        if (priority > 19) {
            priority = 19; //set priority to highest val
        }
        //set the current process to current priority += 10
        int status = setpriority(PRIO_PROCESS, pid, priority);

        if (status == 0) {
            printf("Sucsessfully adjusted priority!\n");
        } else {
            printf("Failed to adjust program priority.\n");
            perror("Error: ");
        }
        time.tv_sec = 1;
        time.tv_nsec = 837272638;
        nanosleep(&time, NULL);
        printf("Goodbye!\n");

    } else {
        printf("Error obtaining program priority\n");
    }

    return 0;
}

