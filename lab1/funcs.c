#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>  // Incluir a biblioteca ctype.h para usar a função toupper
#include "funcs.h"

#define VOGAIS "aeiou"

char *allocate_buffer(int size) {
    char *buffer = (char *) malloc (size + 1);
    if (buffer == NULL) {
        printf("Erro na alocação de memória do buffer.\n");
        exit(1);
    }
    return buffer;
}

void deallocate_buffer(char *buffer) {
  free(buffer);
}

void replace_print(const char *content, int tamanhoBuffer, FILE *arquivo) {
  char *buffer = allocate_buffer(tamanhoBuffer);

  size_t bytesRead;
  while ((bytesRead = fread(buffer, 1, tamanhoBuffer, arquivo)) > 0) {
    buffer[bytesRead] = '\0';
    upper_vowel(buffer);  // Chama a função para alterar vogais para maiúsculas
    printf("%s", buffer);
    fflush(stdout);
    sleep(1);
  }

  deallocate_buffer(buffer); // Desaloca a memoria do buffer
}

void upper_vowel(char *buffer) {
  size_t length = strlen(buffer);
  for (size_t i = 0; i < length; i++) { // Percorre os caracteres no buffer
    if (strchr(VOGAIS, buffer[i]) != NULL) {  // Verifica se o caractere é uma vogal
      buffer[i] = toupper(buffer[i]);  // Converte para maiúscula
    }
  }
}
