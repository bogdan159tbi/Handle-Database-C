#include <stdio.h>
#include "DataDefinition.h"
#include <string.h>
#include "structures.h"
#include "DataManipulation.h"
#include "DataQuery.h"
#define DELIM " "

t_table *tableExists(t_db *db,char name[30])
{
	t_table *t;
	if(db->tables == NULL)
		return 0;
	for(t = db->tables; t != NULL; t = t->next)
		if( !strcmp(name,t->name))
			return t;
	return NULL;
}
t_column *columnExists(t_column *c,char name[30])
{
	for(; c!= NULL; c = c->next)
		if(!strcmp(c->name, name))
			return c;
	return NULL;
}
int modificaLinii(t_table **t,t_column *c,char rel[4],char value[30])
{
	t_column *col = (*t)->columns;
	int nr = 0;
	for( ; col != NULL ; col = col->next,nr++)
		if(!strcmp(col->name,c->name))
			break;
	t_table *table = *t;
	if((*t)->type == INT)
  	{	
  		t_intLine *l = (*t)->lines,*aux,*prev = NULL;//t_stringLine *line,int whichColumn,char *value,char *rel
  			//deleteIntCells(&aux->cells);
  			//free(aux)
  			for(; l != NULL;)
  			  if(checkIntLine(l,nr,atoi(value),rel))
  			  {
  			  	aux = l;
  			  	l = l->next;
  			  	if(prev)
  			  	prev->next = l;
   			  	else
   			  		(*t)->lines = l;
  			  	deleteIntCells(&aux->cells);
  			  }
  			  else{
  			  	prev = l;
  			  	l = l->next;
  			  }
  	}
	else if((*t)->type == FLOAT)
	{
		t_floatLine *l = (*t)->lines,*aux,*prev = NULL;//t_stringLine *line,int whichColumn,char *value,char *rel
  			//deleteFloatCells(&aux->cells);
  			//free(aux);
  			for(; l != NULL; )
  			  if(checkFloatLine(l,nr,atof(value),rel))
  			  {
  			  	aux = l;
  			  	l = l->next;
  			  	if(prev)
  			  	prev->next = l;
  			  	else
  			  	(*t)->lines = l;
  			  	deleteFloatCells(&aux->cells);
  			  }
  			  else{
  			  	prev = l;
  			  	l = l->next;
  			  }

	}
	else if ((*t)->type == STRING)
	{
	t_stringLine *l = (*t)->lines,*aux,*prev = NULL;//t_stringLine *line,int whichColumn,char *value,char *rel
  	//deleteStringCells(&aux->cells);

 	for(; l != NULL; ){
  	  if(checkStringLine(l,nr,value,rel))
  	  {
  	  	aux = l;
  	  	l = l->next;
  	  	if(prev && l)
  	  	prev->next = l;
  	  	else if(prev && !l)
  	  		prev->next = NULL;
  	  	else if(!prev && !l)
  	  		{	aux = (*t)->lines;
  	  			deleteStringCells(&aux->cells);
  	  			(*t)->lines = NULL;
  	  		}
  	  	else if(!prev && l)
  	  	{
  	  		aux = (*t)->lines;
  	  		(*t)->lines = aux->next;
  	  		deleteStringCells(&aux->cells);
  	  	}
   	//deleteStringCells(&aux->cells);
  	  }
  	  else{
  	  	prev = l;
  	  	l = l->next;
  		}
  	}
	}
}

int main()
{
	char request[MAX_CMD_LEN];
	t_db *db;
	
	while(fgets(request,MAX_CMD_LEN,stdin)){
		
		char *tok = strtok(request," ");
		if( !strcmp(tok,"INIT_DB"))
		{
			tok = strtok(NULL,"\n");
			db = initDB(tok);
		}
		else if (!strcmp("CREATE",tok))
		{
			tok = strtok(NULL," ");
			char tabel[30],tip[8],valoriColoane[444];
			strcpy(tabel,tok);
			tok = strtok(NULL," ");
			strcpy(tip,tok);
			tok = strtok(NULL,"\n");
			strcpy(valoriColoane,tok);
			if(tableExists(db,tabel) == NULL){
				createTable(&db->tables,tabel,tip,valoriColoane);
			}
			else
				printf("Table \"%s\" already exists.\n",tabel);
		}
		else if (!strcmp("DELETE",tok))
		{ 
			tok = strtok(NULL," ");
			char name[30];
			strcpy(name,tok);
			tok = strtok(NULL," ");
			if(tok)
			{
				char colName[30];
				strcpy(colName,tok);
				char rel[5];
				tok = strtok(NULL," ");
				strcpy(rel,tok);
				char val[444];
				tok = strtok(NULL," ");
				strcpy(val,tok);
				t_table *t =tableExists(db,name);
				if(t)
				{	//check column
					t_column *c = columnExists(t->columns,colName);
					if(c)
					{
						//deleteLine(&t,c,rel,val);
						val[strlen(val)-1 ] = '\0';
						modificaLinii(&t,c,rel,val);
					}
					else
					printf("Table \"%s\" does not contain column \"%s\".\n",t->name,colName);
				}
				else
				printf("Table \"%s\" not found in database.\n",name);

			}
			else
			{	
				name[strlen(name)-1] ='\0';
				t_table *t = tableExists(db,name),*prev = NULL;
				t_table *p = db->tables;
				if(t){
					if(db->tables == t)
					{
					t_table *aux = t->next;
					//deleteTable(&t);
					db->tables = aux;
			    	}
					else
					{	
					for(prev = p; p != NULL;prev = p, p = p->next)
						if(!strcmp(p->name,name))
								break;
						
						prev->next = p ->next;
					deleteTable(&p);
					}
				}
				else{
				printf("Table \"%s\" not found in database.\n",name);
				}
			}
			/*
			if(tableExists(db,name) && !tok){
			printf("fara relatie\n");
			deleteTable(&db->tables,name);
			}
			else if(!tok && tableExists(db,name) == NULL){

				printf("Table \"%s\"  not found in database.\n",name);
			}
			else if(tableExists(db,name) && tok)
			{
			char cname[30];
			strcpy(cname,tok);
			tok = strtok(NULL," ");
			char val[23],rel[5];
			strcpy(rel,tok);
			tok = strtok(NULL," ");
			strcpy(val,tok);
			}
		*/
		}
		else if (!strcmp("PRINT_DB\n",tok))
				printDB(db);
		else if (!strcmp("PRINT",tok))
		{	tok = strtok(NULL,"\n");
			if(tableExists(db,tok)){
			printf("TABLE: %s\n",tok);
			t_table *t = tableExists(db,tok);
			printTable(t);
			}
			else
				printf("Table \"%s\" not found in database.\n",tok);
		}
		else if (!strcmp("SEARCH",tok))
		{
			char TName[20],CName[20],Relation[4],Value[444];
			tok = strtok(NULL," ");
			strcpy(TName,tok);
			tok = strtok(NULL," ");
			strcpy(CName,tok);

			tok = strtok(NULL," ");
			strcpy(Relation,tok);

			tok = strtok(NULL,"\n");
			strcpy(Value,tok);
			
			t_table *t = tableExists(db,TName);
			if(t){
			t_column *c = columnExists(t->columns,CName);
			if(!c)
			{
			printf("Table \"%s\" does not contain column \"%s\".\n",TName,CName);

			}
			else{
			int ok = 0;
			if(t->type == INT)
			ok = findIntLine(t,TName,CName,Relation,Value);
			else if(t->type == FLOAT)
				ok = findFloatLine(t,TName,CName,Relation,Value);
			else
				ok =findStringLine(t,TName,CName,Relation,Value);
			if(!ok)
			printf("\n");	

				}
	
			}
			else
				printf("Table \"%s\" not found in database.\n",TName);
			
		}
		else if(!strcmp("ADD",tok))
		{
			char TName[20];
			tok = strtok(NULL," ");
			strcpy(TName,tok);
			
			char ColValues[100];
			tok = strtok(NULL,"\n");
			strcpy(ColValues,tok);
			if(tableExists(db,TName)){	
			t_table *t = tableExists(db,TName);
			addTable(&t,ColValues);	
			}
			else
				printf("Table \"%s\" not found in database.\n",TName);
		
		}
		/*
		else if(!strcmp("DELETE",tok))
		{
			char TName[20],CName[20],Relation[4],Value[20];
			tok = strtok(NULL," ");
			strcpy(TName,tok);

			tok = strtok(NULL," ");
			strcpy(CName,tok);

			tok = strtok(NULL," ");
			strcpy(Relation,tok);

			tok = strtok(NULL,"\n");
			strcpy(Value,tok);
			//deleteLine(TName,CName,Relation,Value);
		}
		*/
		else if(!strcmp("CLEAR",tok))
		{
			char TName[20];
			tok = strtok(NULL,"\n");
			strcpy(TName,tok);
			t_table *t = tableExists(db,TName);
			if(t)
			{
				//clearTable(t,TName);
			}
			else
				printf("Table \"%s\" not found in database.\n",TName);
		}
		else if(!strcmp("DELETE_DB\n",tok))
			deleteDB(&db);
		}
	
	return 0;
}
