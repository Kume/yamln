#ifndef TST_YAMLMANAGERTEST_H
#define TST_YAMLMANAGERTEST_H


#include <QObject>

class YamlManagerTest : public QObject
{
    Q_OBJECT

public:
    YamlManagerTest();
    
private Q_SLOTS:
    void testNotify();
};

#endif // TST_YAMLMANAGERTEST_H
