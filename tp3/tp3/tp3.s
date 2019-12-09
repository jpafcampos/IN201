.global enter_coroutine
enter_coroutine:

    mov %rdi, %rsp  /* RDI contains the argument to enter_coroutine */
                    /* And is copied to RSP */
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %rbx
    pop %rbp
    ret     /* Pop the program counter */
    


.global switch_coroutine
switch_coroutine:
    push %rbp
    push %rbx
    push %r12
    push %r13
    push %r14
    push %r15
    mov %rsp, (%rdi)        /*Store the stack pointer to *(first argument) */
    mov %rsi, %rdi
    jmp enter_coroutine     /* Call enter_coroutine with the second argument */
