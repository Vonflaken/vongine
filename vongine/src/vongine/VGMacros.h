#ifndef __VGMACROS_H__
#define __VGMACROS_H__

#define NS_VG_BEGIN			namespace vongine {
#define NS_VG_END			}
#define USING_NS_VG			using namespace vongine
#define NS_VG				::vongine

#define VG_CALLBACK(func, obj)			std::bind(&func, obj)

#ifdef VG_DLL
#ifdef VG_EXPORT
#define DLLAPI __declspec(dllexport)
#define EXTERN_TEMPL 
#else
#define DLLAPI __declspec(dllimport)
#define EXTERN_TEMPL extern
#endif // VG_EXPORT
#else
#define DLLAPI 
#define EXTERN_TEMPL 
#endif // VG_DLL

#endif // __VGMACROS_H__
