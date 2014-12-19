Implement-System-Call
=====================

System call

A system call is used by application (user) programs to request service from the operating system. The
following statements illustrate why system calls are needed. An operating system can access a system's
hardware directly, but a user program is not given direct access to the hardware. This is done so that the
kernel can keep the system safe and secure from malicious user programs. But often, a user program
requires some information from the hardware (e.g., from a web camera to show you the picture), but it
cannot get the information directly. So, it requests the operating system to supply it the information. This
request is made by using an appropriate system call.

A system call executes in the kernel mode. Every system call has a number associated with it. This
number is passed to the kernel and that's how the kernel knows which system call was made. When a user
program issues a system call, it is actually calling a library routine. The library routine issues a trap to the
Linux operating system by executing INT 0x80 assembly instruction. It also passes the system call
number to the kernel using the EAX register. The arguments of the system call are also passed to the
kernel using other registers (EBX, ECX, etc.). The kernel executes the system call and returns the result
to the user program using a register. If the system call needs to supply the user program with large
amounts of data, it will use another mechanism (e.g., copy_to_user call).


How to Add Your Own System Calls

1. Create a directory under the /usr/src/linux/ directory to hold your code.
2. Put any include files in /usr/include/sys/ and /usr/include/linux/.
3. Add the relocatable module produced by the link of your new kernel code to
the ARCHIVES and the subdirectory to the SUBDIRS lines of the top level Makefile.
See fs/Makefile, target fs.o for an example.
4. Add a #define __NR_xx to unistd.h to assign a call number for your system call,
where xx, the index, is something descriptive relating to your system call. It
will be used to set up the vector through sys_call_table to invoke you code.
5. Add an entry point for your system call to the sys_call_table in sys.h. It should
match the index (xx) that you assigned in the previous step.
The NR_syscalls variable will be recalculated automatically.
6. Modify any kernel code in kernel/fs/mm/, etc. to take into account the
environment needed to support your new code.
7. Run make from the top level to produce the new kernel incorporating your new
code.