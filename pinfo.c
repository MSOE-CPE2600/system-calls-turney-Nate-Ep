/**
* @file pinfo.c
* @author Nathan Eppler <epplern@msoe.edu>
* @date 30 October 2025
* @brief Displays process information for a specified PID.
*
* Course: CPE 2600
* Section: 111
* Due: 3 November 2025
*
* To Compile: make pinfo
* To Run: ./pinfo <pid if applicable>
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/resource.h>

char* get_policy(int policy);

int main(int argc, char* argv[])
{
    char *pid_str = argv[1];
    char *end;
    pid_t pid;
    int priority;

    if (argc == 2) {
        pid_str = argv[1];
        pid = strtol(pid_str, &end, 10);
    } else {
        pid = getpid(); //current process
    }

    errno = 0;
    //check if pid is valid
    priority = getpriority(PRIO_PROCESS, pid);
    //errno is less than or equal to zero, valid priority value
    if (errno <= 0 && pid > 0) {
        printf("For Pid: %d\n", pid);
        printf("Process priority: %d\n", priority);

        int policy = sched_getscheduler(pid);
        char *policy_str = get_policy(policy);

        printf("Scheduling method: %s\n", policy_str);

    } else {
        printf("Error pid not found\n");
        
        if (pid < 0) {
            printf("Pid is negative\n");
        }
    }

    return 0;
}

char* get_policy(int policy) {
    switch (policy) {
        case SCHED_FIFO:
            return "FIFO\n";
            break;
        case SCHED_RR:
            return "Round Robbin\n";
            break;
        case SCHED_DEADLINE:
            return "Sporadic task model deadline\n";
            break;
        case SCHED_OTHER:
            return "Default Linux time-sharing scheduling";
            break;
        case SCHED_BATCH:
            return "Scheduling batch processes";
            break;
        case SCHED_IDLE:
            return "Scheduling very low priority jobs";
            break;
        default:
            return "Error";
            break;
    }
}