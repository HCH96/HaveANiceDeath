#ifndef SAMPLING
#define SAMPLING

Texture2D<float4> inputTexture : register(t0);
RWTexture2D<float4> outputTexture : register(u0);

#define RESRESOL 


[numthreads(32, 32, 1)]
void CSMain(uint3 dispatchThreadID : SV_DispatchThreadID)
{
    // �Է� �ؽ�ó�� ���� 0�� ũ��
    uint inputWidth, inputHeight;
    inputTexture.GetDimensions(inputWidth, inputHeight);

    // �Է� �ؽ�ó���� �ȼ� ���� �о�� ��ġ ��� (�ػ󵵰� ����)
    uint2 inputPixelPos = uint2(dispatchThreadID.xy * 2);

    // ��� �ؽ�ó�� ������ ��ġ ���
    uint2 outputPixelPos = uint2(dispatchThreadID.xy);

    // �Է� �ؽ�ó���� �ȼ� ���� �о�ͼ� ��� �ؽ�ó�� ����
    outputTexture[outputPixelPos] = inputTexture[inputPixelPos];
}

#endif