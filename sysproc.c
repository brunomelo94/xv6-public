#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_trace(void)
{
  // Get the current process
  struct proc *curproc = myproc();

  // Get the new trace mask
  int new_mask;

  // Get the new trace mask from the stack
  if (argint(0, &new_mask) < 0)
  {
    return -1;
  }

  // If the new trace mask is 0 then reset the syscall count
  if (new_mask == 0)
  {
    curproc->syscallcount = 0;
  }

  // Set the new trace mask
  curproc->syscalltrace = new_mask;

  // Return sys calls count curproc->syscallcount
  return curproc->syscallcount;
}

int sys_cs(void)
{
  struct proc *curproc = myproc();

  return curproc->contextSwitchCount;
}

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}