#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ayush.h"
static void ask(const char *p,char *b,int cap){ printf("%s",p); if(!fgets(b,cap,stdin)) exit(0); b[strcspn(b,"\n")]=0; }
int main(void){
    char a[96],b[96],c[96],d[96];
    for(;;){
        puts("\n1 Register  2 Call next  3 Suggest codes  4 Finalize  5 Undo  6 Care  7 Patient  8 Claim  9 State  0 Exit");
        ask("> ",a,sizeof a);
        switch(atoi(a)){
        case 1: ask("Name: ",a,40); ask("Age: ",b,8); ask("Prakriti (vata/pitta/kapha/other): ",c,12); ask("Complaint: ",d,96); puts(api_register(a,atoi(b),c,d)); break;
        case 2: puts(api_next()); break;
        case 3: ask("Complaint: ",a,96); puts(api_suggest(a)); break;
        case 4: ask("Patient ID: ",a,8); ask("Term: ",b,32); puts(api_finalize(atoi(a),b)); break;
        case 5: puts(api_undo()); break;
        case 6: ask("Term: ",a,32); ask("Prakriti: ",b,12); puts(api_care(a,b)); break;
        case 7: ask("Patient ID: ",a,8); puts(api_patient(atoi(a))); break;
        case 8: ask("Patient ID: ",a,8); puts(api_bill(atoi(a))); break;
        case 9: puts(api_state()); break;
        case 0: return 0;
        }
    }
}
