#include "eagersingleton.h"
#include "common.h"

EagerSingletonRef EagerSingletonRef::m_instance;

EagerSingletonRef::EagerSingletonRef()
{
    PRINT_FUNC_NAME;
}

EagerSingletonRef& EagerSingletonRef::instance()
{
    TEST_MSG(" EagerSingletonRef address : ", &m_instance);
    return m_instance;
}


/////////////////////////////////////////////
/// \brief EagerSingletonRef::EagerSingletonRef
///

EagerSingletonPtr EagerSingletonPtr::m_instance;

EagerSingletonPtr::EagerSingletonPtr()
{
    PRINT_FUNC_NAME;
}

EagerSingletonPtr* EagerSingletonPtr::instance()
{
    TEST_MSG(" EagerSingletonPtr address : ", &m_instance);
    return &m_instance;
}

