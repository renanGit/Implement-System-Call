struct pinfo {
 int pid;                   /* process id */
 long state;                /* current state of process */
 long nice;                 /* process nice value */
 int parent_pid;            /* process id of parent */
 int children;              /* total number of children */
 int youngest_child_pid;    /* pid of youngest child */
 int younger_sibling_pid;   /* pid of younger sibling */
 int older_sibling_pid;     /* pid of older sibling */
 unsigned long start_time;  /* process start time */
 long user_time;            /* CPU time spent in user mode */
 long sys_time;             /* CPU time spent in system mode */
 long uid;                  /* user id of process owner */
 char comm[16];             /* name of program executed */
};

