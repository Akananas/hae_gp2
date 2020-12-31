#version 120
uniform sampler2D 	texture;
uniform sampler2D 	noise;
uniform float 		time;	
uniform float 		maxTime;	
uniform vec2 center;
void main()
{
	vec2 uv = gl_TexCoord[0].xy /(1280/720);
	float ratioTime = mod(time,10) / maxTime;
	vec4 pixel = texture2D(texture, uv);
	
	vec2 distanceVector = uv - center;
	float dist = sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);
	if(ratioTime <10){
		if(dist < ratioTime ){
			vec4 noisePixel = texture2D(noise, uv) / 10;
			pixel.rgb += (1 + dist)/ratioTime * noisePixel.rgb;
		}
	}
    gl_FragColor = gl_Color * pixel;
}