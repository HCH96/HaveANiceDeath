#ifndef _STORMBACKGROUND
#define _STORMBACKGROUND

#include "register.fx"
#include "func.fx"


#define Width   g_float_0
#define Height  g_float_1



#define TexWidth 2048.f
#define TexHeight 1024.f

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

VS_OUT VS_StormBackground(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // World로 이동
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWorld);
    
    // World 저장
    output.vWorldPos = output.vPosition;
    
    // View, Proj 행렬 
    output.vPosition = mul(output.vPosition, g_matView);
    output.vPosition = mul(output.vPosition, g_matProj);
    
    output.vColor = _in.vColor;
    
    float MagX = Width / TexWidth;
    float MagY = Height / TexHeight;
    
    
    output.vUV = float2(_in.vUV.x * MagX, _in.vUV.y * MagY);
    
    return output;          
}

struct PS_Std2D_Glow_Output
{
    float4 RenderTarget : SV_Target0;
    float4 GlowTarget : SV_Target1;
};


PS_Std2D_Glow_Output PS_StormBackground(VS_OUT _in) : SV_Target
{
    PS_Std2D_Glow_Output output;
    
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
    
    
    if (g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    }
    
    
    output.RenderTarget = vColor;
    
    return output;
}


//float hash(float n)
//{
//    return fract(sin(n) * 43758.5453);
//}

//float noise(in vec2 x)
//{
//    vec2 p = floor(x);
//    vec2 f = fract(x);
//    f = f * f * (3.0 - 2.0 * f);
//    float n = p.x + p.y * 57.0;
//    return mix(mix(hash(n + 0.0), hash(n + 1.0), f.x),
//               mix(hash(n + 57.0), hash(n + 58.0), f.x), f.y);
//}

//vec2 map(vec2 p, in float offset)
//{
//    p.x += 0.1 * sin(iTime + 2.0 * p.y);
//    p.y += 0.1 * sin(iTime + 2.0 * p.x);
	
//    float a = noise(p * 1.5 + sin(0.1 * iTime)) * 6.2831;
//    a -= offset;
//    return vec2(cos(a), sin(a));
//}

//void mainImage(out vec4 fragColor, in vec2 fragCoord)
//{
//    vec2 p = fragCoord.xy / iResolution.xy;
//    vec2 uv = -1.0 + 2.0 * p;
//    uv.x *= iResolution.x / iResolution.y;
		
//    float offset = iTime + fragCoord.x / iResolution.x;
    
//    float acc = 0.0;
//    vec3 col = vec3(0.0);
//    for (int i = 0; i < 32; i++)
//    {
//        vec2 dir = map(uv, offset);
		
//        float h = float(i) / 32.0;
//        float w = 4.0 * h * (1.0 - h);
		
//        vec3 ttt = w * texture(iChannel0, uv).xyz;
//        ttt *= mix(vec3(0.6, 0.7, 0.7), vec3(1.0, 0.95, 0.9), 0.5 - 0.5 * dot(reflect(vec3(dir, 0.0), vec3(1.0, 0.0, 0.0)).xy, vec2(0.707)));
//        col += w * ttt;
//        acc += w;
		
//        uv += 0.008 * dir;
//    }
//    col /= acc;
    
//    float gg = dot(col, vec3(0.333));
//    vec3 nor = normalize(vec3(dFdx(gg), 0.5, dFdy(gg)));
//    col += vec3(0.4) * dot(nor, vec3(0.7, 0.01, 0.7));

//    vec2 di = map(uv, offset);
//    col *= 0.65 + 0.35 * dot(di, vec2(0.707));
//    col *= 0.20 + 0.80 * pow(4.0 * p.x * (1.0 - p.x), 0.1);
//    col *= 1.7;

//    fragColor = vec4(col, 1.0);
//}



#endif