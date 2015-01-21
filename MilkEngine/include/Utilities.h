#include "glm/glm.hpp"

struct Vertex
{
	union
	{
		struct
		{
			glm::vec3 Pos;
			glm::vec4 Color;
			glm::vec2 UV;
		};
		struct
		{
			float X, Y, Z;
			float R, G, B, A;
			float U, V;
		};
	};
	bool operator == (const Vertex& rhs){
		return (X == rhs.X && Y == rhs.Y && Z == rhs.Z
			&& R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A
			&& U == rhs.U && V == rhs.V);
	}
};

