/*
** generic list implementation
*/
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"
#include "glist.h"


int g_list_init (g_list *gl, int sd, fcmp cmp)
{
  gl->head = gl->tail = NULL;
  gl->sizedata = sd;
  gl->sizelist = 0;
  gl->cmp = cmp;
  return 0;
}

int g_list_clear (g_list *gl)
{
  node_g_list *aux, *current;
  current = gl->head;
  while (current)
    {
      aux = current->next;
      if (gl->sizedata)
	free (current->data);
      free (current);
      current = aux;
    }
  gl->head = gl->tail = NULL;
  gl->sizelist = 0;
  return 0;
}

int g_list_insertfirst (g_list *gl, void *data)
{
  node_g_list *nnode;
  nnode = (node_g_list *) malloc (sizeof(node_g_list));
  if (!nnode)
    return -1;
  if (gl->sizedata)
    {
      nnode->data = (void *) malloc (gl->sizedata);
      if (!nnode->data)
	return -1;
      memcpy (nnode->data, data, gl->sizedata);
    }
  else
    nnode->data = data;
  nnode->next = gl->head;
  gl->head = nnode;
  gl->sizelist++;
  if (gl->sizelist == 1)
    gl->tail = nnode;
  return 0;
}

int g_list_insertlast (g_list *gl, void *data)
{
  node_g_list *nnode;
  nnode = (node_g_list *) malloc (sizeof(node_g_list));
  if (!nnode)
    return -1;
  if (gl->sizedata)
    {
      nnode->data = (void *) malloc (gl->sizedata);
      if (!nnode->data)
	return -1;
      memcpy (nnode->data, data, gl->sizedata);
    }
  else
    nnode->data = data;
  nnode->next = NULL;
  if (gl->tail)
    gl->tail->next = nnode;
  gl->tail = nnode;
  gl->sizelist++;
  if (gl->sizelist == 1)
    gl->head = nnode;
  return 0;
}

int g_list_insertsort (g_list *gl, void *data)
{
  node_g_list *nnode, *onode;
  nnode = (node_g_list *) malloc (sizeof(node_g_list));
  if (!nnode)
    return -1;
  if (gl->sizedata)
    {
      nnode->data = (void *) malloc (gl->sizedata);
      if (!nnode->data)
	return -1;
      memcpy (nnode->data, data, gl->sizedata);
    }
  else
    nnode->data = data;
  if (!gl->cmp)
    return -1;
  gl->sizelist++;
  if (gl->sizelist == 1)
    {
      gl->head = gl->tail = nnode;
      return 0;
    }
  onode = gl->head;
  while ((*gl->cmp)(onode->data, data) < 0)
    {
      onode = onode->next;
      if (!onode)
	{
	  gl->tail->next = nnode;
	  gl->tail = nnode;
	  return 0;
	}
    }
  nnode->next = onode;
  if (onode == gl->head)
    gl->head = nnode;
  return 0;
}
int g_list_insertsortexclusive (g_list *gl, void *data)
{
  void *aux;
  node_g_list *nnode, *onode;
  nnode = (node_g_list *) malloc (sizeof(node_g_list));
  if (!nnode)
    return -1;
  if (gl->sizedata)
    {
      nnode->data = (void *) malloc (gl->sizedata);
      if (!nnode->data)
	return -1;
      memcpy (nnode->data, data, gl->sizedata);
    }
  else
    nnode->data = data;
  if (!gl->cmp)
    return -1;

  gl->sizelist++;
  if (gl->sizelist == 1)
    {
      gl->head = gl->tail = nnode;
      return 0;
    }
  onode = gl->head;
  while ((*gl->cmp)(onode->data, nnode->data) < 0)
    {
       if (!onode->next)
	{
	  gl->tail->next = nnode;
	  gl->tail = nnode;
	  return 0;
	}
        onode = onode->next;  
    }
  if ((*gl->cmp)(onode->data, nnode->data) == 0)
    {
      gl->sizelist--;
      free(nnode);
      return 1;
    }
  nnode->next = onode->next;
  onode->next = nnode;
  aux=nnode->data;
  nnode->data=onode->data;
  onode->data=aux;
  if (onode == gl->head)
    gl->head = onode;
  if (nnode->next == NULL)
    gl->tail = nnode;
  return 0;
}

int g_list_delfirst (g_list *gl)
{
  node_g_list *aux;
  if (!gl->head)
    return -1;
  aux = gl->head;
  gl->head = aux->next;
  if (gl->sizedata)
    free (aux->data);
  free (aux);
  gl->sizelist--;
  return 0;
}

int g_list_dellast (g_list *gl)
{
  node_g_list *aux;
  if (!gl->head)
    return -1;
  if (gl->sizelist == 1)
    return g_list_clear(gl);
  aux = gl->head;
  while (aux->next != gl->tail)
    aux = aux->next;
  aux->next = NULL;
  if (gl->sizedata)
    free (gl->tail->data);
  free (gl->tail);
  gl->tail = aux;
  gl->sizelist--;
  return 0;
}

int g_list_delnode (g_list *gl, void *data)
{
  node_g_list *aux, *prev=NULL;
  if (!gl->head)
    return 1;
  aux = gl->head;
  while ((*gl->cmp)(aux->data, data) != 0)
    {
      prev = aux;
      aux = aux->next;
      if (!aux)
	return 1;
    }
  if (gl->sizedata)
    free (aux->data);
  if (aux == gl->head)
    gl->head = aux->next;
  else
    prev->next = aux->next;
  free (aux);
  gl->sizelist--;
  return 0;
}

int g_list_delnodesort (g_list *gl, void *data)
{
  node_g_list *aux, *prev=NULL;
  if (!gl->head)
    return 1;
  aux = gl->head;
  while ((*gl->cmp)(aux->data, data) < 0)
    {
      prev = aux;
      aux = aux->next;
      if (!aux)
	return 1;
    }
  if ((*gl->cmp)(aux->data, data) > 0)
    return 1;
  if (gl->sizedata)
    free (aux->data);
  if (aux == gl->head)
    gl->head = aux->next;
  else
    prev->next = aux->next;
  free (aux);
  gl->sizelist--;
  return 0;
}

int g_list_search (g_list *gl, void *data)
{
  node_g_list *aux/*, *prev*/;
  if (!gl->head)
    return 0;
  aux = gl->head;
  while ((*gl->cmp)(aux->data, data) != 0)
    {
      /* prev = aux; */
      aux = aux->next;
      if (!aux)
	return 0;
    }
  return 1;
}

int g_list_searchsort (g_list *gl, void *data)
{
  node_g_list *aux/* , *prev */;
  if (!gl->head)
    return 0;
  aux = gl->head;
  while ((*gl->cmp)(aux->data, data) < 0)
    {
      /* prev = aux; */
      aux = aux->next;
      if (!aux)
	return 0;
    }
  if ((*gl->cmp)(aux->data, data) > 0)
    return 0;
  return 1;
}
