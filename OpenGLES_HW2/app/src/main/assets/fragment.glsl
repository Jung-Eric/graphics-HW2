#version 300 es

precision mediump float;

uniform sampler2D textureDiff;
uniform sampler2D textureDissolve;

uniform vec3 matSpec, matAmbi, matEmit;
uniform float matSh;
uniform vec3 srcDiffL, srcSpecL, srcAmbiL;
uniform vec3 srcDiffR, srcSpecR, srcAmbiR;
uniform float threshold;

in vec3 v_normal;
in vec2 v_texCoord;
in vec3 v_view, v_lightL, v_lightR;
in float v_attL, v_attR;

layout(location = 0) out vec4 fragColor;

void main() {

    vec3 color = texture(textureDiff, v_texCoord).rgb;

    // re-normalize unit vectors (normal, view, and light vectors)
    vec3 normal = normalize(v_normal);
    vec3 view = normalize(v_view);
    vec3 lightL = normalize(v_lightL);
    vec3 lightR = normalize(v_lightR);

    // diffuse term
    vec3 matDiff = texture(textureDiff,v_texCoord).grb;
    vec3 diffL = max(dot(normal,lightL),0.0)*srcDiffL*matDiff;
    vec3 diffR = max(dot(normal,lightR),0.0)*srcDiffR*matDiff;
    vec3 diff = diffL+diffR;

    // specular term
    vec3 reflL = 2.0 * normal * dot(normal,lightL)-lightL;
    vec3 reflR = 2.0 * normal * dot(normal,lightR)-lightR;
    vec3 specL = pow(max(dot(reflL,view),0.0),matSh)*srcSpecL * matSpec;
    vec3 specR = pow(max(dot(reflR,view),0.0),matSh)*srcSpecR * matSpec;
    vec3 spec = specL+specR;

    // ambient term
    vec3 ambiL = srcAmbiL * matAmbi;
    vec3 ambiR = srcAmbiR * matAmbi;
    vec3 ambi = ambiL+ambiR;

    color = diff+spec+ambi+matEmit;

    float alpha = 1.0f;

    // dissolving
    /*
    float dissolve = alpha ;
    if (dissolve < threshold){
        alpha = 0.0f;
      }
    */
    alpha = 1.0f - threshold;

    // final output color with alpha
    fragColor = vec4(color, alpha);
}