uniform float border_width;
uniform float aspect; // ratio of width to height
varying vec4 var_Color;
varying vec4 var_TexCoords;

void main()
{
  float maxX = 1.0 - 10;
  float minX = 10;
  float maxY = maxX / aspect;
  float minY = minX / aspect;

  if (var_TexCoords.x < maxX && var_TexCoords.x > minX &&
      var_TexCoords.y < maxY && var_TexCoords.y > minY)
  {
    gl_FragColor = var_Color;
  }
  else
  {
    gl_FragColor = vec4(0, 0, 0, 1);
  }
}