#ifndef __PTHREAD_MACRO__H
#define __PTHREAD_MACRO__H

#if defined(pthread_cleanup_push)

#undef pthread_cleanup_push
#undef pthread_cleanup_pop

#define pthread_cleanup_push(routine, arg)                                       \
    do {                                                                         \
        __pthread_unwind_buf_t __cancel_buf;                                     \
        void (*__cancel_routine)(void*) = (routine);                             \
        void* __cancel_arg = (arg);                                              \
        int __not_first_call = __sigsetjmp_cancel(__cancel_buf.__cancel_jmp_buf, \
            0);                                                                  \
        if (__glibc_unlikely(__not_first_call)) {                                \
            __cancel_routine(__cancel_arg);                                      \
            __pthread_unwind_next(&__cancel_buf);                                \
            /* NOTREACHED */                                                     \
        }                                                                        \
        __pthread_register_cancel(&__cancel_buf);                                \
    } while (0)
extern void __pthread_register_cancel(__pthread_unwind_buf_t* __buf)
    __cleanup_fct_attribute;

/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
   If EXECUTE is non-zero, the handler function is called. */
#define pthread_cleanup_pop(execute)                \
    do {                                            \
        __pthread_unregister_cancel(&__cancel_buf); \
        if (execute) {                              \
            __cancel_routine(__cancel_arg);         \
        }                                           \
    } while (0)
extern void __pthread_unregister_cancel(__pthread_unwind_buf_t* __buf)
    __cleanup_fct_attribute;

#endif

#endif /* __PTHREAD_MACRO__H */