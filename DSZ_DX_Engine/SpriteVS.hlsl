cbuffer PerFrameBuffer : register(b0)
{
    matrix viewMatrix;
};

cbuffer PerObjectBuffer : register(b1)
{
    matrix worldMatrix;
};

struct VertexInput
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInput
{
    float4 position : SV_Position;
    float2 tex : TEXCOORD0;
};

PixelInput main(VertexInput input)
{
    PixelInput output;

    input.position.w = 1.0f;
    float4 pos = mul(input.position, worldMatrix);
    output.position = mul(pos, viewMatrix);
    output.tex = input.tex;

    return output;
}