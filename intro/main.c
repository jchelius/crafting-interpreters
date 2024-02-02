#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 16

struct ListNode{
	char* val;
	struct ListNode *prev;
	struct ListNode *next;
};

typedef struct ListNode ListNode;
ListNode *head = NULL;
ListNode *tail = NULL;

void dll_insert(char *val){
	ListNode *new_node = malloc(sizeof(ListNode));
	new_node->prev = tail;
	new_node->next = NULL;
	// malloc one extra char for zero termination
	new_node->val = malloc((MAXLEN+1)*sizeof(char));
	// should probably convert this to snprintf instead of strncpy
	strncpy(new_node->val, val, MAXLEN);
	new_node->val[MAXLEN] = 0;
	// printf("%c\n", new_node->val[MAXLEN]);
	if (!head){
		head = new_node;
	}
	else{
		tail->next = new_node;
	}
	tail = new_node;
}

ListNode *dll_find(char *val){
	ListNode *cur = head;
	// if (strncmp(val, cur->val, MAXLEN) == 0){
	// 	return cur;
	// }
	// cur = cur->next;
	// return NULL;
	while (cur){
		// printf("dll_find: %s\n", cur->val, MAXLEN);
		// printf("%s %s\n", val, cur->val);
		if (strncmp(val, cur->val, MAXLEN) == 0){
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

void dll_delete(ListNode *node){
	if (!node->prev){
		// target = head
		head = node->next;
	}
	printf("-----------------------------------\n");
	else{
		node->prev->next = node->next;
	}
	if (!node->next){
		// target = tail
		tail = node->prev;
	}
	else{
		node->next->prev = node->prev;
	}
	free(node);
	node = NULL;
}

void dll_free(){
	ListNode *cur = head;
	while (cur){
		ListNode *next = cur->next;
		free(cur->val);
		free(cur);
		cur = next;
	}
}

void dll_print(){
	ListNode *cur = head;
	int i = 0;
	while (cur){
		if (i) printf(" <--> ");
		printf("%s", cur->val);
		cur = cur->next;
		i += 1;
	}
	printf("\n");
}

int main(void){
	dll_insert("Hello world! this is a test of poorly written code to see if the security measures will be broken");
	dll_insert("1+1=2");
	dll_insert("foo");
	dll_insert("baz");
	dll_insert("bar");
	ListNode *foo = dll_find("foo");
	ListNode *baz = dll_find("baz");
	ListNode *bar = dll_find("bar");
	ListNode *eq = dll_find("1+1=2");
	printf("%s\n", head->val);
	printf("%s\n", eq->val);
	printf("%s\n", foo->val);
	printf("%s\n", baz->val);
	printf("%s\n", bar->val);
	dll_delete(foo);
	printf("-----------------------------------\n");
	
	dll_print();
	dll_delete(head);
	printf("-----------------------------------\n");
	dll_print();
	dll_delete(tail);
	printf("-----------------------------------\n");
	dll_print();
	dll_free();
	return 0;
}
