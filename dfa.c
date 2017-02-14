#include "dfa.h"

//Allocates memory for the DFA
DFA *DFA_new(int nstates) {
	DFA *DFA_new = (DFA*)malloc(sizeof(DFA));
	DFA_new->nstates = nstates;
	DFA_new->states = (DFA_State*)malloc(nstates * sizeof(DFA_State));
	DFA_new->current_state = DFA_START_STATE; //Starts at state 0

	for (int i = 0; i < nstates; i++) { //Set all nodes to not accept by default
		DFA_new->states[i].is_accepting = FALSE;
		for (int j = 0; j < DFA_NSYMBOLS; j++) //Set all states to have no transitions by default
			DFA_new->states[i].transitions[j] = DFA_NO_TRANSITION;
	}

	return DFA_new;
}

//Frees all memory used by the DFA and its states
void DFA_free(DFA *dfa) {
	free(dfa->states);
	free(dfa);
}

//Return number of nodes in the DFA
inline int DFA_get_size(DFA *dfa) {
	return dfa->nstates;
}

inline int DFA_get_transition(DFA *dfa, int statenum, char symbol) {
	return dfa->states[statenum].transitions[symbol];
}
inline void DFA_set_transition(DFA *dfa, int src, char symbol, int dst) {
	dfa->states[src].transitions[symbol] = dst;
}
void DFA_set_transition_str(DFA *dfa, int src, char *str, int dst) { //Transition on any characters in the string, not the string itself
	for (int i = 0; i < strlen(str); i++){
		DFA_set_transition(dfa, src, str[i], dst);
	}
}
void DFA_set_transition_all(DFA *dfa, int src, int dst) {
	for (int i = 0; i < DFA_NSYMBOLS; i++) {
		DFA_set_transition(dfa, src, i, dst);
	}
}
void DFA_set_transition_remaining(DFA *dfa, int src, int dst) { //Only change if the transition is currently set to -1
	for (int i = 0; i < DFA_NSYMBOLS; i++) {
		if(DFA_get_transition(dfa, src, i) == DFA_NO_TRANSITION)
			DFA_set_transition(dfa, src, i, dst);
	}
}

inline int DFA_get_current_state(DFA *dfa) {
	return dfa->current_state;
}
inline void DFA_set_current_state(DFA *dfa, int statenum) {
	dfa->current_state = statenum;
}
inline int DFA_get_accepting(DFA *dfa, int statenum) {
	return dfa->states[statenum].is_accepting;
}
inline void DFA_set_accepting(DFA *dfa, int statenum, int value) {
	dfa->states[statenum].is_accepting = value;
}
inline int DFA_is_accepting(DFA *dfa) { //Checks if the current state is accepting
	return dfa->states[dfa->current_state].is_accepting;
}

int DFA_execute(DFA *dfa, char *input) {
	DFA_set_current_state(dfa, DFA_START_STATE);
	for (int i = 0; i < strlen(input); i++) {
		DFA_set_current_state(dfa, DFA_get_transition(dfa, dfa->current_state, input[i]));
		if (DFA_get_current_state(dfa) == -1) 
			return FALSE;
	}
	if (dfa->states[dfa->current_state].is_accepting)
		return TRUE;
	return FALSE;
}

int DFA_execute_from_one(DFA *dfa, char *input) { //Use this for NFAs converted to DFAs because they start at state 1, not 0
	DFA_set_current_state(dfa, 1);
	for (int i = 0; i < strlen(input); i++) {
		DFA_set_current_state(dfa, DFA_get_transition(dfa, dfa->current_state, input[i]));
		if (DFA_get_current_state(dfa) == -1)
			return FALSE;
	}
	if (dfa->states[dfa->current_state].is_accepting)
		return TRUE;
	return FALSE;
}

void DFA_print(DFA *dfa) { //Adjacency matrix style printing
	for (int i = 0; i < dfa->nstates; i++) {
		char *accepting = "";
		if (dfa->states[i].is_accepting)
			accepting = " (Accepting)";
		char *start_state = "";
		if (i == DFA_START_STATE)
			start_state = " (Start State)";
		printf("\nState %d%s%s Transitions:", i, start_state, accepting);
		for (int j = 0; j < DFA_NSYMBOLS; j++) {
			if (dfa->states[i].transitions[j] != -1)
				printf(" %c->%i", j, dfa->states[i].transitions[j]);
		}
	}
}
