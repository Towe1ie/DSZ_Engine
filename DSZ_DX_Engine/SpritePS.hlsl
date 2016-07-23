Texture2D textureSampler;
SamplerState sampleType;

struct PixelInputType
{
    float4 pos : SV_Position;
    float2 tex : TEXCOORD0;
};

float4 main(PixelInputType input) : SV_TARGET
{
    float4 texColor;

    texColor = textureSampler.Sample(sampleType, input.tex);
	return texColor;
}