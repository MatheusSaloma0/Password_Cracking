#include <stdlib.h>
#include <stdio.h>
#include "key.h"

int main(int argc, char *argv[]) {
    Key password;                  // A senha fornecida pelo usuário.
    Key encrypted;                 // A senha criptografada.
    Key T[N];                      // A tabela T.
    if (argc != 2) {
        fprintf(stderr, "Usage: ./encrypt [password] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }
    encrypted = init_key(argv[1]); //Encrypted = senha encriptada
    print_key(encrypted);
    printf("\n");
    // Lê a tabela T.
    unsigned char buffer[C+1];     // Buffer temporário.
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }   

    char first [C];
    char it [C];
    char las [C];
    for(int i = 0; i<C ;i++){
        first[i] = ALPHABET[0];
        it[i] = ALPHABET[0];
        las[i] = ALPHABET[R-1];
    }
    it[C-1] = ALPHABET[1];

    Key temp = init_key(first);
    Key iterator = init_key(it);
    Key end = init_key(las);
    while(!equals(temp,end)){
        temp = add(temp,iterator);
        Key try = subset_sum(temp,T);
        if (equals(try,encrypted))
            print_key_char(temp);
    }

    return 0;
}