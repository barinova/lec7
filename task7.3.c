# include <stdio.h>
# include <string.h>
# include <stdlib.h>

struct NODE
{
	char word[256];
	unsigned int count;
	NODE *left;
	NODE *right;
};

NODE *makeTree(NODE *root,char *add)
{
	if(root==NULL)
	{
	root=(NODE*)malloc(sizeof(NODE));
	strcpy(root->word,add);
	root->count=0; 
	root->left=root->right=NULL;
	}
	else if(strcmp(root->word,add)>0)
	root->left=makeTree(root->left,add);
	else if(strcmp(root->word,add)<0)
	root->right=makeTree(root->right,add);
	return root;
}

void searchTree(NODE *node, char *str)
{
	if(node) {
	searchTree(node->left, str);
	if(strcmp(node->word, str) == 0)
		node->count++;
	searchTree(node->right, str);
	}
}

void printTree(NODE *node)
{
	if(node) {
	printTree(node->left);
	printf("%s %d\n",node->word, node->count);
	printTree(node->right);
	}
}

int main()
{
	int N,i = 0,j = 0, count=0; 
	char buf[256][256], c;
	FILE *fp;
	NODE *words;
	fp=fopen("words.txt","rt");
	if(!fp) {
		puts("File error!");
		return -1;
	}
	

	while(!feof(fp))
	{
		c = fgetc(fp);
		if(c == '\n')
		{
			buf[i][j] = '\0';		
			i++;
			j = 0;
		}
		else
			buf[i][j++] = c;
	}

	buf[i][j-1] = '\0';
	N = i;
	words=(NODE*)calloc(N,sizeof(NODE));
	if(!words) {
	puts("Memory error!");
	return -1;
	}
	
	i = 0;
	while(i != N + 1)
	{
		*makeTree(words,buf[i++]);
	}

	fclose(fp);
	for (i = 0; i < N; i++) 
		for (j = 0; j < N; j++) buf[i][j] = 0;

	fp=fopen("file.txt","rt");
	i = j = 0;
	while(!feof(fp))
	{
		c = fgetc(fp);
		if(c == ' ')
		{
			buf[i][j] = '\0';		
			i++;
			j = 0;
		}
		else
			buf[i][j++] = c;
	}
	buf[i][j-1] = '\0';
	N = i;

	i = 0;
	while(i != N + 1)
	{
		searchTree(words, buf[i++]);
	}
	printTree(words);
	free(words);
	//print(words,count);
	return 0;
}