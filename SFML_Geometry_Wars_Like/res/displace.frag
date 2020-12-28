
uniform sampler2D 	texture;
uniform sampler2D 	texture2;

uniform float 		time;

uniform vec2		uvTranslateDisp;		
uniform vec2		uvScaleDisp;		

void main()
{
	vec2 uv = gl_TexCoord[0].xy;
	vec2 ouv = uv;
	float dispAmount = 0.0 + mod(time*0.1,1) * 1;
	
	uvScaleDisp*=3;
	uvScaleDisp -=  mod(time*0.1,0.33)*3;
	uvTranslateDisp.x = - mod(time*0.1,1);
	uvTranslateDisp.y = - mod(time*0.2,1);
	vec2 dir = texture2D(texture2,uv*uvScaleDisp+uvTranslateDisp);
	uv.x += (dir.x * 2.0 - 1.0) * dispAmount;
	uv.y += (dir.y * 2.0 - 1.0) * dispAmount;
    // récupère le pixel dans la texture
    //vec4 pixel = 0.5 * texture2D(texture, ouv) + 0.5 * texture2D(texture2,ouv);
	vec4 pixel = texture2D(texture, uv);
	
    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;

}