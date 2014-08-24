#include <stdio.h>
#include <include/core.h>
#include <include/xml.h>

int main (int argc, char *argv[])
{
	int error = 0;
	XMLDOCPTR doc;
	if (!(doc = XmlOpen("./data.xml", &error))) {
		printf("XmlOpen failed!\n");
	}

	XMLNODEPTR root;
	if (!(root = XmlGetRootNode(doc))) {
		printf("XmlGetRootNode failed!\n");
	}

	XMLNODEPTR module;
	if ((module = XmlGetNodeFromName(root, "Module"))) {
		printf("name: %s\n", XmlGetAttribute(module, "Name"));
	}

	XMLNODEPTR next = XmlGetChildNode(root);
	while (next != NULL) {

		printf("tag: %s\n", XmlGetTag(next));
		printf("val: %s\n", XmlGetValue(next));
		printf("int: %d\n", XmlGetIntValue(next));

		printf("att: %s\n", XmlGetAttribute(next, "Name"));
		next = XmlGetNextNode(next);
	}

	XmlFreeDoc(doc);
	return 0;
}

