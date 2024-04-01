#ifndef _PLAYER
#define _PLAYER

#include "register.fx"
#include "func.fx"

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

VS_OUT VS_Player(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    // World로 이동
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWorld);
    
    // Offset 가져오기
    float2 vOffset = { g_vOffset.x * g_vAtlasSize.x, g_vOffset.y * g_vAtlasSize.y };
    
    
    // Animation 뒤집기
    if (g_int_0 == -1)
    {
        output.vUV = float2((1.f - _in.vUV.x), _in.vUV.y);
        output.vPosition -= float4(-vOffset.x, vOffset.y, 0.f, 0.f);
    }
    else
    {
        output.vUV = _in.vUV;
        output.vPosition -= float4(vOffset.x, vOffset.y, 0.f, 0.f);
    }
    
    
    // World 저장
    output.vWorldPos = output.vPosition;
    
    // View, Proj 행렬 
    output.vPosition = mul(output.vPosition, g_matView);
    output.vPosition = mul(output.vPosition, g_matProj);
    
    output.vColor = _in.vColor;
    

    
    return output;
}


float4 PS_Player(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    if (g_UseAnim2D)
    {
        float2 vLeftTop = g_vLeftTop;
        float2 vUV = g_vLeftTop + (_in.vUV * g_vSliceSize);
        
        // 샘플링
        vColor = g_anim2d_tex.Sample(g_sam_1, vUV);
    }
    else
    {
        if (g_btex_0)
        {
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        }
        
        
        // 마젠타 색에 가까우면 discard
        //saturate 0 ~ 1 을 넘지 않게 보정
        float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
        
        if (fAlpha < 0.1f)
        {
            // 픽셀 쉐이더를 중간에 폐기처리
            discard; //clip(-1);            
        }
        
    }
        
    // 광원 처리
    // 광원의 타입별 처리
    // 광원이 여러개일 때 처리
    //g_Light2DCount;    
    tLightColor LightColor = (tLightColor) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        CalLight2D(_in.vWorldPos, i, LightColor);
    }
    
    vColor.rgb *= (LightColor.vColor.rgb + LightColor.vAmbient.rgb);

    if (0.f == vColor.a)
        discard;
    
    return vColor;
}



#endif