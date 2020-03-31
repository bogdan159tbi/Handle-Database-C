#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _DATADEFINITION_
#define _DATADEFINITION_

t_db *initDB(char name[20])
{
	t_db *db = calloc(1,sizeof(t_db));
	if(!db)
		return NULL;
	strcpy(db->name,name);
	db->tables = NULL;
	return db;
}

t_column *initColumn(char name[20])
{
	t_column *col = calloc(1,sizeof(t_column));
	if(!col)
		return NULL;
	strcpy(col->name,name);
	return col;
}

int createTable(t_table **t,char TName[30],char tip[10],char valoriColoane[444])
{
	t_table *tables = *t,*aux;
	if(*t){
	for(;tables->next != NULL ; tables = tables->next);

	aux = calloc(1,sizeof(t_table));
	if(!aux)
		return 1;
	strcpy(aux->name,TName);

	if (!strcmp(tip,"STRING"))
		aux->type =  STRING;
	if (!strcmp(tip,"INT"))
		aux->type =  INT;
	if (!strcmp(tip,"FLOAT"))
		aux->type =  FLOAT;
	tables->next = aux;
	aux->next = NULL;
	//adaugare coloane
	t_column *c,*prev = NULL;
	char *tok;
	tok = strtok(valoriColoane," ");
	aux->columns = initColumn(tok);
	prev = aux->columns;
	while(tok =  strtok(NULL," "))
	{
		c = initColumn(tok);
		prev->next = c;
		prev = c;
	}
	aux->lines = NULL;
	}
	else
	{
	(*t) = calloc(1,sizeof(t_table));
	if (!strcmp(tip,"STRING")){
		(*t)->type =  STRING;
	}
	if (!strcmp(tip,"INT")){
		(*t)->type =  INT;
	}
	if (!strcmp(tip,"FLOAT")){
		(*t)->type =  FLOAT;
	}
	strcpy((*t)->name,TName);
	(*t)->next = NULL;
	
	t_column *c,*prev = NULL;
	char *tok = strtok(valoriColoane," ");
	(*t)->columns = initColumn(tok);
	prev = (*t)->columns;
	while(tok =  strtok(NULL," "))
	{
		c = initColumn(tok);
		prev->next = c;
		prev = c;
	}
	(*t)->lines = NULL;

	}
	return 0;
}

void deleteColumns(t_column **c)
{
	t_column *col = *c,*aux;
	for(;col != NULL; )
	{
		aux = col;
		col = col->next;
		free(aux);
	}
	//free(*c);
}
void deleteIntCells(t_intCell **cell)
{
	t_intCell *aux = NULL,*c = *cell;
	for(;c != NULL;)
	{
		aux = c;
		c = c->next;
		if(aux)
		free(aux);
	}
	//free(*cell);
}
void deleteIntLines(t_intLine **lin)
{
	t_intLine *linie = *lin,*aux;
	for(; linie != NULL; )
	{
		aux = linie;
		linie = linie->next;
		t_intCell *c = aux->cells;
		deleteIntCells(&c);
		free(aux);
	}
	//free(*lin);

}
void deleteFloatCells(t_floatCell **cell)
{
	t_floatCell *aux,*c = *cell;
	for(;c != NULL;)
	{
		aux = c;
		c = c->next;
		free(aux);
	}
	//free(*cell);
}
void deleteFloatLines(t_floatLine **lin)
{
	t_floatLine *linie = *lin,*aux;
	for(; linie != NULL; )
	{
		aux = linie;
		linie = linie->next;
		t_floatCell *c = aux->cells;
		deleteFloatCells(&c);
		free(aux);
	}
	//free(*lin);

}
void deleteStringCells(t_stringCell **cell)
{
	t_stringCell *aux,*c = *cell;
	for(;c != NULL;)
	{
		aux = c;
		c = c->next;
		free(aux->value);
		free(aux);
	}
	//free(*cell);
}
void deleteStringLines(t_stringLine **lin)
{
	t_stringLine *l = *lin,*aux;
	for(;l != NULL ;)
	{
		aux = l;
		l = l->next;
		t_stringCell *c = aux->cells;
		deleteStringCells(&c);
		free(aux);
	}
	//free(*lin);// = NULL;
}
void deleteTable(t_table **t)//,char name[30])
{
	/*
	t_table *tab = *t,*prev = NULL,*aux;
	if(!strcmp((*t)->name,name))
	{	
		aux = *t;
		*t = (*t)->next;
		t_column *c = aux->columns;
		deleteColumns(&c);
		if(aux->type == INT){
		t_intLine *l = aux->lines;
		deleteIntLines(&l);
		}
		else if(aux->type == FLOAT)
		{t_floatLine *l = aux->lines;
		deleteFloatLines(&l);
		}
		else if(aux->type == STRING)
		{
		t_stringLine *l = aux->lines;
		deleteStringLines(&l);
		}
		free(aux);
		aux = NULL;
		
		return;
	}
	else
	{
		for( prev = tab, tab = tab->next;tab != NULL ;prev = tab,tab = tab->next)
			if(!strcmp(tab->name,name))
			{
				aux = tab;
				prev->next = tab->next;
				deleteColumns(&tab->columns);
				if(tab->type == INT){
				t_intLine *l = tab->lines;
				deleteIntLines(&l);
						}
				else if(tab->type == FLOAT)
				{
				t_stringLine *l = tab->lines;
				deleteStringLines(&l);
				}
				else if(tab->type == FLOAT)
				{
				t_floatLine *l = tab->lines;
				deleteFloatLines(&l);
				}
			}
	}
	*/
	t_column *c = (*t)->columns;
	deleteColumns(&c);

	if((*t)->type == INT){
		t_intLine *l = (*t)->lines;
		deleteIntLines(&l);
						}
		else if((*t)->type == FLOAT)
		{
		t_stringLine *l = (*t)->lines;
		deleteStringLines(&l);
		}
		else if((*t)->type == FLOAT)
		{
		t_floatLine *l = (*t)->lines;
		deleteFloatLines(&l);
		}

	
}

void deleteDB(t_db **db)
{
	if(*db){
	t_db *data = *db;
	t_table *t = data->tables,*prev = NULL,*aux = NULL;
	
	for(; t != NULL ;prev = t)
		{	
		aux = t;
		t = t->next;
		deleteTable(&aux);
		free(aux);
		}
	//(*db)->tables = NULL;
	free(*db);
	*db = NULL;
}
}

#endif