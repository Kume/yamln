#include "yamlmanager.h"


ActiveYaml::YamlManager::YamlManager(const ActiveYaml::YamlObjectPtr &root)
{

}

void ActiveYaml::YamlManager::addObserver(YamlObserver *observer)
{

}

void ActiveYaml::YamlManager::removeObserver(const ActiveYaml::YamlObserver *observer)
{

}

void ActiveYaml::YamlManager::addObserverPath(const ActiveYaml::YamlPath &path, const ActiveYaml::YamlObserver *observer)
{

}

void ActiveYaml::YamlManager::removeObserverPath(const ActiveYaml::YamlPath &path, const ActiveYaml::YamlObserver *observer)
{

}

void ActiveYaml::YamlManager::execAction(const ActiveYaml::YamlActionPtr &action)
{

}

void ActiveYaml::YamlManager::undo()
{

}

bool ActiveYaml::YamlManager::canUndo() const
{
    return !m_actionHistory.empty();
}
