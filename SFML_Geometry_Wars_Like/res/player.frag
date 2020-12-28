
uniform sampler2D 	texture;

uniform float 		time;	
uniform float 		maxTime;	

void main()
{
	vec2 uv = gl_TexCoord[0].xy;

	vec4 pixel = texture2D(texture, uv);
	pixel.r = 1;
	if(0.5 > time / maxTime){
		pixel.g = 1;
		pixel.b = 1;
	}

    gl_FragColor = gl_Color * pixel;

}