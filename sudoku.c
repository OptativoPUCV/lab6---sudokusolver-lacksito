#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  int row_check[9][10] = {0}; // 9 filas, 10 números
  int col_check[9][10] = {0}; // 9 columnas, 10 números
  int submatrix_check[9][10] = {0}; // 9 submatrices de 3x3, 10 números

  for (int i = 0; i < 9; i++) 
  {
    for (int j = 0; j < 9; j++) 
    {
      int num = n->sudo[i][j];
      // Verificar si el número ya ha aparecido en la fila
      if (num != 0 && row_check[i][num] == 1 
      {
        return 0;
      }
      // Verificar si el número ya ha aparecido en la columna
      if (num != 0 && col_check[j][num] == 1) 
      {
        return 0; 
      }
        // Verificar si el número ya ha aparecido en la submatriz
      int submatrix_index = 3 * (i / 3) + (j / 3);
      if (num != 0 && submatrix_check[submatrix_index][num] == 1) 
      {
        return 0; 
      }

    
      row_check[i][num] = 1;
      col_check[j][num] = 1;
      submatrix_check[submatrix_index][num] = 1;
      }
    }

  return 1; 
}



List* get_adj_nodes(Node* n)
{
  List* list = createList();
  int row = -1, col = -1;
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            if (n->sudo[i][j] == 0) 
            {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1) 
        {
            break;
        }
    }

    if (row == -1 || col == -1) 
    {
        return list;
    }

  for (int num = 1; num <= 9; num++) 
  {
        Node* new_node = copy(n);
        new_node->sudo[row][col] = num;
        pushBack(list, new_node); 
    }

  return list;
  
}


int is_final(Node* n)
{
    return 0;
}

Node* DFS(Node* initial, int* cont){
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