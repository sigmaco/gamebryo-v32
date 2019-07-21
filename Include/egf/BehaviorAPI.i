/* File : BehaviorAPI.i */

/* Force the swig compiler to only generate on function and copy in the default arguments
    instead on on function for each on the or the default argument combinations */
%feature("compactdefaultargs");

%import "egf/Warnings.i"


%include <windows.i>
%include <typemaps.i>

%ignore efd::NonAtomicRefCount;
%ignore efd::AtomicRefCount;
%ignore efd::EventRecord;
%ignore efd::EventRecordPtr;

%module BehaviorAPI
%{
#include <efd/UniversalTypes.h>
#include <efd/StdContainers.h>
#include <efd/ID128.h>
#include <efd/efdLibType.h>
#include <egf/EntityTypes.h>
#include <egf/BehaviorAPI.h>
#include <egf/bapiEntity.h>
#include <egf/bapiConfig.h>
#include <egf/bapiBlock.h>

using namespace egf;
using namespace efd;
%}

%import "BasicTypes.i"

// Need a definition of EE_FORCEINLINE for SmartPointer
%define EE_FORCEINLINE inline
%enddef

// An import will parse the file for symbols but not wrapper its contents
%import "efd/efdLibType.h"          // for EE_UTILITIES_ENTRY macro definition
%import "efd/utf8string.h"          // for utf8string
%import "egf/egfLibType.h"          // for EE_EGFLIBTYPE_H macro definition
%import "efd/SmartPointer.h"        // for EE_DECLARE_SMART_POINTER macro definition
%import "efd/ClassInfo.h"           // for EE_DECLARE_INTERFACE macro definition
%import "efd/ReferenceCounting.h"   // for EE_DECLARE_CONCRETE_REFCOUNT macro definition
%import "efd/IBase.h"
%import "efd/UniversalID.h"

// NOTE: Do NOT include this header, below we lie and tell SWIG that EntityID is just a
// UInt64.  See the note below for details.
//%import "EntityID.h"
//%import "EventID.h"

// We have two options for pulling in the typedefs that we need (we reject trying to use %ignore on
// header files not meant for SWIG consumption)

// Option 1: just duplicate the typedef and include comments so we can manually sync to any changes
namespace egf
{

// NOTE: The following typedef might look horridly wrong because EntityID is really a class and
// not just a UInt64, but this is being done on purpose.  EntityID has-a uint64 and we have a
// custom type map rule so that this class becomes a plain uint64 inside of the script language
// but there were still problems where overloaded functions could not be called.  Basically when
// trying to decide which function overload should be called SWIG cannot use the custom type maps
// to relize that the PyObject *could* be converted to the C++ type in question so it never finds
// a match for the function.
typedef efd::UInt64 EntityID;

// NOTE: EventID uses the same trick as EntityID, see above for details.
typedef efd::UInt64 EventID;

}

// Option 2: make new header files that just contain the typedefs and constants that we want to
// SWIG and then directly include that header file.  I think this will be our best option long
// term, but for getting things working quickly option 1 is easier.
%include "egf/EntityTypes.h"

// Now we include the real meat
%include "egf/BehaviorAPI.h"
%include "egf/bapiEntity.h"
%include "egf/bapiConfig.h"
%include "egf/bapiBlock.h"
