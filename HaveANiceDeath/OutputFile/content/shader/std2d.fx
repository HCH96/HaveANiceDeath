#ifndef _STD2D
#define _STD2D

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

VS_OUT VS_Std2D(VS_IN _in)
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

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    if (g_vec4_1.w == 3.14f)
        return float4(1.f, 1.f, 0.f, 1.f);
    
    if (g_UseAnim2D)
    {
        // Background
        float2 vBackgroundLeftTop = g_vLeftTop + (g_vSliceSize / 2.f) - (g_vBackground / 2.f);
        // vBackgroundLeftTop -= g_vOffset;
        float2 vUV = vBackgroundLeftTop + (_in.vUV * g_vBackground); //UV는 한 프레임의 크기를 대상으로 함
        
        // 가져오려는 이미지를 벗어나면 그리지 않음
        // 즉, 부족한 부분에 대해서만 더 그림
        if (vUV.x < g_vLeftTop.x || vUV.x > g_vLeftTop.x + g_vSliceSize.x
            || vUV.y < g_vLeftTop.y || vUV.y > g_vLeftTop.y + g_vSliceSize.y)
            discard;
        else
            vColor = g_anim2d_tex.Sample(g_sam_1, vUV);
    }
    else
    {
        if (g_btex_0)
        {
            //vColor = g_tex_0.Sample(g_sam_1, _in.vUV + float2(g_time * 0.1, 0.f));
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
                    
            ////saturate 0 ~ 1 을 넘지 않게 보정
            //float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
        
            //if (fAlpha < 0.1f)
            //{
            //// 픽셀 쉐이더를 중간에 폐기처리
            //    discard; //clip(-1);            
            //}
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
        
    //if (0.f == vColor.a)
    //    discard;
    
    //float x = g_NoiseTex.Sample(g_sam_0, _in.vUV).x;
    //if (0 > x - g_float_1)
    //{
    //    discard;
    //}
    
    return vColor;
}


// EffectShader
float4 PS_Std2D_Effect(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
  
    
    if (g_UseAnim2D)
    {
        float2 vBackgroundLeftTop = g_vLeftTop + (g_vSliceSize / 2.f) - (g_vBackground / 2.f);
        vBackgroundLeftTop -= g_vOffset;
        float2 vUV = vBackgroundLeftTop + (g_vBackground * _in.vUV);
        
        if (vUV.x < g_vLeftTop.x || (g_vLeftTop.x + g_vSliceSize.x) < vUV.x
            || vUV.y < g_vLeftTop.y || (g_vLeftTop.y + g_vSliceSize.y) < vUV.y)
        {
            //vColor = float4(1.f, 1.f, 0.f, 1.f);
            discard;
        }
        else
        {
            vColor = g_anim2d_tex.Sample(g_sam_1, vUV);
        }
    }
    else
    {
        if (g_btex_0)
        {
            //vColor = g_tex_0.Sample(g_sam_1, _in.vUV + float2(g_time * 0.1, 0.f));
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
                    
            //saturate 0 ~ 1 을 넘지 않게 보정
            float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
        
            if (fAlpha < 0.1f)
            {
            // 픽셀 쉐이더를 중간에 폐기처리
                discard; //clip(-1);            
            }
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
    
    return vColor;
}


#endif