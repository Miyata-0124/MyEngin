#include "Basic.hlsli"

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

VSOutput main(float4 pos:POSITION, float2 uv : TEXCOORD)
{
	VSOutput output; // ピクセルシェーダに渡す値
	output.svpos = mul(mat, pos);
	output.uv = uv;
	return output;
}