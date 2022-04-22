#pragma once

#define SINGLE(TYPE) friend class Singleton<TYPE>;\
					 private:\
						TYPE();\
						~TYPE();

#define DT CTimeMgr::GetInst()->GetDT()

#define KEY_TAP(key) KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(key)
#define KEY_PRESSED(key) KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(key)
#define KEY_AWAY(key) KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(key)

#define DEVICE CDevice::GetInst()->GetDevice().Get()
#define CONTEXT CDevice::GetInst()->GetDeviceContext().Get()

#define MAX_LAYER 32

#define SAFE_DELETE(p) if(nullptr != p) delete p; p = nullptr;
#define CLONE(type) virtual type* Clone() { return new type(*this); }
#define CLONE_DISABLE(type) virtual type* Clone() { return nullptr; }

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;

// 상수 버퍼 타입
enum class CB_TYPE
{
	TRANSFORM,		// b0
	SCALAR_PARAM,	// b1
	GLOBAL,			// b2
	END,
};


// Rasterizer option
enum class RS_TYPE
{
	CULL_BACK,				// 뒷면을 표시하지 않는다. (Default)
	CULL_FRONT,				// 앞면을 표시하지 않는다.
	CULL_NONE,				// 앞면과 뒷면을 모두 표시한다.
	WIRE_FRAME,				// 선만 표시한다.
	END,
};


// DepthStencil Option
enum class DS_TYPE
{
	LESS,					// 더 앞에 있는 Object 우선 통과 (Default)
	LESS_EQUAL,

	GREATER,				// 더 뒤에 있는 Obejct 우선 통과
	GREATER_EQUAL,

	NO_TEST,				// 깊이테스트 하지 않음, 깊이는 기록
	NO_WRITE,				// 깊이테스트 진행, 깊이를 기록하지 않음

	NO_TEST_NO_WRITE,		// 깊이테스트 하지 않음, 깊이 기록하지 않음
	END,
};

// BlendState Option
enum class BS_TYPE
{
	DEFAULT,				// SrcRGB * (1) + DestRGB * (0)
	ALPHA_BLEND,			// SrcRGB * (SrcAlpha) + DestRGB * (1 - SrcAlpha)
	END,
};
