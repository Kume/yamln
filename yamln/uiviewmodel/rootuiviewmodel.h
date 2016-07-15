#ifndef ROOTUIVIEWMODEL_H
#define ROOTUIVIEWMODEL_H

#include "uiviewmodel.h"

class RootUIViewModel : public UIViewModel
{
    Q_OBJECT
public:
    Q_PROPERTY(UIViewModel* content READ content WRITE setContent NOTIFY contentChanged)

    RootUIViewModel(QObject* parent, const YamlObjectPtr &spec);


    UIViewModel* content() const;
private slots:
    void setContent(UIViewModel* content);
signals:
    void contentChanged(UIViewModel* content);
private:
    UIViewModel* m_content;

    // UIViewModel interface
public:
    virtual RootUIViewModel *rootViewModel() override;
};

#endif // ROOTUIVIEWMODEL_H
