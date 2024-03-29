#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"



// like constructor
void setNode(struct node* node, char key, int value)
{
	node->key = key;
	node->value = value;
	node->next = NULL;
	return;
}



// like constructor
void initializeHashMap(struct hashMap* mp)
{

	// Default capacity in this case
	mp->capacity = 100;
	mp->numOfElements = 0;

	// array of size = 1
	mp->arr = (struct node**)malloc(sizeof(struct node*) * mp->capacity);
	return;
}

int hashFunction(struct hashMap* mp, char key)
{
	int bucketIndex;
	int sum = 0, factor = 31;
	// sum = sum + (ascii value of
    // char * (primeNumber ^ x))...
    // where x = 1, 2, 3....n
    sum = ((sum % mp->capacity)
        + (((int)key) * factor) % mp->capacity)
        % mp->capacity;

    // factor = factor * prime
    // number....(prime
    // number) ^ x
    factor = ((factor % __INT16_MAX__)
            * (31 % __INT16_MAX__))
            % __INT16_MAX__;

	bucketIndex = sum;
	return bucketIndex;
}

void insert(struct hashMap* mp, char key, int value)
{

	// Getting bucket index for the given
	// key - value pair
	int bucketIndex = hashFunction(mp, key);
	struct node* newNode = (struct node*)malloc(

		// Creating a new node
		sizeof(struct node));

	// Setting value of node
	setNode(newNode, key, value);

	// Bucket index is empty....no collision
	if (mp->arr[bucketIndex] == NULL) {
		mp->arr[bucketIndex] = newNode;
	}

	// Collision
	else {

		// Adding newNode at the head of
		// linked list which is present
		// at bucket index....insertion at
		// head in linked list
		newNode->next = mp->arr[bucketIndex];
		mp->arr[bucketIndex] = newNode;
	}
	return;
}

void delete (struct hashMap* mp, char key)
{

	// Getting bucket index for the
	// given key
	int bucketIndex = hashFunction(mp, key);

	struct node* prevNode = NULL;

	// Points to the head of
	// linked list present at
	// bucket index
	struct node* currNode = mp->arr[bucketIndex];

	while (currNode != NULL) {

		// Key is matched at delete this
		// node from linked list
		if (key == currNode->key) {

			// Head node
			// deletion
			if (currNode == mp->arr[bucketIndex]) {
				mp->arr[bucketIndex] = currNode->next;
			}

			// Last node or middle node
			else {
				prevNode->next = currNode->next;
			}
			free(currNode);
			break;
		}
		prevNode = currNode;
		currNode = currNode->next;
	}
	return;
}

int search(struct hashMap* mp, char key)
{

	// Getting the bucket index
	// for the given key
	int bucketIndex = hashFunction(mp, key);

	// Head of the linked list
	// present at bucket index
	struct node* bucketHead = mp->arr[bucketIndex];
	while (bucketHead != NULL) {

		// Key is found in the hashMap
		if (bucketHead->key == key) {
			return bucketHead->value;
		}
		bucketHead = bucketHead->next;
	}

	// If no key found in the hashMap
	// return -1
	// char errorMssg = (char)malloc(sizeof(char) * 25);
	// errorMssg = "Oops! No data found.\n";
	return -1;
}

void free_map(struct hashMap * mp){
	for(int i =0; i < mp->capacity; i++){
		if(mp->arr[i] != NULL){
			free(mp->arr[i]);
		}
	}
	// for(int i =0; i < 10; i++){
	// 	if(i != 1){ 
	// 		int bucketIndex = hashFunction(mp, '0' + i);
	// 		if(mp->arr[bucketIndex] != NULL){
	// 			free(mp->arr[bucketIndex]);
	// 		}	
	// 	}	
	// }
	// int bucketIndex = hashFunction(mp, 'A');
	// if(mp->arr[bucketIndex] != NULL){
	// 	free(mp->arr[bucketIndex]);
	// }
	// bucketIndex = hashFunction(mp, 'K');
	// if(mp->arr[bucketIndex] != NULL){
	// 	free(mp->arr[bucketIndex]);
	// }
	// bucketIndex = hashFunction(mp, 'J');
	// if(mp->arr[bucketIndex] != NULL){
	// 	free(mp->arr[bucketIndex]);
	// }
	// bucketIndex = hashFunction(mp, 'Q');
	// if(mp->arr[bucketIndex] != NULL){
	// 	free(mp->arr[bucketIndex]);
	// }
	free(mp->arr);
	free(mp);
}

// Drivers code
// int main()
// {

// 	// Initialize the value of mp
// 	struct hashMap* mp
// 		= (struct hashMap*)malloc(sizeof(struct hashMap));
// 	initializeHashMap(mp);

// 	insert(mp, "Yogaholic", "Anjali");
// 	insert(mp, "pluto14", "Vartika");
// 	insert(mp, "elite_Programmer", "Manish");
// 	insert(mp, "GFG", "GeeksforGeeks");
// 	insert(mp, "decentBoy", "Mayank");

// 	printf("%s\n", search(mp, "elite_Programmer"));
// 	printf("%s\n", search(mp, "Yogaholic"));
// 	printf("%s\n", search(mp, "pluto14"));
// 	printf("%s\n", search(mp, "decentBoy"));
// 	printf("%s\n", search(mp, "GFG"));

// 	// Key is not inserted
// 	printf("%s\n", search(mp, "randomKey"));

// 	printf("\nAfter deletion : \n");

// 	// Deletion of key
// 	delete (mp, "decentBoy");
// 	printf("%s\n", search(mp, "decentBoy"));

// 	return 0;
// }
