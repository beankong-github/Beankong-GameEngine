#pragma once

#define SINGLE(TYPE) friend class CSingleton<TYPE>;\
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

// ��� ���� Ÿ��
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
	CULL_BACK,				// �޸��� ǥ������ �ʴ´�. (Default)
	CULL_FRONT,				// �ո��� ǥ������ �ʴ´�.
	CULL_NONE,				// �ո�� �޸��� ��� ǥ���Ѵ�.
	WIRE_FRAME,				// ���� ǥ���Ѵ�.
	END,
};


// DepthStencil Option
enum class DS_TYPE
{
	LESS,					// �� �տ� �ִ� Object �켱 ��� (Default)
	LESS_EQUAL,

	GREATER,				// �� �ڿ� �ִ� Obejct �켱 ���
	GREATER_EQUAL,

	NO_TEST,				// �����׽�Ʈ ���� ����, ���̴� ���
	NO_WRITE,				// �����׽�Ʈ ����, ���̸� ������� ����

	NO_TEST_NO_WRITE,		// �����׽�Ʈ ���� ����, ���� ������� ����
	END,
};

// BlendState Option
enum class BS_TYPE
{
	DEFAULT,				// SrcRGB * (1) + DestRGB * (0)
	ALPHA_BLEND,			// SrcRGB * (SrcAlpha) + DestRGB * (1 - SrcAlpha)
	END,
};
