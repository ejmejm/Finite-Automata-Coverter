Name: Edan Meyer

Collaborators: None

How to Build: Run the make file with the command "make all"
(Optional) To clean the project you can run "make clean"
(Optional) Another way to build is with the following command:
"gcc -o 173proj IntSet.c LinkedList.c nfa.c dfa.c conversion.c Driver.c"

How to Run: Use the command, "./173proj"

Testing: All the NFAs and DFAs that are required to be created
for the project are hardcoded. If you look in the "Driver.c" file,
there are comments showing where each individual NFA and DFA is
created. You will also find 2 comments reading, "!!!FOR GRADER!!!"
If you change the strings in the arrays found where these comments
are, you can use different inputs for each NFA and DFA. So for
example, changing the string "dfa_test_string[0]" will change the
input for DFA part a.

Output: The output for a DFA or NFA will be "True" if it matches
its test string and "False" if it doesn't match. The NFA to DFA
conversion for NFA part b could take a couple seconds, so please
wait for it to finish (It really shouldn't be more than several 
seconds though).

Thank you!
