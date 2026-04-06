#ifndef _DASHTYPES_H
#define _DASHTYPES_H

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

#include <map>
#include <vector>

// clang-format off

#define ND_HEADER 		"Header"
#define ND_CDATE 		"CreationDateUTC"
#define ND_COPYRIGHT	"Copyright"
#define ND_APIVER 		"APIVersion"
#define ND_TIMEZONE 	"TimeZone"

#define ND_SERVER 		"Server"
#define ND_SRVNAME 		"ServerName"
#define ND_SRVACT 		"ServerActiveNetCount"

#define ND_NET 			"Net"
#define ND_NETNAME 		"NetName"
#define ND_ALTNETNAME 	"AltNetName"
#define ND_FREQ 		"Frequency"
#define ND_LOGGER 		"Logger"
#define ND_NETCONTROL	"NetControl"
#define ND_DATE			"Date"
#define ND_MODE 		"Mode"
#define ND_BAND 		"Band"
#define ND_SUBCOUNT 	"SubscriberCount"
#define ND_FREQ 		"Frequency"
#define ND_BAND         "Band"
#define ND_NETID 		"NetID"
#define ND_UPDINTERVAL 	"UpdateInterval"
#define ND_AIM 			"AIM"
#define ND_NETID 		"NetID"
#define ND_POINTER      "Pointer"
#define ND_SERIALNO     "SerialNo"

#define ND_CHECKIN 		"Checkin"

#define ND_ERROR 		"Error"
#define ND_RESPCODE 	"ResponseCode"
#define ND_SRVLIST 		"ServerList"
#define ND_CHKLIST 		"CheckinList"

// clang-format on

// flatten it all out to lists of strings/value

typedef std::map<String, String> Vpairs;
typedef std::map<String, Vpairs> Vlist;

class CheckinList
{
  public:
    Vpairs Data;
    std::vector<Vpairs> Checkins;
    inline void clear()
    {
        Data.clear();
        Checkins.clear();
    }
    //	CheckinList(const CheckinList&) = delete;

    //	const CheckinList& operator =(const CheckInList&) = delete;
};

class ServerList
{
  public:
    Vpairs Data;
    Vlist Servers;
    Vlist Nets;
    Vlist NameByID;
    CheckinList Chklist;
    inline void clear()
    {
        Servers.clear();
        Data.clear();
        NameByID.clear();
        Nets.clear();
        Chklist.clear();
    }
    //	ServerList(const ServerList&) = delete;
    //	const ServerList& operator =(const CheckinList&) = delete;
    //	ServerList() {};
};

// root NETLOGGER XML object

class NLData
{
  public:
    Vpairs Header;
    ServerList Servers;
    CheckinList ChkList;
};

#endif
