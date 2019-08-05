attribute vec4 attr_TexCoord0;
attribute vec4 attr_Color;
varying vec4   var_TexCoords;
varying vec4   var_Color;

void main()
{
	var_TexCoords.xy = attr_TexCoord0.st;
	var_Color = attr_Color;
}
