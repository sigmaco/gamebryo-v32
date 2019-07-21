%feature("compactdefaultargs");

%module ecr

%{
#include <ecr/bapiCoreRuntime.h>
%}

#if defined(SWIGLUA)
%{
#include "egfLua/bapiLua.h"
#include "ecr/ecrLua/ecrLuaRuntimeInitializer.h"
%}
#endif

// For an explanation of this typedef see BehaviorAPI.i
typedef etp::UInt64 egf::EntityID;

// As soon as we are done importing all of our typedefs and what-not, we need to define some
// special typemaps that are used by other portions of the Built-ins API:

#if defined(SWIGLUA)
%import "egfLua/bapiLuaTypeMaps.i"
#else
#error "This language is not currently supported."
#endif

// We should understand everything in the default game framework Bahavior API:
%import "egf/BehaviorAPI.i"

%import "ecr/ecrLibType.h"
%include "bapiCoreRuntime.h"

%init %{
    ecr::lua_ecrInitializePropertyHandlers(L);
%}
