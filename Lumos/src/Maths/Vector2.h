#pragma once
#include "lmpch.h"
#include "MathsCommon.h"

#include "Core/Serialisable.h"

namespace Lumos
{
	namespace Maths
	{
		class LUMOS_EXPORT MEM_ALIGN Vector2
		{
		public:
			Vector2() { ToZero(); }
			Vector2(const float x, const float y) : x(x), y(y) {}
			Vector2(const float x) : x(x), y(x) { }
			~Vector2() {}

#ifdef LUMOS_SSEVEC2
			union
			{
				struct
				{
					float x, y;
				};
				__m128 mmvalue;
			} MEM_ALIGN;
#else
			float x, y;
#endif

		public:

			float GetX() const { return x; }
			float GetY() const { return y; }
			void SetX(const float X) { x = X; }
			void SetY(const float Y) { y = Y; }

			void ToZero() { x = 0.0f; y = 0.0f; }

			inline void Normalise()
			{
				float length = Length();

				if (length != 0.0f)
				{
					length = 1.0f / length;
					x = x * length;
					y = y * length;
				}
			}

			inline float Length() const { return sqrt((x * x) + (y * y)); }

			inline friend std::ostream &operator<<(std::ostream &o, const Vector2 &v)
			{
				o << "Vector2(" << v.x << "," << v.y << ")" << std::endl;
				return o;
			}

			nlohmann::json Serialise()
			{
				nlohmann::json output;
				output["typeID"] = LUMOS_TYPENAME(Vector2);
				output["x"] = x;
				output["y"] = y;

				return output;
			};

			void Deserialise(nlohmann::json& data)
			{
				x = data["x"];
				y = data["y"];
			};

			inline Vector2 operator-(const Vector2 &a) const { return Vector2(x - a.x, y - a.y); }
			inline Vector2 operator+(const Vector2 &a) const { return Vector2(x + a.x, y + a.y); }
			inline Vector2 operator*(const float a) const { return Vector2(x * a, y * a); }
			inline Vector2 operator/(const float v) const { return Vector2(x / v, y / v); };
			inline bool operator==(const Vector2 &A) const { return (A.x == x && A.y == y) ? true : false; };
		};
	}
}
namespace std
{
	template<>
	struct hash<Lumos::Maths::Vector2>
	{
		size_t operator()(const Lumos::Maths::Vector2& x) const
		{
			return hash<float>()(x.GetX()) ^ (hash<float>()(x.GetY()) * 997u);
		}
	};
}
