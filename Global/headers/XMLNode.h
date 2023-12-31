#ifndef _INC_TSTRA_XMLNODE
#define _INC_TSTRA_XMLNODE

#include <list>
#include <string>
#include <vector>

#if 1
namespace rapidxml
{
    template <class Ch>
    class xml_node;
}
#else
#include "rapidxml.hpp"
#endif

#include "Globals.h"
#include "Utilities.h"

namespace tstra
{
    class _TstraExport XMLNode
    {
        friend class XMLDocument;

    public:
        /**
         * @brief Construct a new XMLNode object 默认继承
         *
         */
        XMLNode();

        ~XMLNode();

        operator bool() const { return fDOMElement != 0; }
        /**
         * @brief Get the Single XML Node object
         * 如果有多个，返回第一个
         * @param _sName 要返回的子节点名称
         * @return XMLNode 返回第一个正确的子节点，如果不存在的话返回空指针
         */
        XMLNode getSingleNode(std::string _sName) const;
        /**
         * @brief Get the Nodes object
         * 获取_sName的所有的子节点
         * @param _sName 目标子节点名称
         * @return std::list<XMLNode> 包含名称为_sName的子节点列表
         */
        std::list<XMLNode> getNodes(std::string _sName) const;
        /**
         * @brief Get the Nodes object
         * 获取所有子节点
         * @return std::list<XMLNode>
         */
        std::list<XMLNode> getNodes() const;
        /**
         * @brief Get the Name object
         * 获取该节点的名称
         * @return std::string
         */
        std::string getName() const;
        /**
         * @brief Get the Content object
         * 获取XML节点的内容
         * @return std::string 将节点的内容以string方式返回
         */
        std::string getContent() const;
        /**
         * @brief Get the Content Int object
         *
         * @return int 将节点的内容以Int方式返回
         */
        int getContentInt() const;
        /**
         * @brief Get the Content Numerical object
         *
         * @return float32 将节点的内容以float方式返回
         */
        float32 getContentNumerical() const;
        /**
         * @brief Get the Content Bool object
         * 将节点的内容以bool方式返回
         * @return true
         * @return false
         */
        bool getContentBool() const;
        /**
         * @brief Get the Content Array object
         * 将节点以vector<string>的方式返回
         * @return std::vector<std::string>
         */
        std::vector<std::string> getContentArray() const;
        /**
         * @brief Get the Content Numerical Array object
         * 将节点以vector<float32>的方式返回
         * @return std::vector<float32>
         */
        std::vector<float32> getContentNumericalArray() const;
        /**
         * @brief Get the Content Numerical Array Double object
         * 将节点以vector<Double>的方式返回
         * @return std::vector<double>
         */
        std::vector<double> getContentNumericalArrayDouble() const;
        /**
         * @brief Is Attribute ?
         *
         * @param _sName
         * @return true
         * @return false
         */
        bool hasAttribute(std::string _sName) const;
        /**
         * @brief
         * Get attribute - STRING
         * @param _sName 返回找到的sName节点
         * @param _sDefaultValue 如果没有找到该节点，返回默认值
         * @return std::string
         */
        std::string getAttribute(std::string _sName, std::string _sDefaultValue = " ") const;
        /**
         * @brief Get the Attribute Numerical object
         *
         * @param _sName
         * @param _fDefaultValue
         * @return float32
         */
        float32 getAttributeNumerical(std::string _sName, float32 _fDefaultValue = 0) const;
        /**
         * @brief Get the Attribute Numerical Double object
         *
         * @param _sName
         * @param _fDefaultValue
         * @return double
         */
        double getAttributeNumericalDouble(std::string _sName, double _fDefaultValue = 0) const;
        /**
         * @brief Get the Attribute Int object
         *
         * @param _sName
         * @param _fDefaultValue
         * @return int
         */
        int getAttributeInt(std::string _sName, int _fDefaultValue = 0) const;
        /**
         * @brief Get the Attribute Bool object
         *
         * @param _sName
         * @param _bDefaultValue
         * @return true
         * @return false
         */
        bool getAttributeBool(std::string _sName, bool _bDefaultValue = false) const;
        /**
         * @brief
         * Does this node contain an option with a certain key?
         * @param _sKey
         * @return true
         * @return false
         */
        bool hasOption(std::string _sKey) const;
        /**
         * @brief Get the Option object
         * Get the value of an option within this XML Node
         * @param _sKey option key
         * @param _fDefaultValue value to return if key isn't found
         * @return std::string _sDefaultValue if the option doesn't exist
         */
        std::string getOption(std::string _sKey, std::string _fDefaultValue = "") const;
        /**
         * @brief Get the Option Numerical object
         * Get the value of an option within this XML Node
         * @param _sKey option key
         * @param _fDefaultValue value to return if key isn't found
         * @return float32 option value. _fDefaultValue if the option doesm't exist
         */
        float32 getOptionNumerical(std::string _sKey, float32 _fDefaultValue = 0) const;
        int getOptionInt(std::string _sKey, int _fDefaultValue = 0) const;
        /**
         * @brief Get the Option Bool object
         * Get the value of an option within this XML Node
         * @param _sKey option key
         * @param _bDefaultValue value to return if key isn't found
         * @return true
         * @return false
         */
        bool getOptionBool(std::string _sKey, bool _bDefaultValue = false) const;
        /**
         * @brief Get the Option Numerical Array object
         * Get the value of an option within this XML Node
         * @param _sKey option key
         * @return std::vector<float32> numerical array
         */
        std::vector<float32> getOptionNumericalArray(std::string _sKey) const;
        /**
         * @brief Create a new XML node as a child to this one: &lt ... &gt;&lt;_sNodeName/&gt;</...&gt;
         *
         * @param _sNodeName the name of the new childnote
         * @return XMLNode new child node
         */
        XMLNode addChildNode(std::string _sNodeName);

        XMLNode addChildNode(std::string _sNodeName, std::string _sValue);

        XMLNode addChildNode(std::string _sNodeName, float32 _fValue);

        XMLNode addChildNode(std::string _sNodeName, float32 *_pList, int _iSize);

        void setContent(std::string _sText);

        void setContent(float32 _fValue);

        void setContent(float32 *_pList, int iSize);

        void setContent(double *pfList, int _iSize);

        void setContent(float32 *_pfMatrix, int _iWidth, int _iHeight, bool transposed);

        void setContent(double *_pfMatrix, int _iWidth, int _iHeight, bool transposed);

        void addAttribute(std::string _sName, std::string _sValue);

        void addAttribute(std::string _sName, float32 _fValue);

        void addOption(std::string _sKey, std::string _sValue);

        void addOption(std::string _sKey, float32 _fValue);

        std::string toString() const;

        void print() const;

    protected:
        /// @brief 普通外部用户无法调用，但对于派生类是可访问的。
        /// @param n
        XMLNode(rapidxml::xml_node<char> *n);

        void setDOMNode(rapidxml::xml_node<char> *n);

        rapidxml::xml_node<char> *fDOMElement;
    };
}

#endif