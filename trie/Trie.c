// C implementation of search and insert operations on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26) // Alphabet size (# of symbols)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') // Converts key current character into index use only 'a' through 'z' and lower case

// trie node
typedef struct TrieNode{
	struct TrieNode *children[ALPHABET_SIZE];
	bool isEndOfWord;
}TrieNode;

// Returns new trie node (initialized to NULLs)
TrieNode *getNode(void){
	
	TrieNode *pNode = NULL;
	pNode = (TrieNode *)malloc(sizeof(TrieNode));
	if (pNode){
		int i;
		pNode->isEndOfWord = false;
		for (i = 0; i < ALPHABET_SIZE; i++)
			pNode->children[i] = NULL;
	}
	
	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(TrieNode *root, char *key){
	
	int level;
	int length = strlen(key);
	int index;

	TrieNode *pCrawl = root;

	for (level = 0; level < length; level++){
		index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index]){
			pCrawl->children[index] = getNode();
		}
		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else false
bool search(TrieNode *root, char *key){
	
	int level;
	int length = strlen(key);
	int index;
	TrieNode *pCrawl = root;

	for (level = 0; level < length; level++){
		index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index]){
			return false;
		}		
		pCrawl = pCrawl->children[index];
	}

	return (pCrawl->isEndOfWord);
}

void deleteFromTrie(TrieNode* root, char* key) {
    
	int level;
    int length = strlen(key);
    int index;

    TrieNode* pCrawl = root;
    TrieNode* prev = NULL;

    // Traverse the trie to find the node for the key
    for (level = 0; level < length; level++) {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index]) {
            return; // Key is not present in trie
        }

        prev = pCrawl;
        pCrawl = pCrawl->children[index];
    }

    // Unmark the end of word flag
    pCrawl->isEndOfWord = false;

    // Check if the node has any children
    for (index = 0; index < ALPHABET_SIZE; index++) {
        if (pCrawl->children[index]) {
            return; // Node has children, so don't delete it
        }
    }

    // Node has no children, delete it and recursively delete its parent if needed
    if (prev) {
        prev->children[CHAR_TO_INDEX(key[length-1])] = NULL;
        deleteFromTrie(root, key); // Recursively delete the parent if it has no other children
    }
}


// Driver
int main(){

	TrieNode *root = getNode();
		
	insert(root, "the");
	insert(root, "the world");
	insert(root,"a");
	insert(root,"there");
	insert(root,"answer");
	insert(root,"any");
	insert(root,"by");
	insert(root,"bye");
	insert(root,"their");
	insert(root,"thaw");

	// Search for different keys
	printf("word = \"%s\" ---> %d\n", "the",search(root, "the"));
	printf("word = \"%s\" ---> %d\n", "these", search(root, "these"));
	printf("word = \"%s\" ---> %d\n", "their", search(root, "their"));
	printf("word = \"%s\" ---> %d\n", "thaw", search(root, "thaw"));
	
	deleteFromTrie(root,"the");
	
	printf("-------after deleting \"the\"---------------\n");
	printf("word = \"%s\" ---> %d\n", "the",search(root, "the"));
	printf("word = \"%s\" ---> %d\n", "these", search(root, "these"));
	printf("word = \"%s\" ---> %d\n", "their", search(root, "their"));
	printf("word = \"%s\" ---> %d\n", "thaw", search(root, "thaw"));
	
	
	return 0;
}


	// Input keys (use only 'a' through 'z' and lower case)
	//	char keys[][8] = {"the", "a", "there", "answer", "any","by", "bye", "their"};
	//  char output[][32] = {"Not present in trie", "Present in trie"};
		// Construct trie
	//	int i;
	//	for (i = 0; i < ARRAY_SIZE(keys); i++)
	//		insert(root, keys[i]);
	
