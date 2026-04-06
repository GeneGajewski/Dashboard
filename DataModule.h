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
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <System.Classes.hpp>
#include <System.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.xmldom.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.URLClient.hpp>

#include "DashTypes.h"

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
    TXMLDocument* XMLDocument1;
  private: // User declarations
    NLData NL; // holds everything!

    bool ReadHeader(_di_IXMLNode& Head, NLData& nl);
    bool ReadServerList(_di_IXMLNode& Head, NLData& nl);
    bool ReadServer(_di_IXMLNode& Head, NLData& nl);
    bool ReadNet(_di_IXMLNode& Head, String& ServerName, NLData& nl);
    bool ReadCheckinList(_di_IXMLNode& Head, NLData& nl);
    bool ReadCheckin(_di_IXMLNode& Head, CheckinList& list);
    inline String GetValue(const _di_IXMLNode& Node);
  public: // User declarations
    __fastcall TDMod(TComponent* Owner);
    bool DoQuery(NLData& nl);
    bool GetNetData(const String& Netname, Vpairs& NetData);
    bool GetLiveNetNames(TStringList* List);
    CheckinList* GetLiveCheckins(const String NetName);
    const String ErrorMessage();
};
//---------------------------------------------------------------------------
extern PACKAGE TDMod* DMod;

//---------------------------------------------------------------------------
#endif

