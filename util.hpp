#include <string>
#include <vector>

namespace util {

class StringRef
{
private:
    char const*     begin_;
    int             size_;

public:
    int size() const { return size_; }
    char const* begin() const { return begin_; }
    char const* end() const { return begin_ + size_; }

    StringRef( char const* const begin, int const size )
        : begin_( begin )
        , size_( size )
    {}
};

void split3( std::vector<StringRef> & result, std::string const& str, char delimiter = ',' )
{
    enum State { inSpace, inToken };

    State state = inSpace;
    char const*     pTokenBegin = 0;    // Init to satisfy compiler.
    for( std::string::const_iterator it = str.begin(); it != str.end(); ++it )
    {
        State const newState = (*it == delimiter? inSpace : inToken);
        if( newState != state )
        {
            switch( newState )
            {
            case inSpace:
                result.push_back( StringRef( pTokenBegin, &*it - pTokenBegin ) );
                break;
            case inToken:
                pTokenBegin = &*it;
            }
        }
        state = newState;
    }
    if( state == inToken )
    {
        result.push_back( StringRef( pTokenBegin, &*str.end() - pTokenBegin ) );
    }
}

}
