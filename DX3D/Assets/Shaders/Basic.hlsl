struct VSInput
{
    float3 position: POSITION0;
    float4 color : COLOR0;
};
struct VSOutput
{
    float4 position: SV_Position;  //clip space postion for system value
    float4 color : COLOR0; 
};

cbuffer ConstantData : register(b0)
{//
    row_major float4x4 world;  //scale changes, geometry visibly grows/shrinks.
};

VSOutput VSMain(VSInput input)
{ //Row-major vectors multiply left (v * M), W=1 ensures translation applies, W=0 would suppress it.
    VSOutput output;
    output.position = mul(float4(input.position, 1), world);
    output.color = input.color;
    return output;
}


float4 PSMain(VSOutput input) : SV_Target
{
    return input.color;
}