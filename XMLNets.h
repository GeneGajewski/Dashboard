//---------------------------------------------------------------------------

#ifndef XMLNetsH
#define XMLNetsH
//---------------------------------------------------------------------------

#include <map>
#include <stack>
#include <unordered_map>

// fast xmllite 'pull' parser for net logger 'net' records


// This object parses XML responses and works for both 'Active and 'Past' nets. A user call back
// is fired for earch 'net' record which receives a std::map of Name/Value pairs representing the record.


class XML_Nets_Machine {

public:
    typedef std::map<String, String> NamedValues;

    using Callback = std::function<void(NamedValues&)>;

private:

    enum State { Unk,
        Header,
        ServerList,
        Server,
        Net };

    String element, text;

    State state; // nesting level
    NamedValues List; // parameter accumulator
    std::stack<NamedValues> Stack; // holds nested parent lists
    Callback Fcb; // user's callback

    // the xml element tags we're interested in

    // clang-format off
    static const std::unordered_map<String, State>& Keys() {
        static const std::unordered_map<String, State> keys = {
        { "Header" , 	Header 		},
        { "ServerList", ServerList	},
        { "Server",     Server      },
        { "Net",        Net         }
        };
        return keys;
    }
    // clang-format on

    void Element(const String& str);
    void EndElement(const String& str);
    void Text(const String& str);

public:

    explicit XML_Nets_Machine(Callback cb)
        : state(Unk)
        , Fcb(cb)
    {
    }
   void Execute(const TBytes& bytes);
};


#endif
