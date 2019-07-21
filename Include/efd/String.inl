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

//--------------------------------------------------------------------------------------------------
// Buffer operations - length manipulation
//--------------------------------------------------------------------------------------------------
inline efd::Bool String::IsValid() const
{
    if (m_kHandle == NULL)
        return false;

    return ValidateString(m_kHandle);
}

//--------------------------------------------------------------------------------------------------
inline String::StringHeader* String::GetRealBufferStart(StringBody* pBody)
{
    EE_ASSERT(pBody != NULL);
    return (StringHeader*)((StringData*)pBody);
}

//--------------------------------------------------------------------------------------------------
inline efd::Char* String::GetString(StringBody* pBody, efd::Bool bValidate)
{
#ifdef _DEBUG
    if (bValidate)
        EE_ASSERT(ValidateString(pBody));
#else
    EE_UNUSED_ARG(bValidate);
#endif
    // No need to perform an if NULL check, because
    // it will correctly return NULL if pBody == NULL
    return pBody->m_data;
}

//--------------------------------------------------------------------------------------------------
inline size_t String::GetLength(StringBody* pBody, efd::Bool bValidate)
{
    if (pBody == NULL)
    {
        return 0;
    }
    else
    {
#ifdef _DEBUG
        if (bValidate)
            EE_ASSERT(ValidateString(pBody));
#else
        EE_UNUSED_ARG(bValidate);
#endif
        StringHeader* pHeader = GetRealBufferStart(pBody);
        return pHeader->m_cchStringLength;
    }
}

//--------------------------------------------------------------------------------------------------
inline void String::SetLength(StringBody* pBody, size_t stLength)
{
    if (pBody == NULL)
        return;

    StringHeader* pHeader = GetRealBufferStart(pBody);
    pHeader->m_cchStringLength = stLength;
#ifdef _DEBUG
    EE_ASSERT(pHeader->m_cchStringLength <= pHeader->m_cbBufferSize);
    EE_ASSERT(stLength == strlen(pBody->m_data));
#endif
}

//--------------------------------------------------------------------------------------------------
inline void String::CalcLength()
{
    // SetLength do the NULL check
    SetLength(m_kHandle, strlen(m_kHandle->m_data));
}

//--------------------------------------------------------------------------------------------------
inline void String::SetBuffer(StringBody* pBody)
{
    if (pBody == m_kHandle)
        return;

    DecRefCount(m_kHandle);
    IncRefCount(pBody);
    m_kHandle = pBody;
}

//--------------------------------------------------------------------------------------------------
inline void String::CopyOnWrite(efd::Bool bForceCopy)
{
    if (GetRefCount(m_kHandle) > 1 || bForceCopy)
    {
        StringBody* pBody = m_kHandle;
        m_kHandle = AllocateAndCopyHandle(m_kHandle);
        DecRefCount(pBody);
    }
}

//--------------------------------------------------------------------------------------------------
inline void String::CopyOnWriteAndResize(size_t stSizeDelta, efd::Bool bForceCopy)
{
    if (Resize(stSizeDelta))
        return;

    CopyOnWrite(bForceCopy);
}

//--------------------------------------------------------------------------------------------------
// Basic string operations
//--------------------------------------------------------------------------------------------------
inline size_t String::Length() const
{
    return GetLength(m_kHandle, false);
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool String::IsEmpty() const
{
    return Length() == 0;
}

//--------------------------------------------------------------------------------------------------
inline void String::Empty()
{
    *this = NullString();
}

//--------------------------------------------------------------------------------------------------
inline efd::Char String::GetAt(size_t ui) const
{
    if (ui >= Length())
        return '\0';

    return GetString(m_kHandle)[ui];
}

//--------------------------------------------------------------------------------------------------
inline void String::SetAt(size_t ui, efd::Char c)
{
    if (ui >= Length())
        return;

    CopyOnWrite();
    GetString(m_kHandle)[ui] = c;

    if (c == '\0')
    {
        // we have altered the length of the string, update the stored length
        SetLength(m_kHandle, ui);
    }
}

//--------------------------------------------------------------------------------------------------
// String comparison
//--------------------------------------------------------------------------------------------------
inline efd::Bool String::Contains(const efd::Char* pcStr) const
{
    return Find(pcStr) != INVALID_INDEX;
}

//--------------------------------------------------------------------------------------------------
// String manipulation
//--------------------------------------------------------------------------------------------------
inline String String::Left(size_t stCount) const
{
    // Mid will check range and reduce count to string length if needed.
    return Mid(0, stCount);
}

//--------------------------------------------------------------------------------------------------
inline String String::Right(size_t stCount) const
{
    size_t stLength = Length();
    if (stCount > stLength)
        stCount = stLength;

    return Mid(stLength - stCount, stCount);
}

//--------------------------------------------------------------------------------------------------
// String operators
//--------------------------------------------------------------------------------------------------
inline String::operator const efd::Char*() const
{
    return GetString(m_kHandle);
}

//--------------------------------------------------------------------------------------------------
inline String& String::operator=(const String& kStr)
{
    if (GetString(kStr.m_kHandle) == GetString(m_kHandle))
        return *this;

    SetBuffer(kStr.m_kHandle);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline String& String::operator=(const efd::Char* pcStr)
{
    if (pcStr == GetString(m_kHandle))
        return *this;

    Swap(m_kHandle, pcStr);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline String& String::operator=(efd::Char ch)
{
    efd::Char acString[2];
    acString[0] = ch;
    acString[1] = '\0';
    return String::operator=((const efd::Char*)&acString[0]);
}

//--------------------------------------------------------------------------------------------------
inline String& String::operator+=(const String& kStr)
{
    Concatenate(kStr.c_str());
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline String& String::operator+=(const efd::Char* pcStr)
{
    Concatenate(pcStr);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline String& String::operator+=(efd::Char ch)
{
    Concatenate(ch);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline String operator+(const String& kStr1, const String& kStr2)
{
    String kResult(kStr1);
    kResult.Concatenate(kStr2.c_str());
    return kResult;
}

//--------------------------------------------------------------------------------------------------
inline String operator+(const String& kStr1, const efd::Char* pcStr2)
{
    String kResult(kStr1);
    kResult.Concatenate(pcStr2);
    return kResult;
}

//--------------------------------------------------------------------------------------------------
inline String operator+(const efd::Char* pcStr1, const String& kStr2)
{
    String kResult(pcStr1);
    kResult.Concatenate(kStr2.c_str());
    return kResult;
}

//--------------------------------------------------------------------------------------------------
inline String operator+(const String& kStr1, efd::Char ch2)
{
    String kResult(kStr1);
    kResult.Concatenate(ch2);
    return kResult;
}

//--------------------------------------------------------------------------------------------------
inline String operator+(efd::Char ch1, const String& kStr2)
{
    String kResult(ch1);
    kResult.Concatenate(kStr2.c_str());
    return kResult;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator==(const String& kStr1, const String& kStr2)
{
    return kStr1.Equals(kStr2);
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator==(const String& kStr1, const efd::Char* pcStr2)
{
    return kStr1.Equals(pcStr2);
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator==(const efd::Char* pcStr1, const String& kStr2)
{
    return kStr2.Equals(pcStr1);
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator!=(const String& kStr1, const String& kStr2)
{
    return !kStr1.Equals(kStr2);
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator!=(const String& kStr1, const efd::Char* pcStr2)
{
    return !kStr1.Equals(pcStr2);
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator!=(const efd::Char* pcStr1, const String& kStr2)
{
    return kStr2.Equals(pcStr1);
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator<(const String& kStr1, const String& kStr2)
{
    return kStr1.Compare(kStr2) < 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator<(const String& kStr1, const efd::Char* pcStr2)
{
    return kStr1.Compare(pcStr2) < 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator<(const efd::Char* pcStr1, const String& kStr2)
{
    return kStr2.Compare(pcStr1) > 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator>(const String& kStr1, const String& kStr2)
{
    return kStr1.Compare(kStr2) > 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator>(const String& kStr1, const efd::Char* pcStr2)
{
    return kStr1.Compare(pcStr2) > 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator>(const efd::Char* pcStr1, const String& kStr2)
{
    return kStr2.Compare(pcStr1) < 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator<=(const String& kStr1, const String& kStr2)
{
    return kStr1.Compare(kStr2) <= 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator<=(const String& kStr1, const efd::Char* pcStr2)
{
    return kStr1.Compare(pcStr2) <= 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator<=(const efd::Char* pcStr1, const String& kStr2)
{
    return kStr2.Compare(pcStr1) >= 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator>=(const String& kStr1, const String& kStr2)
{
    return kStr1.Compare(kStr2) >= 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator>=(const String& kStr1, const efd::Char* pcStr2)
{
    return kStr1.Compare(pcStr2) >= 0;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool operator>=(const efd::Char* pcStr1, const String& kStr2)
{
    return kStr2.Compare(pcStr1) <= 0;
}

//--------------------------------------------------------------------------------------------------
// utf8string compatibility methods
//--------------------------------------------------------------------------------------------------
inline const efd::Char* String::c_str() const
{
    if (!m_kHandle)
        return "";

    return GetString(m_kHandle);
}

//--------------------------------------------------------------------------------------------------
inline const efd::Char* String::data() const
{
    if (!m_kHandle)
        return "";

    return GetString(m_kHandle);
}

//--------------------------------------------------------------------------------------------------
inline size_t String::size() const
{
    return GetLength(m_kHandle);
}

//--------------------------------------------------------------------------------------------------
inline size_t String::length() const
{
    return GetLength(m_kHandle);
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool String::empty() const
{
    return GetLength(m_kHandle) == 0;
}

//--------------------------------------------------------------------------------------------------
inline void String::clear()
{
    Empty();
}

//--------------------------------------------------------------------------------------------------
inline void String::toupper()
{
    ToUpper();
}

//--------------------------------------------------------------------------------------------------
inline void String::tolower()
{
    ToLower();
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool String::is_valid() const
{
    return IsValid();
}

//--------------------------------------------------------------------------------------------------
inline String String::substr(size_t stBegin, size_t stCount) const
{
    if (stCount != INVALID_INDEX)
        stCount += stBegin;

    return GetSubstring(stBegin, stCount);
}

//--------------------------------------------------------------------------------------------------
inline int String::compare(const String& kStr) const
{
    return Compare(kStr);
}

//--------------------------------------------------------------------------------------------------
inline int String::compare(const efd::Char* pcStr) const
{
    return Compare(pcStr);
}

//--------------------------------------------------------------------------------------------------
inline int String::icompare(const String& kStr) const
{
    return CompareNoCase(kStr.c_str());
}

//--------------------------------------------------------------------------------------------------
inline int String::icompare(const efd::Char* pcStr) const
{
    return CompareNoCase(pcStr);
}

//--------------------------------------------------------------------------------------------------
inline void String::insert(size_t stPos, const efd::Char* pcStr)
{
    Insert(pcStr, stPos);
}

//--------------------------------------------------------------------------------------------------
inline void String::insert(size_t stPos, const efd::Char* pcStr, size_t stCount)
{
    String kPartStr(pcStr, stCount);

    Insert(kPartStr.c_str(), stPos);
}

//--------------------------------------------------------------------------------------------------
inline void String::push_back(efd::Char ch)
{
    Concatenate(ch);
}

//--------------------------------------------------------------------------------------------------
inline String& String::append(const efd::Char* pcStr)
{
    Concatenate(pcStr);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline String& String::append(efd::Char ch)
{
    Concatenate(ch);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline String& String::append(const efd::Char* pcStr, size_t stPos, size_t stCount)
{
    if (stPos >= strlen(pcStr))
        return *this;

    String kTempStr(pcStr + stPos, stCount);
    Concatenate(kTempStr);

    return *this;
}

//--------------------------------------------------------------------------------------------------
inline String& String::append(size_t stCount, efd::Char ch)
{
    if (!stCount)
        return *this;

    String kTempStr(stCount);
    while (stCount--)
        kTempStr.SetAt(stCount, ch);

    Concatenate(kTempStr);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline size_t String::find(const efd::Char* pcStr, size_t stBegin) const
{
    return Find(pcStr, stBegin);
}

//--------------------------------------------------------------------------------------------------
inline size_t String::find(efd::Char ch, size_t stBegin) const
{
    return Find(ch, stBegin);
}

//--------------------------------------------------------------------------------------------------
inline size_t String::rfind(const efd::Char* pcStr, size_t stBegin) const
{
    return FindReverse(pcStr, stBegin);
}

//--------------------------------------------------------------------------------------------------
inline size_t String::rfind(efd::Char ch, size_t stBegin) const
{
    return FindReverse(ch, stBegin);
}

//--------------------------------------------------------------------------------------------------
inline size_t String::find_first_of(const efd::Char* pcDelimiters, size_t stBegin) const
{
    return FindOneOf(pcDelimiters, stBegin);
}

//--------------------------------------------------------------------------------------------------
inline size_t String::find_first_of(efd::Char cDelimiter, size_t stBegin) const
{
    return Find(cDelimiter, stBegin);
}

//--------------------------------------------------------------------------------------------------
inline size_t String::find_last_of(const efd::Char* pcDelimiters, size_t stBegin) const
{
    return FindOneOfReverse(pcDelimiters, stBegin);
}

//--------------------------------------------------------------------------------------------------
inline size_t String::find_last_of(efd::Char cDelimiter, size_t stBegin) const
{
    return FindReverse(cDelimiter, stBegin);
}

//--------------------------------------------------------------------------------------------------
inline void String::trim(_Trim t, const efd::Char* pcDelimiters)
{
    switch (t)
    {
    case TrimBack:
        TrimSetRight(pcDelimiters);
        return;
    case TrimAll:
        TrimSetRight(pcDelimiters);
        TrimSetLeft(pcDelimiters);
        return;
    default:
        TrimSetLeft(pcDelimiters);
        return;
    }
}

//--------------------------------------------------------------------------------------------------
inline size_t String::replace_substr(const efd::Char* pcFindStr, const efd::Char* pcReplaceStr)
{
    return Replace(pcFindStr, pcReplaceStr);
}

//--------------------------------------------------------------------------------------------------
} // end namespace efd
