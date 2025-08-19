static float4 outColor;
static float3 fragColor;
static float2 fragTexCoord;

struct SPIRV_Cross_Input
{
    float2 fragTexCoord : TEXCOORD0;
    float3 fragColor : TEXCOORD1;
};

struct SPIRV_Cross_Output
{
    float4 outColor : SV_Target0;
};

void frag_main()
{
    outColor = float4(fragColor, 1.0f);
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    fragColor = stage_input.fragColor;
    fragTexCoord = stage_input.fragTexCoord;
    frag_main();
    SPIRV_Cross_Output stage_output;
    stage_output.outColor = outColor;
    return stage_output;
}
