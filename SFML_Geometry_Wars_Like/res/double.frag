#version 120
uniform sampler2D texture;
uniform sampler2D texture2;

uniform vec2		uvTranslate;		
uniform vec2		uvScale;		

void main()
{
    // récupère le pixel dans la texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	pixel *= texture2D(texture2, (gl_TexCoord[0].xy+uvTranslate)*uvScale);

    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;

}