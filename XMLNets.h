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

#ifndef XMLNetsH
#define XMLNetsH
//---------------------------------------------------------------------------

#include <map>
#include <stack>
#include <unordered_map>

// fast xmllite 'pull' parser for net logger 'net' records


// This object parses XML responses and works for both 'Active and 'Past' nets. A user call back
// is fired for earch 'net' record - it receives a std::map of Name/Value pairs representing the record.


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

    State state; // parse nesting level
    NamedValues List; // parameter accumulator
    std::stack<NamedValues> Stack; // pushed parent lists
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
