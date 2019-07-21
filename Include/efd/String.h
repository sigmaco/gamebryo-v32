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

#pragma once
#ifndef EE_STRING_H
#define EE_STRING_H

#include <efd/MemObject.h>
#include <efd/IBase.h>
#include <efd/utf8char.h>
#include <efd/StdContainers.h>

/// @cond EMERGENT_INTERNAL

namespace efd
{

/** \class String
    \brief This class encapsulates a copy-on-write reference-counted string

    String is a copy-on-write reference-counted string. It provides fast and efficient copy
    constructors as well as fast comparison. When a new string is created from an existing string
    both strings will share a reference to the same string data; if one of these strings is then
    modified only then will the string data be copied into a seperate buffer so that only the
    modified string is updated. Comparison is optimized by first comparing data pointers and then
    looking at the length and only comparing the string contents when needed.

    This class is mostly compatible with efd::utf8string class. It contains wrappers for nearly all
    methods from utf8string and utf8string in most cases can be just replaced with String. The main
    difference is that String operates on \b bytes rather than on \b characters. In utf8 strings
    one \b character can be represented by more than one byte. String also contains utf8-aware
    methods (methods with a name ending with utf8) which work with utf8 characters rather than
    bytes so this class can still handle utf8 data when needed.  As the utf8 aware methods are
    slower than regular methods they should only be used when required. It is a good practice to
    use these methods only when the string needs to be converted to Unicode or a system specific
    locale or used to generate a glyph list.

    In general, utf8string is more efficient for short temporary strings that are not frequently
    iterated through and String is more efficient for longer strings, strings that will be
    frequently iterated as bytes rather than characters, or strings that will be passed around
    and potentially referenced in multiple places.
 */

class Point2;
class Point3;
class Color;
class ColorA;

/// Special tag for passing to the constructor when you want prinft-style formatting
enum _Formatted { Formatted };

/// Tags to control the behavior of String::trim
enum _Trim { TrimFront, TrimBack, TrimAll };

class EE_EFD_ENTRY String : public MemObject
{
public:
    /// Invalid index value
    static const size_t INVALID_INDEX = (size_t)-1;
    /// Invalid index value for compatibility with stl-style strings
    static const size_t npos = (size_t)-1;

    /** @name Constructors
     *  String constructors and destructor
    */
    //@{
    /// Constructs an empty String.
    String();

    /// Constructs String from another String. Increments RefCount only, no data is copied.
    String(const String& kStr);

    /// Constructs String from an input string. String is copied into internal buffer.
    String(const efd::Char* pcStr);

    /// Constructs String from a part of input string. String is copied into internal buffer.
    String(const efd::Char* pcStr, size_t stStrLength);

    /// Constructs an empty String, allocating given buffer size.
    String(size_t stBuffLength);

    /// Constructs String from a single char.
    String(efd::Char ch);

    /// Constructs String from a single UTF8 char.
    String(const efd::utf8char_t& ch);

    /// Constructs String using printf-style formating.
    String(_Formatted, const efd::Char* pcFormat, ...);

    /// Destroys String. Refcount is decremented and if it equals zero, the buffer is deleted.
    ~String();
    //@}

    /** @name Basic string operations
        Methods to get string length, get / set char at some position, check, if string is valid.
        All these methods works at a \b byte level.
    */
    //@{
    /// Returns the length of the string.
    size_t Length() const;

    /// Tests whether a String object contains no characters.
    efd::Bool IsEmpty() const;

    /// Forces a string to have 0 length.
    void Empty();

    /// Returns the character at a given position.
    efd::Char GetAt(size_t stPos) const;

    /// Sets a character at a given position.
    void SetAt(size_t stPos, efd::Char ch);

    /// Allocate buffer and copy string to it. You must free the buffer after use!
    efd::Char* MakeExternalCopy() const;

    /// Returns true if this string initialized and valid
    efd::Bool IsValid() const;
    //@}

    /** @name Comparison methods
     *  These methods compare strings.
    */
    //@{
    /// This method compares String to given String and returns their relationship.
    int Compare(const String& kStr) const;

    /// This method compares String to given string and returns their relationship.
    int Compare(const efd::Char* pcStr) const;

    /// This method compares lowercase versions of strings.
    int CompareNoCase(const efd::Char* pcStr) const;

    /// Does this string exactly equal the input String?
    efd::Bool Equals(const String& kStr) const ;

    /// Does this string exactly equal the input string?
    efd::Bool Equals(const efd::Char* pcStr) const ;

    /// Does this string exactly equal the input string ignoring case?
    efd::Bool EqualsNoCase(const efd::Char* pcStr) const;
    //@}

    /** @name String searching
     *  Methods to search string for occurence of string/char, get substring, etc.
    */
    //@{
    /// Is the input character string a substring of this string
    efd::Bool Contains(const efd::Char* pcStr) const;

    /// Is the input character string a substring of this string (ignore case version)
    efd::Bool ContainsNoCase(const efd::Char* pcStr) const;

    /// Find a character within this string and return its index
    size_t Find(efd::Char ch, size_t uiStart = 0) const;

    /// Find a substring within this string and return its index
    size_t Find(const efd::Char* pcStr, size_t stStart = 0) const;

    /// Find a character, starting from the uiSearchEnd and working backwards, and return its index
    size_t FindReverse(efd::Char ch, size_t stStart = npos) const;

    /// Find string, starting from given position and working backwards, and return its index
    size_t FindReverse(const efd::Char* pcStr, size_t stStart = npos) const;

    /// Find a character within this string from the set of characters in pcStr and return its index
    size_t FindOneOf(const efd::Char* pcDelimiters, size_t stStart = 0) const;

    /// Find a character within this string from the set of characters in pcStr and return its index
    size_t FindOneOfReverse(const efd::Char* pcDelimiters, size_t stStart = 0) const;
    //@}

    /** @name String manipulation
     *  Methods to get / set, trim, replace or delete parts of the string.
    */
    //@{
    /// Add the efd::Char* to the end of this string, growing the buffer as necessary.
    void Concatenate(const efd::Char* pcStr);

    /// Add the char to the end of this string, growing the buffer as necessary.
    void Concatenate(efd::Char ch);

    /// Get a separate copy of a substring from stBegin up to stEnd
    String GetSubstring(size_t stBegin, size_t stEnd = npos) const;

    /** Get a separate copy of a substring from uiBegin up to the first
    *  character found in pcDelimiters
    */
    String GetSubstring(size_t stBegin, const efd::Char* pcDelimeters) const;

    /// Set to a substring.
    String& SetToSubstring(const efd::Char* pcStr, size_t stCount);

    /** Insert the input string at the specified index, shifting all subsequent
     *  characters to the right. If the index is >= the original string length,
     *  the insertion string is concatenated. The address of the insertion
     *  string cannot be within the address space of the internal string buffer.
    */
    void Insert(const efd::Char* pcStr, size_t stBegin);

    /// Extracts the middle part of a string
    String Mid(size_t stBegin, size_t stCount = npos) const;

    /// Extracts the left part of a string
    String Left(size_t stCount) const;

    /// Extracts the right part of a string
    String Right(size_t stCount) const;

    /// Replace all exact matches of pcWhatToReplace in this string with pcReplaceWith
    size_t Replace(const efd::Char* pcWhatToReplace, const efd::Char* pcReplaceWith);

    /** Overlapping Replace Substring
        This will replace all occurrences of the find string with the replace string including
        any occurrences which are the result of a previous substitution.

        @note If the replacement string contains the find sting this function will return npos
        and make no modifications to the string.

        Examples:
        @code
            "foooooo".OverlappingReplace("oo", "o") => "fo"
            "flolol".OverlappingReplace("lol", "l") => "fl"
        @endcode

        @note The search for additional replacements proceedes forward from the beginning of the
        previous replacement.  This means that it is possible for instances of the search string
        to remain in the final result.  Consider this example:
        @code
            "flloll".OverlappingReplace("lol", "o") => "flol"
        @endcode

        @param pcFindStr The sub-string to find
        @param pcReplaceStr The replacement string
        @return The number of replacements that were made, or -1 if the arguments are invalid.
    */
    size_t OverlappingReplace(const efd::Char* pcFindStr, const efd::Char* pcReplaceStr);

    /// Remove the substring specified
    void RemoveRange(size_t stBegin, size_t stCount);

    /// Trim this character from the beginning of the string
    void TrimLeft(efd::Char ch = ' ');

    /// Trim this character from the end of the string
    void TrimRight(efd::Char ch = ' ');

    /// Trim this string from the beginning of the string
    void TrimLeft(const efd::Char* pcStr = " ");

    /// Trim this string from the end of the string
    void TrimRight(const efd::Char* pcStr = " ");

    /// Trim this string from the beginning of the string
    void TrimSetLeft(const efd::Char* pcDelimiters = " ");

    /// Trim this string from the end of the string
    void TrimSetRight(const efd::Char* pcDelimiters = " ");

    /// Reverse the string
    void Reverse();

    /// Convert the string to uppercase internally. This function operates only english letters.
    void ToUpper();

    /// Convert the string to lowercase internally. This function operates only english letters.
    void ToLower();

    /// Format the string buffer as a standard sprintf do
    size_t Format(const efd::Char* pcFormat, ...);

    /// Format the string buffer as a standard vsprintf do
    size_t Vformat(const efd::Char* pcFormat, va_list argList);
    //@}

    /** @name Utf8 methods
     *  These methods are designed to safely work with utf8 strings at \b symbol level. Usually
     *  they are slower than regular \b byte level methods.
    */
    //@{
    /// Returns number of utf8 chars in the string
    size_t GetLengthUtf8();
    /// Returns byte position of symbol with given index. Returns npos in case of error.
    size_t ConvertUtf8Pos(size_t stSymIdx) const;

    /// Returns length of character, pointed by pcStr
    size_t GetCharLengthUtf8(const efd::Char* pcStr) const;

    /// Returns length of character at given position. Position is Utf8 symbol offset in string.
    size_t GetCharLengthUtf8(size_t stBytePos) const;

    /// Returns the character at a given symbol position.
    efd::utf8char_t GetAtUtf8(size_t stPos) const;

    /// Sets a character at a given position
    void SetAtUtf8(size_t stPos, efd::utf8char_t uc);
    //@}

    /** @name Conversion to/from other types
        Try to extract basic types from string or converts given types to string representation.
        @note These methods are deprecated.  Use ParseHelper::ToString/FromString instead.
    */
    //@{
    /// Convert the string into a boolean. True if successful, false if not.
    efd::Bool ToBool(efd::Bool& b) const;
    /// Convert the string into a efd::Float32. True if successful, false if not.
    efd::Bool ToFloat32(efd::Float32& f) const;
    /// Convert the string into a efd::Float64. True if successful, false if not.
    efd::Bool ToFloat64(efd::Float64& f) const;
    ///// Convert the string into a 64-bit integer. True if successful, false if not.
    //efd::Bool ToInt64(efd::SInt64 & i);
    /// Convert the string into a 32-bit integer. True if successful, false if not.
    efd::Bool ToInt32(efd::SInt32& i) const;
    /// Convert the string into a 16-bit integer. True if successful, false if not.
    efd::Bool ToInt16(efd::SInt16& i) const;
    /// Convert the string into a 8-bit integer. True if successful, false if not.
    efd::Bool ToInt8(efd::SInt8& i) const;
    /// Convert the string into a Point2. True if successful, false if not.
    efd::Bool ToPoint2(Point2& kPoint);
    /// Convert the string into a Point3. True if successful, false if not.
    efd::Bool ToPoint3(Point3& kPoint);
    ///// Convert the string into a Point4. True if successful, false if not.
    //efd::Bool ToPoint4(Point4& kPoint);
    /// Convert the string into an Color. True if successful, false if not.
    efd::Bool ToRGB(Color& kColor);
    /// Convert the string into an ColorA. True if successful, false if not.
    efd::Bool ToRGBA(ColorA& kColor);

    /// Returns String representation of a boolean.
    static String FromBool(efd::Bool b);
    /// Returns String representation of a 64-bit float.
    static String FromFloat64(efd::Float64 f);
    /// Returns String representation of a 32-bit float.
    static String FromFloat32(efd::Float32 f);
    ///// Returns String representation of a 64-bit integer.
    //static String FromInt64(efd::SInt64 i);
    /// Returns String representation of a 32-bit integer.
    static String FromInt32(efd::SInt32 i);
    /// Returns String representation of a 16-bit integer.
    static String FromInt16(efd::SInt16 i);
    /// Returns String representation of a 8-bit integer.
    static String FromInt8(efd::SInt8 i);
    /// Returns the String representation of a point.
    static String FromPoint2(Point2& kPt);
    /// Returns the String representation of a point.
    static String FromPoint3(Point3& kPt);
    ///// Returns the String representation of a point.
    //static String FromPoint4(Point4& kPt);
    // Returns the String representation of a color.
    static String FromRGB(Color& kColor);
    // Returns the String representation of a color.
    static String FromRGBA(ColorA& kColor);
    //@}

    /** @name Operators
     *  All forms of assignment and addition operators. Any operator can be used with utf8.
    */
    //@{
    /// Returns const pointer to string
    operator const efd::Char*() const;

    /// Ref-counted copy from another String
    inline String& operator=(const String& kStr);

    /// Copy string content from string
    inline String& operator=(const efd::Char* pcStr);

    /// Set string content to single character
    inline String& operator=(efd::Char ch);

    /// Concatenate from another String
    inline String& operator+=(const String& kStr);

    /// Concatenate from string
    inline String& operator+=(const efd::Char* pcStr);

    /// Concatenate with a single character
    inline String& operator+=(efd::Char ch);

    /// Create a new string that is the composite of String 1 and String 2
    inline friend String operator+(const String& kStr1, const String& kStr2);

    /// Create a new string that is the composite of String and efd::Char*
    inline friend String operator+(const String& kStr1, const efd::Char* pcStr2);

    /// Create a new string that is the composite of efd::Char* and String
    inline friend String operator+(const efd::Char* pcStr1, const String& kStr2);

    /// Create a new string that is the composite of String and a character
    inline friend String operator+(const String& kStr1, efd::Char ch2);

    /// Create a new string that is the composite of a character and String
    inline friend String operator+(efd::Char ch1, const String& kStr2);
    //@}

    /** @name utf8string compatibility
     *  These methods are wrappers to String methods. They are designed for easier migration
     *  from utf8string to String and define interface, similar to std::string.
    */
    //@{
    /// Returns pointer to a string string.
    inline const efd::Char* c_str() const;

    /// Returns pointer to internal data.
    inline const efd::Char* data() const;

    /// Return length of string. Similar to GetLength().
    inline size_t size() const;

    /// Return length of string.
    inline size_t length() const;

    /// Returns true if the string is empty. Similar to IsEmpty().
    inline efd::Bool empty() const;

    /// Clears string and sets length to zero
    inline void clear();

    /// Convert string to upper case
    inline void toupper();

    /// Convert string to lower case
    inline void tolower();

    /// Checks, if the string is valid
    inline efd::Bool is_valid() const;

    /// Get substring
    inline String substr(size_t stBegin = 0, size_t stCount = npos) const;

    /// Compare this string against provided
    inline int compare(const String& pcStr) const;

    /// Compare this string against provided
    inline int compare(const efd::Char* pcStr) const;

    /// Compare this string against provided, ignoring case
    inline int icompare(const String& kStr) const;

    /// Compare this string against provided, ignoring case
    inline int icompare(const efd::Char* pcStr) const;

    /// Insert provided string at given position
    inline void insert(size_t stPos, const efd::Char* pcStr);

    /// Insert first n characters from provided string at given position
    inline void insert(size_t pos, const efd::Char* pcInsertString, size_t stCount);

    /// Add a character to the end of string
    inline void push_back(efd::Char uc);

    /// Append string to the end
    inline String& append(const efd::Char* pcStr);
    /// Append char to the end
    inline String& append(efd::Char ch);
    /// Append string to the end, starting at stPos and no more chars than stCount
    inline String& append(const efd::Char* pcStr, size_t stPos, size_t stCount = npos);
    /// Insert char, repeated stCount times
    inline String& append(size_t stCount, efd::Char ch);

    /// Search for psStr from stBegin position
    inline size_t find(const efd::Char* pcStr, size_t stBegin = 0) const;
    /// Search for psStr from stBegin position
    inline size_t find(efd::Char ch, size_t stBegin = 0) const;
    /// Search for psStr backward from stBegin position
    inline size_t rfind(const efd::Char* pcStr, size_t stBegin = npos) const;
    /// Search for psStr backward from stBegin position
    inline size_t rfind(efd::Char ch, size_t stBegin = npos) const;
    /// Find first occurrence of any pcStr character from stBegin position
    inline size_t find_first_of(const efd::Char* pcDelimiters, size_t stBegin = 0) const;
    /// Find first occurrence of cDelimiter character from stBegin position
    inline size_t find_first_of(efd::Char cDelimiter, size_t stBegin = 0) const;
    /// Find first occurrence of any pcStr character from stBegin position searching backwards
    inline size_t find_last_of(const efd::Char* pcDelimiters, size_t stBegin = npos) const;
    /// Find first occurrence of cDelimiter character from stBegin position searching backwards
    inline size_t find_last_of(efd::Char cDelimiter, size_t stBegin = npos) const;

    /// Remove characters from begin / end of a string
    inline void trim(_Trim t = TrimAll, const efd::Char* set = " \t\r\n");

    /// Replace all occurrences of a substring with another string.
    inline size_t replace_substr(const efd::Char* pcFindStr, const efd::Char* pcReplaceStr);

    /// Split a string into multiple sub-strings by matching against a set of delimiters.
    size_t split(const efd::Char* pcDelimiters, efd::vector<String>& kResults) const;

    /// Format the string buffer as a standard sprintf do
    size_t sprintf(const efd::Char* pcFormat, ...);
    /// Format the string buffer as a standard vsprintf do
    size_t vsprintf(const efd::Char* pcFormat, va_list argList);
    /// Format the string buffer as a standard sprintf do and append the result
    size_t sprintf_append(const efd::Char* pcFormat, ...);
    /// Format the string buffer as a standard vsprintf do and append the result
    size_t vsprintf_append(const efd::Char* pcFormat, va_list argList);


    /// utf8string compatibility typedef
    typedef size_t size_type;

    /// Returns string, containing one of each whitespace character
    static const String& WhiteSpace();
    /// Returns an empty string
    static const String& NullString();
    //@}

protected:
    /// Internal structure defining the header data for a string
    struct StringHeader
    {
        size_t m_cbBufferSize;
        size_t m_RefCount;
        size_t m_cchStringLength;
    };
    /// Internal structure defining the body, used for providing type information.  The actually
    /// buffer allocated is larger than StringBody making it safe to read beyond the one character
    /// defined in this class.
    struct StringBody
    {
        // This could be a zero length array, but that causes issues for some compilers.  Also
        // we want to guarantee room for a terminating NULL character anyway so this avoids the
        // need to add one all over the place.
        efd::Char m_data[1];
    };
    /// The internal storage for the string
    struct StringData : public StringHeader, public StringBody
    {
    };

    /// A string's only member variable is a pointer directly to the Body of a StringData
    StringBody* m_kHandle;

    // support function similar to NiString
    efd::Char* Strtok(efd::Char* pcStr, const efd::Char* pcDelimit, efd::Char** ppcContext);

    /** @name Handles methods (internal): allocation / deallocation, reference counting
    */
    //@{
    static StringBody* Allocate(size_t stCount);
    static StringBody* AllocateAndCopy(const efd::Char* pcStr, size_t stCount = 0);
    static StringBody* AllocateAndCopyHandle(StringBody* kHandle);
    static void Deallocate(StringBody*& io_pBody);

    static void IncRefCount(StringBody* pBody, efd::Bool bValidate = true);
    static void DecRefCount(StringBody*& io_pBody, efd::Bool bValidate = true);
    static size_t GetRefCount(StringBody* pBody, efd::Bool bValidate = true);

    static void Swap(StringBody*& io_pBody, const efd::Char* pcNewValue,
        size_t stLength = 0, efd::Bool bValidate = true);

    static efd::Char* GetString(StringBody* pBody, efd::Bool bValidate = true);
    static size_t GetLength(StringBody* pBody, efd::Bool bValidate = true);
    static size_t GetAllocationSize(StringBody* pBody, efd::Bool bValidate = true);
    static size_t GetBufferSize(StringBody* pBody, efd::Bool bValidate = true);
    static void SetLength(StringBody* pBody, size_t stLength);
    static StringHeader* GetRealBufferStart(StringBody* pBody);
    static efd::Bool ValidateString(StringBody* pBody);
    static size_t GetBestBufferSize(size_t stSize);

    efd::Bool Resize(size_t stDelta);
    void SetBuffer(StringBody* pBody);

    void CalcLength();

    // Called before any operation that changes the string buffer. If this string is the only one
    // holding on to the buffer, a copy is not made. Otherwise, a copy is made.
    void CopyOnWrite(efd::Bool bForceCopy = false);
    void CopyOnWriteAndResize(size_t stSizeDelta, efd::Bool bForceCopy = false);
    //@}

    // Internal implementation of vsprintf
    StringBody* vformat(const char *pcFormat, va_list argPtr);
};


// Do these two strings exactly match?
inline efd::Bool EE_EFD_ENTRY operator==(const String& kStr1, const String& kStr2);
inline efd::Bool EE_EFD_ENTRY operator==(const String& kStr1, const efd::Char* pcStr2);
inline efd::Bool EE_EFD_ENTRY operator==(const efd::Char* pcStr1, const String& kStr2);

// Do these two strings not match?
inline efd::Bool EE_EFD_ENTRY operator!=(const String& kStr1, const String& kStr2);
inline efd::Bool EE_EFD_ENTRY operator!=(const String& kStr1, const efd::Char* pcStr2);
inline efd::Bool EE_EFD_ENTRY operator!=(const efd::Char* pcStr1, const String& kStr2);

// Is Str1 less than Str2?
inline efd::Bool EE_EFD_ENTRY operator<(const String& kStr1, const String& kStr2);
inline efd::Bool EE_EFD_ENTRY operator<(const String& kStr1, const efd::Char* pcStr2);
inline efd::Bool EE_EFD_ENTRY operator<(const efd::Char* pcStr1, const String& kStr2);

// Is Str1 greater than Str2?
inline efd::Bool EE_EFD_ENTRY operator>(const String& kStr1, const String& kStr2);
inline efd::Bool EE_EFD_ENTRY operator>(const String& kStr1, const efd::Char* pcStr2);
inline efd::Bool EE_EFD_ENTRY operator>(const efd::Char* pcStr1, const String& kStr2);

// Is s1 less than or equal to s2?
inline efd::Bool EE_EFD_ENTRY operator<=(const String& kStr1, const String& kStr2);
inline efd::Bool EE_EFD_ENTRY operator<=(const String& kStr1, const efd::Char* pcStr2);
inline efd::Bool EE_EFD_ENTRY operator<=(const efd::Char* pcStr1, const String& kStr2);

// Is s1 greater than or equal to s2?
inline efd::Bool EE_EFD_ENTRY operator>=(const String& kStr1, const String& kStr2);
inline efd::Bool EE_EFD_ENTRY operator>=(const String& kStr1, const efd::Char* pcStr2);
inline efd::Bool EE_EFD_ENTRY operator>=(const efd::Char* pcStr1, const String& kStr2);

} // end namespace efd

/// @endcond

// Include inlines
#include <efd/String.inl>

#endif  // EE_STRING_H
