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
inline ProcessorAffinity::ProcessorAffinity() :
    m_idealProcessor(PROCESSOR_DONT_CARE),
    m_affinityMask((efd::UInt32)PROCESSOR_DONT_CARE)
{
}
//-------------------------------------------------------------------------------------------------
inline ProcessorAffinity::ProcessorAffinity(
    Processor idealProcessor,
    efd::UInt32 affinityMask) :
        m_idealProcessor(idealProcessor),
        m_affinityMask(affinityMask)
{
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 ProcessorAffinity::GetAffinityMask() const
{
    return m_affinityMask;
}
//-------------------------------------------------------------------------------------------------
inline void ProcessorAffinity::SetAffinityMask(efd::UInt32 affinityMask)
{
    m_affinityMask = affinityMask;
}
//-------------------------------------------------------------------------------------------------
inline ProcessorAffinity::Processor
    ProcessorAffinity::GetIdealProcessor() const
{
    return m_idealProcessor;
}
//-------------------------------------------------------------------------------------------------
inline void ProcessorAffinity::SetIdealProcessor(
    ProcessorAffinity::Processor processor)
{
    m_idealProcessor = processor;
}
//-------------------------------------------------------------------------------------------------
} // end namespace efd

