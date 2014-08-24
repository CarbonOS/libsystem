#ifndef xmlparser_h
#define xmlparser_h

/* XML Parse data */
typedef struct xml_parse
{
	int handle;
	int offset;
	int length;
	const char *data;
	char temp[32];

} XMLParse;

typedef struct xmlattribute
{
  char *name;                /* attriibute name */
  char *value;               /* attribute value (without quotes) */
  struct xmlattribute *next; /* next pointer in linked list */
} XMLATTRIBUTE;

/* XML Node data */
typedef struct IXmlNode
{
	char *tag;                 /* tag to identify data type */
	XMLATTRIBUTE *attributes;  /* attributes */
	char *data;                /* data as ascii */
	int position;              /* position of the node within parent's data string */
	struct IXmlNode *next;      /* sibling node */
	struct IXmlNode *child;     /* first child node */

} XMLNODE;

/* XML Document data */
typedef struct IXmlDoc
{
	XMLNODE *root;             /* the root node */

} XMLDOC;


XMLDOC *loadxmldoc(char *fname, int *err);
XMLDOC *floadxmldoc(FILE *fp, int *err);
void killxmldoc(XMLDOC *doc);



int xml_Nchildrenwithtag(XMLNODE *node, const char *tag);
XMLNODE *xml_getchild(XMLNODE *node, const char *tag, int index);
XMLNODE **xml_getdescendants(XMLNODE *node, const char *tag, int *N);

#endif
