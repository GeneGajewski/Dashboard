#ifndef mylogH
#define mylogH
/*
 *   Copyright (C) 2023 Gene Gajewski WG5ENE
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "CodeSiteLogging.hpp"

#ifndef _NOLOG

#define FILELINE String(__FILE__) + ":" + __LINE__ + " " + __FUNC__

#define ENTERFUNC CodeSite->EnterMethod(FILELINE)
#define EXITFUNC CodeSite->ExitMethod(FILELINE)
#define LogInfo(str) CodeSite->Send(csmInfo, FILELINE + " " + str)
#define LogWarn(str) CodeSite->Send(csmWarning, FILELINE + " " + str)
#define LogExcept(ex) CodeSite->SendException(FILELINE, ex)
#define LogError(str) CodeSite->Send(csmError, FILELINE + " " + str)
#define LogNameVal(__name, __val) CodeSite->Send(csmInfo, FILELINE + " " + __name + " = " + __val)

#else

#define ENTERFUNC
#define EXITFUNC
#define LogInfo(str)
#define LogWarn(str)
#define LogExcept(ex)
#define LogError(str)
#define LogNameVal(__name, __val)

#endif

#endif // myLogH
