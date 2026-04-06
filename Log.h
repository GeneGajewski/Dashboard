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

#ifndef _NOGLOG

#define ENTERFUNC CodeSite->EnterMethod(__FUNC__)
#define EXITFUNC CodeSite->ExitMethod(__FUNC__)
#define LogInfo(str) CodeSite->Send(csmInfo, (UnicodeString)str)
#define LogNameVal(__name, __val) CodeSite->Send(csmInfo, __name + " = " + __val)
#define LogWarn(str) CodeSite->Send(csmWarning, (UnicodeString)str)
#define LogExcept(ex) CodeSite->SendException(__FUNC__, ex);

#else

#define ENTERFUNC
#define EXITFUNC
#define LogInfo(str)
#define LogWarn(str)
#define LogExcept(ex)

#endif

#endif // myLogH
