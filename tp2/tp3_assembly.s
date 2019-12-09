.global enter_coroutine
enter_coroutine:
    mov %rdi, %rsp  /* RDI contains the argument to enter_coroutine, and it's moved to sp */
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %rbp
    pop %rbx
    ret

