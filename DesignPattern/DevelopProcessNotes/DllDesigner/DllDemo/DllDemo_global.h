#ifndef DLLDEMO_GLOBAL_H
#define DLLDEMO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLDEMO_LIBRARY)
#  define DLLDEMO_EXPORT Q_DECL_EXPORT
#else
#  define DLLDEMO_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLDEMO_GLOBAL_H
