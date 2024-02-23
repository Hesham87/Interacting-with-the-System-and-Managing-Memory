// Linked List node
struct node {

	// key is string
	char key;

	// value is also string
	int value;
	struct node* next;
};

void setNode(struct node* node, char key, int value);

struct hashMap {

	// Current number of elements in hashMap
	// and capacity of hashMap
	int numOfElements, capacity;

	// hold base address array of linked list
	struct node** arr;
};


void initializeHashMap(struct hashMap* mp);
int hashFunction(struct hashMap* mp, char key);
void insert(struct hashMap* mp, char key, int value);
void delete (struct hashMap* mp, char key);
int search(struct hashMap* mp, char key);

