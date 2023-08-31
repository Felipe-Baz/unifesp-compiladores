#ifndef FUNCS_H
#define FUNCS_H

#define BUFFER_SIZE 256

typedef struct BUFFER {
  char buffer_value[BUFFER_SIZE];
  int last_char_pos;
  int line;
} buffer_type;

buffer_type *allocate_buffer();
void deallocate_buffer(buffer_type *buffer);
void analyze_file(FILE *arquivo);

#endif