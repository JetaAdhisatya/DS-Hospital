#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Node{
  char name[100];
  int count;
  Node *next;
  Node *prev;
} *head = NULL, *tail = NULL;

Node *createNode(char name[], int count){
  Node *newNode = (Node *)malloc(sizeof(Node));
  strcpy(newNode->name, name);
  newNode->prev = newNode->next = NULL;
  newNode->count = count;
  return newNode;
}

void pushHead(char name[], int count){
  Node *newNode = createNode(name, count);
  if (head == NULL){
    head = tail = newNode;
  }else{
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
}

void pushTail(char name[], int value){
  Node *newNode = createNode(name, value);
  if (head == NULL){
    head = tail = newNode;
  }else{
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
}

void pop(){
  if (head == NULL){
    return;
  }else if (head == tail){
    head->next = NULL;
    head->prev = NULL;
    free(head);
    head = tail = NULL;
  }else{
    Node *temp = head;
    head = head->next;
    head->prev = NULL;
    temp->next = NULL;
    free(temp);
  }
}

void push(char name[], int count){
  if (head == NULL){
    Node *newNode = createNode(name, count);
    head = tail = newNode;
  }
  else if (head->count > count){
    pushHead(name, count);
  }
  else if (tail->count <= count){
    pushTail(name, count);
  }else{
    Node *newNode = createNode(name, count);
    Node *curr = head;
    while (curr->count <= count){
      curr = curr->next;
    }
    newNode->prev = curr->prev;
    newNode->next = curr;
    newNode->prev->next = newNode;
    newNode->next->prev = newNode;
  }
}

void printAll(){
  Node *curr = head;
  printf("Queue content : ");
  if (curr != NULL){
    printf("%s ", curr->name);
    curr = curr->next;
  }
  while (curr != NULL){
    printf("- %s", curr->name);
    curr = curr->next;
  }
  printf("\n");
}

int main(){
	int input;
	do{
		printf("menu  \n");
		printf("1. input\n");
		printf("2. Exit\n");
		scanf("%d", &input);
		getchar();
		
	char name[100];
	char pelayanan;
    int count = 10;
    printf("Patient Arrive (Name) : ");
    scanf("%[^\n]", name);

    if (strcmp(name, "End") == 0){
      printf("Thankyou for using this program!");
      return 0;
    }

    do{
      printf("Nature of Emergency : ");
      scanf("%d", &count);
      getchar();
    } while (count != 2 && count != 1);

    push(name, count);
    printAll();

    do{
      printf("Service? ");
      scanf("%c", &pelayanan);
      getchar();
    } while (pelayanan != 'Y' && pelayanan != 'N');

    switch (pelayanan){
    case 'Y':
      pop();
      printAll();
      break;
    }

    printf("\n");
    
	}while(input != 2);

  return 0;
}
