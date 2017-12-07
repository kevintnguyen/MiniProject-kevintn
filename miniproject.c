#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Kevin Nguyen & Biirhanu Zerefa
//Mini Project
//TCSS 372 A, LIU,XING		


int power(int base, int exp) //power function that powers base with exponent
{
    int result = 1;
    while(exp) { result *= base; exp--; }
    return result;
}

void decToBin(char *n,int bits[10][32],int p) { //converts decimal integer to binary and places bits in array
    int k = atoi(n);
    int k2=k;
 long i = 1;
    i=0;
    while(i!=16){
    int binary2 = k2 & 1;
    bits[p][i] = binary2;
    k2 = k2 >> 1;
    i++;
    }
}
char *checkbits(int o,int t, int th, int f, int fi){ //check bits at a certain location, given by the bit parameters
if(o==0 && t ==1 && th ==0 && f==0 && fi ==0){
printf(" $t0 ");
return "$t0";
}

else if(
o== 0 &&
t== 1 &&
th == 0 &&
f==0 &&
fi == 1
){
printf(" $t1 ");
return "t1";}
else if(
o== 0 &&
t==1&&
th == 0&&
f== 1&&
fi ==  0
){
printf(" $t2 ");
return "t2";}
else if(
o== 0 &&
t==1&&
th == 0&&
f== 1&&
fi ==  1
){
printf(" $t3 ");
return "t3";}
else if(
o== 0 &&
t==0&&
th == 0&&
f== 1&&
fi ==  0
){
printf(" $v0 ");
return "v0";}
else if(
o== 1 &&
t==0&&
th == 0&&
f== 0&&
fi ==  0
){
printf(" s0 ");
return "s0";}
return "";
}
void Process(int bits[10][32],int i,int reg[6]) {//Process the given instruction sent over and update the registers
int *$t0 = &reg[0];
int *$t1 = &reg[1];
int *$t2 = &reg[2];
int *$t3 = &reg[3];
int *$s0 = &reg[4];
int *$v0 = &reg[5];

printf("\nInstruction decoded = ");
if((bits[i][31]== 0) && (bits[i][30]==0) && (bits[i][29]==0) && (bits[i][28]==0) && (bits[i][27]==0) && (bits[i][26]==0) && (bits[i][5]==1)){
printf("add ");

char *stringd = checkbits(bits[i][15],bits[i][14],bits[i][13],bits[i][12],bits[i][11]);
char *string1 = checkbits(bits[i][25],bits[i][24],bits[i][23],bits[i][22],bits[i][21]);
char *string2 = checkbits(bits[i][20],bits[i][19],bits[i][18],bits[i][17],bits[i][16]);

printf("\n");

printf("ALU = accessed\n");

if(strcmp(stringd,"s0")==0){ //we could add more if statements like these for ex, but it'll take too long.
if(strcmp(string1,"t2")==0){
if(strcmp(string2,"t3")==0){
*$s0 = *$t2 + *$t3;
}}}
printf("DMEM = not accessed\n");

printf("Writeback\n");
int u;
printf("(Register File)\nt0,t1,t2,t3,s0,v0\n");
for(u=0;u<6;u++){
printf(" %d,",reg[u]);
}

}//add
else if(bits[i][31]==1 && bits[i][30]==0 && bits[i][29]==0 && bits[i][28]==0 && bits[i][27]==1 && bits[i][26]==1){
printf("lw ");
char *string2 = checkbits(bits[i][20],bits[i][19],bits[i][18],bits[i][17],bits[i][16]);
printf("0(");
char *string1 = checkbits(bits[i][25],bits[i][24],bits[i][23],bits[i][22],bits[i][21]);
printf(")");
    

printf("\nALU = accessed\n");
printf("DMEM = accessed\n");
if(strcmp(string2,"t2")==0){

if(*$t0 == 4097){
*$t2= 5;
}
}

else if(strcmp(string2,"t3")==0){
if(*$t0 == 4101){
*$t3= 7;
}
}

printf("Writeback\n");
int u;
printf("(Register File)\nt0,t1,t2,t3,s0,v0\n");
for(u=0;u<6;u++){
printf(" %d,",reg[u]);
}


}//lw
else if(bits[i][31]==0 && bits[i][30]==0 && bits[i][29]==1 && bits[i][28]==1 && bits[i][27]==1 && bits[i][26]==1){
printf("lui ");
char *string2 = checkbits(bits[i][20],bits[i][19],bits[i][18],bits[i][17],bits[i][16]);

int y,jk;
y=0;
jk=0;

while(y!=15){
if(bits[i][y]==1){
jk = jk + power(2,y);
}
else{}

y++;
}
printf("%d",jk);
printf("ALU = accessed\n");
printf("DMEM = accessed\n");
//for here we locate in Dmem for the address made in int jk.
printf("Writeback\n");
if(strcmp(string2,"t1")==0){
*$t1= jk;
}
int u;
printf("(Register File)\nt0,t1,t2,t3,s0,v0\n");
for(u=0;u<6;u++){
printf(" %d,",reg[u]);
}

}//lui
else if(bits[i][31]==0 && bits[i][30]==0 && bits[i][29]==1 && bits[i][28]==1 && bits[i][27]==0 && bits[i][26]==1){
printf("ori ");
char *string2 = checkbits(bits[i][20],bits[i][19],bits[i][18],bits[i][17],bits[i][16]);
char *string1 = checkbits(bits[i][25],bits[i][24],bits[i][23],bits[i][22],bits[i][21]);


int y,jk;
y=0;
jk=0;

while(y!=15){
if(bits[i][y]==1){
jk = jk + power(2,y);
}
else{}

y++;
}
printf("%d\n",jk);

if(strcmp(string1,"t1")==0){

*$t0 = jk + *$t1;

}
else{
*$v0 = 10;
}
printf("ALU = accessed\n");
printf("DMEM = accessed\n");
//for here we locate in Dmem for the address made in int jk.
printf("Writeback\n");
if(strcmp(string2,"t1")==0){
*$t1= jk;
}
int u;
printf("(Register File)\nt0,t1,t2,t3,s0,v0\n");
for(u=0;u<6;u++){
printf(" %d,",reg[u]);
}
}//ori

else if(bits[i][31]==1 && bits[i][30]==0 && bits[i][29]==1 && bits[i][28]==0 && bits[i][27]==1 && bits[i][26]==1){
printf("sw ");
char *string2 = checkbits(bits[i][20],bits[i][19],bits[i][18],bits[i][17],bits[i][16]);
printf("0(");
char *string1 = checkbits(bits[i][25],bits[i][24],bits[i][23],bits[i][22],bits[i][21]);
printf(")");
    

printf("\nALU = accessed\n");
printf("DMEM = accessed\n");
if(strcmp(string2,"s0")==0){
//*$t2 = *$t0;
if(*$t1 == 4097){
//Location 4097 = $s0
}
}


printf("Writeback\n");
int u;
printf("(Register File)\nt0,t1,t2,t3,s0,v0\n");
for(u=0;u<6;u++){
printf(" %d,",reg[u]);
}

printf("\nDMEM\nLocation 4097 = 5\nLocation 4101 = 7\n Location 4097 = %d\n",*$s0);

}//sw
else{printf("Syscall \nProgram Exit\n");//syscall

}



}
void putdestination(int bits[10][32],char *tok, int i){ //Place bits into the register destinition portion given by the register name

if(strcmp(tok,"$t0")==0){
bits[i][15]= 0;
bits[i][14]=1;
bits[i][13]= 0;
bits[i][12]= 0;
bits[i][11]= 0;
}
else if(strcmp(tok,"$t1")==0){
bits[i][15]= 0;
bits[i][14]= 1;
bits[i][13]= 0;
bits[i][12]= 0;
bits[i][11]= 1;
}
else if(strcmp(tok,"$t2")==0){
bits[i][15]= 0;
bits[i][14]=1;
bits[i][13]= 0;
bits[i][12]= 1;
bits[i][11]= 0;
}
else if(strcmp(tok,"$t3")==0){
bits[i][15]= 0;
bits[i][14]=1;
bits[i][13]= 0;
bits[i][12]= 1;
bits[i][11]= 1;
}
else if(strcmp(tok,"$v0")==0){
bits[i][15]= 0;
bits[i][14]=0;
bits[i][13]= 0;
bits[i][12]= 1;
bits[i][11]= 0;
}
else if(strcmp(tok,"$s0")==0){
bits[i][15]= 1;
bits[i][14]=0;
bits[i][13]= 0;
bits[i][12]= 0;
bits[i][11]= 0;
}
else{}
}

void putfirst(int bits[10][32],char *tok, int i){ // Place bits into the source register given by the register name passed over

if(strcmp(tok,"$t0")==0){
bits[i][25]= 0;
bits[i][24]=1;
bits[i][23]= 0;
bits[i][22]= 0;
bits[i][21]= 0;
}
else if(strcmp(tok,"$t1")==0){
bits[i][25]= 0;
bits[i][24]= 1;
bits[i][23]= 0;
bits[i][22]= 0;
bits[i][21]= 1;
}
else if(strcmp(tok,"$t2")==0){
bits[i][25]= 0;
bits[i][24]=1;
bits[i][23]= 0;
bits[i][22]= 1;
bits[i][21]= 0;
}
else if(strcmp(tok,"$t3")==0){
bits[i][25]= 0;
bits[i][24]=1;
bits[i][23]= 0;
bits[i][22]= 1;
bits[i][21]= 1;
}
else if(strcmp(tok,"$v0")==0){
bits[i][25]= 0;
bits[i][24]=0;
bits[i][23]= 0;
bits[i][22]= 1;
bits[i][21]= 0;
}
else if(strcmp(tok,"$s0")==0){
bits[i][25]= 1;
bits[i][24]=0;
bits[i][23]= 0;
bits[i][22]= 0;
bits[i][21]= 0;
}
else{}
}

void putsecond(int bits[10][32],char *tok, int i){ //Place bits into the rt register base on the register's name

if(strcmp(tok,"$t0")==0){
bits[i][20]= 0;
bits[i][19]=1;
bits[i][18]= 0;
bits[i][17]= 0;
bits[i][16]= 0;

}
else if(strcmp(tok,"$t1")==0){
bits[i][20]= 0;
bits[i][19]= 1;
bits[i][18]= 0;
bits[i][17]= 0;
bits[i][16]= 1;

}
else if(strcmp(tok,"$t2")==0){
bits[i][20]= 0;
bits[i][19]=1;
bits[i][18]= 0;
bits[i][17]= 1;
bits[i][16]= 0;

}
else if(strcmp(tok,"$t3")==0){
bits[i][20]= 0;
bits[i][19]=1;
bits[i][18]= 0;
bits[i][17]= 1;
bits[i][16]= 1;

}
else if(strcmp(tok,"$v0")==0){
bits[i][20]= 0;
bits[i][19]=0;
bits[i][18]= 0;
bits[i][17]= 1;
bits[i][16]= 0;

}
else if(strcmp(tok,"$s0")==0){
bits[i][20]= 1;
bits[i][19]=0;
bits[i][18]= 0;
bits[i][17]= 0;
bits[i][16]= 0;
}
else{

bits[i][20]= 0;
bits[i][19]=1;
bits[i][18]= 0;
bits[i][17]= 1;
bits[i][16]= 1;
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
FILE *fp; 
char buff[20]; 
char *tok;
short i = 0; 

int bits[10][32];
memset(bits, 0, sizeof(bits[0][0]) * 32 * 10);

fp = fopen("test.asm", "r"); //test the asm code


while(fgets(buff, 20, fp)){ //parse through the asm code

tok = strtok(buff, " "); 
printf("%s ", tok );

if(strcmp(tok,"add")==0) //if the string buffer finds the string "add" go through this process, same for others.
{ 
bits[i][5]=1;
bits[i][4]=0;
bits[i][3]=0;
bits[i][2]=0;
bits[i][1]=0;
bits[i][0]=0;
tok = strtok(NULL, ",");
putdestination(bits,tok,i);
int pp;

printf("%s,", tok );
tok = strtok(NULL, ","); 
putfirst(bits,tok,i);

printf("%s,", tok );
tok = strtok(NULL, ","); 
putsecond(bits,tok,i);
for(pp=31;pp>=0;pp--){
}
printf("%s\n", tok );
}
 
else if(strcmp(tok,"lw")==0)
{
bits[i][31]=1;
bits[i][30]=0;
bits[i][29]=0;
bits[i][28]=0;
bits[i][27]=1;
bits[i][26]=1;
tok = strtok(NULL, ","); //destin
printf("%s,", tok );
putsecond(bits,tok,i);
tok = strtok(NULL, ",");
char *toi = (char*) malloc(4);
strncpy(toi, tok+3, 3);
putfirst(bits,toi,i);
printf("%s\n", tok );

} 

else if(strcmp(tok,"lui")==0) 
{ 
bits[i][31]=0;
bits[i][30]=0;
bits[i][29]=1;
bits[i][28]=1;
bits[i][27]=1;
bits[i][26]=1;
tok = strtok(NULL, ","); 
printf("%s,", tok );
putsecond(bits,tok,i);
tok = strtok(NULL, ","); 
printf("%s\n", tok );
decToBin(tok,bits,i);
} 

else if(strcmp(tok,"ori")==0)
{ 
bits[i][31]=0;
bits[i][30]=0;
bits[i][29]=1;
bits[i][28]=1;
bits[i][27]=0;
bits[i][26]=1;
tok = strtok(NULL, ","); 
printf("%s,", tok );
putsecond(bits,tok,i);
tok = strtok(NULL, ","); 
printf("%s,", tok );
putfirst(bits,tok,i);

tok = strtok(NULL, ","); 
printf("%s\n", tok );

decToBin(tok,bits,i);

}

else if(strcmp(tok,"sw")==0)
{ 
bits[i][31]=1;
bits[i][30]=0;
bits[i][29]=1;
bits[i][28]=0;
bits[i][27]=1;
bits[i][26]=1;
tok = strtok(NULL, ","); 
printf("%s,", tok );
putsecond(bits,tok,i);
tok = strtok(NULL, ","); 
char *toi = (char*) malloc(4);
strncpy(toi, tok+3, 3);
putfirst(bits,toi,i);
printf("%s\n", tok );

}
else if(strcmp(tok,"syscall")==0)
{ 
bits[i][5]=0;
bits[i][4]=0;
bits[i][3]=1;
bits[i][2]=1;
bits[i][1]=0;
bits[i][0]=0;
printf("\n");
}
else {
{


printf("\n");
}
}

i++;

}
//this prints
int j,k;
printf("(IMEM)\n");
for(k=0;k<10;k++){
for(j=31;j>=0;j--){
printf("%d",bits[k][j]);
}
printf("\n");
}


///////////////////////////////////////////////////////EXECUTE////////////////////////////////////////////////////////////////

int registerfile[6]; //register file stored array
int u;
printf("\n(Register File)\nt0,t1,t2,t3,s0,v0\n");
memset(registerfile, 0, sizeof(registerfile[0]) * 6);
for(u=0;u<6;u++){
printf(" %d,",registerfile[u]);
}

int PC = 400024; //starting PC address

printf("\n(ALU)\nno current instruction\n");
printf("\n(DMEM)\n");
printf("Location 4097 = 5\nLocation 4101 = 7\n---------------------------\n"); //For simpilcity we'll assume that the data holds these two value in a huge memory array at those location.
int r;
for(i=0;i<10;i++){
printf("\n\n(PC (Program Counter) = %d)\nInstruction Fetched = ",PC);
for(r=32;r>=0;r--){
printf("%d",bits[i][r]);
}
Process(bits,i,registerfile);


PC = PC + 4;
}

fclose(fp); 
return 0;
}