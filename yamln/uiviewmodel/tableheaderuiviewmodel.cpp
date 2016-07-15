#include "tableheaderuiviewmodel.h"
#include "exceptions/uidefinitionexception.h"

#include <memory>

TableHeaderUIViewModel::TableHeaderUIViewModel(UIViewModel *parent, const YamlObjectPtr &spec)
    : UIViewModel(parent)
{
    setBasicValues(spec);
    std::unique_ptr<UIViewModel> content(createAtomicUIViewModel(this, spec));

    if (!content) {
        throw UIDefinitionException("table column cannot accept.", spec);
    }

    m_spec = spec;
}

const YamlObjectPtr &TableHeaderUIViewModel::spec() const
{
    return m_spec;
}
