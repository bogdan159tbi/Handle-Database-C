#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataQuery.h"
#include "DataDefinition.h"

#ifndef _DATAMANIPULATIION_
#define _DATAMANIPULATIION_


void addTable(t_table **t,char colVal[50])
{
char *tok = strtok(colVal," ");

if((*t)->type == INT)
{
//adauga linie noua in tabel cu colVal valori pt coloane
t_intLine *l = (t_intLine*)(*t)->lines;
if(!l){
	l = malloc(sizeof(t_intLine));
	if(!l)
		return;
	t_intCell *aux,*prev = NULL;
	while(tok)
	{
		aux = malloc(sizeof(t_intCell));
		if(!aux){
			free(l);
			return;
		}
		aux->value = atoi(tok);
		if(l->cells)
		{
			prev->next = aux;
			prev = aux;
		}
		else
		{	
			l->cells = aux;
			prev = aux;
		}
		tok = strtok(NULL," ");
	}
	(*t)->lines = (t_intLine*)l;
free(aux);

}
else{
for(; l->next != NULL ; l = l->next);
t_intLine *l2 = malloc(sizeof(t_intLine));
if(!l2)
return;
	t_intCell *aux,*prev = NULL;
	while(tok)
	{
		aux = malloc(sizeof(t_intCell));
		if(!aux){
			free(l2);
			return;
		}
		aux->value = atoi(tok);
		if(l2->cells)
		{
			prev->next = aux;
			prev = aux;
		}
		else 
		{	
			l2->cells = aux;
			prev = aux;
		}
		tok = strtok(NULL," ");
	}
l->next = l2;
free(aux);
}


}
else if((*t)->type == FLOAT)
{
//adauga linie noua in tabel cu colVal valori pt coloane
t_floatLine *l = (t_floatLine*)(*t)->lines;
if(!l){
	l = malloc(sizeof(t_floatLine));
	if(!l)
		return;
	t_floatCell *aux,*prev = NULL;
	while(tok)
	{
		aux = malloc(sizeof(t_floatCell));
		if(!aux){
			free(l);
			return;
		}
		aux->value = atof(tok);
		if(prev)
		{
			prev->next = aux;
			prev = aux;
		}
		else
		{	
			l->cells = aux;
			prev = aux;
		}
		tok = strtok(NULL," ");
	}
	(*t)->lines =(t_stringLine*)l;
	free(aux);

}
else{
for(; l->next != NULL ; l = l->next);
t_floatLine *l2 = malloc(sizeof(t_floatLine));
if(!l2)
return;
	t_floatCell *aux,*prev = NULL;
	while(tok)
	{
		aux = malloc(sizeof(t_floatCell));
		if(!aux){
			free(l2);
			return;
		}
		aux->value = atof(tok);
		if(prev)
		{
			prev->next = aux;
			prev = aux;
		}
		else
		{	
			l2->cells = aux;
			prev = aux;
		}
		tok = strtok(NULL," ");
	}
l->next = l2;
free(aux);

}


}
else if((*t)->type == STRING)
{
	t_stringLine *l = (t_stringLine*)(*t)->lines;
if(!l){
	l = malloc(sizeof(t_stringLine));
	if(!l)
		return;
	t_stringCell *aux,*prev = NULL;
	while(tok)
	{
		aux = malloc(sizeof(t_stringCell));
		if(!aux){
			free(l);
			return;
		}
		aux->value = malloc(30);
		strcpy(aux->value,tok);
		if(prev)
		{
			prev->next = aux;
			prev = aux;
		}
		else
		{	
			l->cells = aux;
			prev = aux;
		}
		tok = strtok(NULL," ");
	}
	(*t)->lines =(t_floatLine*)l;
	free(aux);

}
else{
for(; l->next != NULL ; l = l->next);
t_stringLine *l2 = malloc(sizeof(t_stringLine));
if(!l2)
return;
	t_stringCell *aux,*prev = NULL;
	while(tok)
	{
		aux = malloc(sizeof(t_stringCell));
		if(!aux){
			free(l2);
			return;
		}
		aux->value = malloc(30);
		strcpy(aux->value,tok);
		if(prev)
		{
			prev->next = aux;
			prev = aux;
		}
		else
		{	
			l2->cells = aux;
			prev = aux;
		}
		tok = strtok(NULL," ");
	}
l->next = l2;
free(aux);

}

}
}

void deleteLine(t_table **t,t_column *c,char rel[4],char value[100])//t,colName,rel,va
{
	/*
	t_column *col = (*t)->columns;
	int nr = 0;
	for( ; col != NULL ; col = col->next,nr++)
		if(!strcmp(col->name,c->name))
			break;
	t_table *table = *t;
	if((*t)->type == INT)
  	{
  		t_intLine *l = (*t)->lines,*aux,*prev = NULL;//t_stringLine *line,int whichColumn,char *value,char *rel
  		if(checkIntLine(l,nr,atoi(value),rel))
  		{
  			aux = l;
  			(*t)->lines = l->next;
  			deleteIntCells(&aux->cells);
  			free(aux);
  		}
  		else
  		{
  			for(prev = l; l != NULL; prev = l)
  			  if(checkIntLine(l,nr,atoi(value),rel))
  			  {
  			  	aux = l;
  			  	prev->next = l->next;
  			  	l = l->next;
  			  	deleteIntCells(&aux->cells);
  			  }
  			  else
  			  	l = l->next;
  		}
  	}
	else if((*t)->type == FLOAT)
	{
		t_floatLine *l = (*t)->lines,*aux,*prev = NULL;//t_stringLine *line,int whichColumn,char *value,char *rel
  		if(checkFloatLine(l,nr,atoi(value),rel))
  		{
  			aux = l;
  			(*t)->lines = l->next;
  			deleteFloatCells(&aux->cells);
  			free(aux);
  		}
  		else
  		{
  			for(prev = l; l != NULL; prev = l)
  			  if(checkFloatLine(l,nr,atof(value),rel))
  			  {
  			  	aux = l;
  			  	prev->next = l->next;
  			  	l = l->next;
  			  	deleteFloatCells(&aux->cells);
  			  }
  			  else
  			  	l = l->next;
  		}

	}
	else if ((*t)->type == STRING)
	{t_stringLine *l = (*t)->lines,*aux,*prev = NULL;//t_stringLine *line,int whichColumn,char *value,char *rel
  		if(checkStringLine(l,nr,valueg,rel))
  		{
  			aux = l;
  			(*t)->lines = l->next;
  			deleteStringCells(&aux->cells);
  			free(aux);
  		}
  		else
  		{
  			for(prev = l; l != NULL; prev = l)
  			  if(checkStringLine(l,nr,value,rel))
  			  {
  			  	aux = l;
  			  	prev->next = l->next;
  			  	l = l->next;
  			  	deleteStringCells(&aux->cells);
  			  }
  			  else
  			  	l = l->next;
  		}

	}
	*/
}
void clearTable(t_table *t,char tname[30])
{



}


#endif