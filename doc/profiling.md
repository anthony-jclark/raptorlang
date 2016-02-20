
## Profiling

bin/raptorlang -v 10 --vmodule main=3
ish: 'bin/raptorlang -v 10 --vmodule…' terminated by signal SIGBUS (Misaligned address error)

SET (CMAKE_BUILD_TYPE debug)


==57114== Memcheck, a memory error detector
==57114== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==57114== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==57114== Command: bin/raptorlang
==57114==
==57114== Invalid write of size 1
==57114==    at 0x100006CC7: main (main.cpp:167)
==57114==  Address 0x10098e85f is 0 bytes after a block of size 15 alloc'd
==57114==    at 0x100174EBB: malloc (in /usr/local/Cellar/valgrind/3.11.0/lib/valgrind/vgpreload_memcheck-amd64-darwin.so)
==57114==    by 0x1001B943D: operator new(unsigned long) (in /usr/lib/libc++.1.dylib)
==57114==    by 0x100006006: main (memory:3084)
==57114==
--57114-- UNKNOWN mach_msg unhandled MACH_SEND_TRAILER option
--57114-- UNKNOWN mach_msg unhandled MACH_SEND_TRAILER option (repeated 2 times)
--57114-- UNKNOWN mach_msg unhandled MACH_SEND_TRAILER option (repeated 4 times)
2015-11-09 20:22:03,302 VER-0 [default] Level : 0
2015-11-09 20:22:03,513 VER-0 [default] Logging parameters:
2015-11-09 20:22:03,519 VER-0 [default]     bin/raptorlang
==57114==
==57114== HEAP SUMMARY:
==57114==     in use at exit: 54,824 bytes in 452 blocks
==57114==   total heap usage: 1,495 allocs, 1,043 frees, 137,451 bytes allocated
==57114==
==57114== LEAK SUMMARY:
==57114==    definitely lost: 0 bytes in 0 blocks
==57114==    indirectly lost: 0 bytes in 0 blocks
==57114==      possibly lost: 0 bytes in 0 blocks
==57114==    still reachable: 19,914 bytes in 23 blocks
==57114==         suppressed: 34,910 bytes in 429 blocks
==57114== Reachable blocks (those to which a pointer was found) are not shown.
==57114== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==57114==
==57114== For counts of detected and suppressed errors, rerun with: -v
==57114== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 21 from 21)


            ELPP_argv_managed.push_back(make_unique<char[]>(arg_string.length()+1));
            std::copy(arg_string.begin(), arg_string.end(), ELPP_argv_managed.back().get());
            ELPP_argv_managed.back().get()[arg_string.length()+1] = '\0';
