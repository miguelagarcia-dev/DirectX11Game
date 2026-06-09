struct VSInput
{
    float3 positon: POSITION0;
    float4 color : COLOR0;
};
struct VSOutput
{
    float4 positon: SV_Position;  //clip space postion for system value
    float4 color : COLOR0; 
};


VSOutput VSMain(VSInput input) 
{
    VSOutput output;
    output.positon = float4(input.positon, 1);
    output.color = input.color;
    return output;
}


float4 PSMain(VSOutput input) : SV_Target
{
    return input.color;
}