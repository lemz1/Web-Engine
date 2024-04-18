#pragma once

#include "engine/util/Math.h"

class Camera
{
public:
	Camera(
		uint32_t width,
		uint32_t height
	);
	~Camera();

	void Resize(
		uint32_t width,
		uint32_t height
	);

	const Mat4& GetProjection() const { return _projection; }
	const Mat4& GetInverseProjection() const { return _inverseProjection; }
	const Mat4& GetView() const { return _view; }
	const Mat4& GetInverseView() const { return _inverseView; }

	uint32_t GetWidth() const { return _width; }
	uint32_t GetHeight() const { return _height; }

	void SetVerticalFOV(float verticalFOV) { _verticalFOV = verticalFOV; RecalculateProjection(); }
	float GetVerticalFOV() const { return _verticalFOV; }

	void SetNearClipPlane(float nearClipPlane) { _nearClipPlane = nearClipPlane; RecalculateProjection(); }
	float GetNearClipPlane() const { return _nearClipPlane; }

	void SetFarClipPlane(float farClipPlane) { _farClipPlane = farClipPlane; RecalculateProjection(); }
	float GetFarClipPlane() const { return _farClipPlane; }

	void SetOrthographic(bool isOrthographic) { _isOrthographic = isOrthographic; RecalculateProjection(); }
	bool IsOrthographic() const { return _isOrthographic; }

	void SetOrthographicZoom(float orthographicZoom) { _orthographicZoom = Math::Max(orthographicZoom, 0.0001f); RecalculateProjection(); }
	float GetOrthographicZoom() const { return _orthographicZoom; }

	void SetPosition(const Vec3& position) { _position = position; RecalculateView(); }
	const Vec3& GetPosition() const { return _position; }

	void SetRotation(const Quat& rotation) { _rotation = rotation; RecalculateView(); }
	const Quat& GetRotation() const { return _rotation; }
private:
	void RecalculateProjection();
	void RecalculateView();
private:
	Mat4 _projection = Mat4Identity;
	Mat4 _inverseProjection = Mat4Identity;
	Mat4 _view = Mat4Identity;
	Mat4 _inverseView = Mat4Identity;

	uint32_t _width;
	uint32_t _height;
	float _verticalFOV = 45.0f;
	float _nearClipPlane = 0.1f;
	float _farClipPlane = 5000.0f;
	bool _isOrthographic = true;
	float _orthographicZoom = 1.0f;
	
	Vec3 _position = Vec3(0.0f);
	Quat _rotation = QuatIdentity;
};
