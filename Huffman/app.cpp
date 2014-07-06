#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#define SIZE 50000
using namespace std;
int NodeNumber;
int Loc;
typedef struct Katarým
{
	char * Root;//root
	int *rpt;//repeat
} ktr;
typedef struct Node
{
	string Name;
	int Times;
	Node *left;
	Node *right;
}Node;
typedef struct Table
{
	char Letter;
	string Huffmancode;
}Table;
Node * CreateNode()
{
	Node *root=(Node *)calloc(1,sizeof(Node));
	root->left=root->right=NULL;
	return(root);
}
Node * CreateNode(ktr *s,int f)
{
	Node *root=(Node *)calloc(1,sizeof(Node));
	root->Name=s->Root[f];
	root->Times=s->rpt[f];
	root->left=root->right=NULL;
	return(root);
}
void PrintNodes(const Node* nodes)
{
	FILE *cout;
	if((cout=fopen("Output.txt","a"))==NULL)
		exit (0);
	NodeNumber=0;
	int c=0;int sum;
	for(c=0;c<26;c++)
		if(nodes[c].Times>0 && nodes[c].Times<SIZE)
		{
			NodeNumber++;
			sum=nodes[c].Times;
			char Name[SIZE];
			strncpy(Name,&nodes[c].Name[0],SIZE);fprintf(cout,"%d. Node is ",c+1);fprintf(cout,"%s",Name);fprintf(cout," Repeated :%d times\n",sum);
		}
	fclose(cout);
}
void FindRepeats (ktr *s,char Kat[SIZE],Node * nodes)
{
	int c=0;
	for( ;Kat[c]!=0;c++)
		s->rpt[((int)(Kat[c]))-65]++;
	int f ,t=0;
	for(c=0;c<26;c++)
		if(s->rpt[c]>0 && s->rpt[c]<SIZE)
		{
			nodes[t++]=*(CreateNode(s,c));
		}
	PrintNodes(nodes);
} 
void FindMin(Node* Nodes)
{
	FILE *cout;
	if((cout=fopen("Output.txt","a"))==NULL)
		exit (0);
	int c=0 ,min=SIZE,firstminloc=-1, SecondminLoc=-1;
	for(;c<26;c++)
		if((Nodes[c].Times>0 && Nodes[c].Times<min))
		{
			min=Nodes[c].Times;
			firstminloc=c;
		}
	min=SIZE;
	for(c=0;c<26;c++)
		if((Nodes[c].Times>0 && Nodes[c].Times<min)&& c!=firstminloc)
		{
			min=Nodes[c].Times;
			SecondminLoc=c;
		}
	if(SecondminLoc==-1 || firstminloc==-1)//FOR AA,aaaaaa,bbbbb,ccccc etc;
	{
		Loc=firstminloc;
		return;
	}
	Node *TempNode=CreateNode();
	Node *frst=CreateNode();
	Node *scnd=CreateNode();
	*frst=Nodes[firstminloc];
	*scnd=Nodes[SecondminLoc];
	TempNode->left=frst;
	TempNode->right=scnd;
	TempNode->Name= Nodes[firstminloc].Name+Nodes[SecondminLoc].Name;
	TempNode->Times=Nodes[firstminloc].Times+Nodes[SecondminLoc].Times;
	Nodes[firstminloc]=*TempNode;
	Nodes[SecondminLoc].Times=-1;
	fprintf(cout,"------AFTER A STEP------------\n");
	fprintf(cout,"%d<->%d Allocated\n",firstminloc+1,SecondminLoc+1);
	fclose(cout);
	PrintNodes(Nodes);
	Loc=firstminloc;
}
string FindHashCode(char s,Node *root,string * path)
{	
	Node *c=root;
	if(s == c->Name[0] && c->Name.length()==1)
	{
		return ("b");
	}
	if(c->left!=NULL)
		if(FindHashCode(s,c->left,path)=="b")
		{
			(*path)+="0";
			return("b");
		}
	if(c->right!=NULL)
		if(FindHashCode(s,c->right,path)=="b")
			{
				(*path)+="1";
				return("b");
			}
	return(*path);
}
const void CreateHashCode(char katar[],string &hash,Table *tab)
{
	FILE *cout;
	if((cout=fopen("Output.txt","a"))==NULL)
		exit (0);
	Table *first=tab;
	int c=0;
	for(c=0 ;c<strlen(katar);c++)
		for(int s=0;first!=NULL;s++)
			if(katar[c]==first[s].Letter)
			{
				hash+=first[s].Huffmancode;
				break;
			}
		if(hash=="")
			hash="\n\nOnly One Node Exist.";
		else{
			fprintf(cout,"\n\n->HuffmanCode:#",katar[c]);
			int l;
			for(l=0;l<hash.length();l++){
				if(l%100==0) fprintf(cout,"\n");fprintf(cout,"%c",hash[l]);}
			fprintf(cout,"\n#\n");
			}
		fclose(cout);
}
Table * PHCFEL(string katar,Node *root)// Print Hash Code For Each Letters
{
	FILE *cout;
	if((cout=fopen("Output.txt","a"))==NULL)
		exit (0);
	int c=0;
	string p;
	string *path=&p;
	Table * tab=(Table *)calloc(katar.length(),sizeof(Table));
	tab->Huffmancode="";
	for(; c<katar.length();c++)
	{
		p="";
		FindHashCode(katar[c],root,path);
		tab[c].Letter=katar[c];
		reverse(p.begin(),p.end());//reverse path 111011->110111 its huffman algorithm
		tab[c].Huffmancode=p;
		fprintf(cout,"%c code:#",tab[c].Letter);
		for(int m=0;m<p.length();m++)
			fprintf(cout,"%c",p[m]);
		fprintf(cout,"#\n");
	}
	return(tab);
}
int main ()
{
	FILE *cin;
	if((cin=fopen("Input.txt","rb"))==NULL)
		exit(0);
	char Katar[SIZE];
	fscanf(cin,"%s",Katar);
	fclose(cin);
	string Hash;	int t=0;
	Table * tab;
	/*do{
	printf("Enter String To Encoding(max 80000)\n");
	gets(Katar);
	}while(strlen(Katar)>SIZE);*/
	FILE *cout;
	if((cout=fopen("Output.txt","w"))==NULL)
		exit (0);
	fclose(cout);
	if((cout=fopen("Output.txt","a"))==NULL)
		exit (0);
	Katar[strlen(Katar)+1]=0;	strupr(Katar);
	ktr* s=(ktr *) malloc (sizeof(ktr));
	s->Root=(char *)calloc(SIZE,sizeof(char));
	s->rpt=(int *)calloc(26,sizeof(int));
	Node * Nodes=(Node *) calloc (26,sizeof(Node));
	for(t;t<26;t++)
	{
		s->Root[t]=((char)(t+65));
		s->rpt[t]=0;
	}
	FindRepeats(s,Katar,Nodes);
	do{
	FindMin(Nodes);
	}while(NodeNumber!=1);fprintf(cout,"\n\nString:%s\n",Katar);
	tab=PHCFEL(Nodes[Loc].Name,&Nodes[Loc]);//Print Hash Code For Each Letters
	CreateHashCode(Katar,Hash,tab);
	
	free(Nodes);
	free(s);
	fprintf(cout,"\t Normal Size=%d bits *With Huffman code:%d bits\t % Pressing:%4.2lf\n",8*strlen(Katar),Hash.length(),(Hash.length()/(double)(8*strlen(Katar)))*100);
	fclose(cout);
	
}