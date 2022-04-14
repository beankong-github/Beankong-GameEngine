#pragma once

#define SINGLE(TYPE) friend class CSingleton<TYPE>;\
					 private:\
						TYPE();\
						~TYPE();


typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;
