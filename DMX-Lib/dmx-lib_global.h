#ifndef DMXLIB_GLOBAL_H
#define DMXLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DMXLIB_LIBRARY)
#  define DMXLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DMXLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DMXLIB_GLOBAL_H
