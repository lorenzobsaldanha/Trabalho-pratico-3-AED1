/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int descobreMaiorProfundidade(struct TreeNode* arvore, int i, int maior) {
    if (arvore != NULL) {
        printf(" Prof:%d - ", i);
        if (maior <= i) {
            maior = i;
        }
        i++;
        printf("%d ", arvore->val);
        maior = descobreMaiorProfundidade(arvore->left, i, maior);
        maior = descobreMaiorProfundidade(arvore->right, i, maior);
    }
    return maior;
}

int descobreNoProfundo(struct TreeNode* arvore, int i, int maior,  int profundo, int *contaNoFinal) {
    if (arvore != NULL) {
        
        if (i == maior) {
           (*contaNoFinal)++;
           
            return arvore->val;
        }
        i++;
        profundo = descobreNoProfundo(arvore->left, i, maior,  profundo,contaNoFinal);
        profundo = descobreNoProfundo(arvore->right, i, maior,  profundo,contaNoFinal);
    }
    return profundo;
}

struct TreeNode* descobreSubarvore(struct TreeNode* arvore,  int maior,  int profundo, struct TreeNode *subarvore) {
    if (arvore != NULL) {
        if (((arvore->left != NULL) && (arvore->left->val == profundo)) || ((arvore->right != NULL) && (arvore->right->val == profundo))) {
            printf("\nAnterior: %d\n", arvore->val);
            
            return arvore;
        }
        
    
       subarvore = descobreSubarvore(arvore->left, maior,  profundo, subarvore);
        if (subarvore != NULL) {
            return subarvore;
        }
       subarvore = descobreSubarvore(arvore->right, maior,  profundo, subarvore);
        if (subarvore != NULL) {
            return subarvore;
        }
    }
    return subarvore;
}

struct TreeNode *descobreArvoreFolha(struct TreeNode* arvore, int i, int maior, int profundo, struct TreeNode *subarvore) {
    if (arvore != NULL) {
       
        if (arvore->val == profundo) {
          
           
            return arvore;
        }
        
        subarvore = descobreArvoreFolha(arvore->left, i, maior, profundo, subarvore);
        subarvore = descobreArvoreFolha(arvore->right, i, maior, profundo, subarvore);
        
    }
    return subarvore;
}

void print(struct TreeNode *arvore) {
    if (arvore != NULL) {
        printf(" %d ", arvore->val);
        print(arvore->left);
        print(arvore->right);
    }
}
//descobre o nodo mais profundo pra depois pegar a subarvore dele com struct TreeNode *anterior
struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
   
    struct TreeNode *sub = NULL;
    int i = 0, maior = 0, profundo = 0;
    int *contaNoFinal = (int*) malloc (sizeof(int));
    *contaNoFinal = 0;
    
    maior = descobreMaiorProfundidade(root, i, maior);
    printf("\nMaior profundidade: %d\n", maior);
    i = 0;
   
    profundo = descobreNoProfundo(root, i, maior,  profundo, contaNoFinal);
    printf("No mais profundo : %d\n", profundo);
    printf("Quantidade de nos finais: %d\n",*contaNoFinal);

    if(*contaNoFinal > 1)
    sub = descobreSubarvore(root,  maior,  profundo, sub);
    else{
        i=0;
    sub = descobreArvoreFolha(root , i, maior, profundo, sub);
    }
    print(sub);
    return sub;
}

