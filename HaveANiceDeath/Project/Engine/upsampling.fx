#ifndef UPSAMPLING
#define UPSAMPLING

// Resource Tex (������)
Texture2D<float4> inputTexture : register(t0);

// Target Tex (ū��)
RWTexture2D<float4> outputTexture : register(u0);


SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);

[numthreads(32, 32, 1)]
void CS_UpSampling(uint3 dispatchThreadID : SV_DispatchThreadID)
{
    // �Է� �ؽ�ó�� �ʺ�� ����
    uint inputWidth, inputHeight;
    inputTexture.GetDimensions(inputWidth, inputHeight);
    
    // ��� �ؽ�ó�� �ʺ�� ���� (�Է� �ؽ�ó�� �� ��)
    uint outputWidth, outputHeight;
    outputTexture.GetDimensions(outputWidth, outputHeight);
    
    if (outputWidth <= dispatchThreadID.x || outputHeight <= dispatchThreadID.y)
    {
        return;
    }
    // �Է� �ؽ�ó���� ���ø��� ��ġ ���
    float2 inputUV = float2(dispatchThreadID.xy) / float2(outputWidth, outputHeight);
    float2 Location = inputUV * float2(inputWidth, inputHeight);
    
    // �Է� �ؽ�ó���� ���ø��Ͽ� ���ο� �ؽ�ó�� ����
    float4 color = inputTexture.Load(int3(Location.x, Location.y, 0));
    //float4 color = inputTexture.SampleLevel(g_sam_0, Location,0);
    
    
    //color.a = 1.f;
    
    outputTexture[dispatchThreadID.xy] = color;
}

#endif