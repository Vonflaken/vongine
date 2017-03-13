#ifndef __VGMACROS_H__
#define __VGMACROS_H__

#define NS_VG_BEGIN			namespace vongine {
#define NS_VG_END			}
#define USING_NS_VG			using namespace vongine
#define NS_VG				::vongine

#define VG_CALLBACK(func, obj)			std::bind(&func, obj)

#endif // __VGMACROS_H__
