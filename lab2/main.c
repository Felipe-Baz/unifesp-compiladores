#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Por favor, forneça exatamente 1 parametro, sendo ele nomeDoArquivo.txt.\n");
    return 1;
  }

  char *nomeArquivo = argv[1];

  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    printf("Não foi possível abrir o arquivo: %s.\n", nomeArquivo);
    return 1;
  }
  
  analyze_file(arquivo);
  
  fclose(arquivo);
  return 0;
}