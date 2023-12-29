#include "headers/XMLDocument.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace tstra;
using namespace std;

XMLDocument::XMLDocument()
{
    fDOMDocument = 0;
}

XMLDocument::~XMLDocument()
{
    delete fDOMDocument;
}

XMLDocument *XMLDocument::readFromFile(string filename)
{
    XMLDocument *res = new XMLDocument();
    /// 为res对象的成员变量fDOMDocument分配内存，创建一个xml_doucment<>对象，
    /// 并将其指针赋给fDOMDocument
    res->fDOMDocument = new xml_document<>();

    /// 使用给定的文件名创建一个输入文件流对象file
    std::ifstream file(filename.c_str());
    /// 创建一个字符串对象reader
    std::stringstream reader;
    /// 将文件流file中的数据读取到字符串流reader中
    reader << file.rdbuf();
    /// 将字符串流reader中的内容存储在res对象的成员变量fBuf中
    res->fBuf = reader.str();
    /// 使用fDOMDocument对象的parse函数解析保存在fBuf中的XML数据
    res->fDOMDocument->parse<0>((char *)res->fBuf.c_str());
    /// 返回新创建的XMLDocument对象res
    return res;
}

XMLDocument *XMLDocument::createDocument(string sRootName)
{

    XMLDocument *res = new XMLDocument();
    res->fDOMDocument = new xml_document<>();

    /// 分配内存来存储根节点名称
    char *node_name = res->fDOMDocument->allocate_string(sRootName.c_str());
    /// 创建XML节点
    xml_node<> *node = res->fDOMDocument->allocate_node(node_element, node_name);
    /// 将新创建的节点添加到fDOMDocument文档中
    res->fDOMDocument->append_node(node);

    return res;
}

void XMLDocument::saveToFile(string sFilename)
{
    std::ofstream file(sFilename.c_str());

    file << *fDOMDocument;
}

XMLNode XMLDocument::getRootNode()
{
    return XMLNode(fDOMDocument->first_node());
}

std::string XMLDocument::toString()
{
    std::stringstream ss;
    ss << *fDOMDocument->first_node();
    return ss.str();
}