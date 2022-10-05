#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "elf.h"
// #include "proc.h"

int main(void)
{
    // struct proc *curproc = myproc();

    trace(1);

    sleep(1, 5);

    exit();
}