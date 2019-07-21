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

//-------------------------------------------------------------------------------------------------
inline bool LoopedThread::GetLastLoop()
{
    return m_lastLoop;
}
//-------------------------------------------------------------------------------------------------
inline void LoopedThread::SetLastLoop()
{
    m_lastLoop = true;
}
//-------------------------------------------------------------------------------------------------
inline void LoopedThread::WaitStart()
{
    m_start.Wait();
}
//-------------------------------------------------------------------------------------------------
inline void LoopedThread::SignalStart()
{
    m_start.Signal();
}
//-------------------------------------------------------------------------------------------------
inline void LoopedThread::WaitComplete()
{
    m_complete.Wait();
}
//-------------------------------------------------------------------------------------------------
inline void LoopedThread::SignalComplete()
{
    m_complete.Signal();
}
//-------------------------------------------------------------------------------------------------
inline void LoopedThread::Shutdown()
{
    // SetLastLoop() is not thread-safe to be called in the middle of a loop, because
    // "DoLoop(); Shutdown();" might not iterate if SetLastLoop() gets set before the loop checks
    // it.
    WaitForLoopCompletion();
    SetLastLoop();

    // Now that we're at the end, signal start to finish the thread.
    SignalStart();
}
//-------------------------------------------------------------------------------------------------

}   // End namespace efd.
