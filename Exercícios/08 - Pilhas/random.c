// The following functions takes a stack of characters as an argument and
// removes from it all trailing 'A's before inserting a 'B' into it.

void Sledgewick(Stack *s) {
    while (!isEmpty(s) && peek(s) == 'A')
        pull(s);
    push(s, 'B');
}
