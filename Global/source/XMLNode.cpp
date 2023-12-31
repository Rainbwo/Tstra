#include "XMLNode.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

#include <sstream>
#include <iomanip>

using namespace rapidxml;
using namespace tstra;
using namespace std;

tstra::XMLNode::XMLNode()
{
    fDOMElement = 0;
}

tstra::XMLNode::~XMLNode()
{
}

XMLNode tstra::XMLNode::getSingleNode(std::string _sName) const
{
    xml_node<> *node = fDOMElement->first_node(_sName.c_str());
    return XMLNode(node);
}

std::list<XMLNode> tstra::XMLNode::getNodes(std::string _sName) const
{
    list<XMLNode> result;
    xml_node<> *iter;
    for (iter = fDOMElement->first_node(_sName.c_str()); iter; iter = iter->next_sibling(_sName.c_str()))
    {
        result.push_back(XMLNode(iter));
    }
    return result;
}

std::list<XMLNode> tstra::XMLNode::getNodes() const
{
    list<XMLNode> result;
    xml_node<> *iter;
    for (iter = fDOMElement->first_node(); iter; iter = iter->next_sibling())
    {
        result.push_back(XMLNode(iter));
    }
    return result;
}

std::string tstra::XMLNode::getName() const
{
    return fDOMElement->name();
}

std::string tstra::XMLNode::getContent() const
{
    return fDOMElement->value();
}

int tstra::XMLNode::getContentInt() const
{

    return StringUtil::stringToInt(getContent());
}

float32 tstra::XMLNode::getContentNumerical() const
{
    return StringUtil::stringToFloat(getContent());
}

bool tstra::XMLNode::getContentBool() const
{
    string res = getContent();

    return ((res == "1") || (res == "yes") || (res == "true") || (res == "on"));
}

std::vector<std::string> tstra::XMLNode::getContentArray() const
{
    int iSize = StringUtil::stringToInt(getAttribute("listsize"));
    vector<string> res(iSize);
    list<XMLNode> nodes = getNodes("ListItem");
    for (list<XMLNode>::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        int iIndex = it->getAttributeNumerical("index");
        string sValue = it->getAttribute("value");
        TSTRA_ASSERT(iIndex < iSize);
        res[iIndex] = sValue;
    }
    return res;
}

std::vector<float32> tstra::XMLNode::getContentNumericalArray() const
{
    return StringUtil::stringToFloatVector(getContent());
}

std::vector<double> tstra::XMLNode::getContentNumericalArrayDouble() const
{
    return StringUtil::stringToDoubleVector(getContent());
}

bool tstra::XMLNode::hasAttribute(std::string _sName) const
{
    xml_attribute<> *attr = fDOMElement->first_attribute(_sName.c_str());
    return (attr != 0);
}

std::string tstra::XMLNode::getAttribute(std::string _sName, std::string _sDefaultValue) const
{
    xml_attribute<> *attr = fDOMElement->first_attribute(_sName.c_str());
    if (!attr)
        return _sDefaultValue;
    return attr->value();
}

float32 tstra::XMLNode::getAttributeNumerical(std::string _sName, float32 _fDefaultValue) const
{
    if (!hasAttribute(_sName))
        return _fDefaultValue;

    return StringUtil::stringToFloat(getAttribute(_sName));
}

double tstra::XMLNode::getAttributeNumericalDouble(std::string _sName, double _fDefaultValue) const
{
    if (!hasAttribute(_sName))
        return _fDefaultValue;
    return StringUtil::stringToDouble(getAttribute(_sName));
}

int tstra::XMLNode::getAttributeInt(std::string _sName, int _fDefaultValue) const
{
    if (!hasAttribute(_sName))
        return _fDefaultValue;

    return StringUtil::stringToInt(getAttribute(_sName));
}

bool tstra::XMLNode::getAttributeBool(std::string _sName, bool _bDefaultValue) const
{
    if (!hasAttribute(_sName))
        return _bDefaultValue;
    string res = getAttribute(_sName);

    return ((res == "1") || (res == "yes") || (res == "yes") || (res == "on"));
}

bool tstra::XMLNode::hasOption(std::string _sKey) const
{
    xml_node<> *iter;
    for (iter = fDOMElement->first_node("Option"); iter; iter = iter->next_sibling("Option"))
    {
        xml_attribute<> *attr = iter->first_attribute("key");
        if (attr && _sKey == attr->value())
        {
            return true;
        }
    }
    return false;
}

std::string tstra::XMLNode::getOption(std::string _sKey, std::string _fDefaultValue) const
{
    xml_node<> *iter;
    for (iter = fDOMElement->first_node("Option"); iter; iter = iter->next_sibling("Option"))
    {
        xml_attribute<> *attr = iter->first_attribute("key");
        if (attr && _sKey == attr->value())
        {
            attr = iter->first_attribute("value");
            if (!attr)
                return "";
            return attr->value();
        }
    }
    return _fDefaultValue;
}

float32 tstra::XMLNode::getOptionNumerical(std::string _sKey, float32 _fDefaultValue) const
{
    if (!hasOption(_sKey))
        return _fDefaultValue;

    return StringUtil::stringToFloat(getOption(_sKey));
}

int tstra::XMLNode::getOptionInt(std::string _sKey, int _fDefaultValue) const
{
    if (!hasOption(_sKey))
        return _fDefaultValue;

    return StringUtil::stringToInt(getOption(_sKey));
}

bool tstra::XMLNode::getOptionBool(std::string _sKey, bool _bDefaultValue) const
{
    bool bHasOption = hasOption(_sKey);
    if (!bHasOption)
        return _bDefaultValue;
    string res = getOption(_sKey);
    return ((res == "1") || (res == "yes") || (res == "true") || (res == "on"));
}

std::vector<float32> tstra::XMLNode::getOptionNumericalArray(std::string _sKey) const
{
    if (!hasOption(_sKey))
        return vector<float32>();

    list<XMLNode> nodes = getNodes("Option");
    for (list<XMLNode>::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (it->getAttribute("key") == _sKey)
        {
            vector<float32> vals = it->getContentNumericalArray();
            return vals;
        }
    }
    return std::vector<float32>();
}

XMLNode tstra::XMLNode::addChildNode(std::string _sNodeName)
{
    xml_document<> *doc = fDOMElement->document();
    char *node_name = doc->allocate_string(_sNodeName.c_str());
    xml_node<> *node = doc->allocate_node(node_element, node_name);
    fDOMElement->append_node(node);
    return XMLNode(node);
}

XMLNode XMLNode::addChildNode(string _sNodeName, string _sText)
{
    XMLNode res = addChildNode(_sNodeName);
    res.setContent(_sText);
    return res;
}

XMLNode tstra::XMLNode::addChildNode(std::string _sNodeName, float32 _fValue)
{
    XMLNode res = addChildNode(_sNodeName);
    res.setContent(_fValue);
    return res;
}

XMLNode tstra::XMLNode::addChildNode(std::string _sNodeName, float32 *_pList, int _iSize)
{
    XMLNode res = addChildNode(_sNodeName);
    res.setContent(_pList, _iSize);
    return res;
}

void tstra::XMLNode::setContent(std::string _sText)
{
    xml_document<> *doc = fDOMElement->document();
    char *text = doc->allocate_string(_sText.c_str());
    fDOMElement->value(text);
}

void tstra::XMLNode::setContent(float32 _fValue)
{
    setContent(StringUtil::floatToString(_fValue));
}

template <typename T>
static std::string setContentList_internal(T *pfList, int iSize)
{
    std::string str;
    for (int i = 0; i < _iSize; i++)
    {
        str += StringUtil::toString(pfList[i]) + ";";
    }
    return str;
}

void XMLNode::setContent(float32 *pfList, int _iSize)
{
    setContent(setContentList_internal<float32>(pfList, _iSize));
}

void XMLNode::setContent(double *pfList, int _iSize)
{
    setContent(setContentList_internal<double>(pfList, _iSize));
}

template <typename T>
static std::string setContentMatrix_internal(T *_pfMatrix, int _iWidth, int _iHeight, bool transposed)
{
    int s1, s2;
    if (!transposed)
    {
        s1 = 1;
        s2 = _iWidth;
    }
    else
    {
        s1 = _iHeight;
        s2 = 1;
    }

    std::ostringstream s;
    s.imbue(std::locale::classic());
    s << std::setprecision(17);
    for (int y = 0; y < _iHeight; ++y)
    {
        if (_iWidth > 0)
        {
            s << _pfMatrix[0 * s1 + y * s2];
        }
        for (int x = 1; x < _iWidth; x++)
        {
            s << "," << _pfMatrix[x * s1 + y * s2];
        }
        s << ";";
    }
    return s.str();
}

void XMLNode::setContent(float32 *_pfMatrix, int _iWidth, int _iHeight, bool transposed)
{
    setContent(setContentMatrix_internal<float32>(_pfMatrix, _iWidth, _iHeight, transposed));
}

void XMLNode::setContent(double *_pfMatrix, int _iWidth, int _iHeight, bool transposed)
{
    setContent(setContentMatrix_internal<double>(_pfMatrix, _iWidth, _iHeight, transposed));
}

void XMLNode::addAttribute(string _sName, float32 _fValue)
{
    addAttribute(_sName, StringUtil::floatToString(_fValue));
}

void XMLNode::addOption(string _sName, string _sText)
{
    XMLNode node = addChildNode("Option");
    node.addAttribute("key", _sName);
    node.addAttribute("value", _sText);
}

void XMLNode::addOption(string _sName, float32 _sText)
{
    XMLNode node = addChildNode("Option");
    node.addAttribute("key", _sName);
    node.addAttribute("value", _sText);
}

std::string tstra::XMLNode::toString() const
{
    std::string s;
    ::print(std::back_inserter(s), *fDOMElement, 0);
    return s;
}

void tstra::XMLNode::print() const
{
    std::cout << fDOMElement;
}

/// @brief 私有继承
/// @param node
XMLNode::XMLNode(xml_node<> *node)
{
    fDOMElement = node;
}

void tstra::XMLNode::setDOMNode(rapidxml::xml_node<char> *n)
{
    fDOMElement = n;
}
