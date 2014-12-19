#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "pinfo.h"
#include <errno.h>
#include <stdlib.h>

#define __NR_pinfo 301

int main(void){

	struct pinfo p_info;
	int status = 1;	

	status = syscall(__NR_pinfo, &p_info);

	printf("CURRENT PROCESS INFORMATION\n");
	printf("-----------------------------------------------\n");
	printf("PID:\t\t\t%i\n",p_info.pid);
	printf("STATE:\t\t\t%ld\n", p_info.state);
	printf("NICE:\t\t\t%ld\n", p_info.nice);
	printf("PARENT PID:\t\t%i\n", p_info.parent_pid);
	printf("NUMBER OF CHILDREN: \t%i\n",p_info.children);
	printf("YOUNGEST CHILD (PID): \t%i\n", p_info.youngest_child_pid);
	printf("YOUNGER SIBLING (PID):\t%i\n", p_info.younger_sibling_pid);
	printf("OLDER SIBLING (PID):\t%i\n", p_info.older_sibling_pid);
	printf("START TIME (nanosecs):\t%lu\n", p_info.start_time);
	printf("USER TIME (millisecs): \t%ld\n", p_info.user_time);
	printf("SYSTEM TIME (millisecs):%ld\n", p_info.sys_time);
	printf("UID (user id):\t\t%ld\n", p_info.uid);
	printf("COMM (program name):\t%s\n", p_info.comm);

	return 0;
}

