#ifndef AYUSH_H
#define AYUSH_H
#define QCAP 32
#define SCAP 64

/* Singly linked list: a patient's visit history */
typedef struct Visit { char term[32], namc[16], tm2[16]; struct Visit *next; } Visit;
/* Binary search tree node: patient index keyed by id */
typedef struct Patient { int id, age; char name[40], prakriti[12], cc[96];
    Visit *visits; struct Patient *l, *r; } Patient;
/* Circular array queue: OPD waiting line (FIFO) */
typedef struct { int a[QCAP], f, n; } Queue;
/* Array stack: undo history of finalized diagnoses (LIFO) */
typedef struct { int pid[SCAP], top; } Stack;
/* Hash table chain node: NAMASTE term -> ICD-11 TM2 code + care rules */
typedef struct Entry { const char *term, *system, *namc, *tm2, *kw, *aush, *kala, *pathya, *apathya;
    struct Entry *next; } Entry;

extern Entry db[]; extern int ND;

/* Every call returns a JSON string held in a static buffer */
const char *api_register(const char *name, int age, const char *prakriti, const char *complaint);
const char *api_next(void);
const char *api_suggest(const char *text);
const char *api_finalize(int id, const char *term);
const char *api_undo(void);
const char *api_care(const char *term, const char *prakriti);
const char *api_patient(int id);
const char *api_bill(int id);
const char *api_state(void);
#endif
