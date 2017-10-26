

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 05:14:07 2038
 */
/* Compiler settings for ..\..\src\calculator.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __calculator_h_h__
#define __calculator_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICalculator_FWD_DEFINED__
#define __ICalculator_FWD_DEFINED__
typedef interface ICalculator ICalculator;

#endif 	/* __ICalculator_FWD_DEFINED__ */


#ifndef __IMemory_FWD_DEFINED__
#define __IMemory_FWD_DEFINED__
typedef interface IMemory IMemory;

#endif 	/* __IMemory_FWD_DEFINED__ */


#ifndef __ICloneable_FWD_DEFINED__
#define __ICloneable_FWD_DEFINED__
typedef interface ICloneable ICloneable;

#endif 	/* __ICloneable_FWD_DEFINED__ */


#ifndef __Calculator_FWD_DEFINED__
#define __Calculator_FWD_DEFINED__

#ifdef __cplusplus
typedef class Calculator Calculator;
#else
typedef struct Calculator Calculator;
#endif /* __cplusplus */

#endif 	/* __Calculator_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Calculator_LIBRARY_DEFINED__
#define __Calculator_LIBRARY_DEFINED__

/* library Calculator */
/* [version][lcid][helpstring][uuid] */ 


EXTERN_C const IID LIBID_Calculator;

#ifndef __ICalculator_INTERFACE_DEFINED__
#define __ICalculator_INTERFACE_DEFINED__

/* interface ICalculator */
/* [unique][helpstring][nonextensible][uuid][object] */ 


EXTERN_C const IID IID_ICalculator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12341234-1234-1234-1234-123412340002")
    ICalculator : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ int value,
            /* [retval][out] */ int *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Substract( 
            /* [in] */ int value,
            /* [retval][out] */ int *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Multiply( 
            /* [in] */ int value,
            /* [retval][out] */ int *result) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICalculatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICalculator * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICalculator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICalculator * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ICalculator * This,
            /* [in] */ int value,
            /* [retval][out] */ int *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Substract )( 
            ICalculator * This,
            /* [in] */ int value,
            /* [retval][out] */ int *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Multiply )( 
            ICalculator * This,
            /* [in] */ int value,
            /* [retval][out] */ int *result);
        
        END_INTERFACE
    } ICalculatorVtbl;

    interface ICalculator
    {
        CONST_VTBL struct ICalculatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICalculator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICalculator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICalculator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICalculator_Add(This,value,result)	\
    ( (This)->lpVtbl -> Add(This,value,result) ) 

#define ICalculator_Substract(This,value,result)	\
    ( (This)->lpVtbl -> Substract(This,value,result) ) 

#define ICalculator_Multiply(This,value,result)	\
    ( (This)->lpVtbl -> Multiply(This,value,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICalculator_INTERFACE_DEFINED__ */


#ifndef __IMemory_INTERFACE_DEFINED__
#define __IMemory_INTERFACE_DEFINED__

/* interface IMemory */
/* [unique][helpstring][nonextensible][uuid][object] */ 


EXTERN_C const IID IID_IMemory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12341234-1234-1234-1234-123412340003")
    IMemory : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Store( 
            /* [retval][out] */ SIZE_T *slot) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Recall( 
            /* [in] */ SIZE_T value) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMemoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMemory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMemory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMemory * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Store )( 
            IMemory * This,
            /* [retval][out] */ SIZE_T *slot);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Recall )( 
            IMemory * This,
            /* [in] */ SIZE_T value);
        
        END_INTERFACE
    } IMemoryVtbl;

    interface IMemory
    {
        CONST_VTBL struct IMemoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMemory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMemory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMemory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMemory_Store(This,slot)	\
    ( (This)->lpVtbl -> Store(This,slot) ) 

#define IMemory_Recall(This,value)	\
    ( (This)->lpVtbl -> Recall(This,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMemory_INTERFACE_DEFINED__ */


#ifndef __ICloneable_INTERFACE_DEFINED__
#define __ICloneable_INTERFACE_DEFINED__

/* interface ICloneable */
/* [unique][helpstring][nonextensible][uuid][object] */ 


EXTERN_C const IID IID_ICloneable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12341234-1234-1234-1234-123412340004")
    ICloneable : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ICalculator **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICloneableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICloneable * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICloneable * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICloneable * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ICloneable * This,
            /* [retval][out] */ ICalculator **clone);
        
        END_INTERFACE
    } ICloneableVtbl;

    interface ICloneable
    {
        CONST_VTBL struct ICloneableVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICloneable_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICloneable_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICloneable_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICloneable_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICloneable_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Calculator;

#ifdef __cplusplus

class DECLSPEC_UUID("12341234-1234-1234-1234-123412340001")
Calculator;
#endif
#endif /* __Calculator_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


