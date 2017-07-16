#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/readline.h>

#include "mpc.h"

int main(int argc, char** argv) {

  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
      "\
        number : /-?[0-9]+/ ; \
        operator : '+' | '-' | '*' | '/' ; \
        expr : <number> | '(' <operator> <expr>+ ')' ; \
        lispy : /^/ <operator> <expr>+ /$/ ; \
      ",
      Number, Operator, Expr, Lispy);

  /* Print Version and Exit Information */
  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  /* In a never ending loop */
  while (1) {
      char* input = readline("lispy> ");

      add_history(input);

      mpc_result_t r;
      if (mpc_parse("<stdin>", input, Lispy, &r)) {
        mpc_ast_print(r.output);
        mpc_ast_delete(r.output);

        mpc_ast_t* a = r.output;
        printf("Tag: %s\n", a->tag);
        printf("Contents: %s\n", a->contents);
        printf("Number of children: %i\n", a->children_num);

        mpc_ast_t* c0 = a->children[0];
        printf("First child tag: %s\n", c0->tag);
        printf("First child contents: %s\n", c0->contents);
        printf("First child number of children: %i\n", c0->children_num);
      } else {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
      }

      free(input);
    }

  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
}
