#ifndef HASH_H
#define HASH_H

#include "key.h"

typedef struct item Item;
Item** hash;
int hash_size;

// Inicializa a hash e define o size
void init_hash(int c, int r);

// Insere na hash, em caso de colisão vira uma BST balanceada
void insert_hash(Key key,Key enc);

// Retorna o nó que contem o target no campo enc
void search_hash(Key target,Key toprint);

// Libera toda a memória alocada
void destroy_hash();

// Retorna o campo key do Item*
Key getKey(Item* item);


#endif