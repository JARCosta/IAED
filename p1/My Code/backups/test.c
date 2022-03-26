#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

/*___max elementos___*/
#define MAXTAREFAS 10000
#define MAXATIVIDADES 10
#define MAXUSERS 50

/*___max characters___*/
#define MAXCHARDESC 50
#define MAXCHARACTIVITY 20
#define MAXCHARUSER 20
#define MAXCHARINPUT 100

struct memoria{
    int ID;
    int START;
    int DURATION;
    char ACTIVITY[MAXCHARACTIVITY];
    char DESCRIPTION[MAXCHARDESC];
};
struct memoria memID[MAXTAREFAS];
struct memoria memALF[MAXTAREFAS];
struct memoria memIDsortedbySTART[MAXTAREFAS];

char USERS[MAXUSERS][MAXCHARUSER+1];
char ACTIVITIES[MAXATIVIDADES][MAXCHARACTIVITY+1]={""};


char inputinwords[MAXCHARINPUT][MAXCHARINPUT]={{' '}};
char inputinstring[MAXCHARINPUT]={' '};

int TASKCOUNTER=0;
int USERCOUNTER=0;
int TIME=0;
int ACTIVITYCOUNTER=3;
int QUITFLAG=0;
int NUMINPUTS=0;

int intlen(char n[]){
    int i,res=0,j=strlen(n);
    for(i=0;i<j;i++){
        if(n[i]<='9'&&n[i]>='0') res++;
    }
    return res;
}

int strlin(char n[]){
    int i,res=0;
    for(i=0;i<MAXCHARINPUT;i++){
        if((n[i]<='9'&&n[i]>='0')||n[i]==' '||(n[i]<='z'&&n[i]>='a')||(n[i]<='Z'&&n[i]>='A')) res++;
    }
    return res;
}

int chartoint(char n[]){
    int i,res=0,l=intlen(n);
    char j;
    for(i=0;i<l;i++){
        j= n[i];
        j=j-'0';
        res=res*10;
        res = res+j;
    }
    return res;
}

int isint(char n){
    if('0'<=n&&n<='9') return 0;
    else return 1;
}

int ischar(char n){
    if(('0'<=n&&n<='9')||('a'<=n&&n<='z')||('A'<=n&&n<='Z')) return 0;
    else return 1;
}

void sortbyALPH(){
    char tempchar[MAXCHARINPUT]={' '};
    int i,j,tempint;

    for(i=0;i<TASKCOUNTER;i++){                    /*copia toda a memoria*/
        memALF[i].ID=memID[i].ID;
        memALF[i].START=memID[i].START;
        memALF[i].DURATION=memID[i].DURATION;
        strcpy(memALF[i].ACTIVITY,memID[i].ACTIVITY);
        strcpy(memALF[i].DESCRIPTION,memID[i].DESCRIPTION);
    }
    /*for(i=0;i<TASKCOUNTER;i++)printf("%d %s %d %d %s %s .\n", memALF[i].ID, memALF[i].USER,memALF[i].START, memALF[i].DURATION, memALF[i].ACTIVITY,memALF[i].DESCRIPTION);
    */
    for(i=0;i<TASKCOUNTER;i++){
        for(j=i+1;j<TASKCOUNTER;j++) {
            if(strcmp(memALF[i].DESCRIPTION,memALF[j].DESCRIPTION)>0&&TASKCOUNTER>1){
                tempint=memALF[i].ID,memALF[i].ID=memALF[j].ID,memALF[j].ID=tempint;
                tempint=memALF[i].START,memALF[i].START=memALF[j].START,memALF[j].START=tempint;
                tempint=memALF[i].DURATION,memALF[i].DURATION=memALF[j].DURATION,memALF[j].DURATION=tempint;
                strcpy(tempchar,memALF[i].ACTIVITY),strcpy(memALF[i].ACTIVITY,memALF[j].ACTIVITY), strcpy(memALF[j].ACTIVITY,tempchar);
                strcpy(tempchar,memALF[i].DESCRIPTION),strcpy(memALF[i].DESCRIPTION,memALF[j].DESCRIPTION), strcpy(memALF[j].DESCRIPTION,tempchar);
                /*for(k=0;k<TASKCOUNTER;k++)printf("%d %s %d %d %s %s memsorted\n", memALF[k].ID, memALF[k].USER,memALF[k].START, memALF[k].DURATION, memALF[k].ACTIVITY,memALF[k].DESCRIPTION);
            */}
        }
    }
    /*for(i=0;i<TASKCOUNTER;i++)printf("%d %s %d %d %s %s mem\n", memID[i].ID, memID[i].USER, memID[i].START, memID[i].DURATION,memID[i].ACTIVITY, memID[i].DESCRIPTION);
    for(i=0;i<TASKCOUNTER;i++)printf("%d %s %d %d %s %s memsorted\n", memALF[i].ID, memALF[i].USER,memALF[i].START, memALF[i].DURATION, memALF[i].ACTIVITY,memALF[i].DESCRIPTION);
*/
}

void sortbySTART(char act[]){
    char tempchar[MAXCHARINPUT];
    int i,j,tempint;


    int actpointer=0;
    for(i=0;i<TASKCOUNTER;i++)if(strcmp(memID[i].ACTIVITY,act)==0){
            memIDsortedbySTART[i].ID=memALF[actpointer].ID;
            memIDsortedbySTART[i].START=memALF[actpointer].START;
            memIDsortedbySTART[i].DURATION=memALF[actpointer].DURATION;
            strcpy(memIDsortedbySTART[i].ACTIVITY,memALF[actpointer].ACTIVITY);
            strcpy(memIDsortedbySTART[i].DESCRIPTION,memALF[actpointer].DESCRIPTION);
            actpointer++;
        }
    for(i=0;i<TASKCOUNTER;i++){
        for(j=i+1;j<TASKCOUNTER;j++) {
            if(memIDsortedbySTART[i].START>memIDsortedbySTART[j].START&&TASKCOUNTER>1){
                tempint=memIDsortedbySTART[i].ID,memIDsortedbySTART[i].ID=memIDsortedbySTART[j].ID,memIDsortedbySTART[j].ID=tempint;
                tempint=memIDsortedbySTART[i].START,memIDsortedbySTART[i].START=memIDsortedbySTART[j].START,memIDsortedbySTART[j].START=tempint;
                tempint=memIDsortedbySTART[i].DURATION,memIDsortedbySTART[i].DURATION=memIDsortedbySTART[j].DURATION,memIDsortedbySTART[j].DURATION=tempint;
                strcpy(tempchar,memIDsortedbySTART[i].ACTIVITY),strcpy(memIDsortedbySTART[i].ACTIVITY,memIDsortedbySTART[j].ACTIVITY), strcpy(memIDsortedbySTART[j].ACTIVITY,tempchar);
                strcpy(tempchar,memIDsortedbySTART[i].DESCRIPTION),strcpy(memIDsortedbySTART[i].DESCRIPTION,memIDsortedbySTART[j].DESCRIPTION), strcpy(memIDsortedbySTART[j].DESCRIPTION,tempchar);
                /*for(k=0;k<TASKCOUNTER;k++)printf("%d %s %d %d %s %s memsorted\n", memIDsortedbySTART[k].ID, memIDsortedbySTART[k].USER,memIDsortedbySTART[k].START, memIDsortedbySTART[k].DURATION, memIDsortedbySTART[k].ACTIVITY,memIDsortedbySTART[k].DESCRIPTION);
            */}
        }
    }
}


/*FUNCOES AUXILIARES
---------------------------------------------------------------------------------------------------
  FUNCOES DE COMANDOS */

void input(){
    int i,numinputs=1,pointer=0, len,j;
    for(i=0;i<MAXCHARINPUT;i++)inputinstring[i]=0;
    for(i=0;i<MAXCHARINPUT;i++)for(j=0;j<MAXCHARINPUT;j++)inputinwords[i][j]=0;
    scanf(" %[^\n]", inputinstring);

    len = strlen(inputinstring)+1;
    for(i=0;i<len;i++){
        if(inputinstring[i]==' '&& (inputinstring[i+1]!=' ')){
            if(inputinstring[i+1]!='\n'){
                numinputs++,pointer=0;                 /* conta o numero de palavras e de espacos no input */
            }
        }
        else if(inputinstring[i]!=' '){
            inputinwords[numinputs-1][pointer]=inputinstring[i],pointer++; /* separa o input por palavras */
        }
    }
    NUMINPUTS=numinputs;
}

void newtask(){
    char description[MAXCHARDESC]={' '};
    int i,numcharsuselessfordescription=strlen(inputinwords[0])+strlen(inputinwords[1])+2;
    int leninput=strlen(inputinstring),l;

    for(i=numcharsuselessfordescription;i<leninput;i++)description[i-numcharsuselessfordescription]=inputinstring[i];

    if(TASKCOUNTER+1>MAXTAREFAS){
        printf("too many tasks\n");
        return;
    }
    l= strlen(inputinwords[1]);
    for(i=0;i<TASKCOUNTER;i++) if(strcmp(memID[i].DESCRIPTION,description)==0){
            printf("duplicate description\n");
            return;
        }
    for(i=0;i<l;i++)if(ischar(inputinwords[1][i])==1||strcmp(inputinwords[1],"0")==0){
            printf("invalid duration\n");
            return;
        }

    memID[TASKCOUNTER].ID=TASKCOUNTER+1;
    memID[TASKCOUNTER].START=TIME;
    memID[TASKCOUNTER].DURATION=chartoint(inputinwords[1]);
    strcpy(memID[TASKCOUNTER].ACTIVITY,"TO DO");
    strcpy(memID[TASKCOUNTER].DESCRIPTION,description);

    printf("task %d\n",TASKCOUNTER+1);
    TASKCOUNTER++;
}

void printmemID() {
    int i,j,existflag=0;

    sortbyALPH();
    if(strcmp(inputinstring,"l")==0) for(i=0;i<TASKCOUNTER;i++) {
            printf("%d %s #%d %s\n", memALF[i].ID, memALF[i].ACTIVITY, memALF[i].DURATION, memALF[i].DESCRIPTION);
        }
    else{
        for(i=1;i<NUMINPUTS;i++) {
            existflag=0;
            for (j = 0; j < TASKCOUNTER; j++) if (memID[j].ID==chartoint(inputinwords[i])) existflag = 1;

            if(existflag==0) printf("%s: no such task\n",inputinwords[i]);

            else for(j=0;j<TASKCOUNTER;j++){
                    if(memID[j].ID==chartoint(inputinwords[i])) printf("%d %s #%d %s\n",memID[j].ID,memID[j].ACTIVITY,memID[j].DURATION,memID[j].DESCRIPTION);
                }
        }
    }
}



int advancetime(int n){
    int i,numdigs=0,l;
    l =strlen(inputinwords[1]);
    for(i=0;i<l;i++) if(isint(inputinwords[1][i])==1){
            printf("invalid time\n");
            return 1;
        }
    while(isint((inputinstring[i]))==0){
        numdigs++;
        i++;
    }
/*
    for(i=0;i<numdigs;i++) if(isint(mi[i])==1) isnotint=1;
    if(isnotint==1){
        printf("invalid time\n");
        return 1;
    }
*/
    for(i=0;i<n;i++)TIME++;
    return 0;
}

void newuser(){
    int i,j;

    for(i=1;i<NUMINPUTS;i++) for(j=0;j<USERCOUNTER;j++) if(strcmp(inputinwords[i],USERS[j])==0){
                printf("user already exists\n");
                return;
            }
    if(USERCOUNTER>=MAXUSERS){
        printf("too many users\n");
        return;
    }
    if(NUMINPUTS==1){
        for(i=0;i<USERCOUNTER;i++)printf("%s\n",USERS[i]);
    }
    else{
        for(i=1;i<NUMINPUTS;i++) {
            strcpy(USERS[USERCOUNTER],inputinwords[i]);
            USERCOUNTER++;
        }
    }
}

void changeState(){
    char activity[MAXCHARACTIVITY+1]={' '};
    int i,taskid=chartoint(inputinwords[1])-1,savestartflag=1;
    int IDexists=1,USERexists=1,ACTIVITYexists=1;
    int numcharuselessforactivity=strlin(inputinwords[0])+strlen(inputinwords[1])+strlen(inputinwords[2])+3;
    int leninput=strlen(inputinstring);

    if(strcmp(memID[taskid].ACTIVITY,"TO DO")==0) savestartflag=0;
    for(i=numcharuselessforactivity;i<leninput;i++){
        activity[i-numcharuselessforactivity]=inputinstring[i];
    }


    for(i=0;i<ACTIVITYCOUNTER;i++){
        if(strcmp(ACTIVITIES[i],activity)==0){
            ACTIVITYexists=0;
        }
    }
    for(i=0;i<USERCOUNTER;i++) if(strcmp(USERS[i],inputinwords[2])==0) USERexists=0;
    for(i=0;i<TASKCOUNTER;i++) if(memID[i].ID==taskid+1) IDexists=0;

    if(IDexists==1){
        printf("no such task\n");
        return;}
    if(strcmp(memID[taskid].ACTIVITY,"TO DO")!=0&&strcmp(activity,"TO DO")==0){
        printf("task already started\n");
        return;
    }
    if(USERexists==1){
        printf("no such user\n");
        return;}
    if(ACTIVITYexists==1){
        printf("no such activity\n");
        return;}

    if(savestartflag==0){
        memID[taskid].START=TIME;
    }
    strcpy(memID[taskid].ACTIVITY,activity);

    if(strcmp(activity,"DONE")==0){
        printf("duration=%d slack=%d\n",TIME-memID[taskid].START,(TIME-memID[taskid].START)-memID[taskid].DURATION);
    }
}

void showtasksonactivity(){
    char activity[MAXCHARACTIVITY]={' '};
    int i,intlenactivity=0,activityexists=1;

    for(i=2;i<MAXCHARACTIVITY;i++){
        if(ischar(inputinstring[i])==0||inputinstring[i]==' ') intlenactivity++;} /* mede o tamanho da string atividade dada*/
    for(i=0;i<intlenactivity;i++)activity[i]=inputinstring[i+2];                   /*usa a informação interior e passa a atividade dada para uma nova variavel, sem lixo*/

    for(i=0;i<ACTIVITYCOUNTER;i++) if(strcmp(ACTIVITIES[i],activity)==0) activityexists=0;
    if(activityexists==1){
        printf("no such activity\n");
        return;
    }
    sortbySTART(activity);
    for(i=0;i<TASKCOUNTER;i++){
        if(strcmp(memID[i].ACTIVITY,activity)==0){
            printf("%d %d %s\n",memID[i].ID,memID[i].START,memID[i].DESCRIPTION);
        }

    }
}

void newactivity(){
    int i,l;
    char act[MAXCHARACTIVITY]={""};
    if(NUMINPUTS==1){
        for(i=0;i<ACTIVITYCOUNTER;i++)printf("%s\n",ACTIVITIES[i]);
    }
    else{
        if(ACTIVITYCOUNTER==10){
            printf("too many activities\n");
            return;
        }
        l= strlin(inputinstring);
        for(i=2;i<l;i++){
            if(inputinstring[i]!=' '&&(inputinstring[i]<'A'||inputinstring[i]>'Z'))
                if(inputinstring[i]<'0'||inputinstring[i]>'9'){
                    printf("invalid description\n");
                    return;
                }
            act[i-2]=inputinstring[i];
        }

        for(i=0;i<ACTIVITYCOUNTER;i++){
            if(strcmp(act,ACTIVITIES[i])==0){
                printf("duplicate activity\n");
                return;
            }
        }
        strcpy(ACTIVITIES[ACTIVITYCOUNTER],act);
        ACTIVITYCOUNTER++;
    }
}


void execcomands(char command[]){
    int n;
    /*for(i=0;i<TASKCOUNTER;i++)printf("%d %s %s\n",memID[i].ID,memID[i].DESCRIPTION,memID[i].ACTIVITY);*/

    if(command[0]=='q')QUITFLAG=1;
    else if(command[0]=='t'){
        newtask();
    }
    else if(command[0]== 'l')printmemID();
    else if(command[0]== 'n'){
        n = advancetime(chartoint(inputinwords[1]));
        if(n==0)printf("%d\n",TIME);
    }
    else if(command[0]== 'u')newuser();
    else if(command[0]== 'm')changeState();
    else if(command[0]== 'd')showtasksonactivity();
    else if(command[0]== 'a')newactivity();
}

int main(){
    int i;
    strcpy(ACTIVITIES[0],"TO DO"),strcpy(ACTIVITIES[1],"IN PROGRESS"),strcpy(ACTIVITIES[2],"DONE");
    while(QUITFLAG!=1) {
        strcpy(inputinstring," ");
        for(i=0;i<MAXCHARACTIVITY;i++)strcpy(inputinwords[i]," ");
        input();
        execcomands(inputinwords[0]);
    }
    return 0;
}
