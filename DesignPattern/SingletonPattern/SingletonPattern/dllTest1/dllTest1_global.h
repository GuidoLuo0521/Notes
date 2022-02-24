#ifndef DLLTEST1_GLOBAL_H
#define DLLTEST1_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLTEST1_LIBRARY)
#  define DLLTEST1_EXPORT Q_DECL_EXPORT
#else
#  define DLLTEST1_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLTEST1_GLOBAL_H
