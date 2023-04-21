#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Trie{
int count;
struct Trie * nextTrie[26];
}Trie;

void insert(struct Trie *ppTrie, char *word, int z){
    if(strlen(word)==(z)){
        (ppTrie)->count++;
        return;
    }
    int index =(word[z]-'a');
    if(((ppTrie)->nextTrie[index]) == NULL){
        ((ppTrie)->nextTrie[index]) = calloc(1, sizeof(Trie));
        (ppTrie)->nextTrie[index]->count = 0;
        for (int i=0; i<26; i++){
            ((ppTrie)->nextTrie[index])->nextTrie[i] = NULL;

        }
    }
    return(insert(((ppTrie)->nextTrie[index]), word, z+1 ));
}

int numberOfOccurances(struct Trie *pTrie, char *word){
    for(int i =0; i<(strlen(word)); i++){
        if(pTrie->nextTrie[word[i]-'a']==NULL){
            return 0;
        }
        else
        pTrie = pTrie->nextTrie[word[i]-'a'];
    }
    return pTrie->count;
}


void deallocateTrie(struct Trie **pTrie){
    for(int i = 0; i<26; i++){
        if((*pTrie)->nextTrie[i]!=NULL){
            deallocateTrie(&((* pTrie)->nextTrie[i]));
        }
    }
    free(*pTrie);
    
}

int main(void)
{
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[5] = {"notaword", "ucf", "no", "note", "corg"};
    Trie *trie = calloc(1, sizeof(Trie));
    for (int f=0; f<5; f++){
        insert(trie, pWords[f], 0);

    }

    for (int i=0;i<5;i++){
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    deallocateTrie(&trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}