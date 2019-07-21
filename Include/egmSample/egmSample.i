%feature("compactdefaultargs");
%include <windows.i>
%include <typemaps.i>

// module code goes directly into the generated cpp
%module egmSample
%{
#include <egfLua/bapiLua.h>
#include "CameraBuiltins.h"
#include "GameStateBuiltins.h"
#include "WalkableBuiltins.h"
#include "MovementBuiltins.h"
%}

#define LUA_SCRIPTING
%{
#include <egfLua/bapiLua.h>
%}
#if defined(SWIGPYTHON)
%include "egf/bapiTypeMaps.i"
#elif defined(SWIGLUA)
%include "egfLua/bapiLuaTypeMaps.i"
#else
#error "This language is not currently supported."
#endif

%import "egmSampleLibType.h"

%include "CameraBuiltins.h"
%include "GameStateBuiltins.h"
%include "WalkableBuiltins.h"
%include "MovementBuiltins.h"
