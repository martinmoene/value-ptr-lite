#include "nonstd/value_ptr.hpp"

using namespace nonstd;

struct Widget
{
   Widget( int x );

//#if nsvp_CPP11_OR_GREATER
//   // Thanks to value_ptr we get value semantics for free
//   Widget( Widget const& ) = default;
//   Widget & operator=( Widget const& ) = default;
//   ~Widget() = default;
//#endif

   ~Widget();

   int next();

   struct Pimpl;
   value_ptr<Pimpl> ptr;
};

