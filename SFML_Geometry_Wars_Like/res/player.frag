
uniform sampler2D 	texture;

uniform float 		time;	
uniform float 		maxTime;	

void main()
{
	vec2 uv = gl_TexCoord[0].xy;
	float ratioTime = time / maxTime;
	vec4 pixel = texture2D(texture, uv);
	pixel.r = 1;
	float ratioPixel = gl_TexCoord[0].x;
	if(ratioPixel > ratioTime){
		pixel.g = 1;
		pixel.b = 1;
	}else{
		pixel.g = 0.4;
	}
    gl_FragColor = gl_Color * pixel;

}