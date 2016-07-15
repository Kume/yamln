#include "textuiviewmodel.h"

#include "exceptions/yamlobjectexception.h"

QString TextUIViewModel::type() const
{
    return "text";
}

TextUIViewModel::TextUIViewModel(UIViewModel *parent, YamlObjectPtr spec) : UIViewModel(parent)
{
    setBasicValues(spec);
}

QString TextUIViewModel::value() const
{
    return "tttest";
}
