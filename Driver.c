/*
 * File: LinkedListTest.c
 * Creator: George Ferguson
 * Created: Wed Sep  7 17:59:30 2016
 * Time-stamp: <Wed Sep  7 18:01:41 EDT 2016 ferguson>
 *
 * Test program for LinkedList library.
 */

#include <stdio.h>
#include <stdlib.h>
#include "conversion.h"

int main(int argc, char **argv) {

	DFA *dfa[5];

	//DFA to detect "ab"
	 dfa[0] = DFA_new(3);

	DFA_set_accepting(dfa[0], 2, TRUE);
	DFA_set_transition(dfa[0], 0, 'a', 1);
	DFA_set_transition(dfa[0], 1, 'b', 2);

	//DFA to detect strings starting with "ab"
	dfa[1] = DFA_new(3);

	DFA_set_accepting(dfa[1], 2, TRUE);
	DFA_set_transition(dfa[1], 0, 'a', 1);
	DFA_set_transition(dfa[1], 1, 'b', 2);
	DFA_set_transition_all(dfa[1], 2, 2);

	//DFA to detect binary strings with an even number of 1s
	dfa[2] = DFA_new(2);

	DFA_set_accepting(dfa[2], 0, TRUE);
	DFA_set_transition(dfa[2], 0, '1', 1);
	DFA_set_transition(dfa[2], 1, '1', 0);
	DFA_set_transition(dfa[2], 0, '0', 0);
	DFA_set_transition(dfa[2], 1, '0', 1);

	//DFA to detect binary strings with an even number of 1s and 0s
	dfa[3] = DFA_new(4);

	DFA_set_accepting(dfa[3], 0, TRUE);
	DFA_set_transition(dfa[3], 0, '1', 1);
	DFA_set_transition(dfa[3], 0, '0', 2);
	DFA_set_transition(dfa[3], 1, '1', 0);
	DFA_set_transition(dfa[3], 1, '0', 3);
	DFA_set_transition(dfa[3], 2, '1', 3);
	DFA_set_transition(dfa[3], 2, '0', 0);
	DFA_set_transition(dfa[3], 3, '1', 2);
	DFA_set_transition(dfa[3], 3, '0', 1);

	//DFA to detect strings that are a repition of "abc"
	dfa[4] = DFA_new(3);

	DFA_set_accepting(dfa[4], 0, TRUE);
	DFA_set_transition(dfa[4], 0, 'a', 1);
	DFA_set_transition(dfa[4], 1, 'b', 2);
	DFA_set_transition(dfa[4], 2, 'c', 0);

	char *dfa_test_string[5]; //!!!FOR GRADER!!! These strings test the 5 DFAs
							//Change them to test different inputs
	dfa_test_string[0] = "ab";
	dfa_test_string[1] = "abhaos/s98";
	dfa_test_string[2] = "100100100111";
	dfa_test_string[3] = "1010011011";
	dfa_test_string[4] = "abcabcabcabc";

	printf("DFA Testing:\n");
	for (int i = 0; i < 5; i++) {
		char *result;
		if (DFA_execute(dfa[i], dfa_test_string[i]) == TRUE)
			result = "True";
		else
			result = "False";
		printf("DFA Part %c Result: %s\n", i+'a', result);
		DFA_free(dfa[i]);
	}

	//////////////Part 2 NFAs

	NFA *nfa[3];

	//NFA to detect strings enging with "man"dfa[3] = DFA_new(4);
	nfa[0] = NFA_new(4);

	NFA_set_accepting(nfa[0], 3, TRUE);
	NFA_add_transition_all(nfa[0], 0, 0);
	NFA_add_transition(nfa[0], 0, 'm', 1);
	NFA_add_transition(nfa[0], 1, 'a', 2);
	NFA_add_transition(nfa[0], 2, 'n', 3);

	//NFA to detect Strings with more than one a, g, h, i, o, s, t, or w, or more than two n's
	nfa[1] = NFA_new(20);

	NFA_set_accepting(nfa[1], 2, TRUE);
	NFA_set_accepting(nfa[1], 4, TRUE);
	NFA_set_accepting(nfa[1], 6, TRUE);
	NFA_set_accepting(nfa[1], 8, TRUE);
	NFA_set_accepting(nfa[1], 10, TRUE);
	NFA_set_accepting(nfa[1], 12, TRUE);
	NFA_set_accepting(nfa[1], 14, TRUE);
	NFA_set_accepting(nfa[1], 16, TRUE);
	NFA_set_accepting(nfa[1], 19, TRUE);
	for(int i = 0; i < 20; i++)
		NFA_add_transition_all(nfa[1], i, i);
	NFA_add_transition(nfa[1], 0, 'a', 1);
	NFA_add_transition(nfa[1], 1, 'a', 2);
	NFA_add_transition(nfa[1], 0, 'g', 3);
	NFA_add_transition(nfa[1], 3, 'g', 4);
	NFA_add_transition(nfa[1], 0, 'h', 5);
	NFA_add_transition(nfa[1], 5, 'h', 6);
	NFA_add_transition(nfa[1], 0, 'i', 7);
	NFA_add_transition(nfa[1], 7, 'i', 8);
	NFA_add_transition(nfa[1], 0, 'o', 9);
	NFA_add_transition(nfa[1], 9, 'o', 10);
	NFA_add_transition(nfa[1], 0, 's', 11);
	NFA_add_transition(nfa[1], 11, 's', 12);
	NFA_add_transition(nfa[1], 0, 't', 13);
	NFA_add_transition(nfa[1], 13, 't', 14);
	NFA_add_transition(nfa[1], 0, 'w', 15);
	NFA_add_transition(nfa[1], 15, 'w', 16);
	NFA_add_transition(nfa[1], 0, 'n', 17);
	NFA_add_transition(nfa[1], 17, 'n', 18);
	NFA_add_transition(nfa[1], 18, 'n', 19);

	//NFA to detect strings having three consecutive 1's in them
	nfa[2] = NFA_new(4);

	NFA_set_accepting(nfa[2], 3, TRUE);
	NFA_add_transition_all(nfa[2], 0, 0);
	NFA_add_transition(nfa[2], 0, '1', 1);
	NFA_add_transition(nfa[2], 1, '1', 2);
	NFA_add_transition(nfa[2], 2, '1', 3);
	NFA_add_transition_all(nfa[2], 3, 3);

	//Testing the NFAs
	char *nfa_test_string[5]; //!!!FOR GRADER!!! These strings test the 3 NFAs
						  //Change them to test different inputs
	nfa_test_string[0] = "woman";
	nfa_test_string[1] = "more than washington";
	nfa_test_string[2] = "1gr00111001a00141";

	printf("\nNFA Testing:\n");
	for (int i = 0; i < 3; i++) {
		char *result;
		if (NFA_execute(nfa[i], nfa_test_string[i]) == TRUE)
			result = "True";
		else
			result = "False";
		printf("NFA Part %c Result: %s\n", i + 'a', result);
	}

	printf("\nNFA to DFA Testing:\n");
	for (int i = 0; i < 3; i++) {
		DFA *test = NFA_to_DFA(nfa[i]);
		char *result;
		if (DFA_execute_from_one(test, nfa_test_string[i]) == TRUE)
			result = "True";
		else
			result = "False";
		printf("NFA to DFA Part %c Result: %s\n", i + 'a', result);
		NFA_free(nfa[i]);
		DFA_free(test);
	}

	system("pause");
}
