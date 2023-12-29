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

/// @brief 私有继承
/// @param node
XMLNode::XMLNode(xml_node<> *node)
{
    fDOMElement = node;
}
