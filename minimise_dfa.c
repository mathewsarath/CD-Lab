#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define ZERO 0
#define HASH_MAX 134217728
#define TABLE_SIZE 32
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
typedef struct
{
    int final, val, size;
    int transition[10];

} state;

int update(int new, int curr)
{
    int nBit = pow(2, new);
    curr = curr | nBit;
    return curr;
}

void printStates(int val)
{
    val = val >> 1;
    int tmp;
    if (val == 0)
    {
        printf("e");
        return;
    }
    for (int i = 0; i < 27; i++)
    {
        if (val & 1)
        {
            printf("%d,", i);
        }
        val = val >> 1;
    }
}

int findFinalSt(state dfa[],int dfaStNum){
    int final=0;
    for(int i=0;i<dfaStNum;i++){
            if(dfa[i].final==1){
                //printf("\n %d is a final state",dfa[i].val);
                final=final|dfa[i].val;
            }
        //printf("%c",65+dfa[i].val);
        }
    // printf("final states: %d",final);
    return final;
}

bool checkFinal(const int final,int val){
    //printf("\n final: %d, value: %d, result: %d",final,val,final&val);
    if (val==0)
        return 1;
    else if(final&val)
        return 1;
    else
        return 0;
}
int getState(int val){
    val=val>>1;
    return log2((double)val);
}

void printTable(int size, bool table[][TABLE_SIZE]){
    for (int i=1; i<size;i++){
        printf("\n");
        for ( int j = 0; j<i;j++){
            printf("%d ", table[i][j]);
        }
    }
}

void fillTable(int size, state dfa[], int faInNum, bool table[][TABLE_SIZE]){

    bool flag;
    int t1,t2;
    //fill cell with exactly one final state
    for (int i=1; i<size; i++){
        for(int j=0; j<i; j++){
            table[i][j]= dfa[i].final^dfa[j].final;
        }
    }
    printTable(size , table);

    //repeatedly check for additional final states
    do{
        flag=0;
        for(int i=1; i<size; i++){
            for(int j=0; j<i; j++){
                printf("for q%d , q%d : ",i,j);
                if(!table[i][j]){//skip if it is a final state
                    for(int k=0; k<faInNum; k++){

                        t1= getState(dfa[i].transition[k]);
                        t2= getState(dfa[j].transition[k]);
                        if(table[MAX(t1,t2)][MIN(t1,t2)]){
                            flag=1;
                            table[i][j]=1;
                        }
                        printf("( q%d , q%d ) &  %d = %d\n",MAX(t1,t2),MIN(t1,t2),k,table[MAX(t1,t2)][MIN(t1,t2)]);
                    }
                }      
            }
        }
    printTable(size,table);
    }
    while(flag);
}

void main()
{
    int dfaStNum = 6, faInNum = 2, numInSt;
    bool table[TABLE_SIZE][TABLE_SIZE] = {0};
    // const int initVal=0;
    int bitVal, temp, final;
    // state t_dfa[20], dfa[64];
    state t_dfa[6];
    t_dfa[0].val=pow(2,0+1);
    t_dfa[1].val=pow(2,1+1);
    t_dfa[2].val=pow(2,2+1);
    t_dfa[3].val=pow(2,3+1);
    t_dfa[4].val=pow(2,4+1);
    t_dfa[5].val=pow(2,5+1);
    t_dfa[0].final=0;
    t_dfa[1].final=1;
    t_dfa[2].final=1;
    t_dfa[3].final=0;
    t_dfa[4].final=0;
    t_dfa[5].final=1;
    t_dfa[0].size=2;
    t_dfa[1].size=2;
    t_dfa[2].size=2;
    t_dfa[0].transition[0]=4;
    t_dfa[0].transition[1]=8;
    t_dfa[1].transition[0]=16;
    t_dfa[1].transition[1]=32;
    t_dfa[2].transition[0]=32;
    t_dfa[2].transition[1]=16;
    t_dfa[3].transition[0]=64;
    t_dfa[3].transition[1]=64;
    t_dfa[4].transition[0]=64;
    t_dfa[4].transition[1]=64;
    t_dfa[5].transition[0]=64;
    t_dfa[5].transition[1]=64;

    // printf("\nEnter Number of States: ");
    // scanf("%d",&dfaStNum);
    // printf("\nEnter Number of input symbols: ");
    // scanf("%d",&faInNum);
    // printf("\n");

    // for(int i=0;i<dfaStNum;i++){
    //         printf("\nFor State %c",i+65);
    //         t_dfa[i].val=pow(2,i+1);
    //        printf("\nIs this a final state? :");
    //         scanf("%d",&final);
    //         t_dfa[i].final=final;
    //         for(int j=0;j<faInNum;j++){
    //                 printf("\nFor input symbol : %d  \nEnter Number of states: ",j);
    //                 scanf("%d",&numInSt);
    //                 t_dfa[i].size=faInNum;
    //                 bitVal=ZERO;
    //                 for(int k=0;k<numInSt;k++){
    //                         scanf("%d",&temp);
    //                         bitVal=update(temp,bitVal);
    //                 }
    //                 t_dfa[i].transition[j]=bitVal;

    //         }
    // }
    // final=findFinalSt(t_dfa,dfaStNum);
    printf("\n---------------------------------\n\t\tdfa\t\t\n---------------------------------\n");
    //heading
    printf("\nState\t\t|\t\t");
    for (int i = 0; i < faInNum; i++)
        printf("%d\t\t|\t\t", i);
    for (int i = 0; i < dfaStNum; i++)
    {
        printf("\n{");
        printStates(t_dfa[i].val);
        printf("}");
        if (t_dfa[i].final)
            printf("*");
        printf("\t\t");
        for (int j = 0; j < faInNum; j++)
        {
            //printf("%d",dfa[i].transition[j]);
            printf("|\t\t{");
            printStates(t_dfa[i].transition[j]);
            printf("}");
            if (t_dfa[i].final)
                printf("*");
            printf("\t\t");
        }
        printf("|");
    }

    fillTable(dfaStNum, t_dfa, faInNum, table);
    printTable(dfaStNum, table);
}