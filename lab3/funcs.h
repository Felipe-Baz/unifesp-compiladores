#ifndef FUNCS_H
#define FUNCS_H

#define BUFFER_SIZE 256
#define TOKEN_NAME_SIZE 100

typedef struct BUFFER {
  char buffer_value[BUFFER_SIZE];
  int last_char_pos;
  int line;
} buffer_type;

typedef struct TOKEN {
  char token_name[TOKEN_NAME_SIZE];
  struct TOKEN *prox;
} token_type;

buffer_type *allocate_buffer();
void deallocate_buffer(buffer_type *buffer);
void back_char_in_buffer(buffer_type *buffer);
char get_next_char(FILE *arquivo, buffer_type *buffer);
void analyze_file(FILE *arquivo);

#endif