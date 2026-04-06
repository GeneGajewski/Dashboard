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

#pragma hdrstop

#include "DataModule.h"
#include "Log.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TDMod* DMod;


// this is an improvement over the discrete data structs used in previous versions.
// Will likely change to an automatic XML Tranform ->DataSet model in the future


// log any nodes unknown to us

void UnknownNode(String which_func, _di_IXMLNode node)
{
	CodeSite->Send(csmWarning, which_func, node);
}

//---------------------------------------------------------------------------
__fastcall TDMod::TDMod(TComponent* Owner) : TDataModule(Owner) {}

//
// perform an XML REST query and parse the results into the netlogger structure
//
//  RESTRequest1 is assumed to be correctly formed.

bool TDMod::DoQuery(NLData& nl)
{
	bool Retval = true;
	_di_IXMLNode Node, Child;
	nl.Header.clear();
	ENTERFUNC;
	try
	{
		RESTRequest1->Execute();
		if (RESTResponse1->StatusCode == 200)   // ok
		{
			String Name;

			XMLDocument1->LoadFromXML(DMod->RESTResponse1->Content);
			XMLDocument1->Active = true;
			XMLDocument1->SaveToFile("XMLFILLE.XML");
			Node = XMLDocument1->DocumentElement;

			// parse all document nodes
			for (int x = 0; x < Node->ChildNodes->Count; x++)
			{
				Child = Node->ChildNodes->Nodes[x];
				Name = Child->NodeName;

				if (Name == ND_HEADER)
				{
					Retval = ReadHeader(Child, nl);
					if (Retval == false)
						break;
				} else if (Name == ND_ERROR)
				{
					LogNameVal(Name, GetValue(Child));
					nl.Header.insert({ Name, GetValue(Child) });
					Retval = false;
					break;
				} else if (Name == ND_RESPCODE)
					nl.Header.insert({ Name, GetValue(Child) });
				else if (Name == ND_SRVLIST)
					Retval = ReadServerList(Child, nl);
				else if (Name == ND_CHKLIST)
					Retval = ReadCheckinList(Child, nl);
				else
				{
					UnknownNode(__FUNC__, Child);
				}
			}
		}
	} catch (Exception* e)
	{
		LogExcept(e);
		Retval = false;
	}
	EXITFUNC;
	return Retval;
}

//
// parse a 'header' node
//
bool TDMod::ReadHeader(_di_IXMLNode& Head, NLData& nl)
{
	_di_IXMLNode Child;
	bool Retval = true;
	ENTERFUNC;
	try
	{
		for (int x = 0; x < Head->ChildNodes->Count; x++) // get all children
		{
			Child = Head->ChildNodes->Nodes[x];
			LogNameVal(Child->NodeName, GetValue(Child));
			nl.Header.insert({ Child->NodeName, GetValue(Child) });
		}

	} catch (Exception* e)
	{
		LogExcept(e);
		Retval = false;
	}
	EXITFUNC;
	return Retval;
}

//
// parse a 'ServerList' node
//
bool TDMod::ReadServerList(_di_IXMLNode& Head, NLData& nl)
{
	String Name;
	_di_IXMLNode Child;
	bool Retval = true;
	ENTERFUNC;
	try
	{
		nl.Servers.clear();

		for (int x = 0; x < Head->ChildNodes->Count; x++)
		{
			Child = Head->ChildNodes->Nodes[x];
			Name = Child->NodeName;

			if (Name == ND_RESPCODE)
			{
				LogNameVal(Name, GetValue(Child));
				nl.Servers.Data.insert({ Name, GetValue(Child) });
			} else if (Name == ND_SERVER)
			{
				ReadServer(Child, nl);
			} else
			{
				UnknownNode(__FUNC__, Child);
			}
		}

	} catch (Exception* e)
	{
		LogExcept(e);
		Retval = false;
	}
	EXITFUNC;
	return Retval;
}

//
// parse a 'Server' node
//

bool TDMod::ReadServer(_di_IXMLNode& Head, NLData& nl)
{
	String Name;
	_di_IXMLNode Child;
	String ServerName;
	bool Retval = true;
	ENTERFUNC;
	try
	{
		for (int x = 0; x < Head->ChildNodes->Count; x++)
		{
			Child = Head->ChildNodes->Nodes[x];
			Name = Child->NodeName;
			if (Name == "ServerName")       // got a Server
			{
				Vpairs list;
				ServerName = GetValue(Child);
				LogNameVal(Name, ServerName);
				list.insert({ Name, ServerName });
				{
					nl.Servers.Servers.insert({ ServerName, list });
				}
			} else if (Name == ND_SRVACT)   // number of nets claimed active
			{
				LogNameVal(Name, GetValue(Child));
				nl.Servers.Servers[ServerName].insert({ Name, GetValue(Child) });
			} else if (Name == ND_NET)
			{
				if (!ReadNet(Child, ServerName, nl))    // got a Net
				{
					Retval = false;
					break;
				}
			} else
			{
				UnknownNode(__FUNC__, Child);   // ??
			}
		}
	} catch (Exception* e)
	{
		LogExcept(e);
		Retval = false;
	}
	EXITFUNC;
	return Retval;
}

//
// parse a 'Net' node
//

bool TDMod::ReadNet(_di_IXMLNode& Head, String& ServerName, NLData& nl)
{
	String Name;
	_di_IXMLNode Child;
	Vpairs net;
	bool Retval = true;
	ENTERFUNC;
	try
	{
		net.insert({ ND_SRVNAME, ServerName }); // stash ref to server hosting this net

		for (int x = 0; x < Head->ChildNodes->Count; x++) // grab all children
		{
			Child = Head->ChildNodes->Nodes[x];
			LogNameVal(Child->NodeName, GetValue(Child));
			net.insert({ Child->NodeName, GetValue(Child) });
		}

		auto iter = net.find(ND_NETID);

		if (iter != net.end())  // this is a 'past' net use netname + netid as unique key
		{
			LogInfo("Inserting: " + net[ND_NETNAME] + net[ND_NETID]);
			nl.Servers.NameByID.insert({ net[ND_NETNAME] + net[ND_NETID], net });
		} else
		{
			LogInfo("Inserting: " + net[ND_NETNAME]);   //  this is an active net
			nl.Servers.Nets.insert({ net[ND_NETNAME], net });
		}
	} catch (Exception* e)
	{
		LogExcept(e);
		Retval = false;
	}
	EXITFUNC;
	return Retval;
}

//
// parse a "CheckinList" node
//

bool TDMod::ReadCheckinList(_di_IXMLNode& Head, NLData& nl)
{
	String Name;
	_di_IXMLNode Child;
	bool Retval = true;
	ENTERFUNC;
	nl.ChkList.Data.clear();
	nl.ChkList.Checkins.clear();
	try
	{
		for (int x = 0; x < Head->ChildNodes->Count; x++)
		{
			Child = Head->ChildNodes->Nodes[x];
			Name = Child->NodeName;
			if (Name == ND_CHECKIN)
				ReadCheckin(Child, NL.ChkList );   // got a ckeckin record
			else
			{
				LogNameVal(Name, GetValue(Child));
				NL.ChkList.Data.insert({ Name, GetValue(Child) });   // got checkin list meta data
			}
		}

	} catch (Exception* e)
	{
		LogExcept(e);
		Retval = false;
	}
	EXITFUNC;
	return Retval;
}

//
// Read a 'Checkin' node
//
bool TDMod::ReadCheckin(_di_IXMLNode& Head, CheckinList& clist)
{
	String Name;
	_di_IXMLNode Child;
	Vpairs list;
	bool Retval = true;
	ENTERFUNC;

	try
	{
		for (int x = 0; x < Head->ChildNodes->Count; x++)   // grab all fields
		{
			Child = Head->ChildNodes->Nodes[x];
			Name = Child->NodeName;
			LogNameVal( Name, GetValue(Child));
			list.insert({ Name, GetValue(Child) });
		}
		LogInfo("Inserting Checkin");
		clist.Checkins.insert(clist.Checkins.end(), list); // insert list record into checkins list
        LogInfo(" Chkins size: " + IntToStr((int) clist.Checkins.size() ) );
	} catch (Exception* e)
	{
		LogExcept(e);
		Retval = false;
	}
	EXITFUNC;
	return Retval;
}

//
// return an empty string whenever node contents
// are NULL or non text.
//

inline String TDMod::GetValue(const _di_IXMLNode& Node)
{
	String retval;
	try
	{
		if (Node->IsTextElement)
			retval = Node->Text;
		else
		{
			retval = ""; // empty node ...
		}

	} catch (Exception* e) // just in case...
	{
		retval = "";
	}
	return retval;
}

//
// Obtain network info given name of network
//

bool TDMod::GetNetData(const String& Name, Vpairs& Net)
{
    ENTERFUNC;
    bool Retval = true;
    try
    {
        Net = NL.Servers.Nets[Name];

    } catch (Exception* e)
    {
        LogExcept(e);
        Retval = false;
    }
    return Retval;
}

//
// Obtain a TStringlist of active nets
//

bool TDMod::GetLiveNetNames(TStringList* List)
{
    bool Retval;
    ENTERFUNC;
    try
    {
        List->Clear();

        RESTRequest1->Resource = "GetActiveNets.php";
        RESTRequest1->Params->Clear();
        Retval = DoQuery(NL);

        for (auto Item : NL.Servers.Nets)
            List->Add(Item.first);

    } catch (Exception* e)
    {
        LogExcept(e);
        return false;
    }
    return Retval;
    EXITFUNC;
}

//
// return a CheckinList * for the given net
//

CheckinList* TDMod::GetLiveCheckins(const String Netname)
{
    ENTERFUNC;
    bool Retval = false;
    try
    {
        Vpairs& list = NL.Servers.Nets[Netname];
        String _netname = list[ND_NETNAME];
        String _servername = list[ND_SRVNAME];

        RESTRequest1->Resource = "GetCheckins.php";
        RESTRequest1->Params->Clear();
        RESTRequest1->Params->AddItem("ServerName", _servername, pkGETorPOST);
        RESTRequest1->Params->AddItem("NetName", _netname, pkGETorPOST);
		Retval = DoQuery(NL);

		if (Retval)
		{
			LogInfo("chkins count: " + IntToStr( (int) NL.ChkList.Checkins.size()));
			return &(NL.ChkList);
		}

    } catch (Exception* e)
    {
        LogExcept(e);
    }
    EXITFUNC;
    return nullptr;
}

//
// Get the Error string for last XML query, if any
//
const String TDMod::ErrorMessage()
{
    try
    {
        return NL.Header[ND_ERROR];
    } catch (Exception* e)
    {
        LogExcept(e);
    }
    return "";
}
//---------------------------------------------------------------------------

