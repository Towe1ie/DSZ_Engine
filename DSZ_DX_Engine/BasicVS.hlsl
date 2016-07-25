cbuffer Buffer0 : register(b0)
{
    matrix viewMatrix;
    matrix worldMatrix;
    float4 color;
    bool useVertexColor;
};


struct VertexInput
{
    float4 position : POSITION;
    float4 color : COLOR0;
};

struct PixelInput
{
    float4 position : SV_Position;
    float4 color : COLOR0;
};

PixelInput main(VertexInput input)
{
    PixelInput output;

    input.position.w = 1.0f;
    float4 pos = mul(input.position, worldMatrix);
    output.position = mul(pos, viewMatrix);
    output.color = useVertexColor ? input.color : color;

    return output;
}