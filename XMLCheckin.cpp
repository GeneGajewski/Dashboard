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

    // we aren't doing anything with the top-level parameter lists yet ..

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

