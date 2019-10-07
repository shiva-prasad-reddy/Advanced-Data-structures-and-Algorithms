#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct node 
{
	struct node *(array[26]);
};

struct node *newNode()
{
	return (struct node *)calloc(1, sizeof(struct node));
}

struct node *build(char *str, struct node *trie)
{
	if(str[0] != '\0')
	{
		int index = tolower(str[0]);
		index = index - 97;
		if(trie == NULL)
			trie = newNode();
		(trie->array)[index] = build(str+1, (trie->array)[index]);
	}
	return (trie == NULL? newNode() : trie);
}

int search(char *prefix, struct node *trie)
{
	int index = tolower(prefix[0]);
	index = index - 97;
	if( (trie->array)[index] )
	{
		printf("%c\n", prefix[0]);
		if(prefix[1] == '\0') return 1;
		return 1 && search(prefix+1, (trie->array)[index]);
	}
	else
		return 0;
}

int main()
{

	// ' ' --> 32
	// 'a' --> 97
	// 'A' --> 65

	struct node *trie = NULL;
	char str[20];
	char *temp;

	int i;
	int choice;
	do
	{
		printf("\nSelect an option :: \n1.Add a string to trie\n2.Search a prefix\n3.Exit\n");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("\nString :: ");
				scanf("%s", str);
				temp = str;
				while(temp[0] != '\0')
				{
					trie = build(temp, trie);
					temp++;
				}
				break;

			case 2:
				printf("\nPrefix :: ");
				scanf("%s", str);
				if(search(str, trie)) printf("[ %s ] prefix found\n", str);
				else printf("[ %s ] prefix not found\n", str);
				break;

			case 3:
				break;

			default:
				break;
		}


	} while(choice != 3);

	return 0;
}

/*
				for(i=0; i<26; i++)
				{
					printf("[%d --> %c --> %p]\n", i, i+97, (trie->array)[i] );
				}	
				for(i=0; i<26; i++)
				{
					printf("[%d --> %c --> %p]\n", i, i+97, (  ((trie->array)[0])->array)[i] );
				}	
*/