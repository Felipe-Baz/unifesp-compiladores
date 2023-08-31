#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funcs.h"

buffer_type *allocate_buffer() {
    buffer_type *new_buffer = (buffer_type *)malloc(sizeof(buffer_type));
    if (new_buffer == NULL) {
        // fprintf(stderr, "Erro: Falha na alocação de memória para o buffer.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializar os valores do buffer
    new_buffer->last_char_pos = -1;
    new_buffer->line = 1;

    return new_buffer;
}

void deallocate_buffer(buffer_type *buffer) {
  free(buffer);
}

void get_next_buffer_block(FILE *arquivo, buffer_type *buffer) {
  printf("**************** Loading block on buffer ****************\n");
  int i = 0;
  char current_char = getc(arquivo);

  // Reseta o last_char_pos
  buffer->last_char_pos = -1;
  
  
  while(i < BUFFER_SIZE) {
    if (current_char == '\n' || current_char == EOF) {
      printf("\'%c\' %d\n", current_char, i);
      buffer->buffer_value[i] = current_char;
      i++;
      break;
    }
    
    printf("\'%c\' %d\n", current_char, i);
    buffer->buffer_value[i] = current_char;
    i++;
    current_char = getc(arquivo);
  }
  printf("**************** Loading finished ****************\n");
}

char get_next_char(FILE *arquivo, buffer_type *buffer) {
  int aux = buffer->last_char_pos;
  char current_char = buffer->buffer_value[aux + 1];
  buffer->last_char_pos++;
  if (aux == BUFFER_SIZE) { // Fim do buffer
    get_next_buffer_block(arquivo, buffer);
  } else if (current_char == '\n') { // Fim da linha
    get_next_buffer_block(arquivo, buffer);
    buffer->line++;
    return get_next_char(arquivo, buffer);
  }
  
  return current_char;
}

void analyze_file(FILE *arquivo) {
  buffer_type *buffer = allocate_buffer(); // Aloca a memoria do buffer
  get_next_buffer_block(arquivo, buffer);
  
  char c = get_next_char(arquivo, buffer);
  printf("get_next_char response:\'%c\' line: %d position: %d \n", c, buffer->line, buffer->last_char_pos);
  while (c != EOF)
  {
    c = get_next_char(arquivo, buffer);
    printf("get_next_char response:\'%c\' line: %d position: %d \n", c, buffer->line, buffer->last_char_pos);
  }
  
  
  deallocate_buffer(buffer); // Desaloca a memoria do buffer
}
