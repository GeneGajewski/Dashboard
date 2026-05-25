/*
 *   Copyright (C) 2026 Gene Gajewski WG5ENE
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

#include "XMLCheckin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <utilcls.h>
#include <xmllite.h>

#pragma comment(lib, "xmllite.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shlwapi.lib")




// incoming xml tag

void XML_Checkin_Machine::Element(const String& str)
{
    element = str;
    auto keys = Keys();

    auto tag = keys.find(str);

    if (tag != keys.end()) {
        switch (tag->second) {
        case CheckinList:    // push
            Stack.push(std::move(List));
            List.clear();
            state = tag->second;
            break;
        case Checkin:
            if(state != Checkin)
                Stack.push(std::move(List));  // first time only
            List.clear();
            state = tag->second;
            break;
        case Unk:   // don't care
            break;
        case Header:
            List.clear();
            state = tag->second;
            break;
        }
    }
}

// pop stack if indicated or continue on

void XML_Checkin_Machine::EndElement(const String& str)
{
    auto keys = Keys();
    auto tag = keys.find(str);
    if (tag != keys.end()) {
        switch (tag->second) {
        case Header: // top level - no need pop
            Fcb(tag->second, List);
            break;
        case CheckinList:
            List = std::move(Stack.top());
            Stack.pop();
            Fcb(tag->second, List);
            break;
        case Checkin: // bottom-most level - process 'net' record
            Fcb(tag->second, List);
            break;
        default:;  // don't care
        }
    }
}

// store a named value

void XML_Checkin_Machine::Text(const String& str)
{
    List[element] = str;
}

// Process XML as array of bytes

void XML_Checkin_Machine::Execute(const TBytes& bytes)
{

    if (bytes.Length == 0) // huh?
        return;

      // RAII
     struct CoInitGuard
     {
        CoInitGuard() 	{ CoInitialize(NULL); }
        ~CoInitGuard()  { CoUninitialize();	  }
     } comGuard;


    // create memstream interface
    TComInterface<IStream> pMemStream = SHCreateMemStream(&bytes[0], static_cast<UINT>(bytes.Length));
    if (!pMemStream)
        return;

    // create xmlreader interface
    TComInterface<IXmlReader> pReader;
    if (FAILED(CreateXmlReader(__uuidof(IXmlReader), reinterpret_cast<void**>(&pReader), NULL)))
        return;

    // set xmlreader's input
    if (FAILED(pReader->SetInput(pMemStream)))
        return;

    XmlNodeType nodeType;
    const WCHAR* pwszLocalName = NULL;
    const WCHAR* pwszValue = NULL;
    HRESULT hr;

    // pull xml nodes till done

    while (S_OK == (hr = pReader->Read(&nodeType))) {
        switch (nodeType) {
        case XmlNodeType_XmlDeclaration: // not interested
            break;

        case XmlNodeType_Element: // new tag
            pReader->GetLocalName(&pwszLocalName, NULL);
            Element(pwszLocalName);
            break;

        case XmlNodeType_EndElement: // end tag
            pReader->GetLocalName(&pwszLocalName, NULL);
            EndElement(pwszLocalName);
            break;

        case XmlNodeType_Text: // a value (named by previous 'element' )
            pReader->GetValue(&pwszValue, NULL);
            Text(pwszValue);
            break;

        default: // not interested
            break;
        }
    }
}

