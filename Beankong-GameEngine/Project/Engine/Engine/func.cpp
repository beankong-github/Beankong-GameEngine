#include "pch.h"

const wchar_t* ToWString(COMPONENT_TYPE _type)
{
    static const wchar_t* szWString[(UINT)COMPONENT_TYPE::END] = 
    {
        L"TRANSFORM",
        L"CAMERA",
        L"COLLIDER2D",
        L"COLLIDER3D",
        L"ANIMATOR2D",
        L"ANIMATOR3D",
        L"BOUNDINGBOX",
        L"MESHRENDER",
        L"TILEMAP",
        L"PARTICLESYSTEM",
        L"LANDSCAPE",
        L"DECAL"
    };

    return szWString[(UINT)_type];
}

const char* ToString(COMPONENT_TYPE _type)
{
    static const char* szString[(UINT)COMPONENT_TYPE::END] =
    {
        "TRANSFORM",
        "CAMERA",
        "COLLIDER2D",
        "COLLIDER3D",
        "ANIMATOR2D",
        "ANIMATOR3D",
        "BOUNDINGBOX",
        "MESHRENDER",
        "TILEMAP",
        "PARTICLESYSTEM",
        "LANDSCAPE",
        "DECAL"
    };

    return szString[(UINT)_type];
}

const wchar_t* ToWString(RES_TYPE _type)
{
    static const wchar_t* szWString[(UINT)RES_TYPE::END] =
    {
        L"PREFAB",
        L"MESHDATA",
        L"MATERIAL",
        L"GRAPHICS_SHADER",
        L"COMPUTE_SHADER",
        L"MESH",
        L"TEXTURE",
        L"SOUND"
    };

    return szWString[(UINT)_type];
}

const char* ToString(RES_TYPE _type)
{
    static const char* szString[(UINT)RES_TYPE::END] =
    {
        "PREFAB",
        "MESHDATA",
        "MATERIAL",
        "GRAPHICS_SHADER",
        "COMPUTE_SHADER",
        "MESH",
        "TEXTURE",
        "SOUND"
    };

    return szString[(UINT)_type];
}

const wchar_t* ToWString(RS_TYPE _type)
{
    static const wchar_t* szWString[(UINT)RS_TYPE::END] =
    {
        L"CULL_BACK",	// Default
        L"CULL_FRONT",
        L"CULL_NONE", 
        L"WIRE_FRAME"
    };

    return szWString[(UINT)_type];
}

const char* ToString(RS_TYPE _type)
{
    static const char* szString[(UINT)RS_TYPE::END] =
    {
        "CULL_BACK",
        "CULL_FRONT",
        "CULL_NONE",
        "WIRE_FRAME"       
    };

    return szString[(UINT)_type];
}

const wchar_t* ToWString(BS_TYPE _type)
{
    static const wchar_t* szWString[(UINT)BS_TYPE::END] =
    {
        L"DEFAULT",	
        L"ALPHA_BLEND"
    };

    return szWString[(UINT)_type];
}

const char* ToString(BS_TYPE _type)
{
    static const char* szString[(UINT)BS_TYPE::END] =
    {
        "DEFAULT",
        "ALPHA_BLEND"
    };

    return szString[(UINT)_type];
}


const wchar_t* ToWString(DS_TYPE _type)
{
    static const wchar_t* szWString[(UINT)DS_TYPE::END] =
    {
        L"LESS",
        L"LESS_EQUAL",
        
        L"GREATER",
        L"GREATER_EQUAL",
        
        L"NO_TEST",	
        L"NO_WRITE",	
        
        L"NO_TEST_NO_WRITE"
    };

    return szWString[(UINT)_type];
}

const char* ToString(DS_TYPE _type)
{
    static const char* szString[(UINT)DS_TYPE::END] =
    {
        "LESS",
        "LESS_EQUAL",
        
        "GREATER",
        "GREATER_EQUAL",
        
        "NO_TEST",
        "NO_WRITE",
        
        "NO_TEST_NO_WRITE"
    };

    return szString[(UINT)_type];
}

const wchar_t* ToWString(SHADER_DOMAIN _type)
{
    static const wchar_t* szWString[(UINT)SHADER_DOMAIN::END] =
    {
        L"DOMAIN_FORWARD",	// 불투명
        L"DOMAIN_MASKED",	// 불투명, 투명
        L"DOMAIN_TRANSLUCENT",	// 반투명
        L"DOMAIN_POSTPROCESS", // 후 처리
    };

    return szWString[(UINT)_type];
}

const char* ToString(SHADER_DOMAIN _type)
{
    static const char* szString[(UINT)SHADER_DOMAIN::END] =
    {
        "DOMAIN_FORWARD",	// 불투명
        "DOMAIN_MASKED",	// 불투명, 투명
        "DOMAIN_TRANSLUCENT",	// 반투명
        "DOMAIN_POSTPROCESS", // 후 처리

    };

    return szString[(UINT)_type];
}


