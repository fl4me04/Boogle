#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Trie{
	char chr; // Character that stored in the node
	int word; // 1 means there is a word ends at this node, 0 otherwise
	char *desc; // To keep description of the word
	struct Trie* edge[128]; // ASCII representation, ex: 'A' will be save in edge[65]
}*root = NULL;

struct Trie *createNew(char x){
	struct Trie *newNode = (struct Trie*)malloc(sizeof(struct Trie)); // Make newNode size flexible
	newNode->chr = x; // Declare char value to x
	newNode->word = 0; // Declare word value to 0
	newNode->desc = NULL; // Declare desc to NULL
	for(int i = 0; i < 128; i++){
		newNode->edge[i] = 0; // Fill all of the array with 0
	}
	return newNode;
}

void insert(struct Trie *root, char *word, char *description) { // A function to insert Trie
    struct Trie *temp = root; // Initialize temporary pointer to root
    int len = strlen(word); // Calculate length of the word
    for(int i = 0; i < len; i++) {
        int index = (int)word[i]; // Calculate ASCII value of the current character
        if(temp->edge[index] == NULL) {
            temp->edge[index] = createNew(word[i]); // If node doesn't exist, create a new one
        }
        temp = temp->edge[index]; // Move to the next node
    }
    // Check if the word already exists, if so, update its description
    if (temp->desc != NULL && temp->word == 1) {
        free(temp->desc);
    }
    temp->word = 1;
    temp->desc = (char *)malloc(strlen(description) + 1);
    strcpy(temp->desc, description);
}

int searchTrie(char *str){ // A function to search if there is a trie
    struct Trie *temp = root;
    while(*str){ // Iteration until it found the string
        if(temp->edge[*str] == NULL){ // If edge[str] isnt available, return 0 which means not found
			return 0;
		}
        temp = temp->edge[*str];
        str++;
    }
    if(temp->word == 0){ // If the last node is not marked as a word, it means the string is not fully present in the trie
        return 0;
    }
    return 1; // If the loop completes without returning, the string is found
}

char *searchWord(struct Trie *root, char *word) { // A function to output the description
    struct Trie *temp = root; // Initialize temporary pointer to root
    int len = strlen(word); // Calculate length of the word
    for(int i = 0; i < len; i++) {
        int index = (int)word[i]; // Calculate ASCII value of the current character
        if(temp->edge[index] == NULL){
            return NULL; // If node doesn't exist, word doesn't exist in the Trie
        }
        temp = temp->edge[index]; // Move to the next node
    }
    if(temp != NULL && temp->word == 1){
        return temp->desc; // Return description if word is found
    }else{
    	return NULL; // Return NULL if word is not found
    }
}

int itung = 1; // Global var to count how many node are there

void searchWordsHelper(struct Trie *node, char *buffer, int depth) { // A function that help for DFS to find words with prefix
    if(node->word == 1) {
        printf("%d. %s\n", itung++, buffer);
    }
    for(int i = 0; i < 128; i++) {
        if(node->edge[i] != NULL) {
            buffer[depth] = node->edge[i]->chr;
            buffer[depth + 1] = '\0';
            searchWordsHelper(node->edge[i], buffer, depth + 1);
        }
    }
}

void searchWithPrefix(struct Trie *root, char *prefix) { // A function to search for words with a given prefix
    struct Trie *temp = root;
    int len = strlen(prefix);
    int i;
    // Traverse to the node corresponding to the last character of the prefix
    for(i = 0; i < len; i++) {
        int index = (int)prefix[i];
        if(temp->edge[index] == NULL){
            printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
            return;
        }
        temp = temp->edge[index];
    }
    // Once the prefix is found, perform a DFS to find all words with this prefix
    printf("Words starts with \"%s\":\n", prefix);
    char *buffer = (char *)malloc(len + 1);
    strcpy(buffer, prefix);
    searchWordsHelper(temp, buffer, len);
    free(buffer);
}

void release(){
	system("cls");
	char word[10001] = "A";
	int simpen = strlen(word);
	int count = 0;
	while(simpen == 1 || count >= 1){ // Repetition until there are more than 1 char and no space
		printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
		scanf("%[^\n]", &word);
		getchar();
		count = 0;
		simpen = strlen(word);
		for(int i = 0; i < simpen; i++){
			if(word[i] == ' ') count += 1;
		}
	}
	if(searchTrie(word) == 1){ // Condition if the word desc will be updated
		char desc[10001] = "A";
		int simpen2 = strlen(desc);
		int count2 = 0;
		while(count2 < 2){ // Repetition until there are more than 2 words
			printf("Input a new slang word description [Must be more than 2 words]: ");
			scanf("%[^\n]", &desc);
			getchar();
			count2 = 0;
			simpen2 = strlen(desc);
			for(int i = 0; i < simpen2; i++){ // Repetition words count
				if(desc[i] == ' ') count2 += 1;
			}
		}
		insert(root, word, desc); // Inserting words and desc to Tries
		puts("");
		printf("Successfully updated slang word.\n");
		printf("Press enter to continue...");
		getchar();
	}else{
		char desc[10001] = "A";
		int simpen2 = strlen(desc);
		int count2 = 0;
		while(count2 < 2){ // Repetition until there are more than 2 words
			printf("Input a new slang word description [Must be more than 2 words]: ");
			scanf("%[^\n]", &desc);
			getchar();
			count2 = 0;
			simpen2 = strlen(desc);
			for(int i = 0; i < simpen2; i++){ // Repetition words count
				if(desc[i] == ' ') count2 += 1;
			}
		}
		insert(root, word, desc); // Inserting words and desc to Tries
		puts("");
		printf("Successfully released new slang word.\n");
		printf("Press enter to continue...");
		getchar();
	}
}

void search(){
	system("cls");
	char word[10001] = "A";
	int simpen = strlen(word);
	int count = 0;
	while(simpen == 1 || count >= 1){ // Repetition until there are more than 1 char and no space
		printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
		scanf("%[^\n]", &word);
		getchar();
		count = 0;
		simpen = strlen(word);
		for(int i = 0; i < simpen; i++){
			if(word[i] == ' ') count += 1;
		}
	}
	puts("");
	if(searchTrie(word) == 1){ // If there is a word
		printf("Slang word     : %s\n", word);
		printf("Description    : %s\n", searchWord(root, word));
		puts("");
		printf("Press enter to continue...");
		getchar();
	}else{ // If there isnt any word
		printf("There is no word \"%s\" in the dictionary.\n", word);
		printf("Press enter to continue...");
		getchar();
	}
}

void prefix(){
	system("cls");
	itung = 1;
	char prefix[1000];
	printf("Input a prefix to be searched: ");
	scanf("%[^\n]", &prefix);
	getchar();
	puts("");
	searchWithPrefix(root, prefix);
	puts("");
	printf("Press enter to continue...");
	getchar();
}

void showAllHelper(struct Trie *node, char *buffer, int depth) { // Function to perform Depth-First Search traversal to display all slang words
    if(node->word == 1) {
        printf("%d. %s\n", itung++, buffer); // If there is the word so print
    }
    for(int i = 0; i < 128; i++) { // Tranversal Logic
        if(node->edge[i] != NULL) {
            buffer[depth] = node->edge[i]->chr;
            buffer[depth + 1] = '\0';
            showAllHelper(node->edge[i], buffer, depth + 1);
        }
    }
}

void showAll() { // A function to display all slang words in lexicographical order
    system("cls");
    int hasWords = 0; // Check is there any words
    if(root != NULL) {
        for(int i = 0; i < 128; i++) {
            if(root->edge[i] != NULL) {
                hasWords = 1;
                break;
            }
        }
    }
    if(!hasWords) { // If there isnt any words, so printf there are no slang words
        printf("There are no slang words in the dictionary.\n");
        printf("Press enter to continue...");
        getchar();
        return;
    }
    itung = 1;
    printf("List of all slang words in the dictionary:\n");
    char *buffer = (char *)malloc(10000); // Allocate memory for buffer
    showAllHelper(root, buffer, 0); // Start DFS traversal from the root
    free(buffer); // Free allocated memory
    puts("");
    printf("Press enter to continue...");
    getchar();
}

int main(){
	root = createNew('/');
	// Make variable to choose number in the menu
	int choose = 0;
	// 5 is Exit, so while the number chosen isnt 5, we will do looping
	while(choose != 5){
		// Make a main menu description to choose
		system("cls");
		printf("Boogle\n");
		printf("Main Menu : \n");
		printf("1. Release a new slang word\n");
		printf("2. Search a slang word\n");
		printf("3. View all slang words starting with a certain prefix word\n");
		printf("4. View all slang words\n");
		printf("5. Exit\n");
		printf("Choose Menu : ");
		// Choose the menu using input number
		scanf("%d", &choose);
		getchar();
		// Make what happen next if we choose the number from 1-5
		switch(choose){
			case 1:{
				release();
				break;
			}
			case 2:{
				search();
				break;
			}
			case 3:{
				prefix();
				break;
			}
			case 4:{
				showAll();
				break;
			}
			case 5:{
				system("cls");
				printf("Thank you... Have a nice day :)\n");
				break;
			}
		}
	}
	
}
