static float4 gl_Position;
static float3 inPosition;
static float2 fragTexCoord;
static float2 inTexCoord;
static float3 fragColor;
static float3 inColor;

struct SPIRV_Cross_Input
{
    float3 inPosition : TEXCOORD0;
    float2 inTexCoord : TEXCOORD1;
    float3 inColor : TEXCOORD2;
};

struct SPIRV_Cross_Output
{
    float2 fragTexCoord : TEXCOORD0;
    float3 fragColor : TEXCOORD1;
    float4 gl_Position : SV_Position;
};

void vert_main()
{
    gl_Position = float4(inPosition, 1.0f);
    fragTexCoord = inTexCoord;
    fragColor = inColor;
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    inPosition = stage_input.inPosition;
    inTexCoord = stage_input.inTexCoord;
    inColor = stage_input.inColor;
    vert_main();
    SPIRV_Cross_Output stage_output;
    stage_output.gl_Position = gl_Position;
    stage_output.fragTexCoord = fragTexCoord;
    stage_output.fragColor = fragColor;
    return stage_output;
}
