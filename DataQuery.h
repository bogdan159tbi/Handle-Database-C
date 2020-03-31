#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataDefinition.h"

#ifndef _DATAQUERY_
#define _DATAQUERY_

int len(int nr)
{
	int c = 0;
	if(nr == 0)
		return 1;
	while(nr)
	{
		c++;
		nr = nr/10;
	}
	return c;
}

void printColumns(t_column *columns)
{	int j,coloane = 0;
	for( ;columns != NULL; columns = columns->next){
		printf("%s",columns->name);
		for(int i = 0 ; i < MAX_COLUMN_NAME_LEN - strlen(columns->name) + 1; i++)
			printf(" ");
		coloane++;
	}
	printf("\n");

	for(j = 0 ; j < coloane; j++){
	for(int i = 0; i < MAX_COLUMN_NAME_LEN ;i++)
			printf("-");
	printf(" ");
	}
	printf("\n");

}
void printIntCell(t_intCell *cells)
{	
	for(;cells != NULL; cells = cells->next){
		printf("%d",cells->value);
		for(int i = 0; i < MAX_COLUMN_NAME_LEN  -len(cells->value) + 1 ;i++)
			printf(" ");
	}
	printf("\n");
}
void printFloatCells(t_floatCell *cells)
{
	int celule = 0,lungime = len(cells->value);
	for( ;cells != NULL ; cells = cells->next){
		printf("%f ",cells->value);
		for(int i = 0; i < MAX_COLUMN_NAME_LEN - 7  - lungime; i++)
			printf(" ");
	}
	printf("\n");

}
void printStringCells(t_stringCell *cells)
{	
	int celule = 0;
	for( ;cells != NULL ; cells = cells->next)
		{printf("%s",cells->value);
		 for(int j = 0; j < MAX_COLUMN_NAME_LEN - strlen(cells->value) + 1;j++)
		 	 printf(" ");
		}
	printf("\n");
}
void printStringLines(t_stringLine *lines){
	for(; lines != NULL ; lines = lines->next)
		printStringCells(lines->cells);

}
void printIntLines(t_intLine *lines)
{
	for(; lines != NULL ; lines = lines->next){
		
		printIntCell(lines->cells);
	}
	
}
void printFloatLines(t_floatLine *lines)
{	
	for(; lines != NULL ; lines = lines->next)
		printFloatCells(lines->cells);
}

void printTable(t_table *t)
{
	printColumns(t->columns);
		if(t->type == INT){
			printIntLines(t->lines);
		}
		else if(t->type == FLOAT)
			printFloatLines(t->lines);
		else if (t->type == STRING)
			printStringLines(t->lines);
		printf("\n");
}
void printDB(t_db *db)
{
	printf("DATABASE: %s\n\n",db->name);
	t_table *t = db->tables;
	for(; t != NULL ; t = t->next)
	{	printf("TABLE: %s\n",t->name);
		printColumns(t->columns);
		if(t->type == INT)
			printIntLines(t->lines);
		else if(t->type == FLOAT)
			printFloatLines(t->lines);
		else if (t->type == STRING)
			printStringLines(t->lines);
		printf("\n");
	}
	//print lines -> print cells before
	//print table

}
int checkIntLine(t_intLine *line,int whichColumn,int val,char *rel)
{

	t_intCell *cell = line->cells;
	for(int column = 0; cell != NULL,column <= whichColumn; cell = cell->next,column++)
	{
	  if(column == whichColumn  ){
	  if(!strcmp(rel,"<")){
	  	if(val > cell->value)
	  		return 1;
	  }
	  if(!strcmp(rel,"<="))
	  	if(val > cell->value || val == cell->value)
	  		return 1;
   	  if(!strcmp(rel,">")){
   	  	if(val < cell->value){
   	  		return 1;
   	  	}
   	  }
   	  if(!strcmp(rel,">="))
   	  	if(val <= cell->value)
   	  		return 1;
   	  if(!strcmp(rel,"!="))
   	  	if(val != cell->value)
   	  		return 1;
   	  if(!strcmp(rel,"=="))
   	  	if(val == cell->value)
   	  		return 1;
	}
}

	return 0;
}
int findIntLine(t_table *t,char tname[30],char cname[30],char rel[5],char val[444])
{
	t_column *c;
	int nrColumn = 0;
	int ok = 0;
	int valInt = atoi(val);
		for(c = t->columns ; c != NULL; c = c->next,nrColumn++)
			if (!strcmp(c->name,cname))
				break;
		if(c)
		{
			printf("TABLE: %s\n",tname);
					printColumns(t->columns);
			t_intLine *l = t->lines;
			for(; l != NULL; l = l->next)
				if(checkIntLine(l,nrColumn,valInt,rel))
				{
				
					printIntCell(l->cells); // in loc de print line
					ok = 1;
				}
		}
		else
		printf("Table \"%s\" does not contain column \"%s\".\n",tname,cname);
	if(ok)
		printf("\n");
	return ok;
}
int checkFloatLine(t_floatLine *line,int whichColumn,float val,char *rel)
{
	t_floatCell *cell = line->cells;
	for(int column = 0; cell != NULL,column <= whichColumn; cell = cell->next,column++)
	{
	  if(column == whichColumn){

	  if(!strcmp(rel,"<"))
	  	if(val > cell->value)
	  		return 1;
	  if(!strcmp(rel,"<="))
	  	if(val > cell->value || val == cell->value)
	  		return 1;
   	  if(!strcmp(rel,">"))
   	  	if(val < cell->value)
   	  		return 1;
   	  if(!strcmp(rel,">="))
   	  	if(val <= cell->value)
   	  		return 1;
   	  if(!strcmp(rel,"!="))
   	  	if(val != cell->value)
   	  		return 1;
   	  if(!strcmp(rel,"=="))
   	  	if(val == cell->value)
   	  		return 1;
	}
}
	return 0;
}
int  findFloatLine(t_table *t,char tname[30],char cname[30],char rel[5],char val[444])
{
	t_column *c;
	int nrColumn = 0;
	int ok = 0;
	float valFloat = atof(val);
		for(c = t->columns ; c != NULL; c = c->next,nrColumn++)
			if (!strcmp(c->name,cname))
				break;
		if(c)
		{printf("TABLE: %s\n",tname);
		 printColumns(t->columns);
			t_floatLine *l = t->lines;
			for(; l != NULL; l = l->next)
				if(checkFloatLine(l,nrColumn,valFloat,rel))
				{
					printFloatCells(l->cells);//in loc de print lien
					 ok = 1;
				}
		}
		else
		printf("Table \"%s\" does not contain column \"%s\".\n",tname,cname);
	if(ok)
		printf("\n");
	return ok;
}
int checkStringLine(t_stringLine *line,int whichColumn,char *value,char *rel)
{
	t_stringCell *cel = line->cells;
	int coloana = 0;
	for(; cel != NULL ,coloana <= whichColumn; cel = cel->next,coloana++)
	 {
	 if(coloana == whichColumn){
	 if(!strcmp(rel,"<"))
		if (strcmp(value,cel->value) > 0)
		{
			return 1;
		}
	  if(!strcmp(rel,"<="))
		if (strcmp(value,cel->value) > 0 || strcmp(value,cel->value) == 0)
			return 1;
	  if(!strcmp(rel,">"))
		if (strcmp(value,cel->value) < 0){
			//printf("verific %s > %s care da %d\n",cel->value,value,strcmp(value,cel->value));
			return 1;
		}
	  if(!strcmp(rel,">="))
		if (strcmp(value,cel->value) < 0 || strcmp(value,cel->value) == 0)
			return 1;
	  if(!strcmp(rel,"!="))
		if (strcmp(value,cel->value) != 0)
			return 1;
	   if(!strcmp(rel,"=="))
		if (strcmp(value,cel->value) == 0)
			return 1;

			}
	}

	return 0;
}

int findStringLine(t_table *t,char tname[30],char cname[30],char rel[5],char val[444])
{
	int nr = 0;
	int ok = 0;
	t_column *col = t->columns;
	for(; col != NULL ; col = col->next,nr++)
		if (!strcmp(col->name,cname))
			break;
	
	if(col){
		printf("TABLE: %s\n",tname);
		printColumns(t->columns);
		t_stringLine *lin = t->lines;
		for(; lin != NULL ;lin = lin->next)
			if (checkStringLine(lin,nr,val,rel))
			 {	
			printStringCells(lin->cells);
			ok = 1;
			 }
		  }
	else
		printf("Table \"%s\" does not contain column \"%s\".\n",tname,cname);
	if(ok)
		printf("\n");
	return ok;
}

#endif