#ifndef QLIBSSH2_GLOBAL_H
#define QLIBSSH2_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QLIBSSH2_LIBRARY)
#  define QLIBSSH2_EXPORT Q_DECL_EXPORT
#else
#  define QLIBSSH2_EXPORT Q_DECL_IMPORT
#endif

#endif // QLIBSSH2_GLOBAL_H
