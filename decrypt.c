#include <stdlib.h>
#include <stdio.h>
#include "key.h"
#include "hash.h"

int main(int argc, char *argv[]){
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
    unsigned char buffer[C+1];     // Buffer temporário.
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }   

    //Supondo um exemplo de C=4, os comentários são o decorrer do programa
    //sendo a senha desejada, leos, e a encriptada passada na linha de 
    //comando é ird1
    
    //Inicializar chaves da forma desejada
    char first[C];
    char it[C];
    char las[C];
    for(int i = 0; i<C/2 ;i++){// 0 1
        first[i] = ALPHABET[0];//aa
        it[i] = ALPHABET[0];//aa
        las[i] = ALPHABET[0];//aa
    }
    for(int i = C/2; i<C ;i++){// 2 3
        first[i] = ALPHABET[0];//aaaa
        it[i] = ALPHABET[0];//aaaa
        las[i] = ALPHABET[R-1];//aa55
    }
    it[(C)-1] = ALPHABET[1];//aaab
    Key temp = init_key(first);//aaaa
    Key iterator = init_key(it);//aaab
    Key end = init_key(las);//aa55

    //Inicializa a Hash
    init_hash(C,R);

    while(!equals(temp,end)){
        Key tempEnc = subset_sum(temp,T);// senha: aaos, senha encriptada: fqgx
        insert_hash(temp,tempEnc);// Hash[hash_key(fqgx)] = aaos e fqgx
        if (equals(tempEnc,encrypted))
            print_key_char(temp);
        temp = add(temp,iterator);
    }

    for(int i = 0; i<C/2 ;i++){// 0 1
        first[i] = ALPHABET[0];//aa
        it[i] = ALPHABET[0];//aa
        las[i] = ALPHABET[R-1];//55
    }
    it[(C/2)-1] = ALPHABET[1];//ab
    for(int i = C/2; i<C ;i++){// 2 3
        first[i] = ALPHABET[0];//aaaa
        it[i] = ALPHABET[0];//abaa
        las[i] = ALPHABET[0];//55aa
    }
    temp = init_key(first);
    iterator = init_key(it);
    end = init_key(las);
    while(!equals(temp,end)){//ird1
        temp = add(temp,iterator);
        Key tempEnc = subset_sum(temp,T);// senha: leaa , senha encriptada: da3e
        Key result = sub(encrypted,tempEnc); // fqgx
        search_hash(result,temp);//aaos e fqgx
    }

    //Libera hash
    destroy_hash();

    return 0;
}