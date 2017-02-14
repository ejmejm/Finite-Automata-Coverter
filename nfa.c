#include "nfa.h"

NFA *NFA_new(int nstates) {
	NFA *NFA_new = (NFA*)malloc(sizeof(NFA));
	NFA_new->nstates = nstates;
	NFA_new->states = (NFA_State*)malloc(nstates * sizeof(NFA_State));
	NFA_new->current_states = IntSet_new();
	IntSet_add(NFA_new->current_states, NFA_START_STATE); //Starts at state 0

	for (int i = 0; i < nstates; i++) { //Set all nodes to not accept by default
		NFA_new->states[i].is_accepting = false;
		for (int j = 0; j < NFA_NSYMBOLS; j++) //Set all states to have no transitions by default
			NFA_new->states[i].transitions[j] = IntSet_new();
	}

	return NFA_new;
}
void NFA_free(NFA *nfa) {
	for (int i = 0; i < nfa->nstates; i++)
		for (int j = 0; j < NFA_NSYMBOLS; j++)
		IntSet_free(nfa->states[i].transitions[j]);
	free(nfa->states);
	IntSet_free(nfa->current_states);
	free(nfa);
}

inline int NFA_get_size(NFA *nfa) {
	return nfa->nstates;
}

inline IntSet *NFA_get_transitions(NFA *nfa, int statenum, char symbol) {
	return nfa->states[statenum].transitions[symbol];
}
inline void NFA_add_transition(NFA *nfa, int src, char symbol, int dst) {
	IntSet_add(nfa->states[src].transitions[symbol], dst);
}
void NFA_add_transition_str(NFA *nfa, int src, char *str, int dst) {
	for (int i = 0; i < strlen(str); i++) 
		NFA_add_transition(nfa, src, str[i], dst);
}
void NFA_add_transition_all(NFA *nfa, int src, int dst) {
	for (int i = 0; i < NFA_NSYMBOLS; i++)
		NFA_add_transition(nfa, src, i, dst);
}
void NFA_add_transition_remaining(NFA *dfa, int src, int dst) { //Only change if the transition is currently set to -1
	for (int i = 0; i < NFA_NSYMBOLS; i++) {
		if (IntSet_is_empty(NFA_get_transitions(dfa, src, i)))
			NFA_add_transition(dfa, src, i, dst);
	}
}

inline IntSet *NFA_get_current_states(NFA *nfa) {
	return nfa->current_states;
}
void NFA_set_current_states(NFA *nfa, IntSet *states) {
	IntSet_free(nfa->current_states);
	nfa->current_states = states;
}
void NFA_set_current_state(NFA *nfa, int state) {
	IntSet_free(nfa->current_states);
	nfa->current_states = IntSet_new();
	IntSet_add(nfa->current_states, state);
}
inline void NFA_add_current_state(NFA *nfa, int state) {
	IntSet_add(nfa->current_states, state);
}
inline bool NFA_get_accepting(NFA *nfa, int statenum) {
	return nfa->states[statenum].is_accepting;
}
inline void NFA_set_accepting(NFA *nfa, int statenum, bool value) {
	nfa->states[statenum].is_accepting = value;
}
bool NFA_is_accepting(NFA *nfa) {
	IntSetIterator *it = IntSet_iterator(nfa->current_states);
	while (IntSetIterator_has_next(it)) {
		if (NFA_get_accepting(nfa, IntSetIterator_next(it)))
			return true;
	}
	return false;
}

bool NFA_execute(NFA *nfa, char *input) {
	NFA_set_current_state(nfa, NFA_START_STATE);
	for (int i = 0; i < strlen(input); i++) {
		IntSet *new_states = IntSet_new();
		IntSetIterator *it = IntSet_iterator(nfa->current_states);
		while (IntSetIterator_has_next(it))
			IntSet_union(new_states, NFA_get_transitions(nfa, IntSetIterator_next(it), input[i]));
		NFA_set_current_states(nfa, new_states);
		if (IntSet_is_empty(NFA_get_current_states(nfa)))
			return false;
	}
	if (NFA_is_accepting(nfa))
		return true;
	return false;
}

// True to enable tracing during NFA_Execute
int NFA_tracing;
