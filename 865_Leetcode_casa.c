/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int DescobreMaiorProfundidade_r( struct TreeNode* arvore, int i, int maior ) {
    if ( arvore != NULL ) {
        printf(" Prof:%d - ", i);
        if ( maior <= i ) {
            maior = i;
        }
        i++;
        printf( "%d ", arvore->val );
        maior = DescobreMaiorProfundidade_r( arvore->left, i, maior );
        maior = DescobreMaiorProfundidade_r( arvore->right, i, maior );
    }
    return maior;
}

int DescobreNoProfundo_r( struct TreeNode* arvore, int i, int maior,  int profundo, int *contaNoFinal ) {
    if ( arvore != NULL ) {
        
        if ( i == maior ) {
           ( *contaNoFinal )++;
           
            return arvore->val;
        }
        i ++;
        profundo = DescobreNoProfundo_r( arvore->left, i, maior,  profundo,contaNoFinal );
        profundo = DescobreNoProfundo_r( arvore->right, i, maior,  profundo,contaNoFinal );
    }
    return profundo;
}

struct TreeNode* DescobreSubarvore_r( struct TreeNode* arvore,  int maior,  int profundo, struct TreeNode *subarvore ) {
    if ( arvore != NULL ) {
        if ( ( ( arvore->left != NULL ) && ( arvore->left->val == profundo ) ) || ( ( arvore->right != NULL ) && ( arvore->right->val == profundo ) ) ) {
            printf( "\nAnterior: %d\n", arvore->val );
            
            return arvore;
        }
        
    
       subarvore = DescobreSubarvore_r( arvore->left, maior,  profundo, subarvore );
        if ( subarvore != NULL ) {
            return subarvore;
        }
       subarvore = DescobreSubarvore_r( arvore->right, maior,  profundo, subarvore );
        if ( subarvore != NULL ) {
            return subarvore;
        }
    }
    return subarvore;
}

struct TreeNode *DescobreArvoreFolha_r( struct TreeNode* arvore, int i, int maior, int profundo, struct TreeNode *subarvore ) {
    if ( arvore != NULL ) {
       
        if ( arvore->val == profundo ) {
          
           
            return arvore;
        }
        
        subarvore = DescobreArvoreFolha_r( arvore->left, i, maior, profundo, subarvore );
        subarvore = DescobreArvoreFolha_r( arvore->right, i, maior, profundo, subarvore );
        
    }
    return subarvore;
}

void Print_r( struct TreeNode *arvore ) {
    if ( arvore != NULL ) {
        printf( " %d ", arvore->val );
        Print_r( arvore->left );
        Print_r( arvore->right );
    }
}
//descobre o nodo mais profundo pra depois pegar a subarvore dele com struct TreeNode *anterior
struct TreeNode* subtreeWithAllDeepest( struct TreeNode* root ) {
   
    struct TreeNode *sub = NULL;
    int i = 0, maior = 0, profundo = 0;
    int *contaNoFinal = ( int* ) malloc ( sizeof( int ) );
    *contaNoFinal = 0;
    
    maior = DescobreMaiorProfundidade_r( root, i, maior );
    printf( "\nMaior profundidade: %d\n", maior );
    i = 0;
   
    profundo = DescobreNoProfundo_r( root, i, maior,  profundo, contaNoFinal );
    printf( "No mais profundo : %d\n", profundo );
    printf( "Quantidade de nos finais: %d\n", *contaNoFinal );

    if( *contaNoFinal > 1 )
    sub = DescobreSubarvore_r( root,  maior,  profundo, sub );
    else{
        i=0;
    sub = DescobreArvoreFolha_r( root , i, maior, profundo, sub );
    }
    Print_r( sub );
    return sub;
}

