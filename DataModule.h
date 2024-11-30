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

//---------------------------------------------------------------------------

#ifndef DataModuleH
#define DataModuleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>

#include <map>
#include <vector>



class Field
{
	String FName, FTitle, FValue;
	public:
	Field(const char *name, const char *title = 0) : FName(name)
	{
		if(title)
			FTitle = title;
		else FTitle = FName;
	}
	String __property Name  {read=FName};
	String __property Title {read=FTitle};
	String __property Value {read=FValue,write=FValue};
};
// simple 1-1 data structures to match NETLOGGER XML API nodes

class NLHeader
{

	public:

	String CreationDateUTC;
	String Copyright;
	String APIVersion;
	String TimeZone;
};

class NLError
{
	public:
	String Value;
	String ResponseCode;
};

class NLNet
{
  public:
	String NetName;
	String AltNetName;
	String Frequency;
	String Logger;
	String NetControl;
	String Date;
	String Mode;
	String Band;
	String SubscriberCount;

	// === PAST NETS ONLY =======

	String NetID;
	String AIM;
	String UpdateInterval;
	String srcIP;
	String LastActivity;
	String InactivityTimer;
	String MiscNetParameters;
	String ClosedAt;
	String Asassinated;
};

class NLServer
{
	public:
	String ServerName;
	String ServerActiveNetCount;
	std::map<String, NLNet> Nets;
};


class NLCheckin
{
	public:
	String SerialNo;
	String Callsign;
	String State;
	String Remarks;
	String QSLInfo;
	String CityCountry;
	String FirstName;
	String Status;
	String County;
	String Grid;
	String Street;
	String Zip;
	String MemberID;
	String Country;
	String DXCC;
	String PreferredName;
};


class ServerList
{
  public:
	String ResponseCode;
	std::map<String,String> NetServerMap;  // Netname/ServerName
	std::map<String, NLServer> Servers;
};

class CheckinList
{
  public:
	String ServerName;
	String NetName;
	String ResponseCode;
	String CheckinCount;
	String Pointer;
	std::vector<NLCheckin> Checkins;
};

// root NETLOGGER XML object

class NetLoggerXML
{
	public:

	NLHeader header;
	String Error;
	String ResponseCode;
	ServerList serverlist;
	CheckinList checkinlist;
};

//---------------------------------------------------------------------------

//
// XML i/o and parsing implemented as a TDatamodule
//

class TDMod : public TDataModule
{
  __published: // IDE-managed Components
	TRESTClient* RESTClient1;
	TRESTRequest* RESTRequest1;
	TRESTResponse* RESTResponse1;
	TXMLDocument *XMLDocument1;

  private: // User declarations

  NetLoggerXML NL; // holds everything!

  bool ReadHeader(_di_IXMLNode &Head, NLHeader &Header);
  bool ReadServerList(_di_IXMLNode &Head, ServerList &List);
  bool ReadServer(_di_IXMLNode &Head, ServerList &Servers);
  bool ReadNet(_di_IXMLNode &Head, NLServer &Server);
  bool ReadCheckinList(_di_IXMLNode &Head, CheckinList &List);
  bool ReadCheckin(_di_IXMLNode &Head, CheckinList &List);
  String GetValue(const _di_IXMLNode &Node);

  public: // User declarations

	__fastcall TDMod(TComponent* Owner);
	bool DoQuery(NetLoggerXML &nl);
	bool GetNetData(const String &Netname, NLNet &Net);
	bool GetNetNames(TStringList *List);
	CheckinList *GetCheckins(const String NetName);
	const String &ErrorMessage();
	};
//---------------------------------------------------------------------------
extern PACKAGE TDMod* DMod;

//---------------------------------------------------------------------------
#endif

