#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

struct stack
{ char elem; struct stack *next; };
struct Nstack
{ float elem; struct Nstack *next; };
float process(char *out, struct stack *stk, int *l);
int reversePolish(int *l, char *in, char *out, struct stack* stk, int* brkt);
int CheckUrPrivilege(char op);
int CheckNum(char symb);
int CheckOp(char symb, int i, char* in);
int CheckTrig(char symb);
int CheckFunc(char *str, int i);
int CheckFuncDos(char str);
int CheckInvTrig(char *str, int i);
int CheckLog(char *str, int i);
char gettop(struct stack* stk);
char gettop(struct Nstack* stk);
struct stack *push(struct stack* top, char ch);
char pop(struct stack** top);
struct Nstack *pushN(struct Nstack* top, float num);
float poppiN(struct Nstack** top);
void add(struct Nstack *stk);
void sub(struct Nstack *stk);
void mult(struct Nstack *stk);
void div(struct Nstack *stk);
void power(struct Nstack *stk);
struct Nstack *fact(struct Nstack *stk);

int main() 
{
  struct stack *stk=NULL;
  char in[50];
  char out[50];
  int l[50];
  int brkt=0;
  float result=0;
  do {
	  brkt=0;
	  printf("Enter your expression: ");
	  fflush(stdin);
	  gets(in);
	  reversePolish(l,in,out,stk,&brkt);
	  if (brkt!=0)
	  {
		  if (brkt>1)
			printf("Missing %d closing brackets\n", brkt);
		  else if (brkt==1)
			  printf("Missing 1 closing bracket\n");
	      else if (brkt==-1)
			  printf("Missing 1 opening bracket\n");
		  else if (brkt<-1)
			  printf("Missing %d opening brackets\n", brkt);
	  }
	  else if (brkt==0)
	  {
		  result=process(out,stk,l);
		  if(floorf(result)==result)
			printf("%.0f\n",result);
		  else printf("%.5f\n",result);
	  }
		printf("Anything else, master?(y/n)\n");
  }
  while(getchar()!='n');
  return 0;
}

int reversePolish(int *l, char *in, char *out, struct stack* stk, int* brkt)
{
  int i=0;
  int k=0;
  int n=0;
  int length=0;
  int e=0;
  char own[50];
  char temp;
  *brkt=0;
  while(in[i]!='\0')
  { 
	if(CheckOp(in[i],i, in)==1)
	{
		if(CheckNum(in[i-1])==1)
		{
			l[e]=length;
			length=0;
			e++;
		}
		if(in[i]=='(')
		{
			*brkt+=1;
			stk=push(stk, '(');
		}
		else if(in[i]==')')
		{
			*brkt-=1;
			if(stk!=NULL)
			{
			    while((stk->elem)!='(')
				out[n++]=pop(&stk);
				pop(&stk);
			}
			else return 0;
		}
		else if(stk==NULL)
		{
			if(CheckUrPrivilege(in[i])!=4)
				stk=push(stk,in[i]);
			else if(CheckUrPrivilege(in[i])==4)
			{
				if(in[i]!='a' && in[i]!='l')
				{
				    if(CheckFunc(in,i)==1)
						temp='I';
					else if(CheckFunc(in,i)==2)
						temp='O';
					else if(CheckFunc(in,i)==2)
						temp='A';
					else if(CheckFunc(in,i)==2)
						temp='T';
					i+=2;
				}
				else if(in[i]=='l')
				{
					if(CheckLog(in,i)==1)
						temp='G';
					else temp='N';
					i++;
				}
				else if(in[i]=='a')
				{
					if(CheckInvTrig(in,i)==1)
						temp='B';
					else if(CheckInvTrig(in,i)==2)
						temp='C';
					else if(CheckInvTrig(in,i)==3)
						temp='D';
					else if(CheckInvTrig(in,i)==4)
						temp='E';
					i+=5;
				}
				stk=push(stk,temp);
			}
		}
		else if(CheckUrPrivilege(stk->elem)<CheckUrPrivilege(in[i]) && CheckUrPrivilege(in[i])!=4)
			stk=push(stk,in[i]);
		else if(CheckUrPrivilege(stk->elem)<CheckUrPrivilege(in[i]) && CheckUrPrivilege(in[i])==4)
		{
			if(in[i]!='a' && in[i]!='l')
			{
				if(CheckFunc(in,i)==1)
					temp='I';
				else if(CheckFunc(in,i)==2)
					temp='O';
				else if(CheckFunc(in,i)==2)
					temp='A';
				else if(CheckFunc(in,i)==2)
					temp='T';
				i+=2;
			}
			else if(in[i]='l')
			{
				if(CheckLog(in,i)==1)
					temp='G';
				else temp='N';
				i++;
			}
			else if(in[i]='a')
			{
				if(CheckInvTrig(in,i)==1)
					temp='B';
				else if(CheckInvTrig(in,i)==2)
					temp='C';
				else if(CheckInvTrig(in,i)==3)
					temp='D';
				else if(CheckInvTrig(in,i)==4)
					temp='E';
				i+=5;
			}
			stk=push(stk,temp);
		}
		else 				 
		{
			while((stk!=NULL)&&(CheckUrPrivilege(stk->elem)>=CheckUrPrivilege(in[i])))
				out[n++]=pop(&stk);
			stk=push(stk,in[i]);
		}
	}
	else if(CheckNum(in[i])==1)
	{
		length++;
		out[n++]=in[i];
		if(in[i+1]=='\0')
			l[e]=length;
	}
	else if(in[i]=='.')
		out[n++]=in[i];
	else if(in[i]=='F')
	{
		printf("Enter your function: ");
		gets(own);
		n=reversePolish(l,own,out,stk,*&brkt);
	}
	else if(in[i]>='a' && in[i]<='z')
		out[n++]=in[i];
		i++; 
    }   
	while(stk!=NULL)
		out[n++]=pop(&stk);
	out[n]='\0';
	return n;
}

float process(char *out, struct stack *stk, int *l)
{
	int k=0;
	float res=0;
	float a=0;
	float b=0;
	float own=0;
	int e=0;
	int cifr=1;
	int m=0;
	int raz=0;
	int s=0;
	int godHelpMe=0;
	float AAA=0;
	struct Nstack *num=NULL;
	float symbols[26];
	for(int s=0; s<26; s++)
		symbols[s]=FLT_MIN;
	while (out[k]!='\0')
	{
		if(CheckNum(out[k])==1 && cifr==l[e])
		{
			if(cifr==1)
			{
				num=pushN(num,out[k]-48);
				e++;
			}
			else
			{
				godHelpMe=k;
				//starting from zero because the cycle is enterred at the number's last digit
				for(m=0;m<cifr;m++)
				{
					AAA=out[godHelpMe]-48;
					b=b+AAA*pow(10.0,m);
					godHelpMe--;
				}
				num=pushN(num,b);
				cifr=1;
				e++;
				b=0;
			}
		}
		else if(CheckNum(out[k])==1 && cifr!=l[e])
			cifr++;
		else if(out[k]=='.')
		{
			godHelpMe=k-cifr+1;
			while(out[godHelpMe]!='.')
			for(m=cifr-2;m>=0;m--)
			{
				AAA=out[godHelpMe]-48;
				b=b+AAA*pow(10.0,m);
				godHelpMe++;
			}
			for(m=1;m<=(l[e]-cifr+1);m++)
			{
				AAA=out[godHelpMe+1]-48;
				b=b+AAA*pow(10.0,-m);
				godHelpMe++;
				raz++;
			}
			k=k+raz;
			num=pushN(num,b);
			e++;
			b=0;
			cifr=1;
			raz=0;
		}
		else if(CheckOp(out[k],k,out)==1 || CheckFuncDos(out[k])==1)
			stk=push(stk,out[k]);
			  else if(out[k]>='a' && out[k]<='z')
			  {
				  if(symbols[out[k]-97]==(FLT_MIN))
				  {
					 printf("Enter %c: ", out[k]);
					 scanf("%f", &own);
					 symbols[out[k]-97]=own;
				  }
				  else own=symbols[out[k]-97]; 
				  num=pushN(num,own);
			  }
			  if(stk!=NULL)
			  {
				  if(CheckOp(gettop(stk),k,out)!=0)
				  {
					if(gettop(stk)=='+')
						add(num);
					else if(gettop(stk)=='-')
						sub(num);
					else if(gettop(stk)=='*')
						mult(num);
					else if(gettop(stk)=='/')
						div(num);
					else if(gettop(stk)=='^')
						power(num);
					else if(gettop(stk)=='!')
						num=fact(num);
					pop(&stk);
				  }
				  else if(CheckFuncDos(gettop(stk))==1)
				  {
					if(gettop(stk)=='I')
					{
						a=poppiN(&num);
						num=pushN(num,sin(a));
					}
					else if(gettop(stk)=='O')
					{
						a=poppiN(&num);
						num=pushN(num,cos(a));
					}
					else if(gettop(stk)=='A')
					{
						a=poppiN(&num);
						num=pushN(num,tan(a));
					}
					else if(gettop(stk)=='T')
					{
						a=poppiN(&num);
						num=pushN(num,1/tan(a));
					}
					else if(gettop(stk)=='B')
					{
					    a=poppiN(&num);
					    num=pushN(num,asin(a));	
					}
					else if(gettop(stk)=='C')
					{
					    a=poppiN(&num);
					    num=pushN(num,acos(a));	
					}
					else if(gettop(stk)=='D')
					{
					    a=poppiN(&num);
					    num=pushN(num,atan(a));	
					}
					else if(gettop(stk)=='E')
					{
					    a=poppiN(&num);
					    num=pushN(num,asin(a/sqrt(1+pow(a,2))));	
					}
					else if(gettop(stk)=='G')
					{
					    a=poppiN(&num);
						num=pushN(num,log10(a));	
					}
					else if(gettop(stk)=='N')
					{
					    a=poppiN(&num);
						num=pushN(num,log(a));	
					}
					pop(&stk);
				  }
			  }
		    k++;
	}
	res=poppiN(&num);
	return(res);
}

void add(struct Nstack *stk)
{
	float sum=poppiN(&stk)+poppiN(&stk);
	pushN(stk, sum);
}
void mult(struct Nstack *stk)
{
	float res=poppiN(&stk)*poppiN(&stk);
	pushN(stk, res);
}
void div(struct Nstack *stk)
{
	float a,b;
	a=poppiN(&stk);
	b=poppiN(&stk);
	float res=b/a;
	pushN(stk, res);
}
void sub(struct Nstack *stk)
{
	float a,b;
	a=poppiN(&stk);
	b=poppiN(&stk);
	float res=b-a;
	pushN(stk, res);
}
void power(struct Nstack *stk)
{
	float a,b;
	a=poppiN(&stk);
	b=poppiN(&stk);
	float res=pow(b,a);
	pushN(stk, res);
}
struct Nstack *fact(struct Nstack *stk)
{
	float res=1;
	int i=0;
	float n=poppiN(&stk);
	for(i=1; i<=n; ++i)
		res *= i;
	stk=pushN(stk, res);
	return stk;
} 
int CheckUrPrivilege(char op)
{
	switch(op)
	{
		case '(':
			return 1;
			break;
		case '+':
	    case '-': 
			return 2;
			break;
		case '*':
	    case '/':
			return 3;
			break;
		case 's':
		case 'c':
		case 't':
		case 'a':
		case 'l':
			return 4;
			break;
			case '^':
		case '!':
			return 5;
			break;
	}
}

int CheckNum(char symb)
{
	if(symb >= '0' && symb <= '9')
		return 1;
	else
		return 0;
}

int CheckOp(char symb, int i, char* in)
{
	if(symb == '(' || symb == ')' || symb == '+' || symb == '-' || symb == '*' || symb == '/' || symb == '^'|| symb == '!' || CheckFunc(in,i)!=0 || CheckInvTrig(in, i)!=0 || CheckLog(in,i)!=0)
		return 1;
	return 0;
}


int CheckTrig(char symb)
{
	if(symb=='s' || symb=='c' || symb=='t')
		return 1;
	return 0;
}
int CheckFunc(char *str, int i)
{
	if(str[i]=='s' && str[i+1]=='i')
		return 1;
	else if(str[i]=='c' && str[i+1]=='o') 
		return 2;
	else if(str[i]=='t' && str[i+1]=='a') 
		return 3;
	else if(str[i]=='c' && str[i+1]=='t') 
		return 4;
	return 0;
}

int CheckFuncDos(char str)
{
	if(str=='I' || str=='O' || str=='A' || str=='T' || str=='B' || str=='C' || str=='D' || str=='E' || str=='G' || str=='N')
		return 1;
	return 0;
}

int CheckInvTrig(char *str, int i)
{
	if(str[i]=='a')
	{
		if(str[i+3]=='s')
		return 1;
		else if(str[i+4]=='o') 
		return 2;
		else if(str[i+3]=='t') 
		return 3;
		else if(str[i+4]=='t') 
		return 4;
	}
	return 0;
}

int CheckLog(char *str, int i)
{
	if(str[i]=='l')
	{
		if(str[i+1]=='g')
		return 1;
		else if(str[i+1]=='n')
		return 2;
	}
	return 0;
}
struct stack *push(struct stack* top, char ch)
{
	struct stack *temp;
	if((temp=(struct stack*)malloc(sizeof(struct stack)))==NULL)
	{
		printf("Insufficient memory");
		return(0);
	}
	temp->elem=ch;
	temp->next=top;
	return temp;
}

char pop(struct stack** top)
{
	struct stack *temp;
	char ch;
	if(*top==NULL)
		return '\0';
	temp=*top;
	ch=temp->elem;
	*top=temp->next;
	free(temp);
	return ch;
}

struct Nstack *pushN(struct Nstack* top, float num)
{
	struct Nstack *temp;
	temp=(struct Nstack*)malloc(sizeof(struct Nstack));
	if((temp=(struct Nstack*)malloc(sizeof(struct Nstack)))==NULL)
	{
		printf("Insufficient memory");
		return(0);
	}
	temp->elem=num;
	temp->next=top;
	return temp;
}

float poppiN(struct Nstack** top)
{
	struct Nstack *temp;
	float num;
	temp=*top;
	num=temp->elem;
	*top=temp->next;
	free(temp);
	return num;
}

char gettop(struct stack* stk)
{
	return(stk->elem);
}

 
