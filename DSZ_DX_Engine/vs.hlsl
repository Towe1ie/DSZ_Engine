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
    float4 color : COLOR;
};

struct PixelInput
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

PixelInput main(VertexInput input)
{
    PixelInput output;

    input.position.w = 1.0f;
    float4 pos = mul(input.position, worldMatrix);
    output.position = mul(pos, viewMatrix);
    output.color = input.color;

    return output;
}