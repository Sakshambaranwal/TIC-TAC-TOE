#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
char arr[3][3]={32,32,32,32,32,32,32,32,32};
int count=0;
char p1[20],p2[20];
int matches=0;
FILE *data;
main()
{
	int p;
	/*
	 0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       A = Light Green
    3 = Aqua        B = Light Aqua
    4 = Red         C = Light Red
    5 = Purple      D = Light Purple
    6 = Yellow      E = Light Yellow
    7 = White       F = Bright White
	*/
	system("COLOR E4");
	printf("\t\t\t\t\tWELCOME TO  TIC-TAC-TOE GAME\n\n\n");
	data=fopen("tictactoe.txt","w+");
	Sleep(1000);
	printf("\t\t\t\t\tEnter player choice--\n\n");
	printf("\t\t\t\t\t1. Single Player\n");
	printf("\t\t\t\t\t2. Mullti Player\n\t\t\t\t\t");
	scanf("%d",&p);
	fflush(stdin);
	system("cls");
	if(p==1)
	    single();
	else if(p==2)
		multi();
    else
	{
    printf("Enter valid choice\n");
    fflush(stdin);
    main();
    exit(1);
	}
	getch();
}
single()
{
	int i,j,ch,lev;
	char c;
    printf("\t\t\t\t\tEnter your name--\n\t\t\t\t\t");
	gets(p1);
	printf("\n\n\t\t\t\t\tSelect level--\n");
	printf("\t\t\t\t\t1. Moderate\n");
	printf("\t\t\t\t\t2. Pro\n\t\t\t\t\t");
	scanf("%d",&lev);
	fprintf(data,"MATCH       COMPUTER       %s\n\n",p1);
	resingle:
	matches++;
	print();	
	for(i=1;i<=9;i++)
	{
		if(i%2!=0 ^ matches%2==0)
		{
			gotoxy(70,1);
			printf("Thinking...\n");
			Sleep(2500);
			if(lev==1)
			ch=compturn1();
			else
			ch=compturn2();
		}
		else
		{
			gotoxy(70,1);
			printf("Your turn--");
			gotoxy(70,2);
			printf("Enter your choice");
			gotoxy(70,3);
	        repeat:
			scanf("%d",&ch);
		}
    	for(j=1;j<=9;j++)
		{
			if((ch==j && arr[(j-1)/3][(j-1)%3]!=32)||ch>9||ch<1){
			gotoxy(70,4);
			printf("Enter valid choice\n");
			gotoxy(70,5);
       	    goto repeat;}	
		}
		input(ch);
		print();
		gotoxy(70,3);
		if(check()==1)
		{
			printf("YOU LOSE.\n\n");
			fprintf(data,"  %d            1             0\n\n",matches);
			break;
		}
		else if(check()==2)
		{
			printf("YOU WON.\n\n");
			fprintf(data,"  %d            0             1\n\n",matches);
			break;
		}
		else if(check()==0)
		{
			printf(" GAME DRAW.\n\n");
			fprintf(data,"  %d            0             0\n\n",matches);
			break;
    	}			
	}
	Sleep(1000);
	gotoxy(70,5);
	printf("ENTER '0' TO QUIT GAME AND '1' TO CONTINUE---");
    scanf("%d",&ch);
    if(ch==0){
    fclose(data);
    data=fopen("tictactoe.txt","r");
    c=fgetc(data);
   	gotoxy(70,7);
    while(c!=EOF)
    {
    	if(c=='\n')
    	{
    		printf("%c\t\t\t\t\t\t\t\t     ",c);
        	c=fgetc(data);
        	continue;
		}
    	printf("%c",c);
    	c=fgetc(data);
	}
	fclose(data);
	getch();
   	exit(1);}
    else
   	{
    again();
   	goto resingle;
    }
}
compturn1()
{
	int i,j;
    for(i=0;i<=2;i++)
    {
    	if(arr[i][0]==arr[i][1] && arr[i][0]!=32 && arr[i][2]==32)
    	return (i*3)+3;
    	else if(arr[i][1]==arr[i][2] && arr[i][1]!=32 && arr[i][0]==32)
    	return (i*3)+1;
    	else if(arr[i][2]==arr[i][0] && arr[i][2]!=32 && arr[i][1]==32)
    	return (i*3)+2;
    	else if(arr[0][i]==arr[1][i] && arr[0][i]!=32 && arr[2][i]==32)
    	return (i+7);
    	else if(arr[1][i]==arr[2][i] && arr[1][i]!=32 && arr[0][i]==32)
    	return (i+1);
    	else if(arr[2][i]==arr[0][i] && arr[2][i]!=32 && arr[1][i]==32)
    	return (i+4);
	}
	if(arr[0][0]==arr[1][1] && arr[0][0]!=32 && arr[2][2]==32)
    return 9;
    else if(arr[1][1]==arr[2][2] && arr[1][1]!=32 && arr[0][0]==32)
   	return 1;
   	else if(arr[2][2]==arr[0][0] && arr[2][2]!=32 && arr[1][1]==32)
   	return 5;
   	else if(arr[0][2]==arr[1][1] && arr[0][2]!=32 && arr[2][0]==32)
   	return 7;
   	else if(arr[1][1]==arr[2][0] && arr[1][1]!=32 && arr[0][2]==32)
   	return 3;
   	else if(arr[2][0]==arr[0][2] && arr[2][0]!=32 && arr[1][1]==32)
   	return 5;
   	else
   	{
   		srand(time(NULL));
   		while(1)
   		{
			int k=rand()%9+1;
			if(arr[(k-1)/3][(k-1)%3]==32)
		        return k;
		    else 
		        continue;
    	}
			
   	}
}
multi()
{
	int i,j,k,ch;
	char c;
	printf("\t\t\t\t\tEnter player 1 name--\n\t\t\t\t\t");
	gets(p1);
	printf("\t\t\t\t\tEnter player 2 name--\n\t\t\t\t\t");
	gets(p2);
	fprintf(data,"MATCH       %s       %s\n\n",p1,p2);
	remulti:
    matches++;
	print();
	for(i=1;i<=9;i++)
	{
		if(i%2!=0 ^ matches%2==0)
		{
			printf("\n");
	    	gotoxy(70,1);
			for(j=0;j<strlen(p1);j++)
			printf("%c",p1[j]);
		}
		else
		{
			printf("\n");
	    	gotoxy(70,1);
			for(j=0;j<strlen(p2);j++)
			printf("%c",p2[j]);
		}
		printf("'s turn--\n");
		gotoxy(70,2);
		printf("Enter your choice\n");
		gotoxy(70,3);
		repeat:
		scanf("%d",&ch);
		for(k=1;k<=9;k++)
		{
			if((ch==k && arr[(k-1)/3][(k-1)%3]!=' ')||ch>9||ch<1){
	    	gotoxy(70,4);
			printf("Enter valid choice\n");
	    	gotoxy(70,5);
       	    goto repeat;}	
		}
		input(ch);
		print();
		if(check()==1)
		{
			strupr(p1);
           	printf("\n");
	    	gotoxy(70,3);
           	for(j=0;j<strlen(p1);j++)
           	printf("%c",p1[j]);
            printf("  WON.\n\n");
            fprintf(data,"  %d          1          0\n\n",matches);
            break;
		}
		else if(check()==2)
		{
     		strupr(p2);
           	printf("\n");
           	gotoxy(70,3);
           	for(j=0;j<strlen(p1);j++)
           	printf("%c",p2[j]);
            printf("  WON.\n\n");
            fprintf(data,"  %d          0          1\n\n",matches);
            break;
		}
		else if(check()==0)
		{
	    	gotoxy(70,3);
			printf(" GAME DRAW.\n\n");
			fprintf(data,"  %d          0          0\n\n",matches);
			break;
    	}
	}
	Sleep(1000);
	gotoxy(70,5);
    printf("ENTER '0' TO QUIT GAME AND '1' TO CONTINUE---");
    scanf("%d",&ch);
    if(ch==0){
	fclose(data);
    data=fopen("tictactoe.txt","r");
    c=fgetc(data);
    gotoxy(70,7);
    while(c!=EOF)
    {
    	if(c=='\n')
    	{
    		printf("%c\t\t\t\t\t\t\t\t     ",c);
        	c=fgetc(data);
        	continue;
		}
    	printf("%c",c);
    	c=fgetc(data);
	}
	fclose(data);
	getch();
    exit(1);}
   	else
   	{
     	again();
       	goto remulti;
    }
}
print()
{
	system("cls");
	printf("\t\t\t   TIC TAC TOE   \n\n\n\n\n\t\t\t");
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
		printf(" %c  ",arr[i][j]);
		if(j<2)
		printf("%c  ",186);
	    }
		if(i<2)	
    printf("\n\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t\t\t",205,205,205,205,206,205,205,205,205,205,205,206,205,205,205,205);
	}
	gotoxy(90,25);
	printf("-created by-SAKSHAM KUMAR");
}
input(int c)
{
	int i;
	for(i=1;i<=9;i++)
	{
		if(c==i){
		if(count%2==0 ^ matches%2==0)
          arr[(i-1)/3][(i-1)%3]='X';
	    else
	      arr[(i-1)/3][(i-1)%3]='O';}
	}
	count++;
}
check()
{
	int i,j,filled=0;
	for(i=0;i<=2;i++){
	if((arr[i][0]==arr[i][1] && arr[i][1]==arr[i][2] && arr[i][2]=='X') ||
	   (arr[0][i]==arr[1][i] && arr[1][i]==arr[2][i] && arr[2][i]=='X') ||
	   (arr[0][0]==arr[1][1] && arr[1][1]==arr[2][2] && arr[2][2]=='X') ||
	   (arr[0][2]==arr[1][1] && arr[1][1]==arr[2][0] && arr[2][0]=='X'))
    return 1;
    else if((arr[i][0]==arr[i][1] && arr[i][1]==arr[i][2] && arr[i][2]=='O') ||
	   (arr[0][i]==arr[1][i] && arr[1][i]==arr[2][i] && arr[2][i]=='O') ||
	   (arr[0][0]==arr[1][1] && arr[1][1]==arr[2][2] && arr[2][2]=='O') ||
	   (arr[0][2]==arr[1][1] && arr[1][1]==arr[2][0] && arr[2][0]=='O'))
	return 2;
    }
    for(i=0;i<=2;i++)
    for(j=0;j<=2;j++)
    if(arr[i][j]!=32)
    filled++;
    if(filled==9)
    return 0;  
}
again()
{
	int i,j;
    for(i=0;i<3;i++)
    for(j=0;j<3;j++)
    arr[i][j]=32;
    count=0;
}
compturn2()
{
	int i,j;
    for(i=0;i<=2;i++)
    {
    	if(arr[i][0]==arr[i][1] && arr[i][0]!=32 && arr[i][2]==32)
    	return (i*3)+3;
    	else if(arr[i][1]==arr[i][2] && arr[i][1]!=32 && arr[i][0]==32)
    	return (i*3)+1;
    	else if(arr[i][2]==arr[i][0] && arr[i][2]!=32 && arr[i][1]==32)
    	return (i*3)+2;
    	else if(arr[0][i]==arr[1][i] && arr[0][i]!=32 && arr[2][i]==32)
    	return (i+7);
    	else if(arr[1][i]==arr[2][i] && arr[1][i]!=32 && arr[0][i]==32)
    	return (i+1);
    	else if(arr[2][i]==arr[0][i] && arr[2][i]!=32 && arr[1][i]==32)
    	return (i+4);
	}
	if(arr[0][0]==arr[1][1] && arr[0][0]!=32 && arr[2][2]==32)
    return 9;
    else if(arr[1][1]==arr[2][2] && arr[1][1]!=32 && arr[0][0]==32)
   	return 1;
   	else if(arr[2][2]==arr[0][0] && arr[2][2]!=32 && arr[1][1]==32)
   	return 5;
   	else if(arr[0][2]==arr[1][1] && arr[0][2]!=32 && arr[2][0]==32)
   	return 7;
   	else if(arr[1][1]==arr[2][0] && arr[1][1]!=32 && arr[0][2]==32)
   	return 3;
   	else if(arr[2][0]==arr[0][2] && arr[2][0]!=32 && arr[1][1]==32)
   	return 5;
   	else if(arr[0][0]==32 || arr[2][0]==32 || arr[0][2]==32 || arr[2][2]==32)
   	{
   		srand(time(NULL));
   	    while(1)
   		{
			int k=rand()%4+1;
			if(k==1 && arr[0][0]==32)
			return 1;
			else if(k==2 && arr[2][0]==32)
			return 7;
			else if(k==3 && arr[0][2]==32)
			return 3;
			else if(k==4 && arr[2][2]==32)
			return 9;
		    else
		        continue;
    	}
    }
   	else
   	{
   		srand(time(NULL));
   		while(1)
   		{
			int k=rand()%9+1;
			if(arr[(k-1)/3][(k-1)%3]==32)
		        return k;
		    else 
		        continue;
    	}
			
   	}
}
gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1B,y,x);
}
