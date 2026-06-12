struct VSInput
{
    float3 position: POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;

};
struct VSOutput
{
    float4 position: SV_Position;  //clip space postion for system value
    float4 color : COLOR0; 
    float2 uv : TEXCOORD0;

};
//future shader code might need the world-space position keeping them sepreate allows flex
cbuffer ConstantData : register(b0)
{//
    row_major float4x4 world;  //scale changes, geometry visibly grows/shrinks.
    row_major float4x4 view;
    row_major float4x4 proj;

};

Texture2D albedo : register(t0);
SamplerState samp : register(s0);

VSOutput VSMain(VSInput input)
{ //Row-major vectors multiply left (v * M), W=1 ensures translation applies, W=0 would suppress it.
    VSOutput output;
    output.position = mul(float4(input.position, 1), world);
    output.position = mul(output.position, view); 
    output.position = mul(output.position, proj);
    output.color = input.color;
    output.uv = input.uv;

    return output;
}


float4 PSMain(VSOutput input) : SV_Target
{
    
    return albedo.Sample(samp, input.uv);
}