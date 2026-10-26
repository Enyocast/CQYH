#ifndef __CUSTOMXML_H__
#define __CUSTOMXML_H__

class TiXmlElement;
class TiXmlAttribute;
class TiXmlDocument;

class XMLAttribute
{
	friend class XMLDoc;
	friend class XMLElement;
public:
	XMLAttribute( TiXmlAttribute * element = NULL );
	XMLAttribute(const XMLAttribute& src);
	virtual ~XMLAttribute();
	std::string name();
	std::string value();
	bool hasNext();
	bool isValid() const;
	XMLAttribute next();

	float floatValue() const;
	int intValue() const;

private:
	TiXmlAttribute* _attribute;
};

class XMLElement
{
	friend class XMLDoc;
public:

	XMLElement( TiXmlElement * element = NULL );
	XMLElement(const XMLElement& src);
	virtual ~XMLElement();
	XMLElement& operator=(const XMLElement& src);
	XMLElement firstChild();
	XMLElement nextSibling();
	XMLElement firstChildByName(const std::string& childName);
	XMLElement nextSiblingByName(const std::string& childName);
	XMLElement parent();
	std::string name();
	std::string value();
	void setValue(const std::string& val);
	bool		isNull();
	std::string getAttribute(const std::string& attrName);	
	bool		hasChildNodes() const;
	bool		hasAttributes() const;
	XMLAttribute firstAttribute();

	void setAttribute(const std::string& attrName, const std::string& val);
	XMLElement addChild(const std::string& name);
	void removeChild(XMLElement & src);

private:
	TiXmlElement* _element;
};

class XMLDoc
{
public:
	XMLDoc();
	virtual ~XMLDoc();
	// load from disk file.
	bool loadFromFile(const std::string& file);
	XMLElement getRoot();
	bool loadFromXML(const std::string& xmlCode);
	bool save(const std::string& fileName);
	void createRootNode(const std::string& name);

private:
	TiXmlDocument* _doc;
};

float extern getFloatAttribuate(const std::string& attrName, XMLElement& element);
int   extern getIntAttribuate(const std::string& attrName,  XMLElement&  element);
bool  extern getBoolAttribuate(const std::string& attrName, XMLElement& element);

#endif
