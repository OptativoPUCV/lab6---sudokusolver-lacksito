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
  int usado[10] = {0}; 
  int numero;

  
  for (int i = 0; i < 9; i++) 
  {
    for (int k = 1; k <= 9; k++) 
    {
      usado[k] = 0;
    }
    for (int j = 0; j < 9; j++) 
    {
      numero = n->sudo[i][j];
      if (numero != 0 && usado[numero] == 1) 
      {
        return 0;
      }
      usado[numero] = 1;
      }
    
      for (int k = 1; k <= 9; k++) 
      {
        usado[k] = 0; 
      }
      for (int j = 0; j < 9; j++) 
      {
        numero = n->sudo[j][i];
        if (numero != 0 && usado[numero] == 1) 
        {
          return 0;
        }
          usado[numero] = 1;
        }
    }

  // Verificar submatrices
  for (int ai = 0; ai < 3; ai++) 
  {
      for (int aj = 0; aj < 3; aj++) 
    {
      for (int k = 1; k <= 9; k++) 
      {
        usado[k] = 0; 
      }
      for (int i = ai * 3; i < ai * 3 + 3; i++) 
      {
        for (int j = aj * 3; j < aj * 3 + 3; j++) 
        {
          numero = n->sudo[i][j];
          if (numero != 0 && usado[numero] == 1) 
          {
            return 0;
          }
          usado[numero] = 1;
        }
      }
    }
  }
  return 1;
}




List* get_adj_nodes(Node* n)
{
  List* list = createList();

  for (int i = 0; i < 9; i++) 
  {
    for (int j = 0; j < 9; j++) 
    {
      if (!n->sudo[i][j]) 
      {
        Node* newNodo = copy(n);
        for (int numero = 1; numero <= 9; numero++) 
        {
          newNodo->sudo[i][j] = numero;
          if (is_valid(newNodo)) 
          {
            pushBack(list, newNodo);
          } 
          else 
          {
            free(newNodo); 
          }
          newNodo = copy(n);
        }
        free(newNodo); 
        return list;
      }
    }
  }
  return list;
}

int is_final(Node* n)
{
  for (int i = 0 ; i < 9 ; i++)
  {
    for (int j = 0 ; j < 9 ; j++)
    {
      if (n->sudo[i][j] == 0) 
      {  
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack *stack = createStack();
  push(stack, initial);

  while(top(stack) != NULL)
  {
    Node *topNode = top(stack);
    pop(stack);
    
    if (is_final(topNode) == 1)
    {
      return topNode;
    }
    
    List *list = createList();
    list = get_adj_nodes(topNode);

    for (Node *a = first(list) ; a != NULL ; a = next(list))
    {
      push(stack, a);
    }

    free(topNode);
  }

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