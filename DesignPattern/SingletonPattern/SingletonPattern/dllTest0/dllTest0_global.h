#ifndef DLLTEST0_GLOBAL_H
#define DLLTEST0_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLTEST0_LIBRARY)
#  define DLLTEST0_EXPORT Q_DECL_EXPORT
#else
#  define DLLTEST0_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLTEST0_GLOBAL_H
