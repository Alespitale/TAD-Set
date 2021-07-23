# TAD-Set

## TAD Conjunto Finito:

- Compilación:

gcc -Wall -Werror -Wextra -pedantic -std=c99 -c test_set.c

gcc -Wall -Werror -Wextra -pedantic -std=c99 -c set.c

gcc -Wall -Werror -Wextra -pedantic -std=c99 -g -o test_s list-x86_64.o set.o test_set.o -no-pie
