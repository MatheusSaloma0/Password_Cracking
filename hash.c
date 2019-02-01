#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "key.h"

struct item{
    Key key;
    Key enc;
    Key* left;
    Key* right;
};

static Key alreadyPrinteds[N];
static int printeds = 0;

static void printed(Key key){
    for(int i = 0; i < printeds;i++){
        if(equals(alreadyPrinteds[i],key))
            return;
    }
    print_key_char(key);
    alreadyPrinteds[printeds++] = key;
}

// A função de inicialização da hash recebe C (Número de caracteres na senha) e R (Tamanho do alfabeto).
// O tamanho da hash será determinado por R^(C/2).
// Por exemplo o tamanho de uma hash com C = 4 seria 1024, C = 5 seria 32768, etc.
// Após a alocação da memória é checado se o ponteiro da hash é nulo, caso seja, 
// a função tentará valores cada vez menores até que se obtenha sucesso no malloc.
// Por fim, todas as posições da hash são setadas como NULL.
void init_hash(int c, int r){
    hash_size = 1; 

    for(int i = 0; i<(c/2) ;i++)//4 = 1024  5 = 32768  6 = 32768
        hash_size *= r;

    hash = malloc(hash_size*sizeof(Item*));
    
    //Caso não consiga alocar o tamanho desejado ele vai diminuindo até conseguir
    while(hash == NULL){
        hash_size /= r;
        hash = malloc(hash_size*sizeof(Item*));
    }
    
    for(int i = 0; i < hash_size ;i++)
        hash[i] = NULL;
}

// Dado uma chave e sua versão encripitada, um Item é alocado.
// Note que inicialmente todos os Items consistem numa folha.
static Item* create_item(Key key,Key enc){
    Item* new = malloc(sizeof(Item));
    new->key = key;
    new->enc = enc;
    new->left = NULL;
    new->right = NULL;
    return new;
}

// Função de inserção que recebe uma árvore e a chave que será inserida.
static Item* insert_tree(Item* tree,Key key,Key enc){
    if(tree == NULL){
        tree = create_item(key,enc);
        return tree;
    }
    if(compare(tree->enc,enc) == 1){ 
        tree->right = insert_tree(tree->right,key,enc);//Se nó > enc  insere na direita
    }else{
        tree->left = insert_tree(tree->left,key,enc);//Se não, insere na esqueda
    }
    return tree;
}

// Essa função é responsável por inserir a chave passada como parâmetro na tabela Hash.
// Neste trabalho obtamos por tratar as colisões através de uma árvore.  
void insert_hash(Key key,Key enc){
    int pos = hash_key(enc);
    Item* temp = hash[pos];
    temp = insert_tree(temp,key,enc);
    hash[pos] = temp;
}

// Função de busca in-order em uma árvore que retorna o ponteiro para o nó que 
// possui o chave encriptada igual ao parâmetro target ou NULL caso tal 
// chave não tenha sido encontrado.
static void BST_search(Item* tree,Key target,Key toprint){
    if(tree == NULL)
        return;
    int comp = compare(tree->enc,target);
    if(comp == 0){
        Key found = add(tree->key,toprint); 
        printed(found);
        BST_search(tree->left,target,toprint);
    }
    if(comp == 1)
        BST_search(tree->right,target,toprint);
    BST_search(tree->left,target,toprint);
}

// Função de busca em uma hash que verifica se a tabela possui a chave target.
// Nessa função não é necessário tratar o caso de inexistência da chave na tabela 
// pois isso é tratado pela BST_search(), que cuidará de retornar NULL para tal caso.
void search_hash(Key target,Key toprint){
    int pos = hash_key(target);
    BST_search(hash[pos],target,toprint);
}

// Função responsável por desalocar toda a memória alocada pela árvore.
static void BST_destroy(Item* tree){
    if(tree == NULL)
        return;
    BST_destroy(tree->right);
    BST_destroy(tree->left);
    free(tree);
}

// Função responsável por desalocar toda a memória alocada pela Tabela Hash.
void destroy_hash(){
    for(int i = 0; i < hash_size ;i++)
        BST_destroy(hash[i]);
    free(hash);
}

// Retorna a chave de um item.
Key getKey(Item* item){
    return item->key;
}
