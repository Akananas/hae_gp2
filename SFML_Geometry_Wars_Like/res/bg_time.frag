#version 120
uniform sampler2D texture;
uniform float time;

void main()
{
    // récupère le pixel dans la texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // et multiplication avec la couleur pour obtenir le pixel final
	pixel.r = 0.3 + mod(time, 1.0) * 0.5;
    gl_FragColor = gl_Color * pixel;
	//gl_FragColor = vec4(1,0,0,1);
	
	//gl_FragColor =  vec4(gl_TexCoord[0].x,gl_TexCoord[0].y,0,1);
}