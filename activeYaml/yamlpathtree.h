#ifndef YAMLPATHTREE_H
#define YAMLPATHTREE_H

#include "yamlpath.h"
#include <vector>

namespace ActiveYaml
{
class YamlPathTreeNode
{
    typedef std::vector<YamlPathTreeNode> YamlPathTreeNodeList;

public:
    YamlPathTreeNode(const YamlPathElement& element);

    const YamlPathElement& pathElement() const { return m_pathElement; }
    YamlPathTreeNodeList children() const { return m_children; }

private:
    YamlPathElement m_pathElement;
    YamlPathTreeNodeList m_children;
};

class YamlPathTree
{
public:
    YamlPathTree();
};
}

#endif // YAMLPATHTREE_H
