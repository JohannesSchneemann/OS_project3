OS_project3

CS OS 4328.003 - Project 3
Johannes Schneemann

Description:   

Simulate the concurrent execution of two threads using a single program:
Thread A: prints five subsequent lines of letter A on the printer and
keeps looping (about 10 times).
Thread B: prints five subsequent lines of letter B on the printer and
keeps looping (about 10 times).

Implement (a) and (b) using two programs, respectively:

(a) Do not use any algorithm for mutual exclusion and show the printout,
which should be similar to this:

                             1: AAAAAAAAA
                             1: AAAAAAAAA

                             1: BBBBBBBBB
                             1: BBBBBBBBB
                             1: BBBBBBBBB

                             1: AAAAAAAAA
                             1: AAAAAAAAA
                             1: AAAAAAAAA

                             1: BBBBBBBBB
                             1: BBBBBBBBB

                             2: AAAAAAAAA
                             2: AAAAAAAAA

                             .....................


(b) Write the program again considering the mutual exclusion. Run the
program several times to show that mutual exclusion is guaranteed.

To make longer execution of threads, use some sleep(n) functions in
the program. Experiment with n to choose the best one to show the
results.


                            1: AAAAAAAAA
                            1: AAAAAAAAA
                            1: AAAAAAAAA
                            1: AAAAAAAAA
                            1: AAAAAAAAA

                            1: BBBBBBBBB
                            1: BBBBBBBBB
                            1: BBBBBBBBB
                            1: BBBBBBBBB
                            1: BBBBBBBBB

                            2: AAAAAAAAA
                            .....................
