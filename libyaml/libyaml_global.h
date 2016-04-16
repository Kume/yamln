#ifndef LIBYAML_GLOBAL_H
#define LIBYAML_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBYAML_LIBRARY)
#  define LIBYAMLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBYAMLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBYAML_GLOBAL_H
