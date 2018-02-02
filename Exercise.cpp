#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Word Position 
struct Position{
       int linenum;
       int colunum;
       struct Position *next;
       };
typedef struct Position *posptr;

// Word Struct
struct Treenode{
       char *word;
       struct Treenode *left;
       struct Treenode *right;
       posptr Posit;
       };
typedef struct Treenode *Treeptr;

// Hash Function
int calc_hash(char *str)
{
    int sum=0,n=0,b=1,i;
    n=strlen(str);
    for (i=0;i<=n-1;i++)
    {
        sum=sum+b*str[n-i-1];
        b=(b*256)%1031;
        }
        sum=sum%1031;
        return sum;
        }

// Reading the key 
char * read_key(FILE *f)
{
     char keyread[20],*keyword;
     
     fscanf(f,"%s",keyread);
     keyword = strdup(keyread);
     
     return keyword;
}

posptr treeSearch(Treeptr node,char* keyword)
{
	bool Searchflag=true;

	while(Searchflag)
	{
		if (node == NULL)
		{
			Searchflag=false;
		}
		else if (strcmp(node->word,keyword) == 0)
		{
			Searchflag=false;
		}
		else if (strcmp(node->word,keyword) < 0)
		{
			node=node->left;
		}
		else
		{
			node=node->right;
		}
	}
		return node->Posit;
}

int main (void)
{
    char *keyword;
    char wordreading[21];
    int key_hash,c,i,line=0,column=1,hash;
    Treeptr hash_table[1031],NextWord,temp;
    posptr thesi,Keyposition,current,temp1;
    bool flag1;
    
    FILE *f;
    //f=fopen("test.txt","rt");
    f = stdin ;
    if (f == NULL)
    {
          printf("FILE NOT FOUND\n");
          return 1;
    }
    //Reading Key 
    keyword=read_key(f);
    key_hash= calc_hash(keyword);
    for(i=0; i<1031 ; i++) hash_table[i]= NULL ;
    while ((c=getc(f)) != '\n') ;

   //Read rest of the Words 
     c=getc(f);
     while(c!=EOF)
      {
          line++;
          column=1;
          while (c !='\n')
          {
               i=0;
               while((c!= ' ') && (c!='\n'))
               {
                  wordreading[i]=c;
                  i++;
                  c=getc(f);
               }
                  wordreading[i]='\0';         
                  hash=calc_hash(wordreading);
                  //Create the word 
                  NextWord= (Treeptr)malloc(sizeof(struct Treenode));
                  NextWord->word= (char*)malloc(21*sizeof(char));
                  NextWord->word=strdup(wordreading);
                  NextWord->left=NULL;
                  NextWord->right=NULL;
                  
                  
                   //Inserting in correct node 
                   if (hash_table[hash]== NULL)
                     {
                         hash_table[hash]=NextWord;
                        // Create position for new word 
                        thesi = (posptr) malloc(sizeof(struct Position));
                        thesi->linenum= line;
                        thesi->colunum= column;
                        thesi->next = NULL ;
                        NextWord->Posit=thesi;
                     }
                     
                     else
                      {
                             if (strcmp(hash_table[hash]->word,NextWord->word) == 0)
		                        {
                                  thesi=(posptr)malloc(sizeof(struct Position));
                                  thesi->linenum=line;
                                  thesi->colunum=column;
                                  temp1=hash_table[hash]->Posit;
                                  while(temp1->next != NULL)
                                  {
                                    temp1=temp1->next;
                                  }
                                  temp1->next=thesi;
                                  thesi->next=NULL;
                                }
                            else
                            {
                                temp=hash_table[hash];
                                while(temp != NULL)
                                {
                                  if (strcmp(NextWord->word,temp->word) < 0)
                                  {
                                    if(temp->left == NULL)
                                    {
                                     temp->left=NextWord;
                                     thesi=(posptr)malloc(sizeof(struct Position));
                                     thesi->linenum=line;
                                     thesi->colunum=column;
                                     thesi->next=NULL;
                                     temp->left->Posit=thesi;
                                     break;
                                    }
                                     temp=temp->left;
                                  }
			                     else if(strcmp(NextWord->word,temp->word) > 0)
			                     {
                                   if (temp->right == NULL)
                                    {
                                     temp->right=NextWord;
                                     thesi=(posptr)malloc(sizeof(struct Position));
                                     thesi->linenum=line;
                                     thesi->colunum=column;
                                     thesi->next=NULL;
                                     temp->right->Posit=thesi;
                                     break;
                                    }
                                     temp=temp->right;
                                  }
			                     else
			                     {
                                     thesi=(posptr)malloc(sizeof(struct Position));
                                     thesi->linenum=line;
                                     thesi->colunum=column;
                                     thesi->next=NULL;
                                     temp1=temp->Posit;
                                     while(temp1->next !=NULL)
                                     {
                                      temp1=temp1->next;
                                     }
                                     temp1->next=thesi;
                                     break;                                
                                 }
                               }
                           }
                     }
                     column=column+i+1;
                     for(i=0;i<=20;i++) wordreading[i]=' ';
                     if(c == ' ') c=getc(f);
                   }               
                 c=getc(f); 
      }                           
			                     
		  //Keyword search 
		  Keyposition=treeSearch(hash_table[key_hash],keyword);

		  //PRINTING
          printf("%s\n",keyword);
		  if (Keyposition == NULL)
		  {
		    printf("NOT FOUND\n");
		  }
		  else
		  {
			  for(current=Keyposition; current != NULL ; current=current->next)
				  printf("(%d,%d)\n", current->linenum, current->colunum);
		  }
  return 0;
} 
    
    
    
    
    
