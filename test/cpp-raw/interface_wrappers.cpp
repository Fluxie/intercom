
#include <functional>

#include "os.h"
#include "catch.hpp"

#include "testlib.h"

 #ifdef __GNUC__

TEST_CASE( "Using interface wrappers works" )
{
    // Initialize COM.
	InitializeRuntime();

    intercom::ClassFactory< test_lib::raw::RefCountOperationsDescriptor > refCountFactory;
    intercom::RawInterface<IRefCountOperations> refCountOps;
    HRESULT created = refCountFactory.create( IRefCountOperations::ID, refCountOps.out() );
    REQUIRE( S_OK == created );
    REQUIRE( static_cast< bool >( refCountOps ) );
    REQUIRE( refCountOps->GetRefCount() == 1 );

    SECTION( "Acquiring another reference succeeds." )
    {
        intercom::RawInterface<IRefCountOperations> refCountOpsDuplicate = refCountOps;
        REQUIRE( static_cast< bool >( refCountOpsDuplicate ) );
        REQUIRE( refCountOps.get() == refCountOpsDuplicate.get() );

        // There should be another reference now.
        REQUIRE( refCountOpsDuplicate->GetRefCount() == 2 );
    }

    SECTION( "Moving a reference to another variable succeeds." )
    {
        intercom::RawInterface<IRefCountOperations> refCountOpsMoved = std::move( refCountOps );
        REQUIRE( static_cast< bool >( refCountOpsMoved ) );
        REQUIRE( static_cast< bool >( refCountOps ) == false );
        REQUIRE( refCountOpsMoved->GetRefCount() == 1 );
    }

    SECTION( "Releasing a variable succeeds." )
    {
        IRefCountOperations* released = refCountOps.release();
        REQUIRE( static_cast< bool >( refCountOps ) == false );
        REQUIRE( released->GetRefCount() == 1 );
    }

    SECTION( "Reseting a variable to nullptr succeeds." )
    {
        refCountOps.reset();
        REQUIRE( static_cast< bool >( refCountOps ) == false );
    }

    SECTION( "Reseting a variable to another variable succeeds." )
    {
        intercom::RawInterface<IRefCountOperations> anotherCounter =
                std::move( refCountFactory.create< test_lib::raw::IRefCountOperations >() );
        REQUIRE( anotherCounter->GetRefCount() == 1 );
        REQUIRE( refCountOps.get() != anotherCounter.get() );
        refCountOps.reset( anotherCounter.get() );
        REQUIRE( static_cast< bool >( refCountOps ) );
        REQUIRE( anotherCounter.get() == refCountOps.get() );
        REQUIRE( anotherCounter->GetRefCount() == 2 );
    }

    SECTION( "Calculating hash code succeeds." )
    {
        size_t expectedHash = std::hash< IRefCountOperations* >{}( refCountOps.get() );
        REQUIRE( expectedHash == std::hash< intercom::RawInterface<IRefCountOperations>  >{}(
                 refCountOps ) );
    }

    SECTION( "Swapping variables succeeds." )
    {
        intercom::RawInterface<IRefCountOperations> anotherCounter =
                std::move( refCountFactory.create< test_lib::raw::IRefCountOperations >() );

        // Determine expected values after the swap operation.
        IRefCountOperations* expectedAnother = refCountOps.get();
        IRefCountOperations* expectedRefCount = anotherCounter.get();

        // Verify the swap succeeds.
        std::swap( refCountOps, anotherCounter );
        REQUIRE( expectedAnother == anotherCounter.get() );
        REQUIRE( expectedRefCount == refCountOps.get() );
        REQUIRE( anotherCounter->GetRefCount() == 1 );
        REQUIRE( refCountOps->GetRefCount() == 1 );
    }

	UninitializeRuntime();
}

#endif