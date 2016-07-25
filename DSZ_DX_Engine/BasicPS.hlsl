struct PixelInputType
{
    float4 pos : SV_Position;
    float4 color : COLOR0;
};

float4 main(PixelInputType input) : SV_TARGET
{
    return input.color;
}