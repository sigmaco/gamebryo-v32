/* Force the swig compiler to only generate on function and copy in the default arguments instead
    of on function for each on the or the default argument combinations */
%feature("compactdefaultargs");

%import "egf/Warnings.i"

%include <windows.i>
%include <typemaps.i>


%module bapiOnline
%{
#include <eon/bapiOnline.h>
#include <egf/bapiEntity.h>
%}

#if defined(SWIGPYTHON)
#define PYTHON_SCRIPTING
%{
#include <egfPython/bapiPython.h>
%}

#elif defined(SWIGLUA)
#define LUA_SCRIPTING
%{
#include <egfLua/bapiLua.h>
%}

#else
%{
#error Support for Python or Lua only at this time.
%}
#endif


// We should understand everything in the default game framework Bahavior API:
%import "egf/BehaviorAPI.i"
%import "eon/OnlineEntry.h"

// As soon as we are done importing all of our typedefs and what-not, we need to define some
// special typemaps that are used by other portions of the Built-ins API:
#if defined(SWIGPYTHON)
%include "egfPython/bapiPythonTypeMaps.i"
#elif defined(SWIGLUA)
%include "egfLua/bapiLuaTypeMaps.i"
#else
#error "This language is not currently supported."
#endif



// Now we include the real meat
%include "eon/bapiOnline.h"

