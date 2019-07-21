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
// Emergent Game Technologies, Calabasas, California 91302
// http://www.emergent.net

//------------------------------------------------------------------------------------------------
namespace efd
{

//------------------------------------------------------------------------------------------------
inline QOSCompare::QOSCompare(efd::QualityOfService virtualQOS)
    : m_virtualQOS(virtualQOS)
{
}

//------------------------------------------------------------------------------------------------
inline bool QOSCompare::operator==(const efd::QualityOfService& rhs) const
{
    return QOSCompare::Compare(m_virtualQOS, rhs);
}

//------------------------------------------------------------------------------------------------
inline bool QOSCompare::operator!=(const efd::QualityOfService& rhs) const
{
    return !(QOSCompare::Compare(m_virtualQOS, rhs));
}

//------------------------------------------------------------------------------------------------
inline bool QOSCompare::Compare(
    efd::QualityOfService virtualQOS,
    efd::QualityOfService physicalQOS)
{
    efd::QualityOfService foundPhysicalQOS = LookupPhysical(virtualQOS);
    return (physicalQOS == foundPhysicalQOS) || (virtualQOS == physicalQOS);
}

//------------------------------------------------------------------------------------------------
inline efd::QualityOfService QOSCompare::LookupPhysical(efd::QualityOfService virtualQOS)
{
    // if virtualQOS does not have the Virtual bit set, it is already a physical QOS and can be
    // returned as is.
    if (!(virtualQOS & NET_VIRTUAL))
    {
        return virtualQOS;
    }
    // we default to kQOS_Reliable, so if no mapping is found we still have a valid QOS
    efd::QualityOfService physicalQOS = ms_defaultQualityOfService;
    ms_virtualToPhysical.find(virtualQOS,physicalQOS);
    return physicalQOS;
}

//------------------------------------------------------------------------------------------------
inline void QOSCompare::Cleanup()
{
    ms_virtualToPhysical.clear();
    ms_configRead = false;
}

//------------------------------------------------------------------------------------------------
inline void QOSCompare::SetDefaultQualityOfService(efd::QualityOfService physicalQOS)
{
    ms_defaultQualityOfService = physicalQOS;
}

} // end namespace efd
