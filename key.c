#include <stdio.h>
#include <stdlib.h>
#include "key.h"
#include "hash.h"

// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[]) {
    // Converte cada char em um int no intervalo 0-31.
    Key k;
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < R; j++) {
            if (s[i] == ALPHABET[j]) {
                k.digit[i] = j;
            }
        }
    }
    // Note que não há problema de retornar uma variável local aqui porque
    // a semântica do C para variáveis do tipo struct (não struct*) é fazer
    // uma cópia da struct inteira. Isso pode parecer ineficiente mas lembre
    // que o vetor da struct de chave é muito pequeno.
    return k;
}

// Exibe a chave 'k' em stdout em três formatos: chars, ints (base R) e binário.
void print_key(Key k) {
    for (int i = 0; i < C; i++) {
        printf("%c", ALPHABET[k.digit[i]]);
    }
    printf("  ");
    for (int i = 0; i < C; i++) {
        printf("%2d ", k.digit[i]);
    }
    printf("  ");
    for (int i = 0; i < N; i++) {
        printf("%d", bit(k, i));
    }
    printf("\n");
}

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(Key k){
    for (int i = 0; i < C; i++) {
        printf("%c", ALPHABET[k.digit[i]]);
    }
    printf("\n");
}

// Retorna o i-ésimo bit de k.
int bit(Key k, int i) {
    return (k.digit[i/B] >> (B - 1 - i % B)) & 1;
}

// Retorna a + b (mod 2^N) .
Key add(Key a, Key b) {
    Key c = {{0}};
    int carry = 0;
    for (int i = C-1; i >= 0; i--) {
        int sum = a.digit[i] + b.digit[i] + carry;
        c.digit[i] = sum  % R;
        carry      = sum >= R;
    }
    return c;
}

// Algoritmo inspirado na função de soma apresentada acima.
// Retorna a - b (mod 2^N)
Key sub(Key a, Key b) {
    Key c = {{0}};
    int carry = 0;
    for (int i = C-1; i >= 0; i--){
        int subt = a.digit[i] - b.digit[i] + carry;
        c.digit[i] = subt % R;
        if (subt < 0){
            carry = -1;
            c.digit[i] += R;
        }
        else{
            carry = 0;
        }
    }
    return c;
}

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(Key k, Key T[N]) {
    Key sum = {{0}};
    for (int i = 0; i < N; i++) {
        if (bit(k, i)) {
            sum = add(sum, T[i]);
            //printf("%2d ", i);           // Para teste.
            //print_key_char(T[i]);        // Para teste.
            //printf("Soma: ");            
            //print_key_char(sum);         // Para teste.
        }
    }
    //printf("\n");                        // Para teste.
   return sum;
}

// Verifica se a chave a é igual a chave b comparando cada uma dígito por dígito.
// Caso seja detectada diferença entre algum dos dígitos a função interrompe o loop 
// e retorna zero.
int equals(Key a, Key b){
    for(int i = 0; i < C; i++){
        if(a.digit[i] != b.digit[i]){
            return 0;
        }
    }
    return 1;
}

// Seguindo a ordem apresentada no ALPHABET a função compara duas keys para
// determinar qual das duas é maior. 
int compare(Key a, Key b){
    for(int i = 0; i < C; i++){
        if(ALPHABET[a.digit[i]] > ALPHABET[b.digit[i]]){
            return 1;// Key a > Key b
        }
        if(ALPHABET[a.digit[i]] < ALPHABET[b.digit[i]]){
            return -1;// Key a < Key b
        }
    }
    return 0;// Key a == Key b
}

// A função de hash abaixo consiste em multiplicar o valor de cada dígito da chave
// por 32 (o valor de R) elevado a sua posição na chave (considerando que a
// chave começa da direira para a esquerda).
// Utilizando como exemplo a key "abc5", tendo em mente que de acordo com o 
// ALPHABET 'a' = 0, 'b' = 1, 'c' = 2 e '5' = 31, temos que a hash_key
// correspondente a "abc5" seria 0*32^3 + 1*32^2 + 2*32^1 + 31*32^0.
int hash_key(Key key){
    long int sum = 0;
    long int mult = 1;
    for(int i = 0; i < C; i++){
        int dig = key.digit[i];
        sum += (dig)*mult;
        mult *= R;
    }
    return sum%hash_size;
}