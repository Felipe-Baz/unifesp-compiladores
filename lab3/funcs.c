#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funcs.h"

/**
 *  Buffer functions
**/

buffer_type *allocate_buffer() {
  buffer_type *new_buffer = (buffer_type *)malloc(sizeof(buffer_type));
  if (new_buffer == NULL) {
      fprintf(stderr, "Erro: Falha na alocação de memória para o buffer.\n");
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

void back_char_in_buffer(buffer_type *buffer) {
  if (buffer->last_char_pos != 0)
  {
    buffer->last_char_pos--;
  }
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

/**
 * tokens functions
**/

token_type *allocate_token() {
  token_type *new_token = (token_type *)malloc(sizeof(token_type));
  if (new_token == NULL) {
      fprintf(stderr, "Erro: Falha na alocação de memória para a tabela de tokens.\n");
      exit(EXIT_FAILURE);
  }

  new_token->prox = NULL;

  return new_token;
}

void deallocate_token(token_type *token) {
  token_type *atual = token;
  do {
    token_type *prox = atual->prox;
    free(atual);
    atual = prox;
  } while (atual != NULL);
}

int is_empty(char str[TOKEN_NAME_SIZE]) {
  for (int i = 0; i < TOKEN_NAME_SIZE; i++) {
    if (str[i] != '\0') {
      return 0; // Encontrou um caractere não nulo, a string não está vazia
    }
  }
  return 1; // Todos os caracteres são nulos, a string está vazia
}

void insere_no_fim(token_type *token, char identificador[TOKEN_NAME_SIZE]) {
  
  if (is_empty(token->token_name)) {
    strncpy(token->token_name, identificador, TOKEN_NAME_SIZE);
    token->prox = NULL;
    return;
  }
  
  token_type *novo_token = (token_type *)malloc(sizeof(token_type));
  if (novo_token == NULL) {
    fprintf(stderr, "Erro: Falha na alocação de memória.\n");
    exit(1);
  }

  strncpy(novo_token->token_name, identificador, TOKEN_NAME_SIZE);
  novo_token->prox = NULL;

  if (token == NULL) {
    // Se a lista estiver vazia, o novo token será o primeiro
    token = novo_token;
  } else {
    // Caso contrário, percorre a lista até o final e adiciona o novo token lá
    token_type *atual = token;
    while (atual->prox != NULL) {
      atual = atual->prox;
    }
    atual->prox = novo_token;
  }
}

void print_token_list(token_type *token)
{
  token_type *atual = token;
  printf("************ Token List start ************\n");
  do {
    token_type *prox = atual->prox;
    printf("%s\n", atual->token_name);
    atual = prox;
  } while (atual != NULL);
  printf("************ Token List end ************\n");
}

int is_letter(char c) {
    // Verifica se o caractere está no intervalo de 'a' a 'z' ou 'A' a 'Z'
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_number(char c) {
    // Verifica se o caractere está no intervalo de '0' a '9'
    return c >= '0' && c <= '9';
}

/**
 * Analyze functions
**/

void analyze_file(FILE *arquivo) {
  buffer_type *buffer = allocate_buffer();
  token_type *token = allocate_token();
  get_next_buffer_block(arquivo, buffer);
  char c;
  int aux=0;
  char identificador[TOKEN_NAME_SIZE];
  int dfa_state = 0;
  do {
    c = get_next_char(arquivo, buffer);
    switch(dfa_state) {
      case 0:
        if (is_letter(c)) {
          identificador[aux] = c;
          dfa_state = 1;
          aux++;
        } else {
          dfa_state = 0;
          // back_char_in_buffer(buffer);
        }
        break;
      case 1:
        if (is_letter(c) || is_number(c)) {
          identificador[aux] = c;
          dfa_state = 1;
          aux++;
        } else {
          identificador[aux] = '\0';
          insere_no_fim(token, identificador);
          memset(identificador, 0, TOKEN_NAME_SIZE);
          aux=0;
          dfa_state = 0;
          // back_char_in_buffer(buffer);
        }
        break;
      default:
        break;
    }
  } while (c != EOF);

  print_token_list(token); // Imprime a lista de tokens
  
  deallocate_buffer(buffer); // Desaloca a memoria do buffer
  deallocate_token(token);  // Desaloca a memoria da tabela de tokens
}
