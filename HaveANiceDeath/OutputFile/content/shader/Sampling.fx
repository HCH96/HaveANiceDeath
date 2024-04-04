#ifndef SAMPLING
#define SAMPLING

Texture2D<float4> inputTexture : register(t0);
RWTexture2D<float4> outputTexture : register(u0);

#define RESRESOL 


[numthreads(32, 32, 1)]
void CSMain(uint3 dispatchThreadID : SV_DispatchThreadID)
{
    // 입력 텍스처의 레벨 0의 크기
    uint inputWidth, inputHeight;
    inputTexture.GetDimensions(inputWidth, inputHeight);

    // 입력 텍스처에서 픽셀 값을 읽어올 위치 계산 (해상도가 절반)
    uint2 inputPixelPos = uint2(dispatchThreadID.xy * 2);

    // 출력 텍스처로 복사할 위치 계산
    uint2 outputPixelPos = uint2(dispatchThreadID.xy);

    // 입력 텍스처에서 픽셀 값을 읽어와서 출력 텍스처에 쓰기
    outputTexture[outputPixelPos] = inputTexture[inputPixelPos];
}

#endif