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
// efd::vector functions
//--------------------------------------------------------------------------------------------------
template< class _data >
typename vector< _data >::iterator vector< _data >::find(const _data& i_data)
{
    return EE_STL_NAMESPACE::find(vector< _data >::begin(), vector< _data >::end(), i_data);
}

//--------------------------------------------------------------------------------------------------
template< class _data >
typename vector< _data >::const_iterator vector< _data >::find(const _data& i_data) const
{
    return EE_STL_NAMESPACE::find<const_iterator>(
        vector< _data >::begin(), vector< _data >::end(), i_data);
}

//--------------------------------------------------------------------------------------------------
template< class _data >
inline void vector< _data >::static_shutdown()
{
    // ~vector()
    _STLP_STD::_Destroy_Range(this->rbegin(), this->rend());

    // ~vector_base()
    if (this->_M_start != NULL)
    {
        this->_M_end_of_storage.deallocate(
            this->_M_start,
            this->_M_end_of_storage._M_data - this->_M_start);
    }

    // vector_base()
    this->_M_start = NULL;
    this->_M_finish = NULL;
    this->_M_end_of_storage._M_data = NULL;
}

//--------------------------------------------------------------------------------------------------
// efd::list functions
//--------------------------------------------------------------------------------------------------
template< class _data >
bool list< _data >::pop_front(_data& o_data)
{
    if (!list< _data >::empty())
    {
        o_data = list< _data >::front();
        list< _data >::pop_front();
        return true;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
template< class _data >
typename list< _data >::iterator list< _data >::find(const _data& i_data)
{
    return EE_STL_NAMESPACE::find(list< _data >::begin(), list< _data >::end(), i_data);
}

//--------------------------------------------------------------------------------------------------
template< class _data >
typename list< _data >::const_iterator list< _data >::find(const _data& i_data) const
{
    return EE_STL_NAMESPACE::find<const_iterator>(
        list< _data >::begin(), list< _data >::end(), i_data);
}


//--------------------------------------------------------------------------------------------------
// efd::map functions
//--------------------------------------------------------------------------------------------------
template< class _key, class _data, class _compare >
bool map< _key, _data, _compare >::find(const _key& i_key, _data& o_data) const
{
    const_iterator iter = find(i_key);
    if (map< _key, _data, _compare >::end() != iter)
    {
        o_data = iter->second;
        return true;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
// efd::hash_map functions
//--------------------------------------------------------------------------------------------------

template<class _key, class _data, class _HashFcn, class _EqualKey>
bool hash_map<_key, _data, _HashFcn, _EqualKey>::find(const _key& i_key, _data& o_data) const
{
    const_iterator iter = find(i_key);
    if (iter != this->end())
    {
        o_data = iter->second;
        return true;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
} // end namespace efd
