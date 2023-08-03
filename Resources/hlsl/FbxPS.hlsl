#include"FBX.hlsli"
struct TargetOutput {
    float4 target0:SV_TARGET0;
    float4 target1:SV_TARGET1;
};
//0番スロットに設定されたテクスチャ
Texture2D<float4> tex : register(t0);
//0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);
//エントリーポイント
TargetOutput main(VSOutput input)
{
    TargetOutput output;
    //テクスチャマッピング
    float4 texcolor = tex.Sample(smp, input.uv);
    //Lambert反射
    float3 light = normalize(float3(1, -1, 1));//右下奥向きライト
    float diffuse = saturate(dot(-light, input.normal));
    float brightness = diffuse + 0.3f;
    float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);
    //原色
    output.target1 = shadecolor * texcolor;
    //オブジェクトの反転
    //ターゲット1の色
    output.target0 = float4(1 - (shadecolor * texcolor).rgb, 1);
    //印影とテクスチャの色を合成
    return output;
}