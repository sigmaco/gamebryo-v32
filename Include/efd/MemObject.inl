// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net


namespace efd
{
#if !defined(__SPU__)

#ifdef EE_MEMORY_DEBUGGER

//-------------------------------------------------------------------------------------------------
inline void MemObject::operator delete(void*, MemHint, const char*, int, const char*)
{
}
//-------------------------------------------------------------------------------------------------
inline void MemObject::operator delete[](void*, MemHint, const char*, int, const char*)
{
}
//-------------------------------------------------------------------------------------------------

#else   // EE_MEMORY_DEBUGGER

//-------------------------------------------------------------------------------------------------
inline void MemObject::operator delete(void *, MemHint)
{
}
//-------------------------------------------------------------------------------------------------
inline void MemObject::operator delete[](void *, MemHint)
{
}
//-------------------------------------------------------------------------------------------------

#endif  // EE_MEMORY_DEBUGGER


//-------------------------------------------------------------------------------------------------
inline void* MemObject::operator new(size_t, void* p)
{
    return p;
}
//-------------------------------------------------------------------------------------------------
inline void* MemObject::operator new[](size_t, void* p)
{
    return p;
}
//-------------------------------------------------------------------------------------------------
inline void MemObject::operator delete(void *, void*)
{
}
//-------------------------------------------------------------------------------------------------
inline void MemObject::operator delete[](void *, void*)
{
}
//-------------------------------------------------------------------------------------------------

#endif  // !defined(__SPU__)

}   // End namespace efd.
