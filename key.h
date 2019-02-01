#ifndef KEY_H
#define KEY_H

#define C 8          // Número de caracteres na senha.
#define B 5          // Número de bits por caractere.
#define R (1 << B)   // Tamanho do alfabeto (sempre = 32).
#define N (B * C)    // Número de bits por senha.

#define ALPHABET "abcdefghijklmnopqrstuvwxyz012345"

// Um inteiro módulo R formado por C dígitos. O array está contido
// dentro de uma estrutura para facilitar a gerência de memória e
// a passagem de parâmetros nas funções.
typedef struct {
    unsigned char digit[C];
} Key;

// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[]);

// Exibe a chave 'k' em stdout em três formatos: chars, ints (base R) e binário.
void print_key(Key k);

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(Key k);

// Retorna o i-ésimo bit de k.
int bit(Key k, int i);

// Retorna a + b (mod 2^N) .
Key add(Key a, Key b);

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(Key k, Key T[N]);

// Retorna a - b (mod 2^N).
Key sub(Key a, Key b);

// Retorna 1(true) caso sejam iguais e 0(false) caso contrário.
int equals(Key a, Key b);

// Retorna 1 caso a > b, retorna -1 caso a < b e retorna 0 caso sejam iguais.
int compare(Key a, Key b);

// Retorna um inteiro usado como índice para a hash table.
int hash_key(Key a);

#endif
