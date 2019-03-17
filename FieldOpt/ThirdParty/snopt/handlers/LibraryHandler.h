/* Copyright (C) 2008 GAMS Development and others
 All Rights Reserved.
 This code is published under the Eclipse Public License.

 $Id: LibraryHandler.h 2105 2012-06-12 13:22:30Z stefan $

 Author: Stefan Vigerske
 inspired by optcc.h in gams i/o libs

 Modified by Mathias C. Bellout on Feb 28 2019
 <mathias.bellout@petroleumcyberneticsgroup.no>
 <chakibbb-pcg@gmail.com> 
*/

#ifndef LIBRARYHANDLER_H_
#define LIBRARYHANDLER_H_

// ---------------------------------------------------------
#ifndef COIN_USE_F2C
// Define to a macro mangling the given C identifier 
// (in  lower and upper case), which must not contain  
// underscores, for linking with Fortran.
# define F77_FUNC(name,NAME) NAME

// As F77_FUNC, but for C identifiers containing underscores.
# define F77_FUNC_(name,NAME) NAME
#else
// Define to a macro mangling the given C identifier 
// (in lower and upper case), which must not contain 
// underscores, for linking with Fortran.
# define F77_FUNC(name,NAME) name ## _

// As F77_FUNC, but for C identifiers containing underscores.
# define F77_FUNC_(name,NAME) name ## __
#endif

// ---------------------------------------------------------
#define HAVE_DLFCN_H

//#ifdef WIN32
//#define SHAREDLIBEXT "dll"
//#include <windows.h>
//  typedef HINSTANCE soHandle_t;
//#ifdef small
//#undef small
//#endif

//#else
#define HAVE_SNPRINTF 1
#define SHAREDLIBEXT "so"

#ifdef HAVE_DLFCN_H
#include <unistd.h>
#include <dlfcn.h>
typedef void *soHandle_t;
#else
#define ERROR_LOADLIB
typedef void *soHandle_t;
#endif
//#endif

// ---------------------------------------------------------
// Loads a dynamically linked library.
// @param libname The name of the library to load.
// @param msgbuf A buffer to store an error message.
// @param msglen Length of the message buffer.
// @return Shared library handle, or NULL if failure.
// 
soHandle_t LSL_loadLib(const char* libname, 
                       char* msgbuf, int msglen);

// ---------------------------------------------------------
// Unloads a shared library.
// @param libhandle Handle of shared library to unload.
// @return Zero on success, nonzero on failure.
// 
int LSL_unloadLib(soHandle_t libhandle);

#endif /*LIBRARYHANDLER_H_*/