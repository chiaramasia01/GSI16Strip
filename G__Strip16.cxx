// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__Strip16
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "./Strip16UnpackProc.h"
#include "./Strip16HardwareParameter.h"
#include "./Strip16UnpackFact.h"
#include "./Strip16AnlEvent.h"
#include "./Strip16AnlProc.h"
#include "./Strip16AnlFact.h"
#include "./Strip16UnpackParam.h"
#include "./Strip16UnpackEvent.h"
#include "./Strip16Analysis.h"
#include "./Strip16CalibParameter.h"
#include "./Strip16Globals.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_Strip16UnpackEvent(void *p = 0);
   static void *newArray_Strip16UnpackEvent(Long_t size, void *p);
   static void delete_Strip16UnpackEvent(void *p);
   static void deleteArray_Strip16UnpackEvent(void *p);
   static void destruct_Strip16UnpackEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Strip16UnpackEvent*)
   {
      ::Strip16UnpackEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Strip16UnpackEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Strip16UnpackEvent", ::Strip16UnpackEvent::Class_Version(), "Strip16UnpackEvent.h", 28,
                  typeid(::Strip16UnpackEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Strip16UnpackEvent::Dictionary, isa_proxy, 4,
                  sizeof(::Strip16UnpackEvent) );
      instance.SetNew(&new_Strip16UnpackEvent);
      instance.SetNewArray(&newArray_Strip16UnpackEvent);
      instance.SetDelete(&delete_Strip16UnpackEvent);
      instance.SetDeleteArray(&deleteArray_Strip16UnpackEvent);
      instance.SetDestructor(&destruct_Strip16UnpackEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Strip16UnpackEvent*)
   {
      return GenerateInitInstanceLocal((::Strip16UnpackEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Strip16UnpackEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Strip16UnpackProc(void *p = 0);
   static void *newArray_Strip16UnpackProc(Long_t size, void *p);
   static void delete_Strip16UnpackProc(void *p);
   static void deleteArray_Strip16UnpackProc(void *p);
   static void destruct_Strip16UnpackProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Strip16UnpackProc*)
   {
      ::Strip16UnpackProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Strip16UnpackProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Strip16UnpackProc", ::Strip16UnpackProc::Class_Version(), "Strip16UnpackProc.h", 79,
                  typeid(::Strip16UnpackProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Strip16UnpackProc::Dictionary, isa_proxy, 4,
                  sizeof(::Strip16UnpackProc) );
      instance.SetNew(&new_Strip16UnpackProc);
      instance.SetNewArray(&newArray_Strip16UnpackProc);
      instance.SetDelete(&delete_Strip16UnpackProc);
      instance.SetDeleteArray(&deleteArray_Strip16UnpackProc);
      instance.SetDestructor(&destruct_Strip16UnpackProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Strip16UnpackProc*)
   {
      return GenerateInitInstanceLocal((::Strip16UnpackProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Strip16UnpackProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Strip16HardwareParameter(void *p = 0);
   static void *newArray_Strip16HardwareParameter(Long_t size, void *p);
   static void delete_Strip16HardwareParameter(void *p);
   static void deleteArray_Strip16HardwareParameter(void *p);
   static void destruct_Strip16HardwareParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Strip16HardwareParameter*)
   {
      ::Strip16HardwareParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Strip16HardwareParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Strip16HardwareParameter", ::Strip16HardwareParameter::Class_Version(), "Strip16HardwareParameter.h", 11,
                  typeid(::Strip16HardwareParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Strip16HardwareParameter::Dictionary, isa_proxy, 4,
                  sizeof(::Strip16HardwareParameter) );
      instance.SetNew(&new_Strip16HardwareParameter);
      instance.SetNewArray(&newArray_Strip16HardwareParameter);
      instance.SetDelete(&delete_Strip16HardwareParameter);
      instance.SetDeleteArray(&deleteArray_Strip16HardwareParameter);
      instance.SetDestructor(&destruct_Strip16HardwareParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Strip16HardwareParameter*)
   {
      return GenerateInitInstanceLocal((::Strip16HardwareParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Strip16HardwareParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Strip16UnpackFact(void *p = 0);
   static void *newArray_Strip16UnpackFact(Long_t size, void *p);
   static void delete_Strip16UnpackFact(void *p);
   static void deleteArray_Strip16UnpackFact(void *p);
   static void destruct_Strip16UnpackFact(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Strip16UnpackFact*)
   {
      ::Strip16UnpackFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Strip16UnpackFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Strip16UnpackFact", ::Strip16UnpackFact::Class_Version(), "Strip16UnpackFact.h", 15,
                  typeid(::Strip16UnpackFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Strip16UnpackFact::Dictionary, isa_proxy, 4,
                  sizeof(::Strip16UnpackFact) );
      instance.SetNew(&new_Strip16UnpackFact);
      instance.SetNewArray(&newArray_Strip16UnpackFact);
      instance.SetDelete(&delete_Strip16UnpackFact);
      instance.SetDeleteArray(&deleteArray_Strip16UnpackFact);
      instance.SetDestructor(&destruct_Strip16UnpackFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Strip16UnpackFact*)
   {
      return GenerateInitInstanceLocal((::Strip16UnpackFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Strip16UnpackFact*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Strip16CalibParameter(void *p = 0);
   static void *newArray_Strip16CalibParameter(Long_t size, void *p);
   static void delete_Strip16CalibParameter(void *p);
   static void deleteArray_Strip16CalibParameter(void *p);
   static void destruct_Strip16CalibParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Strip16CalibParameter*)
   {
      ::Strip16CalibParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Strip16CalibParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Strip16CalibParameter", ::Strip16CalibParameter::Class_Version(), "Strip16CalibParameter.h", 7,
                  typeid(::Strip16CalibParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Strip16CalibParameter::Dictionary, isa_proxy, 4,
                  sizeof(::Strip16CalibParameter) );
      instance.SetNew(&new_Strip16CalibParameter);
      instance.SetNewArray(&newArray_Strip16CalibParameter);
      instance.SetDelete(&delete_Strip16CalibParameter);
      instance.SetDeleteArray(&deleteArray_Strip16CalibParameter);
      instance.SetDestructor(&destruct_Strip16CalibParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Strip16CalibParameter*)
   {
      return GenerateInitInstanceLocal((::Strip16CalibParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Strip16CalibParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Strip16AnlProc(void *p = 0);
   static void *newArray_Strip16AnlProc(Long_t size, void *p);
   static void delete_Strip16AnlProc(void *p);
   static void deleteArray_Strip16AnlProc(void *p);
   static void destruct_Strip16AnlProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Strip16AnlProc*)
   {
      ::Strip16AnlProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Strip16AnlProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Strip16AnlProc", ::Strip16AnlProc::Class_Version(), "Strip16AnlProc.h", 32,
                  typeid(::Strip16AnlProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Strip16AnlProc::Dictionary, isa_proxy, 4,
                  sizeof(::Strip16AnlProc) );
      instance.SetNew(&new_Strip16AnlProc);
      instance.SetNewArray(&newArray_Strip16AnlProc);
      instance.SetDelete(&delete_Strip16AnlProc);
      instance.SetDeleteArray(&deleteArray_Strip16AnlProc);
      instance.SetDestructor(&destruct_Strip16AnlProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Strip16AnlProc*)
   {
      return GenerateInitInstanceLocal((::Strip16AnlProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Strip16AnlProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Strip16AnlEvent(void *p = 0);
   static void *newArray_Strip16AnlEvent(Long_t size, void *p);
   static void delete_Strip16AnlEvent(void *p);
   static void deleteArray_Strip16AnlEvent(void *p);
   static void destruct_Strip16AnlEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Strip16AnlEvent*)
   {
      ::Strip16AnlEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Strip16AnlEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Strip16AnlEvent", ::Strip16AnlEvent::Class_Version(), "Strip16AnlEvent.h", 12,
                  typeid(::Strip16AnlEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Strip16AnlEvent::Dictionary, isa_proxy, 4,
                  sizeof(::Strip16AnlEvent) );
      instance.SetNew(&new_Strip16AnlEvent);
      instance.SetNewArray(&newArray_Strip16AnlEvent);
      instance.SetDelete(&delete_Strip16AnlEvent);
      instance.SetDeleteArray(&deleteArray_Strip16AnlEvent);
      instance.SetDestructor(&destruct_Strip16AnlEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Strip16AnlEvent*)
   {
      return GenerateInitInstanceLocal((::Strip16AnlEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Strip16AnlEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Strip16AnlFact(void *p = 0);
   static void *newArray_Strip16AnlFact(Long_t size, void *p);
   static void delete_Strip16AnlFact(void *p);
   static void deleteArray_Strip16AnlFact(void *p);
   static void destruct_Strip16AnlFact(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Strip16AnlFact*)
   {
      ::Strip16AnlFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Strip16AnlFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Strip16AnlFact", ::Strip16AnlFact::Class_Version(), "Strip16AnlFact.h", 11,
                  typeid(::Strip16AnlFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Strip16AnlFact::Dictionary, isa_proxy, 4,
                  sizeof(::Strip16AnlFact) );
      instance.SetNew(&new_Strip16AnlFact);
      instance.SetNewArray(&newArray_Strip16AnlFact);
      instance.SetDelete(&delete_Strip16AnlFact);
      instance.SetDeleteArray(&deleteArray_Strip16AnlFact);
      instance.SetDestructor(&destruct_Strip16AnlFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Strip16AnlFact*)
   {
      return GenerateInitInstanceLocal((::Strip16AnlFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Strip16AnlFact*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Strip16UnpackParam(void *p = 0);
   static void *newArray_Strip16UnpackParam(Long_t size, void *p);
   static void delete_Strip16UnpackParam(void *p);
   static void deleteArray_Strip16UnpackParam(void *p);
   static void destruct_Strip16UnpackParam(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Strip16UnpackParam*)
   {
      ::Strip16UnpackParam *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Strip16UnpackParam >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Strip16UnpackParam", ::Strip16UnpackParam::Class_Version(), "Strip16UnpackParam.h", 27,
                  typeid(::Strip16UnpackParam), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Strip16UnpackParam::Dictionary, isa_proxy, 4,
                  sizeof(::Strip16UnpackParam) );
      instance.SetNew(&new_Strip16UnpackParam);
      instance.SetNewArray(&newArray_Strip16UnpackParam);
      instance.SetDelete(&delete_Strip16UnpackParam);
      instance.SetDeleteArray(&deleteArray_Strip16UnpackParam);
      instance.SetDestructor(&destruct_Strip16UnpackParam);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Strip16UnpackParam*)
   {
      return GenerateInitInstanceLocal((::Strip16UnpackParam*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Strip16UnpackParam*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Strip16Analysis(void *p = 0);
   static void *newArray_Strip16Analysis(Long_t size, void *p);
   static void delete_Strip16Analysis(void *p);
   static void deleteArray_Strip16Analysis(void *p);
   static void destruct_Strip16Analysis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Strip16Analysis*)
   {
      ::Strip16Analysis *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Strip16Analysis >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Strip16Analysis", ::Strip16Analysis::Class_Version(), "Strip16Analysis.h", 24,
                  typeid(::Strip16Analysis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Strip16Analysis::Dictionary, isa_proxy, 4,
                  sizeof(::Strip16Analysis) );
      instance.SetNew(&new_Strip16Analysis);
      instance.SetNewArray(&newArray_Strip16Analysis);
      instance.SetDelete(&delete_Strip16Analysis);
      instance.SetDeleteArray(&deleteArray_Strip16Analysis);
      instance.SetDestructor(&destruct_Strip16Analysis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Strip16Analysis*)
   {
      return GenerateInitInstanceLocal((::Strip16Analysis*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Strip16Analysis*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Strip16UnpackEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Strip16UnpackEvent::Class_Name()
{
   return "Strip16UnpackEvent";
}

//______________________________________________________________________________
const char *Strip16UnpackEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Strip16UnpackEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Strip16UnpackEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Strip16UnpackEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Strip16UnpackProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Strip16UnpackProc::Class_Name()
{
   return "Strip16UnpackProc";
}

//______________________________________________________________________________
const char *Strip16UnpackProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Strip16UnpackProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Strip16UnpackProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Strip16UnpackProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Strip16HardwareParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Strip16HardwareParameter::Class_Name()
{
   return "Strip16HardwareParameter";
}

//______________________________________________________________________________
const char *Strip16HardwareParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16HardwareParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Strip16HardwareParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16HardwareParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Strip16HardwareParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16HardwareParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Strip16HardwareParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16HardwareParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Strip16UnpackFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Strip16UnpackFact::Class_Name()
{
   return "Strip16UnpackFact";
}

//______________________________________________________________________________
const char *Strip16UnpackFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Strip16UnpackFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Strip16UnpackFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Strip16UnpackFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Strip16CalibParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Strip16CalibParameter::Class_Name()
{
   return "Strip16CalibParameter";
}

//______________________________________________________________________________
const char *Strip16CalibParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16CalibParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Strip16CalibParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16CalibParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Strip16CalibParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16CalibParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Strip16CalibParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16CalibParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Strip16AnlProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Strip16AnlProc::Class_Name()
{
   return "Strip16AnlProc";
}

//______________________________________________________________________________
const char *Strip16AnlProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Strip16AnlProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Strip16AnlProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Strip16AnlProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Strip16AnlEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Strip16AnlEvent::Class_Name()
{
   return "Strip16AnlEvent";
}

//______________________________________________________________________________
const char *Strip16AnlEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Strip16AnlEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Strip16AnlEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Strip16AnlEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Strip16AnlFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Strip16AnlFact::Class_Name()
{
   return "Strip16AnlFact";
}

//______________________________________________________________________________
const char *Strip16AnlFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Strip16AnlFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Strip16AnlFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Strip16AnlFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16AnlFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Strip16UnpackParam::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Strip16UnpackParam::Class_Name()
{
   return "Strip16UnpackParam";
}

//______________________________________________________________________________
const char *Strip16UnpackParam::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackParam*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Strip16UnpackParam::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackParam*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Strip16UnpackParam::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackParam*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Strip16UnpackParam::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16UnpackParam*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Strip16Analysis::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Strip16Analysis::Class_Name()
{
   return "Strip16Analysis";
}

//______________________________________________________________________________
const char *Strip16Analysis::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16Analysis*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Strip16Analysis::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Strip16Analysis*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Strip16Analysis::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16Analysis*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Strip16Analysis::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Strip16Analysis*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Strip16UnpackEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class Strip16UnpackEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Strip16UnpackEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(Strip16UnpackEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Strip16UnpackEvent(void *p) {
      return  p ? new(p) ::Strip16UnpackEvent : new ::Strip16UnpackEvent;
   }
   static void *newArray_Strip16UnpackEvent(Long_t nElements, void *p) {
      return p ? new(p) ::Strip16UnpackEvent[nElements] : new ::Strip16UnpackEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_Strip16UnpackEvent(void *p) {
      delete ((::Strip16UnpackEvent*)p);
   }
   static void deleteArray_Strip16UnpackEvent(void *p) {
      delete [] ((::Strip16UnpackEvent*)p);
   }
   static void destruct_Strip16UnpackEvent(void *p) {
      typedef ::Strip16UnpackEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Strip16UnpackEvent

//______________________________________________________________________________
void Strip16UnpackProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class Strip16UnpackProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Strip16UnpackProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(Strip16UnpackProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Strip16UnpackProc(void *p) {
      return  p ? new(p) ::Strip16UnpackProc : new ::Strip16UnpackProc;
   }
   static void *newArray_Strip16UnpackProc(Long_t nElements, void *p) {
      return p ? new(p) ::Strip16UnpackProc[nElements] : new ::Strip16UnpackProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_Strip16UnpackProc(void *p) {
      delete ((::Strip16UnpackProc*)p);
   }
   static void deleteArray_Strip16UnpackProc(void *p) {
      delete [] ((::Strip16UnpackProc*)p);
   }
   static void destruct_Strip16UnpackProc(void *p) {
      typedef ::Strip16UnpackProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Strip16UnpackProc

//______________________________________________________________________________
void Strip16HardwareParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class Strip16HardwareParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Strip16HardwareParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(Strip16HardwareParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Strip16HardwareParameter(void *p) {
      return  p ? new(p) ::Strip16HardwareParameter : new ::Strip16HardwareParameter;
   }
   static void *newArray_Strip16HardwareParameter(Long_t nElements, void *p) {
      return p ? new(p) ::Strip16HardwareParameter[nElements] : new ::Strip16HardwareParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_Strip16HardwareParameter(void *p) {
      delete ((::Strip16HardwareParameter*)p);
   }
   static void deleteArray_Strip16HardwareParameter(void *p) {
      delete [] ((::Strip16HardwareParameter*)p);
   }
   static void destruct_Strip16HardwareParameter(void *p) {
      typedef ::Strip16HardwareParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Strip16HardwareParameter

//______________________________________________________________________________
void Strip16UnpackFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class Strip16UnpackFact.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Strip16UnpackFact::Class(),this);
   } else {
      R__b.WriteClassBuffer(Strip16UnpackFact::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Strip16UnpackFact(void *p) {
      return  p ? new(p) ::Strip16UnpackFact : new ::Strip16UnpackFact;
   }
   static void *newArray_Strip16UnpackFact(Long_t nElements, void *p) {
      return p ? new(p) ::Strip16UnpackFact[nElements] : new ::Strip16UnpackFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_Strip16UnpackFact(void *p) {
      delete ((::Strip16UnpackFact*)p);
   }
   static void deleteArray_Strip16UnpackFact(void *p) {
      delete [] ((::Strip16UnpackFact*)p);
   }
   static void destruct_Strip16UnpackFact(void *p) {
      typedef ::Strip16UnpackFact current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Strip16UnpackFact

//______________________________________________________________________________
void Strip16CalibParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class Strip16CalibParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Strip16CalibParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(Strip16CalibParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Strip16CalibParameter(void *p) {
      return  p ? new(p) ::Strip16CalibParameter : new ::Strip16CalibParameter;
   }
   static void *newArray_Strip16CalibParameter(Long_t nElements, void *p) {
      return p ? new(p) ::Strip16CalibParameter[nElements] : new ::Strip16CalibParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_Strip16CalibParameter(void *p) {
      delete ((::Strip16CalibParameter*)p);
   }
   static void deleteArray_Strip16CalibParameter(void *p) {
      delete [] ((::Strip16CalibParameter*)p);
   }
   static void destruct_Strip16CalibParameter(void *p) {
      typedef ::Strip16CalibParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Strip16CalibParameter

//______________________________________________________________________________
void Strip16AnlProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class Strip16AnlProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Strip16AnlProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(Strip16AnlProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Strip16AnlProc(void *p) {
      return  p ? new(p) ::Strip16AnlProc : new ::Strip16AnlProc;
   }
   static void *newArray_Strip16AnlProc(Long_t nElements, void *p) {
      return p ? new(p) ::Strip16AnlProc[nElements] : new ::Strip16AnlProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_Strip16AnlProc(void *p) {
      delete ((::Strip16AnlProc*)p);
   }
   static void deleteArray_Strip16AnlProc(void *p) {
      delete [] ((::Strip16AnlProc*)p);
   }
   static void destruct_Strip16AnlProc(void *p) {
      typedef ::Strip16AnlProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Strip16AnlProc

//______________________________________________________________________________
void Strip16AnlEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class Strip16AnlEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Strip16AnlEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(Strip16AnlEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Strip16AnlEvent(void *p) {
      return  p ? new(p) ::Strip16AnlEvent : new ::Strip16AnlEvent;
   }
   static void *newArray_Strip16AnlEvent(Long_t nElements, void *p) {
      return p ? new(p) ::Strip16AnlEvent[nElements] : new ::Strip16AnlEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_Strip16AnlEvent(void *p) {
      delete ((::Strip16AnlEvent*)p);
   }
   static void deleteArray_Strip16AnlEvent(void *p) {
      delete [] ((::Strip16AnlEvent*)p);
   }
   static void destruct_Strip16AnlEvent(void *p) {
      typedef ::Strip16AnlEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Strip16AnlEvent

//______________________________________________________________________________
void Strip16AnlFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class Strip16AnlFact.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Strip16AnlFact::Class(),this);
   } else {
      R__b.WriteClassBuffer(Strip16AnlFact::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Strip16AnlFact(void *p) {
      return  p ? new(p) ::Strip16AnlFact : new ::Strip16AnlFact;
   }
   static void *newArray_Strip16AnlFact(Long_t nElements, void *p) {
      return p ? new(p) ::Strip16AnlFact[nElements] : new ::Strip16AnlFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_Strip16AnlFact(void *p) {
      delete ((::Strip16AnlFact*)p);
   }
   static void deleteArray_Strip16AnlFact(void *p) {
      delete [] ((::Strip16AnlFact*)p);
   }
   static void destruct_Strip16AnlFact(void *p) {
      typedef ::Strip16AnlFact current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Strip16AnlFact

//______________________________________________________________________________
void Strip16UnpackParam::Streamer(TBuffer &R__b)
{
   // Stream an object of class Strip16UnpackParam.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Strip16UnpackParam::Class(),this);
   } else {
      R__b.WriteClassBuffer(Strip16UnpackParam::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Strip16UnpackParam(void *p) {
      return  p ? new(p) ::Strip16UnpackParam : new ::Strip16UnpackParam;
   }
   static void *newArray_Strip16UnpackParam(Long_t nElements, void *p) {
      return p ? new(p) ::Strip16UnpackParam[nElements] : new ::Strip16UnpackParam[nElements];
   }
   // Wrapper around operator delete
   static void delete_Strip16UnpackParam(void *p) {
      delete ((::Strip16UnpackParam*)p);
   }
   static void deleteArray_Strip16UnpackParam(void *p) {
      delete [] ((::Strip16UnpackParam*)p);
   }
   static void destruct_Strip16UnpackParam(void *p) {
      typedef ::Strip16UnpackParam current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Strip16UnpackParam

//______________________________________________________________________________
void Strip16Analysis::Streamer(TBuffer &R__b)
{
   // Stream an object of class Strip16Analysis.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Strip16Analysis::Class(),this);
   } else {
      R__b.WriteClassBuffer(Strip16Analysis::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Strip16Analysis(void *p) {
      return  p ? new(p) ::Strip16Analysis : new ::Strip16Analysis;
   }
   static void *newArray_Strip16Analysis(Long_t nElements, void *p) {
      return p ? new(p) ::Strip16Analysis[nElements] : new ::Strip16Analysis[nElements];
   }
   // Wrapper around operator delete
   static void delete_Strip16Analysis(void *p) {
      delete ((::Strip16Analysis*)p);
   }
   static void deleteArray_Strip16Analysis(void *p) {
      delete [] ((::Strip16Analysis*)p);
   }
   static void destruct_Strip16Analysis(void *p) {
      typedef ::Strip16Analysis current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Strip16Analysis

namespace {
  void TriggerDictionaryInitialization_libGo4UserAnalysis_Impl() {
    static const char* headers[] = {
"./Strip16UnpackProc.h",
"./Strip16HardwareParameter.h",
"./Strip16UnpackFact.h",
"./Strip16AnlEvent.h",
"./Strip16AnlProc.h",
"./Strip16AnlFact.h",
"./Strip16UnpackParam.h",
"./Strip16UnpackEvent.h",
"./Strip16Analysis.h",
"./Strip16CalibParameter.h",
"./Strip16Globals.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/eel.gsi.de/debian10-x86_64/go4/602-00/include",
"/cvmfs/eel.gsi.de/debian10-x86_64/go4/602-00",
"/cvmfs/eel.gsi.de/debian10-x86_64/root/624-04/include/",
"/u/ship/16_strip_2021/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libGo4UserAnalysis dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$Strip16UnpackEvent.h")))  __attribute__((annotate("$clingAutoload$./Strip16UnpackProc.h")))  Strip16UnpackEvent;
class __attribute__((annotate("$clingAutoload$./Strip16UnpackProc.h")))  Strip16UnpackProc;
class __attribute__((annotate("$clingAutoload$./Strip16HardwareParameter.h")))  Strip16HardwareParameter;
class __attribute__((annotate("$clingAutoload$./Strip16UnpackFact.h")))  Strip16UnpackFact;
class __attribute__((annotate("$clingAutoload$Strip16CalibParameter.h")))  __attribute__((annotate("$clingAutoload$./Strip16AnlEvent.h")))  Strip16CalibParameter;
class __attribute__((annotate("$clingAutoload$Strip16AnlProc.h")))  __attribute__((annotate("$clingAutoload$./Strip16AnlEvent.h")))  Strip16AnlProc;
class __attribute__((annotate("$clingAutoload$./Strip16AnlEvent.h")))  Strip16AnlEvent;
class __attribute__((annotate("$clingAutoload$./Strip16AnlFact.h")))  Strip16AnlFact;
class __attribute__((annotate("$clingAutoload$./Strip16UnpackParam.h")))  Strip16UnpackParam;
class __attribute__((annotate("$clingAutoload$./Strip16Analysis.h")))  Strip16Analysis;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libGo4UserAnalysis dictionary payload"

#ifndef Linux
  #define Linux 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "./Strip16UnpackProc.h"
#include "./Strip16HardwareParameter.h"
#include "./Strip16UnpackFact.h"
#include "./Strip16AnlEvent.h"
#include "./Strip16AnlProc.h"
#include "./Strip16AnlFact.h"
#include "./Strip16UnpackParam.h"
#include "./Strip16UnpackEvent.h"
#include "./Strip16Analysis.h"
#include "./Strip16CalibParameter.h"
#include "./Strip16Globals.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"Strip16Analysis", payloadCode, "@",
"Strip16AnlEvent", payloadCode, "@",
"Strip16AnlFact", payloadCode, "@",
"Strip16AnlProc", payloadCode, "@",
"Strip16CalibParameter", payloadCode, "@",
"Strip16HardwareParameter", payloadCode, "@",
"Strip16UnpackEvent", payloadCode, "@",
"Strip16UnpackFact", payloadCode, "@",
"Strip16UnpackParam", payloadCode, "@",
"Strip16UnpackProc", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libGo4UserAnalysis",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libGo4UserAnalysis_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libGo4UserAnalysis_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libGo4UserAnalysis() {
  TriggerDictionaryInitialization_libGo4UserAnalysis_Impl();
}
