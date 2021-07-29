#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _bst {
    struct _bst* l;
    struct _bst* r;
    char* str;
} bst;



bst* get(bst* root, char* str) {
	
	
    bst* atual = root;
		
	while(atual != NULL){
		
		if(strcmp(str, atual->str) == 0)
			return atual;
			
		if(strcmp(str, atual->str) > 0)
			atual = atual->r;
		else
			atual = atual->l;
	}
	
	return NULL;
	

}

bst* put(bst* root, char* str) {
    if(root) {
        int cmp = strcmp(root->str, str);
        if(cmp > 0)
            root->l = put(root->l,str);
        else if (cmp < 0)
            root->r = put(root->r,str);
        return root;
    } else {
        bst* novo = (bst*)malloc(sizeof(bst));
        novo->str = (char*)malloc(sizeof(char)*(strlen(str)+1));
        strcpy(novo->str,str);
        novo->l = novo->r = NULL;
        return novo;
    }
}

bst* max(bst* root) {
	

	if(root == NULL) return NULL;
		
	if(root->r != NULL){

		return max(root->r);
	}
	else{
		return root;
	}
	
   
}

bst* min(bst* root) {
    
	
	if(root == NULL) return NULL;
		
	if(root->l != NULL){

		return min(root->l);
	}
	else{
		return root;
	}
	
	
}

bst* rem(bst* root, char* str) {
	
    
    if (root == NULL) return root;
    
    
    if(strcmp(str, root->str) == 0){
		

    
	    if( root->r == NULL && root->l == NULL){
	    	free(root->str);
	   		free(root);
	   		root->str = NULL;
	   		root = NULL;

	   		return NULL;
		}
	    	
	    else if(root->r != NULL && root->l != NULL){
	    	
	    	bst* aux = max(root->l);
	    	char* tmp = aux->str;
	    	free(root->str);
	    	
	    	root->str = aux->str;
	    	aux->str = tmp;
			root->l = rem(root->l, aux->str);
			
	    	return root;
	    
		}
		else{
			
			if(root->r != NULL){
	    		bst* aux = root->r;
	    		free(root->str);
	   			free(root);
	   			return aux;
	    		
			}
			else{
				bst* aux = root->l;
				free(root->str);
	   			free(root);
	   			return aux;
			}
			
			
		}
		
	}
	else{
		
		if(strcmp(str, root->str) > 0)
			root->r = rem(root->r, str);
		
		else
			root->l = rem(root->l, str);
		
	}	
	    
    return root;
    
}


void del(bst* root) {
    if(root) {
        del(root->l);
        del(root->r);
        free(root->str);
        free(root);
    }
}



int main() {

    char comando[2], palavra[255];

    bst* raiz = NULL;

    while(scanf("%s", comando) != EOF) {
        scanf("%s", palavra);
        if( comando[0] == 'P' )
            raiz = put(raiz,palavra);
        else if( comando[0] == 'R' ){
            raiz = rem(raiz,palavra);
        
		}else if( comando[0] == 'G' ) {
            bst* result = get(raiz,palavra);
            if( result )
                printf("%s encontrada\n", result->str);
            else
                printf("%s nao foi encontrada\n", palavra);
        }
    }

    del(raiz);

    return 0;
}
