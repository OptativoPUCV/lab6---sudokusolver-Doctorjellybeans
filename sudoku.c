#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {
  int nRep[10];
  int i, j, k, a, b;

  // Inicializar nRep[a] -> 0
  for (a = 0; a < 10; a++)
    nRep[a] = 0;

  // Validar filas
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      nRep[n->sudo[i][j]]++;
    }

    for (k = 1; k < 10; k++) {
      if (nRep[k] > 1)
        return 0;
    }

    for (a = 0; a < 10; a++) {
      nRep[a] = 0;
    }
  }

  // Validar columnas
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      nRep[n->sudo[j][i]]++; // lol
    }

    for (k = 1; k < 10; k++) {
      if (nRep[k] > 1)
        return 0;
    }

    for (a = 0; a < 10; a++) {
      nRep[a] = 0;
    }
  }

  for (k = 0; k < 9; k++) {
    for (b = 0; b < 9; b++) {
      i = 3 * (k / 3) + (b / 3);
      j = 3 * (k % 3) + (b % 3);
      nRep[n->sudo[i][j]]++;
    }

    for (i = 1; i < 10; i++) {
      if (nRep[i] > 1) {
        return 0;
      }

      for (a = 0; a < 10; a++) {
        nRep[a] = 0;
      }
    }
  }

  return 1;
}

/*
**¿Cómo recorrer las submatrices de 3x3?**
El siguiente código se puede usar para recorrer los elementos de una sumbatriz k (por ejemplo k=4):

    int k=4,p; 
    for(p=0;p<9;p++){
        int i=3*(k/3) + (p/3) ;
        int j=3*(k%3) + (p%3) ;
        printf("%d ",nodo->sudo[i][j]);
        if(p%3 == 2) printf("\n");
    }

La salida del código con el estado de la figura es (submatriz del centro):
    
    0 6 0
    8 0 3
    0 2 0
*/

List *get_adj_nodes(Node *n) {
  List *list = createList();
  int i, j, k;

  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0) {
        for (k = 1; k < 9; k++) {
          Node* adj_n = copy(n);
          adj_n->sudo[i][j] = k + 1;

          if (is_valid(adj_n)){
            pushBack(list, adj_n);
          } else {
            free(adj_n);
          }
          
        }
        return list;
      }
    }
  }

  return list;
}

int is_final(Node *n){
  int i,j;

  for (i = 0; i < 9; i++){
    for (j = 0; j < 9; j++){
      if (n->sudo[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}

Node *DFS(Node *initial, int *cont){
  /*
  Stack* stack = createStack();
  push(stack, initial);

  while (!is_empty(stack)){
    Node* current = (Node*)top(stack);
    pop(stack);

    (*cont)++;

    if (is_final(current)){
      clean(stack);
      return current;
    }

    List* adj_nodes = get_adj_nodes(current);
    while (!is_empty(adj_nodes)){
      Node* adj_node = (Node*)front(adj_nodes);
      popFront(adj_nodes);

      push(stack, adj_node);
    }
    clean(adj_nodes);

    free(current);
  }
  
  return NULL;
  */
  return NULL;
}


/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/