#include "Basic.hlsli"

texture2D<float4> tex:register(t0);
SamplerState smp:register(s0);

float4 main(VSOutput input) :SV_TARGET{
	float4 texcolor = float4(tex.Sample(smp,input.uv));

	//����
	float3 light = normalize(float3(1,-1,1));
	float diffuse = saturate(dot(-light, input.normal));
	float brightness = diffuse + 0.3f;
	return float4(texcolor.rgb * brightness, texcolor.a) *color;

	//�g�U���ˌ�
	//float3 light = normalize(float3(1,-1,1)); //�E���� �����̃��C�g
	//float brightness = dot(-light, input.normal); //�����ւ̃x�N�g���Ɩ@���x�N�g���̓���
	//return float4(brightness, brightness, brightness, 1);//�P�x��RGB�ɑ�����ďo��

	//return float4(input.normal,1); //RGB�����ꂼ��@����XYZ,A��1�ŏo��
	/*return float4(tex.Sample(smp,input.uv)*color);*/
	/*return float4(1,1,1,1);*/
}