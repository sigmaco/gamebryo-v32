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
#ifndef EE_GENERICFACTORY_H
#define EE_GENERICFACTORY_H

#include <efd/SmartPointer.h>
#include <efd/StdContainers.h>
#include <efd/MemObject.h>

namespace efd
{

/**
    A generic templated factory class.  T represents the type of object to be
    returned from CreateObject().
*/
template<typename T, typename KEY = ClassID>
class GenericFactory : public MemObject
{

public:
    /// @name Construction and Destruction
    //@{
    /// Virtual destructor
    virtual ~GenericFactory(){}
    //@}

    // typedef for factory method this factory takes to register classes with
    typedef T (FactoryMethod)();

    /**
        Static method to automatically generate a factory method necessary to instantiate the
        concrete type. The concrete type is passed in as a template parameter to this method. The
        concrete type must be a MemObject and must have a no-argument constructor. The usage will
        typically be:

        typedef GenericFactory<IMyInterfaceType> MyFactory;
        MyFactory m_MyFactory;
        m_MyFactory.RegisterFactoryMethod(
            MyClassID,
            MyFactory::GenerateFactoryMethod<MyConcreteClass>);

        @return SmartPointer of the Interface type that points to an instance of the concrete type
    */
    template<typename TConcrete>
    static T GenerateFactoryMethod();

    /**
        Factory an object based on a classID specifying the concrete
        class to factory.

        @param classID The class ID used to identify the concrete class
        @return Smart Pointer of the Interface type pointing to the concrete
        type just created
    */
    virtual T CreateObject(KEY classID) const;

    /**
        Registers a new class with this factory.
        
        @note This method will overwrite any previous registration of a class sharing the same ID.

        @param classID The ClassID identifying the object that is factoried in the FactoryMethod
        @param pMethod A method used to create a new concrete object. GenerateFactoryMethod can
            normally be used to generate this function.
    */
    virtual void RegisterFactoryMethod(KEY classID, FactoryMethod* pMethod);

    /**
        Registers a new class with this factory. The class will be created using the
        GenericFactory::GenerateFactoryMethod as the FactoryMethod.
        
        @note This method will overwrite any previous registration of a class sharing the same ID.

        @param classID The ClassID identifying the object that is factoried in the FactoryMethod
    */
    template<typename TConcrete>
    void RegisterDefaultFactoryMethod(KEY classID);

    /**
        Unregisters a class from the factory.

        @param classID The class to unregister.
    */
    virtual void UnregisterFactoryMethod(KEY classID);


protected:

    //@{
    /// The internal map to hold the classID to function pointers
    typedef efd::map<KEY, FactoryMethod*> FactoryMap;
    FactoryMap m_factoryMap;
    //@}
};

}; //namespace efd

//--------------------------------------------------------------------------------------------------
#include <efd/GenericFactory.inl>

//--------------------------------------------------------------------------------------------------
#endif //EE_GENERICFACTORY_H
