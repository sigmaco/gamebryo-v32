%feature("compactdefaultargs");

%module egmAnimation
%{
#include <egmAnimation/egmAnimationBindings.h>
%}

#if defined(SWIGLUA)
%{
#include "egfLua/bapiLua.h"
%}
#endif

// As soon as we are done importing all of our typedefs and what-not, we need to define some
// special typemaps that are used by other portions of the Built-ins API:

#if defined(SWIGLUA)
%include "egfLua/bapiLuaTypeMaps.i"
#else
#error "This language is not currently supported."
#endif

// Needed so we can use constants in the NiActorManager for things like INVALID_SEQUENCE.
EE_SWIG_LUA_TYPE_WRAP(NiActorManager::SequenceID, SWIG_TYPECHECK_UINT32)

// For an explanation of this typedef see BehaviorAPI.i
typedef etp::UInt64 egf::EntityID;


// We should understand everything in the default game framework Bahavior API:
%import "egf/BehaviorAPI.i"

%import "egmAnimation/egmAnimationLibType.h"
%include "egmAnimation/egmAnimationBindings.h"
