#ifndef __VGMACROS_H__
#define __VGMACROS_H__

#define NS_VG_BEGIN			namespace vongine {
#define NS_VG_END			}
#define USING_NS_VG			using namespace vongine
#define NS_VG				::vongine

#define VG_MEMBER_CALLBACK_0(func, instPtr, ...) std::bind(&func, instPtr, ##__VA_ARGS__)
#define VG_MEMBER_CALLBACK_1(func, instPtr, ...) std::bind(&func, instPtr, std::placeholders::_1, ##__VA_ARGS__)
#define VG_MEMBER_CALLBACK_2(func, instPtr, ...) std::bind(&func, instPtr, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define VG_MEMBER_CALLBACK_3(func, instPtr, ...) std::bind(&func, instPtr, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

#define VG_CALLBACK_0(func, ...) std::bind(func, ##__VA_ARGS__)
#define VG_CALLBACK_1(func, ...) std::bind(func, std::placeholders::_1, ##__VA_ARGS__)
#define VG_CALLBACK_2(func, ...) std::bind(func, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define VG_CALLBACK_3(func, ...) std::bind(func, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

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
