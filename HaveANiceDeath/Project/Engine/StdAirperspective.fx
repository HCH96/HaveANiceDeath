#ifndef _STD2D_AIRPERSP
#define _STD2D_AIRPERSP

#include "register.fx"
#include "func.fx"

#define AirPerspEnable g_int_0
#define AirColor g_vec4_0
#define ObjDepth g_float_0

struct VS_IN
{
    float3 vPos : POSITION; // Sementic
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
    float3 vWorldPos : POSITION;
};

struct PS_OUT
{
    float4 RenderTarget : SV_Target0;
    float4 GlowTarget : SV_Target1;
};


VS_OUT VS_Std2D_AirPersp(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    // World로 이동
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWorld);
    
    // Offset 가져오기
    float2 vOffset = { g_vOffset.x * g_vAtlasSize.x, g_vOffset.y * g_vAtlasSize.y };
    output.vPosition -= float4(vOffset.x, vOffset.y, 0.f, 0.f);
    
    // World 저장
    output.vWorldPos = output.vPosition;
    
    // View, Proj 행렬 
    output.vPosition = mul(output.vPosition, g_matView);
    output.vPosition = mul(output.vPosition, g_matProj);
    
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}


PS_OUT PS_Std2D_AirPersp(VS_OUT _in) : SV_Target
{
    // 1. sampling
    PS_OUT output;
    
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    //float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    if (g_UseAnim2D)
    {
        float2 vLeftTop = g_vLeftTop;
        float2 vUV = g_vLeftTop + (_in.vUV * g_vSliceSize);
        
        // 샘플링
        vColor = g_anim2d_tex.Sample(g_sam_1, vUV);
    }
    else
    {
        // Defalut Texture
        if (g_btex_0)
        {
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        }
    }
    
    // Air Perspective
    if (AirPerspEnable && ObjDepth != 0.f)
    {
        float alpha = ObjDepth / 2000.f;
        float4 airColor = AirColor;
        vColor.rgb = vColor.rgb * (1 - alpha) + airColor.rgb * alpha * AirColor.a;
    }
    
    // 2. lighting
    tLightColor LightColor = (tLightColor) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
        CalLight2D(_in.vWorldPos, i, LightColor);
    
    vColor.rgb *= LightColor.vColor.rgb + LightColor.vAmbient.rgb;
    
    // 3. cut masked
    if (vColor.a == 0.f)
        discard;
    
    // render target 0
    output.RenderTarget = vColor;
    return output;
}

#endif