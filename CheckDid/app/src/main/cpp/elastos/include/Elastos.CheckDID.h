#ifndef __CAR_ELASTOS_CHECKDID_H__
#define __CAR_ELASTOS_CHECKDID_H__

#ifndef _NO_INCLIST
#include "elastos.h"
using namespace Elastos;
#include "Elastos.CoreLibrary.h"

#endif // !_NO_INCLIST

#ifndef __UUNM_Elastos_CheckDID_DEFINED__
#define __UUNM_Elastos_CheckDID_DEFINED__
#define c_pElastos_CheckDIDUunm "libElastos.CheckDID.so"
#endif // __UUNM_Elastos_CheckDID_DEFINED__

#ifndef __ECLSID_CCheckDID_DEFINED__
#define __ECLSID_CCheckDID_DEFINED__
static const _ELASTOS ClassID ECLSID_CCheckDID = {
    {0xA17C1A3F,0x9E4C,0x1206,{0x1A,0xFC,0x68,0x6F,0xE3,0x86,0x0C,0x1B}},
    (char *)c_pElastos_CheckDIDUunm,
    0xa1e9736b };
#endif // __CLSID_CCheckDID_DEFINED__

#ifndef __ECLSID_CCheckDIDClassObject_DEFINED__
#define __ECLSID_CCheckDIDClassObject_DEFINED__
static const _ELASTOS ClassID ECLSID_CCheckDIDClassObject = {
    {0x1EAE2538,0x9E4C,0x1206,{0x1A,0xE8,0x31,0xFA,0xA3,0xBD,0x8D,0x1B}},
    (char *)c_pElastos_CheckDIDUunm,
    0xa1e9736b };
#endif // __CLSID_CCheckDIDClassObject_DEFINED__

#ifndef __EIID_ICheckDID_DEFINED__
#define __EIID_ICheckDID_DEFINED__
static const _ELASTOS InterfaceID EIID_ICheckDID = \
    {0xC7892F1B,0xB312,0xA6A2,{0xDB,0x48,0xCD,0x9F,0xE1,0xE5,0xCB,0x9A}};
#endif // __IID_ICheckDID_DEFINED__

#ifndef __EIID_ICCheckDIDClassObject_DEFINED__
#define __EIID_ICCheckDIDClassObject_DEFINED__
static const _ELASTOS InterfaceID EIID_ICCheckDIDClassObject = \
    {0x8DA75625,0x8312,0x0D3C,{0x24,0x34,0xD0,0x63,0xF4,0x87,0x25,0xA3}};
#endif // __IID_ICCheckDIDClassObject_DEFINED__

interface ICheckDID;
interface ICCheckDIDClassObject;





#ifdef __ELASTOS_CHECKDID_USER_TYPE_H__
#include "Elastos.CheckDID_user_type.h"
#endif
ELAPI _Impl_AcquireCallbackHandler(PInterface pServerObj, _ELASTOS REIID iid, PInterface *ppHandler);
ELAPI _Impl_CheckClsId(PInterface pServerObj, const _ELASTOS ClassID* pClassid, PInterface *ppServerObj);

CAR_INTERFACE("C7892F1B-B312-A6A2-DB48-CD9FE1E5CB9A")
ICheckDID : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
        /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICheckDID*) Probe(PInterface pObj)
    {
        if (pObj == NULL) return NULL;
        return (ICheckDID*)pObj->Probe(EIID_ICheckDID);
    }

    static CARAPI_(ICheckDID*) Probe(IObject* pObj)
    {
        if (pObj == NULL) return NULL;
        return (ICheckDID*)pObj->Probe(EIID_ICheckDID);
    }

    static CARAPI_(ICheckDID*) QueryInterface(const Elastos::String& uid)
    {
        return NULL;
    }

    virtual CARAPI PublicKeyToIdAddress(
        /* [in] */ const _ELASTOS String& publicKey,
        /* [out] */ _ELASTOS String * idAddress) = 0;

    virtual CARAPI VerifyByPublicKey(
        /* [in] */ const _ELASTOS String& publicKey,
        /* [in] */ const _ELASTOS String& message,
        /* [in] */ const _ELASTOS String& signature,
        /* [out] */ _ELASTOS Boolean * result) = 0;

};
CAR_INTERFACE("8DA75625-8312-0D3C-2434-D063F48725A3")
ICCheckDIDClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
        /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICCheckDIDClassObject*) Probe(PInterface pObj)
    {
        if (pObj == NULL) return NULL;
        return (ICCheckDIDClassObject*)pObj->Probe(EIID_ICCheckDIDClassObject);
    }

    static CARAPI_(ICCheckDIDClassObject*) Probe(IObject* pObj)
    {
        if (pObj == NULL) return NULL;
        return (ICCheckDIDClassObject*)pObj->Probe(EIID_ICCheckDIDClassObject);
    }

    static CARAPI_(ICCheckDIDClassObject*) QueryInterface(const Elastos::String& uid)
    {
        return NULL;
    }

    virtual CARAPI CreateObjectWithDefaultCtor(
        /* [out] */ IInterface ** newObj) = 0;

};
#ifndef _INSIDE_ELASTOS_CHECKDID_
class CCheckDID
{
public:
    static _ELASTOS ECode New(
        /* [out] */ ICheckDID** __object)
    {
        return _CObject_CreateInstance(ECLSID_CCheckDID, RGM_SAME_DOMAIN, EIID_ICheckDID, (PInterface*)__object);
    }

    static _ELASTOS ECode New(
        /* [out] */ IObject** __object)
    {
        return _CObject_CreateInstance(ECLSID_CCheckDID, RGM_SAME_DOMAIN, EIID_IObject, (PInterface*)__object);
    }

    static _ELASTOS ECode New(
        /* [out] */ Elastos::Core::ISynchronize** __object)
    {
        return _CObject_CreateInstance(ECLSID_CCheckDID, RGM_SAME_DOMAIN, Elastos::Core::EIID_ISynchronize, (PInterface*)__object);
    }

    static _ELASTOS ECode New(
        /* [out] */ IWeakReferenceSource** __object)
    {
        return _CObject_CreateInstance(ECLSID_CCheckDID, RGM_SAME_DOMAIN, EIID_IWeakReferenceSource, (PInterface*)__object);
    }

};
#endif // _INSIDE_ELASTOS_CHECKDID_


#endif // __CAR_ELASTOS_CHECKDID_H__
