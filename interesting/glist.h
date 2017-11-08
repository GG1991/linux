#ifndef GLIST_H
#define GLIST_H

/*
** generic list
*/

typedef int  (*fcmp) (void *, void *);
/* typedef void (*fprt) (FILE *, void *); */


struct _node_g_list
{
  void *data;
  struct _node_g_list *next;
};
typedef struct _node_g_list node_g_list;

struct _g_list
{
  node_g_list *head;
  node_g_list *tail;
  int sizedata;
  int sizelist;
  fcmp cmp;
  /*        fprt       prt;           // funcao de impressao
  void       errorcmp();    // erro de comparacao
  void       erroralloc();  // erro de alocacao
  void       errorinit();   // erro de inicializacao
  void       errorprt();    // erro de impressao
  */
};
typedef struct _g_list g_list;

int g_list_init (g_list *gl, int sd, fcmp cmp);
int g_list_clear (g_list *gl);
int g_list_insertfirst (g_list *gl, void *data);
int g_list_insertlast (g_list *gl, void *data);
int g_list_insertsort (g_list *gl, void *data); 
int g_list_insertsortexclusive (g_list *gl, void *data); 
int g_list_delfirst (g_list *gl);
int g_list_dellast (g_list *gl);
int g_list_delnode (g_list *gl, void *data);
int g_list_delnodesort (g_list *gl, void *data);
int g_list_search (g_list *gl, void *data);
int g_list_searchsort (g_list *gl, void *data);

#endif
/* GLIST_H */
