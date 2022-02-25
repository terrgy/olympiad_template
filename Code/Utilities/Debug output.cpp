#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <map>

using namespace std;

struct ToStringConverter
{
    template<typename T>
    static string convert(const T& t)
    {
        return to_string(t);
    }

    static string convert(const char* c)
    {
        return convert((string)c);
    }

    static string convert(const char& c)
    {
        ostringstream stream;
        stream << '\'' << c << '\'';
        return stream.str();
    }

    static string convert(const string& str)
    {
        return "\"" + str + "\"";
    }

    static string convert(const bool& b)
    {
        return b ? "true" : "false";
    }

    template<typename T>
    static string convert(const set<T>& st)
    {
        ostringstream stream;
        stream << "set[";
        int index = 0;
        for (const T& i : st)
        {
            stream << convert(i);
            if (++index == (int)st.size())
            {
                stream << ']';
            }
            else
            {
                stream << ", ";
            }
        }
        return stream.str();
    }

    template<typename T>
    static string convert(const vector<T>& v)
    {
        ostringstream stream;
        stream << "vector[";
        for (int i = 0; i < (int)v.size(); ++i)
        {
            stream << convert(v[i]);
            if (i == (int)v.size() - 1)
            {
                stream << ']';
            }
            else
            {
                stream << ", ";
            }
        }
        return stream.str();
    }

    template<typename Key, typename Value>
    static string convert(const map<Key, Value>& mp)
    {
        ostringstream stream;
        stream << "map{";
        int index = 0;
        for (const auto& [key, value] : mp)
        {
            stream << convert(key) << ": " << convert(value);
            if (++index == (int)mp.size())
            {
                stream << '}';
            }
            else
            {
                stream << ", ";
            }
        }
        return stream.str();
    }

    template<int I, typename... Args>
    struct TupleConverter
    {
        static string tuple_convert(const tuple<Args...>& t)
        {
            ostringstream stream;
            stream << TupleConverter<I - 1, Args... >::tuple_convert(t);
            stream << convert(get<I>(t)) << (I == tuple_size_v< tuple<Args...> > - 1 ? ")" : ", ");
            return stream.str();
        }
    };

    template<typename... Args>
    struct TupleConverter<0, Args...>
    {
        static string tuple_convert(const tuple<Args...>& t)
        {
            ostringstream stream;
            stream << '(' << convert(get<0>(t)) << (tuple_size_v< tuple<Args...> > == 1 ? ")" : ", ");
            return stream.str();
        }
    };

    template<typename... Args>
    static string convert(const pair<Args...>& p)
    {
        ostringstream stream;
        stream << '(' << convert(p.first) << ", " << convert(p.second) << ')';
        return stream.str();
    }

    template<typename... Args>
    static string convert(const tuple<Args...>& t)
    {
        return TupleConverter< tuple_size_v< tuple<Args...> > - 1, Args...>::tuple_convert(t);
    }
};

void debug_out(ostream& out)
{
    out << endl;
}

template<typename Head, typename... Tail>
void debug_out(ostream& out, Head head, Tail... tail)
{
    out << ToStringConverter::convert(head) << "; ";
    debug_out(out, tail...);
}