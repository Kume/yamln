#ifndef YAMLMANAGER_H
#define YAMLMANAGER_H

#include "yamlobject.h"
#include "action/yamlaction.h"
#include <vector>

namespace ActiveYaml
{

class YamlObserver
{
public:
    virtual ~YamlObserver() {}
    virtual void onYamlUpdate(const YamlPath& path, const YamlObjectPtr& newObject) const;
};

class YamlManager
{
public:
    YamlManager(const YamlObjectPtr& root);

    void addObserver(YamlObserver *observer);
    void removeObserver(const YamlObserver *observer);
    void addObserverPath(const YamlPath& path, const YamlObserver* observer);
    void removeObserverPath(const YamlPath& path, const YamlObserver* observer);
    void execAction(const YamlActionPtr& action);
    void undo();
    bool canUndo() const;

private:
    YamlObjectPtr m_rootObject;
    typedef std::vector<YamlActionPtr> ActionList;
    ActionList m_actionHistory;
};

}

#endif // YAMLMANAGER_H
