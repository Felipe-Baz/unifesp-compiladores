#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "funcs.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Por favor, forneça exatamente 2 parametros, sendo eles nomeDoArquivo.txt tamanhoDoBuffer.\n");
    return 1;
  }

  char *nomeArquivo = argv[1];
  int tamanhoBuffer;

  // Le o argv[2], caso sejam valores inteiros(%d) salva no &tamanhoBuffer
  if (sscanf(argv[2], "%d", &tamanhoBuffer) != 1) {
    printf("O segundo parametro(Tamanho do buffer) deve ser um número inteiro.\n");
    return 1;
  }

  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    printf("Não foi possível abrir o arquivo: %s.\n", nomeArquivo);
    return 1;
  }

  replace_print(NULL, tamanhoBuffer, arquivo);  // Chama a função para imprimir o conteúdo do arquivo

  fclose(arquivo);

  return 0;
}
