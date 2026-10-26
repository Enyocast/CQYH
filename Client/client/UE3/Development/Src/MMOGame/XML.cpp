#include "stdafx.h"
#include "XML.h"
#include "tinyxml.h"


//#if UE3_LEAN_AND_MEAN
//#pragma message("not use ")
#include "tinyxml.cpp"
#include "tinystr.cpp"
#include "tinyxmlerror.cpp"
#include "tinyxmlparser.cpp"
//#endif

//-------------------------------------------------------------------------------------
// xml attribute
//-------------------------------------------------------------------------------------
XMLAttribute::XMLAttribute( TiXmlAttribute * attribute )
: _attribute (attribute)
{

}
//------------------------------------------------------------------------
XMLAttribute::XMLAttribute(const XMLAttribute& src)
: _attribute (src._attribute)
{
	
}
//------------------------------------------------------------------------
XMLAttribute::~XMLAttribute()
{
}
//------------------------------------------------------------------------
std::string XMLAttribute::name()
{
	assert(_attribute);
	return (_attribute->Name());
}
//------------------------------------------------------------------------
std::string XMLAttribute::value()
{
	assert(_attribute);
	return (_attribute->Value());
}
//------------------------------------------------------------------------
bool XMLAttribute::hasNext()
{
	return _attribute->Next() != NULL;
}
//------------------------------------------------------------------------
XMLAttribute XMLAttribute::next()
{
	if(!isValid()) return XMLAttribute(NULL);
	return XMLAttribute (_attribute->Next());
}
//------------------------------------------------------------------------
bool XMLAttribute::isValid() const
{
	return _attribute != NULL;
}
//------------------------------------------------------------------------
float XMLAttribute::floatValue() const
{
	assert(_attribute);
	return float(_attribute->DoubleValue());
}
//------------------------------------------------------------------------
int XMLAttribute::intValue() const
{
	assert(_attribute);
	return float(_attribute->DoubleValue());
}

//--------------------------------------------------------------------------------------
// xml node
//--------------------------------------------------------------------------------------
XMLElement::XMLElement( TiXmlElement * element )
: _element(element)
{
}
//------------------------------------------------------------------------
XMLElement::XMLElement(const XMLElement& src)
: _element(src._element)
{
}
//------------------------------------------------------------------------
XMLElement::~XMLElement()
{
}
//------------------------------------------------------------------------
XMLElement& XMLElement::operator=(const XMLElement& src)
{
	_element = src._element;
	return	*this;
}
//------------------------------------------------------------------------
XMLElement XMLElement::firstChild()
{
	assert(_element);
	TiXmlNode	*	pXMLNode = _element->FirstChild();

	while((pXMLNode != NULL)
		&& (pXMLNode->Type() != TiXmlNode::ELEMENT))
	{
		pXMLNode = pXMLNode->NextSibling();
	}

	if( pXMLNode )
	{
		return	XMLElement( pXMLNode->ToElement() );
	}
	
	return XMLElement();
}
//------------------------------------------------------------------------
XMLElement XMLElement::firstChildByName(const std::string& childName)
{
	TiXmlNode* pXMLNode = _element->FirstChild((childName.c_str()));
	while((pXMLNode != NULL)
		&& (pXMLNode->Type() != TiXmlNode::ELEMENT))
	{
		pXMLNode = pXMLNode->NextSibling((childName.c_str()));
	}

	if( pXMLNode )
	{
		return	XMLElement( pXMLNode->ToElement() );
	}

	return XMLElement();
}
//------------------------------------------------------------------------
XMLElement XMLElement::nextSibling()
{
	assert(_element);
	TiXmlElement *	element = _element->NextSiblingElement();

	if( element )
	{
		return	XMLElement( element );
	}
	
	return	XMLElement();
}
//------------------------------------------------------------------------
XMLElement XMLElement::nextSiblingByName(const std::string& childName)
{
	TiXmlNode* pXMLNode = _element->NextSibling((childName.c_str()));
	while((pXMLNode != NULL)
		&& (pXMLNode->Type() != TiXmlNode::ELEMENT))
	{
		pXMLNode = pXMLNode->NextSibling((childName.c_str()));
	}

	if( pXMLNode )
	{
		return	XMLElement( pXMLNode->ToElement() );
	}

	return XMLElement();
}
//------------------------------------------------------------------------
XMLElement XMLElement::parent()
{
	assert(_element);
	TiXmlNode	*	pXMLNode = _element->Parent();
	if( pXMLNode )
	{
		return	XMLElement( pXMLNode->ToElement() );
	}

	return	XMLElement();
}
//------------------------------------------------------------------------
std::string	XMLElement::name()
{
	assert(_element);
	return std::string(_element->Value());
}
//------------------------------------------------------------------------
std::string	XMLElement::value()
{
	assert(_element);

	if(_element->GetText())
	{
		std::string str = _element->GetText();		
		return str;
	}
	else
	{
		return std::string();
	}
}
//------------------------------------------------------------------------
bool XMLElement::isNull()
{
	return	_element==NULL;
}
//------------------------------------------------------------------------
std::string	XMLElement::getAttribute(const std::string& attrName)
{
	assert(_element);
	const char * pCElement = _element->Attribute((attrName.c_str()));

	if( pCElement )
	{
		std::string str = pCElement;
		return str;
	}

	return	("");
}
//------------------------------------------------------------------------
bool XMLElement::hasChildNodes() const
{
	assert(_element);
	return	!_element->NoChildren();
}
//------------------------------------------------------------------------
bool  XMLElement::hasAttributes() const
{
	assert(_element);
	return	_element->FirstAttribute() != NULL;
}
//------------------------------------------------------------------------
XMLAttribute XMLElement::firstAttribute()
{
	assert(_element);
	return XMLAttribute(_element->FirstAttribute());
}
//------------------------------------------------------------------------
void XMLElement::setAttribute(const std::string& attrName, const std::string& val)
{
	_element->SetAttribute(attrName.c_str(), val.c_str());
}
//------------------------------------------------------------------------
void XMLElement::setValue(const std::string& val)
{
	_element->SetValue(val.c_str());
}
//------------------------------------------------------------------------
XMLElement XMLElement::addChild(const std::string& name)
{
	TiXmlNode* pNode = _element->InsertEndChild(TiXmlElement(name.c_str()));

	return XMLElement(static_cast<TiXmlElement*>(pNode));
}
//------------------------------------------------------------------------
void XMLElement::removeChild(XMLElement & src)
{
	assert(_element);

	_element->RemoveChild(src._element);
}
//--------------------------------------------------------------------------------------
// xml document
//--------------------------------------------------------------------------------------
XMLDoc::XMLDoc()
{
	_doc = new TiXmlDocument();
}
//------------------------------------------------------------------------
XMLDoc::~XMLDoc()
{
	delete _doc;
}
//------------------------------------------------------------------------
bool XMLDoc::loadFromFile(const std::string& file)
{
	return _doc->LoadFile((file.c_str()));
}
//------------------------------------------------------------------------
XMLElement XMLDoc::getRoot()
{
	return XMLElement(_doc->RootElement());
}
//------------------------------------------------------------------------
bool XMLDoc::loadFromXML(const std::string& xmlCode)
{
	_doc->Parse(xmlCode.c_str());

	return !_doc->Error();
}
//------------------------------------------------------------------------
bool XMLDoc::save(const std::string& fileName)
{
	if(GFileManager->IsReadOnly(ANSI_TO_TCHAR(fileName.c_str())))
	{
		//File::removeReadonly(fileName);
	}

	return _doc->SaveFile(fileName.c_str());
}
//------------------------------------------------------------------------
void XMLDoc::createRootNode(const std::string& name)
{
	_doc->InsertEndChild(TiXmlDeclaration(("1.0"), ("UTF-8"), ("")));

	_doc->InsertEndChild(TiXmlElement(name.c_str()));
}
//------------------------------------------------------------------------
float getFloatAttribuate(const std::string& attrName, XMLElement& element)
{
	std::string val = element.getAttribute(attrName);
	float v = 0.0f;
	appSSCANF(ANSI_TO_TCHAR(val.c_str()), TEXT("%f"), &v);
	return v;
}
//------------------------------------------------------------------------
int getIntAttribuate(const std::string& attrName,  XMLElement&  element)
{
	std::string val = element.getAttribute(attrName);
	int v = 0;
	appSSCANF(ANSI_TO_TCHAR(val.c_str()), TEXT("%d"), &v);
	return v;
}
//------------------------------------------------------------------------
bool getBoolAttribuate(const std::string& attrName, XMLElement& element)
{
	std::string val = element.getAttribute(attrName);	
	int v = 0;
	appSSCANF(ANSI_TO_TCHAR(val.c_str()), TEXT("%d"), &v);
	return v != 0;
}
//------------------------------------------------------------------------
