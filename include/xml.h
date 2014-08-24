#ifndef __SYSTEM_XML_H__
#define __SYSTEM_XML_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* XML Document Handle */
typedef struct IXmlDoc *XMLDOCPTR;

/* XML Node Handle */
typedef struct IXmlNode *XMLNODEPTR;

XMLDOCPTR XmlOpen(char *fname, int *err);

XMLNODEPTR XmlGetRootNode(XMLDOCPTR doc);

XMLNODEPTR XmlGetChildNode(XMLNODEPTR node);

XMLNODEPTR XmlGetNextNode(XMLNODEPTR node);

const XMLNODEPTR XmlGetNodeFromName(XMLNODEPTR parent, const char *name);

const char *XmlGetTag(XMLNODEPTR node);

const char *XmlGetValue(XMLNODEPTR node);

int XmlGetIntValue(XMLNODEPTR node);

const char *XmlGetAttribute(XMLNODEPTR node, const char *attr);

int XmlFreeDoc(XMLDOCPTR doc);

#ifdef __cplusplus
}
#endif /* C++ Interface */
#endif /* __SYSTEM_TASK_H__ */
