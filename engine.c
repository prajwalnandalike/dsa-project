#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include "ayush.h"
#define H 11
#define P(...) do{ if(n<(int)sizeof out-1) n+=snprintf(out+n,sizeof out-n,__VA_ARGS__); }while(0)

static char out[16384];
static int n, ready, nextid = 1, cnt;
static Patient *root; static Queue q; static Stack us; static Entry *tab[H];

/* ---- hash table with chaining ---- */
static unsigned hs(const char *s){ unsigned x=5381; for(;*s;s++) x=x*33+(unsigned)tolower((unsigned char)*s); return x%H; }
static void init(void){ if(ready) return; for(int i=0;i<ND;i++){ unsigned b=hs(db[i].term); db[i].next=tab[b]; tab[b]=&db[i]; } ready=1; }
static Entry *lookup(const char *t){ init(); for(Entry *e=tab[hs(t)];e;e=e->next) if(!strcasecmp(e->term,t)) return e; return NULL; }

/* ---- binary search tree ---- */
static Patient *ins(Patient *t, Patient *p){ if(!t) return p; if(p->id<t->id) t->l=ins(t->l,p); else t->r=ins(t->r,p); return t; }
static Patient *find(int id){ Patient *t=root; while(t&&t->id!=id) t=id<t->id?t->l:t->r; return t; }
static void walk(Patient *t){ if(!t) return; walk(t->l); P("%s{\"id\":%d,\"name\":\"%s\"}",cnt++?",":"",t->id,t->name); walk(t->r); }

/* ---- circular queue ---- */
static int qpush(int v){ if(q.n==QCAP) return 0; q.a[(q.f+q.n++)%QCAP]=v; return 1; }
static int qpop(void){ if(!q.n) return 0; int v=q.a[q.f]; q.f=(q.f+1)%QCAP; q.n--; return v; }

static void clean(char *d, const char *s, int cap){ int i=0; for(;s&&s[i]&&i<cap-1;i++) d[i]=(strchr("\"\\<>&",s[i])||(unsigned char)s[i]<32)?' ':s[i]; d[i]=0; }
static const char *err(const char *m){ n=0; P("{\"ok\":0,\"msg\":\"%s\"}",m); return out; }
static const char *pnote(const char *p){
    if(!strcasecmp(p,"vata")) return "Vata prakriti: prefer warm, unctuous, regular meals; avoid fasting and cold exposure.";
    if(!strcasecmp(p,"pitta")) return "Pitta prakriti: prefer cooling, mildly sweet foods; avoid excess heat, spice and stress.";
    if(!strcasecmp(p,"kapha")) return "Kapha prakriti: prefer light, warm, dry foods; avoid heavy, oily, sweet food and day sleep.";
    return "Constitution (Mizaj / Mukkutram / other): physician to individualise.";
}
static void pj(Patient *p){ P("{\"ok\":1,\"id\":%d,\"name\":\"%s\",\"age\":%d,\"prakriti\":\"%s\",\"cc\":\"%s\"",p->id,p->name,p->age,p->prakriti,p->cc); }
static void visits(Patient *p){ P(",\"visits\":["); int i=0; for(Visit *v=p->visits;v;v=v->next) P("%s{\"term\":\"%s\",\"namc\":\"%s\",\"tm2\":\"%s\"}",i++?",":"",v->term,v->namc,v->tm2); P("]"); }

const char *api_register(const char *nm,int age,const char *pk,const char *cc){
    if(q.n==QCAP) return err("Queue is full");
    Patient *p=calloc(1,sizeof *p); if(!p) return err("Out of memory");
    p->id=nextid++; p->age=age; clean(p->name,nm,40); clean(p->prakriti,pk,12); clean(p->cc,cc,96);
    root=ins(root,p); qpush(p->id); n=0; P("{\"ok\":1,\"id\":%d,\"queued\":%d}",p->id,q.n); return out;
}
const char *api_next(void){ int id=qpop(); if(!id) return err("Queue is empty"); n=0; pj(find(id)); P("}"); return out; }
const char *api_suggest(const char *text){
    init(); char t[128],kw[160]; clean(t,text,128); for(char *c=t;*c;c++) *c=tolower((unsigned char)*c);
    n=0; P("{\"ok\":1,\"matches\":["); int first=1;
    for(int i=0;i<ND;i++){ int s=0; snprintf(kw,sizeof kw,"%s",db[i].kw);
        for(char *k=strtok(kw,",");k;k=strtok(NULL,",")) if(strstr(t,k)) s++;
        if(s){ P("%s{\"term\":\"%s\",\"system\":\"%s\",\"namc\":\"%s\",\"tm2\":\"%s\",\"score\":%d}",first?"":",",db[i].term,db[i].system,db[i].namc,db[i].tm2,s); first=0; } }
    P("]}"); return out;
}
const char *api_finalize(int id,const char *term){
    Patient *p=find(id); Entry *e=lookup(term);
    if(!p) return err("Unknown patient ID");
    if(!e) return err("Unknown term");
    Visit *v=calloc(1,sizeof *v); if(!v) return err("Out of memory");
    snprintf(v->term,sizeof v->term,"%s",e->term); snprintf(v->namc,sizeof v->namc,"%s",e->namc); snprintf(v->tm2,sizeof v->tm2,"%s",e->tm2);
    Visit **pp=&p->visits; while(*pp) pp=&(*pp)->next; *pp=v;          /* append at tail */
    if(us.top<SCAP) us.pid[us.top++]=id;                               /* push undo */
    n=0; P("{\"ok\":1,\"namc\":\"%s\",\"tm2\":\"%s\"}",e->namc,e->tm2); return out;
}
const char *api_undo(void){
    if(!us.top) return err("Nothing to undo");
    Patient *p=find(us.pid[--us.top]); Visit **pp=&p->visits; while((*pp)->next) pp=&(*pp)->next;
    free(*pp); *pp=NULL; n=0; P("{\"ok\":1}"); return out;
}
const char *api_care(const char *term,const char *pk){
    Entry *e=lookup(term); if(!e) return err("Unknown term"); n=0;
    P("{\"ok\":1,\"term\":\"%s\",\"aushadhi\":\"%s\",\"kala\":\"%s\",\"pathya\":\"%s\",\"apathya\":\"%s\",\"prakriti\":\"%s\"}",e->term,e->aush,e->kala,e->pathya,e->apathya,pnote(pk)); return out;
}
const char *api_patient(int id){ Patient *p=find(id); if(!p) return err("Unknown patient ID"); n=0; pj(p); visits(p); P("}"); return out; }
const char *api_bill(int id){ Patient *p=find(id); if(!p) return err("Unknown patient ID"); if(!p->visits) return err("No finalized diagnosis yet"); n=0; pj(p); visits(p); P(",\"note\":\"Dual coding: NAMASTE + ICD-11 TM2\"}"); return out; }
const char *api_state(void){
    init(); n=0; P("{\"ok\":1,\"queue\":["); for(int i=0;i<q.n;i++) P("%s%d",i?",":"",q.a[(q.f+i)%QCAP]);
    P("],\"stack\":%d,\"tree\":[",us.top); cnt=0; walk(root); P("],\"buckets\":[");
    for(int b=0;b<H;b++){ int k=0; for(Entry *e=tab[b];e;e=e->next) k++; P("%s%d",b?",":"",k); }
    P("]}"); return out;
}
