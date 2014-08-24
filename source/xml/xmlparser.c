#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "private.h"
#include "xmlparser.h"
#include "xml.h"

XMLNODE *floadxmlnode(FILE *fp, char *tag, int *err);
//int killxmlnode(XMLNODE *node);

static XMLATTRIBUTE *floadattributes(FILE *fp, int *err);
static int xmlFreeAttribute(XMLATTRIBUTE *attr);
static int xmlFreeNode(XMLNODE *node);

static char *getquotedstring(FILE *fp, int *err);
static char *getdata(FILE *fp, int *err);
static char *getidentifier(FILE *fp, int *err);
static char *unescapedata(char *data);
static char *mystrdup(const char *str);

/* IScanner */
static inline int xmlIsEOF(struct xml_parse *parse, int peek)
{
	int index = 0;
	index = (parse->offset + peek);
	if (index >= parse->length) {
                return 1;
	}
	return 0;
}

static inline int xmlPeek(struct xml_parse *parse, int count)
{
	int index = 0;
	if (xmlIsEOF(parse, count)) {
		return -1;
	}
	index = (parse->offset + count);
	return (int)parse->data[index];
}

/* IScanner */
static inline int xmlRead(struct xml_parse *parse)
{
	if (xmlIsEOF(parse, 0)) {
		return -1;
	}
	return (int)parse->data[parse->offset++];
}

static inline int xmlIsLetter(int code)
{
    if ((code >= 'a' && code <= 'z') || 
        (code >= 'A' && code <= 'Z') ||
        (code == '_')) {
        return 1;
    }
    return 0;
}

XMLDOCPTR XmlOpen(char *fname, int *err)
{
	int errplaceholder;
	XMLDOC *answer;
	FILE *fp;

	if(err == 0)
	err = &errplaceholder;
	*err = 0;
	fp = fopen(fname, "r");
	if(!fp)
	{
		*err = -3;
		return 0;
	}

	answer = floadxmldoc(fp, err);
	fclose(fp);
	return answer;
}

XMLNODEPTR XmlGetRootNode(XMLDOCPTR doc)
{
	RETURN_IF_NULL(doc);
	return (doc->root);
}

XMLNODEPTR XmlGetChildNode(XMLNODEPTR node)
{
	RETURN_IF_NULL(node);
	return (node->child);
}

XMLNODEPTR XmlGetNextNode(XMLNODEPTR node)
{
	RETURN_IF_NULL(node);
	return (node->next);
}

const char *XmlGetTag(XMLNODEPTR node)
{
	RETURN_IF_NULL(node);
	return (node->tag);
}

const char *XmlGetValue(XMLNODEPTR node)
{
	RETURN_IF_NULL(node);
	return (node->data);
}

int XmlGetIntValue(XMLNODEPTR node)
{
	RETURN_IF_NULL(node);
	RETURN_IF_NULL(node->data);
	return atoi(node->data);
}

const char *XmlGetAttribute(XMLNODEPTR node, const char *attr)
{
	XMLATTRIBUTE *item;
	RETURN_IF_NULL(node);
	RETURN_IF_NULL(attr);
	for (item = node->attributes; item; item = item->next) {
		if (!strcmp(item->name, attr)) {
			return (item->value);
		}
	}
	return 0;
}

const XMLNODEPTR XmlGetNodeFromName(XMLNODEPTR parent, const char *name)
{
	XMLNODEPTR item;
	RETURN_IF_NULL(parent);
	RETURN_IF_NULL(name);
	for (item = parent->child; item; item = item->next) {
		if (!strcmp(item->tag, name)) {
			return (item);
		}
	}
	return 0;
}

int XmlFreeDoc(XMLDOCPTR doc)
{
	RETURN_IF_NULL(doc);
	xmlFreeNode(doc->root);
	free(doc);
	return 1;
}

/*
  load document from an open stream
*/
XMLDOC *floadxmldoc(FILE *fp, int *err)
{
	XMLDOC *answer;
	int ch;
	int ch1, ch2;
	XMLNODE *rootnode;
	char *tag;
	char *closetag;

 
	ch1 = fgetc(fp);
	ch2 = fgetc(fp);
	if (ch1 == '<' && ch2 == '?')
	{
		while((ch = fgetc(fp)) != EOF)
			if(ch == '>')
				break;
	}
	else if(ch1 == '<' && isalpha(ch2))
	{
		fseek(fp, -2, SEEK_CUR);
	}
	else
	{
		fseek(fp, -2, SEEK_CUR);
		*err = -4;
		return 0;
	}

  answer = malloc(sizeof(struct IXmlDoc));
  if(!answer)
    goto out_of_memory;

  answer->root = 0;

  while( (ch = fgetc(fp)) != EOF)
  {
    if(ch == '<')
	{
	  ch = fgetc(fp);
	  if(isalpha(ch))
	  {
	    ungetc(ch, fp);
        tag = getidentifier(fp, err);
		if (tag)
		{
		  rootnode = floadxmlnode(fp, tag, err);
		  if(rootnode == 0)
		    goto parse_error;
		  answer->root = rootnode;
		  closetag = getidentifier(fp, err);
		  if(strcmp(tag, closetag))
		    goto parse_error;
		  ch = fgetc(fp);
		  if(ch != '>')
		    goto parse_error;
		  free(tag);
		  free(closetag);
		  break;
		}
	  }
	  else
	  {
	    while( (ch = fgetc(fp)) != EOF)
		  if(ch == '>')
		    break;
	  }
	}
  }
  while( (ch = fgetc(fp)) != EOF)
    if(!isspace(ch))
	{
	  ungetc(ch, fp);
	  break;
	}
  return answer;
parse_error:
  if(*err == 0)
    *err = -2;
  return 0;
out_of_memory:
  if(*err == 0)
    *err = -1;
  return 0;
}



/*
  get child with tag and index
  Params: node - the node
          tag - tag of child (NULL for all children)
		  index - index number of child to retrieve
  Returns: child, or null on fail
  Notes: slow, only call for nodes with relatively small
    numbers of children. If the child list is very long, 
	step through the linked list manually.
*/
XMLNODE *xml_getchild(XMLNODE *node, const char *tag, int index)
{
  XMLNODE *next;
  int count = 0;

  if(node->child)
  {
    next = node->child;
	while(next)
	{
	  if(tag == 0 || (next->tag && !strcmp(next->tag, tag)))
	  {
	    if(count == index)
          return next;
	    count++;
	  }
	  next = next->next;
	}
  }

  return 0;
}


/*
  load a node
    err = 0 = Ok, -1 = out of memory, -2 = parse error
  Notes: recursive
*/
XMLNODE *floadxmlnode(FILE *fp, char *tag, int *err)
{
	XMLNODE *node = 0;
	XMLNODE *child = 0;
	XMLNODE *lastchild = 0;
	char *newtag = 0;
	char *closetag = 0;
	char *data = 0;
	int ch;

  node = malloc(sizeof(XMLNODE));
  if(!node)
    goto out_of_memory;
  node->tag = 0;
  node->data =0;
  node->attributes = 0;
  node->child = 0;
  node->next = 0;
  node->position = 0;

  node->tag = mystrdup(tag);
  if(!node->tag)
    goto out_of_memory;

  while( (ch = fgetc(fp)) != EOF )
    if(!isspace( (unsigned char) ch))
	  break;
  if(ch != '>')
  {
    if(ch == '/')
	  return node;
	ungetc(ch, fp);
    node->attributes = floadattributes(fp, err);
	if(!node->attributes)
      goto parse_error;
	ch = fgetc(fp);
	if(ch == '/')
		return node;
  }
  data = getdata(fp, err);
  if(*err)
    goto parse_error;
  if(!node->data)
    node->data = data;
  else
  {
	  node->data = realloc(node->data, strlen(node->data) + strlen(data) + 1);
	  strcat(node->data, data);
  }
  while(ch != EOF)
  {
    while( (ch = fgetc(fp)) != EOF)
      if(!isspace( (unsigned char) ch))
	    break;
    if(ch == '<')
    {
      ch = fgetc(fp);
	  if(ch == '/')
	  {
	    return node;
	  }
	  else if(isalpha(ch))
	  {
	    ungetc(ch, fp);
	    newtag = getidentifier(fp, err);
        
	    child = floadxmlnode(fp, newtag, err);
	    if(!child)
	      goto parse_error;
		if(node->data)
		  child->position = strlen(node->data);
	    closetag = getidentifier(fp, err);
		ch = fgetc(fp);
		if(ch != '>')
		  goto parse_error;
		if(closetag == 0 && *err == 0)
			;
	    else if(strcmp(newtag, closetag))
          goto parse_error;	    
		if(lastchild)
		  lastchild->next = child;
		else
			node->child = child;
		lastchild = child;
		child = 0;
		free(newtag);
		free(closetag);
		newtag = 0;
		closetag = 0;
	  }
	  else
	  {
	    while( (ch = fgetc(fp)) != EOF)
		  if(ch == '>')
		    break;
	  }
	}
  }
parse_error:
  xmlFreeNode(node);
  xmlFreeNode(child);
  if(*err == 0)
    *err = -2;
  return 0;
out_of_memory:
  xmlFreeNode(node);
  xmlFreeNode(child);
  *err = -1;
  return 0;
}

/*
  parse attributes. they come in the form

   <TAG firstname = "Fred" lastname = 'Bloggs'>
   ot <TAG quote = '"' age="11"/>
*/
static XMLATTRIBUTE *floadattributes(FILE *fp, int *err)
{
	int ch;
	XMLATTRIBUTE *result = 0;
	XMLATTRIBUTE *nextattr = 0;
	XMLATTRIBUTE *tail = 0;
	char *name = 0;
	char *value = 0;

	while ((ch = fgetc(fp)) != EOF)
	{
		if (isspace(ch)) {
			continue;
		}

		if(isalpha(ch))
		{
			ungetc(ch, fp);
			if (nextattr == 0)
			{
				nextattr = malloc(sizeof(XMLATTRIBUTE));
				if (!nextattr) {
			  		goto out_of_memory;
				}

				nextattr->name = 0;
				nextattr->next = 0;
				nextattr->value = 0;
				name = getidentifier(fp, err);
				if (*err) {
					goto parse_error;
				}
				nextattr->name = name;
				name = 0;
			}
			else
			goto parse_error;
		}
	if(ch == '=')
	{
	  if(nextattr == 0)
	    goto parse_error;
	  value = getquotedstring(fp, err);
	  if(*err)
		  goto parse_error;
	  nextattr->value = value;
	  value = 0;
	  if(result == 0)
	    result = nextattr;
	  else
		  tail->next = nextattr;
	  tail = nextattr;
	  nextattr = 0;
	}
	if(ch == '>' || ch == '/')
	{
	  ungetc(ch, fp);
	  return result;
	}
  }
parse_error:
  free(value);
  free(name);
  xmlFreeAttribute(result);
  xmlFreeAttribute(nextattr);
  if(*err == 0)
    *err = -2;
  return 0;
out_of_memory:
  free(value);
  free(name);
  xmlFreeAttribute(result);
  xmlFreeAttribute(nextattr);
  *err = -1;
  return 0;
}

/* Destroy the attributes list */
static int xmlFreeAttribute(XMLATTRIBUTE *attr)
{
	XMLATTRIBUTE *next;
	RETURN_IF_NULL(attr);
	while (attr) {
		next = attr->next;
		free(attr->name);
		free(attr->value);
		free(attr);
		attr = next;
	}
	return 1;
}

static int xmlFreeNode(XMLNODE *node)
{
	XMLNODE *next;
	RETURN_IF_NULL(node);
	while (node) {
		next = node->next;
		if (node->child) {
			xmlFreeNode(node->child);
		}
		xmlFreeAttribute(node->attributes);
		free(node->data);
		free(node->tag);
		free(node);
		node = next;
	}
	return 1;
}

/*
  get a quote string
  Notes: fp must poit to first quote character.
  Both double and single quote allowed
*/
static char *getquotedstring(FILE *fp, int *err)
{
	char *temp;
	char *result;
	int buffsize = 256;
	char quote;
	int ch;
	int N = 0;

  result = malloc(buffsize);
  if(!result)
    goto out_of_memory;

  while( (ch = fgetc(fp)) != EOF )
    if(!isspace(ch))
	  break;

  quote = ch;
  if(quote != '\"' && quote != '\'')
    goto parse_error;

  while( (ch = fgetc(fp)) != EOF)
  {
    if(ch == quote)
	{
		result[N] = 0;
		temp = unescapedata(result);
		free(result);
		return temp;
	}
	else
	{
	  result[N++] = ch;
	  if(N > buffsize -1)
	  {
	    temp = realloc(result, buffsize * 2);
		if(!temp)
		  goto out_of_memory;
		result = temp;
		buffsize = buffsize * 2;
	  }
	}
  }
parse_error:
  free(result);
  *err = -2;
  return 0;
out_of_memory:
  free(result);
  *err = -1;
  return 0;
}

/*
  get data field for an xml node
  Notes: the specifications for whitespace are
    a bit loose, so we retain it 
*/
static char *getdata(FILE *fp, int *err)
{
	char *data;
	char *temp;
	int buffsize = 256;
	int ch;
	int N = 0;

	data = malloc(buffsize);
	if (!data) {
		(*err) = -1;
		return 0;
	}

	while ((ch = fgetc(fp)) != EOF)
	{
    if(ch == '<')
	{
		ungetc('<', fp);
		data[N] = 0;
		temp = unescapedata(data);
		free(data);
		return temp;
	}
	else
	{
	  data[N++] = ch;
	  if(N > buffsize -1)
	  {
	    temp = realloc(data, buffsize * 2);
		if(!temp)
		  goto out_of_memory;
		data = temp;
		buffsize = buffsize * 2;
	  }
	}
  }
parse_error:
  free(data);
  *err = -2;
  return 0;
out_of_memory:
  free(data);
  *err = -1;
  return 0;
}

/*
  get an identifer for the stream
  Notes: return null if not a valid
    identifier but doesn't set err.
  This is because of the closing tag problem
*/
static char *getidentifier(FILE *fp, int *err)
{
  char *answer;
  char *temp;
  int buffsize = 32;
  int N = 0;
  int ch;

  answer = malloc(buffsize);
  if(!answer)
    goto out_of_memory;

  while( (ch = fgetc(fp)) != EOF )
  {
    if(N == 0 && !isalpha(ch))
	{
	  ungetc(ch, fp);
	  free(answer);
	  return 0;
	}
	if(!isalpha(ch) && !isdigit(ch))
	{
	  ungetc(ch, fp);
	  answer[N] = 0;
	  temp = realloc(answer, N +1);
	  return temp;
	}
	answer[N++] = ch;
	if(N > buffsize -1)
	{
	  temp = realloc(answer, buffsize + 32);
	  if(!temp)
	    goto out_of_memory;
	  answer = temp;
	  buffsize = buffsize + 32;
	}
  }
  
  if(*err == 0)
    *err = -2;
  free(answer);
  return 0;
out_of_memory:
  free(answer);
  *err = -1;
  return 0;
}

/*
  unescape an xml string
  Params: data - the data string
  Returns: escaped string
*/
static char *unescapedata(char *data)
{
   size_t len;
   int i = 0, j = 0;
   char *answer = 0;

   len = strlen(data);
   answer = malloc(len +1);
   if(!answer)
     goto out_of_memory;
   for(i=0;data[i];i++)
   {
     if(data[i] != '&')
	   answer[j++] = data[i];
	 else
	 {
	   if(!strncmp(data +i, "&amp;", 5))
	   {
	     answer[j++] = '&';
		 i += 4;
	   }
	   else if(!strncmp(data +i, "&lt;", 4))
	   {
	     answer[j++] = '<';
		 i += 3;
	   }
	   else if(!strncmp(data+i, "&gt;", 4))
	   {
	     answer[j++] = '>';
		 i += 3;
	   }
	   else if(!strncmp(data+i, "&quot;", 6))
	   {
	     answer[j++] = '\"';
		 i += 5;
	   }
	   else if(!strncmp(data+i, "&apos;", 6))
	   {
	     answer[j++] = '\'';
		 i += 5;
	   }
	   else
	     answer[j++] = i;
	 }
   }
   answer[j] = 0;
   return answer;
out_of_memory:
   return 0;
}

/*
  strdup drop-in replacement
*/
static char *mystrdup(const char *str)
{
  char *answer;

  answer = malloc(strlen(str) + 1);
  if(!answer)
    return 0;
  strcpy(answer, str);
  return answer;
}

