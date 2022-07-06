#include "Basic.hlsli"

texture2D<float4> tex:register(t0);
SamplerState smp:register(s0);

float4 main(VSOutput input) :SV_TARGET{
	float4 texcolor = float4(tex.Sample(smp,input.uv));

	//環境光
	float3 light = normalize(float3(1,-1,1));
	float diffuse = saturate(dot(-light, input.normal));
	float brightness = diffuse + 0.3f;
	return float4(texcolor.rgb * brightness, texcolor.a) * color;

	//拡散反射光
	//float3 light = normalize(float3(1,-1,1)); //右下奥 向きのライト
	//float brightness = dot(-light, input.normal); //光源へのベクトルと法線ベクトルの内積
	//return float4(brightness, brightness, brightness, 1);//輝度をRGBに代入して出力

	//return float4(input.normal,1); //RGBをそれぞれ法線のXYZ,Aを1で出力
	/*return float4(tex.Sample(smp,input.uv)*color);*/
	/*return float4(1,1,1,1);*/
}