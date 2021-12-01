# include<stdio.h>
# include<math.h>
# include<stdbool.h>
# include<stdlib.h>
# include<string.h>
# define ZERO 0
# define HASH_MAX 134217728
typedef struct{
 int final,val,size;
 int transition[10];

}state;

int update(int new,int curr){
        int nBit=pow(2,new);
        

        //printf("\nnew state:%d",nBit);
        curr=curr | nBit ;
        //printf("\nupdated state: %d",curr);
        return curr; 
}
void printStates(int val){
        val=val>>1;
        int tmp;
        if(val==0)
        {
                printf("e");
                return;
        }
        for(int i=0;i<27;i++){
                //tmp=val>>1;
                
                if(val&1){
                    printf("%c,",i+65);
                }
                val=val>>1;
                        
        }
}
int findFinalSt(state nfa[],int nfaStNum){
        int final=0;
        for(int i=0;i<nfaStNum;i++){
                if(nfa[i].final==1){
                        //printf("\n %d is a final state",nfa[i].val);
                        final=final|nfa[i].val;
                }
                //printf("%c",65+nfa[i].val);
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

int addNewState(state nfa[],state dfa[],int nfaStNum,int dfa_tmp,int counter,int i,bool* h_tab){
        //printf("\ninside addNewState");
        dfa[counter].val=dfa_tmp;
        dfa[counter].size=nfa[i].size;
        memset(dfa[counter].transition,0,10);
        dfa[counter].final=0;
        //set transitions for the new state
        dfa_tmp=dfa_tmp>>1;
        for(int pos=1;dfa_tmp;pos++){
                //printf("\nthird loop:%d, temp:%d",pos,dfa_tmp);                                       
                if(dfa_tmp&1!=0){
                        //printf("\ninside transition creator of %d",pos);
                        if(dfa[counter].final!=1)
                                dfa[counter].final=nfa[pos-1].final;
                        for(int k=0;k<nfa[pos-1].size;k++){
                                //printf("\ninput: %d",k);
                                //printf("\nbefore: %d",dfa[counter].transition[k]);
                                dfa[counter].transition[k]|=nfa[pos-1].transition[k];
                                //printf("\nafter: %d",dfa[counter].transition[k]);
                        }
                }

                dfa_tmp=dfa_tmp>>1;
        }
        //check if any new states are created
        for(int k=0;k<dfa[counter].size;k++){
                dfa_tmp=dfa[counter].transition[k];
                if(h_tab[dfa_tmp]==1)
                        continue;
                else{
                        h_tab[dfa_tmp]=1;//mark as visited
                        counter=addNewState(nfa,dfa,nfaStNum,dfa_tmp,counter+1,i,h_tab);         
                }
        }
        return counter;     
}

int nfaToDfa(state nfa[],state dfa[],int nfaStNum){
        bool *h_tab;
        int counter=nfaStNum;
        int tmp,dfa_tmp;
        h_tab=malloc(HASH_MAX*sizeof(bool));
        memset(h_tab,0,HASH_MAX*sizeof(bool));
        //printf("working %d\n",h_tab[HASH_MAX]);
        
        //find final states
        const int final=findFinalSt(nfa,nfaStNum);

        //copy states of nfa to dfa
        for(int i=0;i<nfaStNum;i++){
                h_tab[nfa[i].val]=1;
                //printf("\n%d  size:%d",nfa[i].val,nfa[i].size);
                dfa[i].val=nfa[i].val;
                dfa[i].final=nfa[i].final;
                dfa[i].size=nfa[i].size;
                for(int j=0;j<dfa[i].size;j++)
                        dfa[i].transition[j]=nfa[i].transition[j];
        }
        //printf("\ndfa begin: ");
        for(int i=0;i<counter;i++){
                printf("[");

                for(int j=0;j<dfa[i].size;j++)
                        printf("%d,",dfa[i].transition[j]);
                printf("],");
        }
        printf("\n");

        //find transitions with multiple transition states
        for(int i=0;i<nfaStNum;i++){
                //printf("\nfirst loop State:%d",i);
                for(int j=0;j<nfa[i].size;j++){
                        //printf("\nsecond loop:%d",j);
                        tmp=nfa[i].transition[j];
                        if(h_tab[tmp]==0){//add new state for multiple states that are not added to dfa
                                h_tab[tmp]=1;//mark as visited
                                dfa[counter].val=tmp;
                                dfa[counter].size=nfa[i].size;
                                memset(dfa[counter].transition,0,10);
                                dfa[counter].final=0;
                                //set transitions for the new state
                                tmp=tmp>>1;
                                for(int pos=1;tmp;pos++){
                                        //printf("\nthird loop:%d, temp:%d",pos,tmp);                                       
                                        if(tmp&1!=0){
                                                //printf("\ninside transition creator of %d",pos);
                                                if(dfa[counter].final!=1)
                                                        dfa[counter].final=nfa[pos-1].final;
                                                for(int k=0;k<nfa[pos-1].size;k++){
                                                        //printf("\ninput: %d",k);
                                                        //printf("\nbefore: %d",dfa[counter].transition[k]);
                                                        dfa[counter].transition[k]|=nfa[pos-1].transition[k];
                                                        //printf("\nafter: %d",dfa[counter].transition[k]);
                                                }
                                        }

                                        tmp=tmp>>1;
                                }

                                //check if any new states are created
                                for(int k=0;k<dfa[counter].size;k++){
                                        //printf("\n checking for new states");
                                        dfa_tmp=dfa[counter].transition[k];
                                        if(h_tab[dfa_tmp]==1)
                                                continue;
                                        else{
                                                h_tab[dfa_tmp]=1;//mark as visited
                                                counter=addNewState(nfa,dfa,nfaStNum,dfa_tmp,counter+1,i,h_tab);         
                                        }
                                }
                                counter ++;
                        }

                }
        }

        free(h_tab);//free heap space
        return counter;

}

void main(){
        int nfaStNum=3,faInNum=2,numInSt,dfaStNum=0;
        //const int initVal=0;
        int bitVal,temp,final;
        state t_nfa[20],dfa[64];
        // state t_nfa[3];
        // t_nfa[0].val=pow(2,0+1);
        // t_nfa[1].val=pow(2,1+1);
        // t_nfa[2].val=pow(2,2+1);
        // t_nfa[0].final=0;
        // t_nfa[1].final=0;
        // t_nfa[2].final=1;
        // t_nfa[0].size=2;
        // t_nfa[1].size=2;
        // t_nfa[2].size=2;
        // t_nfa[0].transition[0]=14;
        // t_nfa[0].transition[1]=4;
        // t_nfa[1].transition[0]=8;
        // t_nfa[1].transition[1]=8;
        // t_nfa[2].transition[0]=4;
        // t_nfa[2].transition[1]=8;
        
        printf("\nEnter Number of States: ");
        scanf("%d",&nfaStNum);
        printf("\nEnter Number of input symbols: ");
        scanf("%d",&faInNum);
        printf("\n");
        
        for(int i=0;i<nfaStNum;i++){
                printf("\nFor State %c",i+65);
                t_nfa[i].val=pow(2,i+1);
               printf("\nIs this a final state? :");
                scanf("%d",&final);
                t_nfa[i].final=final;
                for(int j=0;j<faInNum;j++){
                        printf("\nFor input symbol : %d  \nEnter Number of states: ",j);
                        scanf("%d",&numInSt);
                        t_nfa[i].size=faInNum;
                        bitVal=ZERO;
                        for(int k=0;k<numInSt;k++){
                                scanf("%d",&temp);
                                bitVal=update(temp,bitVal);                 
                        }
                        t_nfa[i].transition[j]=bitVal;
                        
                }
        }
        final=findFinalSt(t_nfa,nfaStNum);
        printf("\n---------------------------------\n\t\tNFA\t\t\n---------------------------------\n");
        //heading 
        printf("\nState\t\t|\t\t");
        for(int i=0;i<faInNum;i++)
                printf("%d\t\t|\t\t",i);
        for (int i=0;i<nfaStNum;i++){
                printf("\n{");
                printStates(t_nfa[i].val);
                printf("}");
                if(t_nfa[i].final)
                        printf("*");
                printf( "\t\t");
                for(int j=0;j<faInNum;j++){
                        //printf("%d",dfa[i].transition[j]);
                        printf("|\t\t{");
                        printStates(t_nfa[i].transition[j]);
                        printf("}");
                        if(t_nfa[i].final)
                                printf("*");
                        printf( "\t\t");
                                
                }
                printf("|");
        
        }
        dfaStNum=nfaToDfa(t_nfa,dfa,nfaStNum);
        
        //dfa
        printf("\n---------------------------------\n\t\tDFA\t\t\n---------------------------------\n");        //heading 
        printf("\nState\t\t|\t\t");
        for(int i=0;i<faInNum;i++)
                printf("%d\t\t|\t\t",i);
        for (int i=0;i<dfaStNum;i++){
                printf("\n[");
                printStates(dfa[i].val);
                printf("]");
                if(dfa[i].final)
                        printf("*");
                printf( "\t\t");
                for(int j=0;j<faInNum;j++){
                        //printf("%d",dfa[i].transition[j]);
                        printf("|\t[");
                        printStates(dfa[i].transition[j]);
                        printf("]");
                        if(checkFinal(final,dfa[i].transition[j]))
                                printf("*");
                        printf( "\t\t\t");
                                
                }
                printf("|");
        
        }
        printf("\n");
        }
