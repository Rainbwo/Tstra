#ifndef _INC_TSTRA_XMLDOCUMENT
#define _INC_TSTRA_XMLDOCUMENT

#include <string>

#if 1
namespace rapidxml
{
    template <class Ch>
    class xml_document;
}
#else
#include "rapidxml.hpp"
#endif

#include "Globals.h"
#include "XMLNode.h"

namespace tstra
{
    class _TstraExport XMLDocument
    {
    public:
        XMLDocument();

        ~XMLDocument();

        /**
         * @brief 用于从文件中读取XML数据并创建一个包含解析结果的XMLDocument对象
         *
         * @param sFilename 要读取的文件路径
         * @return XMLDocument* 包含解析结果的XMLDocument
         */
        static XMLDocument *readFromFile(std::string sFilename);
        /**
         * @brief Create a Document object 用于创建一个包含指定根节点的XMLDocument对象
         *
         * @param sRootName 要创建的根节点的名称
         * @return XMLDocument*
         */
        static XMLDocument *createDocument(std::string sRootName);

        XMLNode getRootNode();

        /**
         * @brief 将XMLDocument对象中的文档内容保存到指定的文件中，通过使用文件流和插入运算符来实现写操作
         *
         * @param sFilename 要保存到的文件名
         */
        void saveToFile(std::string sFilename);

        std::string toString();

    private:
        rapidxml::xml_document<char> *fDOMDocument;

        std::string fBuf;
    };
}

#endif