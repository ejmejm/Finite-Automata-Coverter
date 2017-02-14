#include "conversion.h"

DFA *NFA_to_DFA(NFA *nfa) {
	DFA *convert = DFA_new(1 << NFA_get_size(nfa));
	int *visited = (int*)calloc(1 << nfa->nstates, sizeof(int));
	LinkedList *pre_nodes = LinkedList_new(); //Nodes that have yet to be checked
	LinkedList_add_at_end(pre_nodes, 1); //Starting state in this DFA is 1
	visited[1] = true; //Whether or not a state has been queued to be visited or already visited

	while (!LinkedList_is_empty(pre_nodes)) {
		int current_state = LinkedList_pop(pre_nodes); //In terms of new DFA

		IntSet *component_states = IntSet_new(); //Getting the sub-states that make up one DFA state
		int tmp_state = current_state;
		for (int i = 0; i < nfa->nstates; i++) {
			if (tmp_state % 2 != 0) {
				IntSet_add(component_states, i);
				if (nfa->states[i].is_accepting)
					DFA_set_accepting(convert, current_state, 1);
			}
			tmp_state = tmp_state >> 1;
		}

		for (int i = 0; i < NFA_NSYMBOLS; i++){
			int state_num = 0;


			IntSetIterator *comp_state_it = IntSet_iterator(component_states);
			while (IntSetIterator_has_next(comp_state_it)) {
				LinkedListIterator *trans_states = LinkedList_iterator(nfa->states[IntSetIterator_next(comp_state_it)].transitions[i]);
				while (LinkedListIterator_has_next(trans_states))
					state_num = state_num | 1 << (int)LinkedListIterator_next(trans_states); //Determines which state to transition to
				free(trans_states);
			}
			
			if (state_num != 0) {
				if (visited[state_num] == FALSE) {
					LinkedList_add_at_end(pre_nodes, state_num);
					visited[state_num] = TRUE;
					DFA_set_transition(convert, current_state, i, state_num);
				}
				else {
					DFA_set_transition(convert, current_state, i, state_num);
				}
			}

			free(comp_state_it);
		}

		IntSet_free(component_states);
	}

	LinkedList_free(pre_nodes, true);

	return convert;
}
