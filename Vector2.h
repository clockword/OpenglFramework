#pragma once
class Vector2
{
public:
	float x;
	float y;

public:
	Vector2();
	Vector2(float x, float y);
	virtual ~Vector2();

	Vector2& operator = (const Vector2 vec);
	Vector2& operator = (const float scalar);
	bool operator == (const Vector2& vec) const;
	bool operator != (const Vector2& vec) const;
	Vector2 operator + (const Vector2& vec) const;
	Vector2 operator - (const Vector2& vec) const;
	Vector2 operator * (const Vector2& vec) const;
	Vector2 operator * (const float scalar) const;
	Vector2 operator / (const Vector2& vec) const;
	Vector2 operator / (const float scalar) const;
	Vector2 operator - () const;
	Vector2& operator += (const Vector2& vec);
	Vector2& operator += (const float scalar);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator -= (const float scalar);
	Vector2& operator *= (const Vector2& vec);
	Vector2& operator *= (const float scalar);
	Vector2& operator /= (const Vector2& vec);
	Vector2& operator /= (const float scalar);

	float GetMagnitude();
	float GetSqrMagnitude();
	Vector2 GetNormalized();
	void Normalize();

	static float Dot(Vector2 lhs, Vector2 rhs);
	static Vector2 Lerp(Vector2 a, Vector2 b, float t);
	static float Angle(Vector2 from, Vector2 to);
	static Vector2 Zero();
};

