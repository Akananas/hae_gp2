#version 120
uniform sampler2D 	texture;
uniform sampler2D 	noise;
uniform float 		time;	
uniform float 		maxTime;	
uniform vec2 center;
void main()
{
	vec2 uv = gl_TexCoord[0].xy;
	float ratioTime = mod(time,10) / maxTime;
	vec4 pixel = texture2D(texture, uv);
	vec2 mask = uv.xy;
	mask.x = (mask.x / 0.65) - 0.275;
	vec2 distanceVector = mask - center;
	float dist = sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);
	if(ratioTime <10){
		if(dist < ratioTime ){
			vec4 noisePixel = texture2D(noise, uv) / 10;
			pixel.rgb += (1 + dist)/ratioTime * noisePixel.rgb;
		}
		/*if(dist < 0.5 ){
			vec4 noisePixel = texture2D(noise, uv) / 10;
			pixel.rgb += (1 + dist)/0.5 * noisePixel.rgb;
		}*/
	}
    gl_FragColor = gl_Color * pixel;
}