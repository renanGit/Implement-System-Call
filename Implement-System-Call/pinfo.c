/*##########################################################
## COP4610 – Principles of Operating Systems – Summer C 2014
## Prof. Jose F. Osorio
## Group: Apsalar
## Group Members: Maylem Gonzalez – 2134900
##                Renan Santana – 4031451
## Project: Customizing Linux Kernel
## Specs: Adding Static System Call
## Due Date: 06/18/2014 by 11:55pm
## Module Name: 
##
## We Certify that this program code has been written by us
## and no part of it has been taken from any sources.
##########################################################*/

#include <linux/linkage.h>
#include <linux/pinfo.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <asm/current.h>
#include <linux/sched.h>

#define NSEC 1000000000
#define time_cal(t) \
	t->start_time.tv_sec * NSEC + t->start_time.tv_nsec

// Prototype functions
int get_PID(void);
long get_state(void);
long get_nice(void);
unsigned long get_start_time(void);
int get_parent_id(void);
int get_children(void);
int get_youngest_child(void);
int get_younger_silbing(void);
int get_older_sibling(void);
long get_user_time(void);
long get_sys_time(void);
char * get_comm(void);
long get_UID(void);

// Global var used to get the task struct
struct task_struct *get_t;

// Process ID
int get_PID(void){
	return get_t->pid;
}

// Current state of process (-1 unrunnable, 0 runnable, >0 stopped)
long get_state(void){
	return get_t->state;
}

// Process nice value range from -20 <> 19 (high prio neg values & lower prio pos values)
long get_nice(void){
	return (get_t->prio - MAX_RT_PRIO - 20);
}

// Process id of parent
int get_parent_id(void){
	return get_t->parent->pid;
}

// Total number of children
int get_children(void){
	struct list_head *tmp;
	int i = 0;
	// Traverse the doubly linked list to get the number of children
	list_for_each(tmp, &get_t->children){ ++i; }
	// no children then return -1
	if(i == 0){ return -1; }
	else{ return i; }
}

// PID of the youngest child
int get_youngest_child(void){
	// get the list of childrens
	struct list_head *tmp = &get_t->children;
	int pid;
	if(&tmp == NULL){ return -1; }
	// use macro to get the task_struck embedded
	// Note: list_entry( ptr, type, member)
	pid = list_entry(tmp->prev, struct task_struct, children)->pid;
	// if list_entry ret is zero or the pid is the same as its self then return -1
	if(pid == 0 || pid == get_PID()){return -1;}
	return pid;
}

// PID of younger sibling
int get_younger_sibling(void){
	// get the list of siblings
	struct list_head *tmp = &get_t->sibling;
	int pid;
	if(&tmp == NULL){return -1;}
	// use macro to get the task_struck embedded
	// Note: list_entry( ptr, type, member) 
	pid = list_entry(tmp->next, struct task_struct, sibling)->pid;
	// if list_entry ret is zero or the pid is the same as its self then return -1
	if(pid == 0 || pid == get_PID()) {return -1;}
	return pid;
}

// PID of older sibling
int get_older_sibling(void){
	// get the list of sibling
	struct list_head *tmp = &get_t->sibling;
	int pid;
	if(&tmp == NULL){return -1;}
	// use macro to get the task_struck embedded
	// Note: list_entry( ptr, type, member) 
	pid = list_entry(tmp->prev, struct task_struct, sibling)->pid;
	// if list_entry ret is zero or the pid is the same as its self then return -1
	if(pid == 0 || pid == get_PID()) {return -1;}
	return pid;
}

// Process start time
unsigned long get_start_time(void){
	return time_cal(get_t);
}

// CPU time spent in user mode
long get_user_time(void){
	return get_t->utime;
}

// CPU time spent in system mode
long get_sys_time(void){
	return get_t->stime;
}

// User id of process owner
long get_UID(void){
	return get_t->uid;
}

// Name of program executed
char * get_comm(void){
	return get_t->comm;
}

asmlinkage long sys_pinfo(struct pinfo *process){
	// if the user didn't provide stack or heap space then return -22
	if(&process == NULL){return -22;}
	
	// Fill in the Process Information
	get_t = get_current();
	process->pid = get_PID();
	process->state = get_state();
	process->nice = get_nice();
	process->parent_pid = get_parent_id();
	process->children = get_children();
	process->youngest_child_pid = get_youngest_child();
	process->younger_sibling_pid = get_younger_sibling();
	process->older_sibling_pid = get_older_sibling();
	process->start_time = get_start_time();
	process->user_time = get_user_time();	
	process->sys_time = get_sys_time();
	process->uid = get_UID();
	strcpy(process->comm, get_comm());

	return 0;
}

