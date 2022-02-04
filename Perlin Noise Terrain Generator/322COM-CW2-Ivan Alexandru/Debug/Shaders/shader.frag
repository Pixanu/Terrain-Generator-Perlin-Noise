#version 330 core

in vec2 f_texCoord;
in vec2 f_texCoord2;
in vec3 f_normal;
in vec3 f_position;

out vec4 fragColor;

uniform sampler2D texture;
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform bool isWireframe;
uniform bool showLight;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{	
	
	//AMBIENT
	vec3 ambientColor = vec3(1, 1, 1);
	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * ambientColor;
	

	//DIFFUSE
	vec3 diffuseColor = vec3(1, 1, 0);
	vec3 lightDirection = normalize((model * vec4(lightPos, 1)).xyz - f_position);
	float brightness = clamp(dot(f_normal, lightDirection), 0, 1);
	vec3 diffuse = diffuseColor * brightness;
	
	vec3 result = (ambient + diffuse) * texture2D(texture, f_texCoord).xyz;
	
	if(isWireframe) 
	{
		fragColor = vec4(0.8, 0.8, 0.8, 1);
		//fragColor = vec4(0.14, 0.14, 0.15, 1);
	} 
	else 
	{
		if(showLight)
		{
			fragColor = vec4(result, 1.0);
		}
		else
		{
			fragColor = texture2D(texture, f_texCoord);
			
			
		}
	}

}