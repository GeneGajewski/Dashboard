//---------------------------------------------------------------------------

#pragma hdrstop

#include "XMLNets.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <utilcls.h>
#include <xmllite.h>

#pragma comment(lib, "xmllite.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shlwapi.lib")




// incoming xml tag

void XML_Nets_Machine::Element(const String& str)
{
    element = str;
    auto keys = Keys();

    // we aren't doing anything with the top-level parameter lists yet ..

    auto tag = keys.find(str);

    if (tag != keys.end()) {
        switch (tag->second) {
        case ServerList:    // push
            Stack.push(std::move(List));
            List.clear();
            state = tag->second;
            break;
        case Server:    // push
            Stack.push(std::move(List));
            List.clear();
            state = tag->second;
            break;
        case Net: // collect a net record's fields
            if (state != Net)   // first time only
                Stack.push(std::move(List));
            List.clear();
            state = tag->second;
            break;
        case Unk:   // don't care
        case Header:
            break;
        }
    }
}

// pop stack if indicated or continue on

void XML_Nets_Machine::EndElement(const String& str)
{
    auto keys = Keys();
    auto tag = keys.find(str);
    if (tag != keys.end()) {
        switch (tag->second) {
        case Header: // top level - no need pop
            break;
        case ServerList:
            List = std::move(Stack.top());
            Stack.pop();
            break;
        case Server:
            List = std::move(Stack.top());
            Stack.pop();
            break;
        case Net: // bottom-most level - process 'net' record
            List["Server"] = Stack.top()["ServerName"];    // add server field to record from parent
            Fcb(List);
            break;
        default:;  // don't care
        }
    }
}

// store a named value

void XML_Nets_Machine::Text(const String& str)
{
    List[element] = str;
}

// Process XML as array of bytes

void XML_Nets_Machine::Execute(const TBytes& bytes)
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

