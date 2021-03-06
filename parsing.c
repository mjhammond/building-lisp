#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/readline.h>

int main(int argc, char** argv) {

  /* Print Version and Exit Information */
  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  /* In a never ending loop */
  while (1) {
      char* input = readline("lispy> ");

      add_history(input);

      printf("No you're a %s\n", input);

      free(input);
    }

  return 0;
}
