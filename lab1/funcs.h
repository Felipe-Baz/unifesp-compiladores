#ifndef FUNCS_H
#define FUNCS_H

char *allocate_buffer(int size);
void deallocate_buffer(char *buffer);
void replace_print(const char *content, int tamanhoBuffer, FILE *arquivo);
void upper_vowel(char *buffer);

#endif
