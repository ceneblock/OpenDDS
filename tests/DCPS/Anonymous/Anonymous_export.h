
// -*- C++ -*-
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl Anonymous
// ------------------------------
#ifndef ANONYMOUS_EXPORT_H
#define ANONYMOUS_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (ANONYMOUS_HAS_DLL)
#  define ANONYMOUS_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && ANONYMOUS_HAS_DLL */

#if !defined (ANONYMOUS_HAS_DLL)
#  define ANONYMOUS_HAS_DLL 1
#endif /* ! ANONYMOUS_HAS_DLL */

#if defined (ANONYMOUS_HAS_DLL) && (MESSENGER_HAS_DLL == 1)
#  if defined (ANONYMOUS_BUILD_DLL)
#    define Anonymous_Export ACE_Proper_Export_Flag
#    define ANONYMOUS_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define ANONYMOUS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* ANONYMOUS_BUILD_DLL */
#    define Anonymous_Export ACE_Proper_Import_Flag
#    define ANONYMOUS_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define ANONYMOUS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* ANONYMOUS_BUILD_DLL */
#else /* ANONYMOUS_HAS_DLL == 1 */
#  define Anonymous_Export
#  define ANONYMOUS_SINGLETON_DECLARATION(T)
#  define ANONYMOUS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* ANONYMOUS_HAS_DLL == 1 */

// Set ANONYMOUS_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (ANONYMOUS_NTRACE)
#  if (ACE_NTRACE == 1)
#    define ANONYMOUS_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define ANONYMOUS_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !ANONYMOUS_NTRACE */

#if (ANONYMOUS_NTRACE == 1)
#  define ANONYMOUS_TRACE(X)
#else /* (ANONYMOUS_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define ANONYMOUS_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (ANONYMOUS_NTRACE == 1) */

#endif /* ANONYMOUS_EXPORT_H */

// End of auto generated file.
