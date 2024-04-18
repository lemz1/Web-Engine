#include "Camera.h"

Camera::Camera(
	uint32_t width,
	uint32_t height
)
:	_width(width),
	_height(height)
{
	RecalculateView();
	RecalculateProjection();
}

Camera::~Camera()
{}

void Camera::RecalculateProjection()
{
	if (_isOrthographic)
	{
		float aspect = (float)_width / (float)_height;
		_projection = glm::ortho(
			-0.5f * aspect / _orthographicZoom,
			 0.5f * aspect / _orthographicZoom,
			-1.0f		   / _orthographicZoom,
			 1.0f          / _orthographicZoom,
			_nearClipPlane,
			_farClipPlane
		);
	}
	else
	{
		_projection = glm::perspectiveFov(
			glm::radians(_verticalFOV),
			(float)_width,
			(float)_height,
			_nearClipPlane,
			_farClipPlane
		);
	}
	_inverseProjection = glm::inverse(_projection);
}

void Camera::RecalculateView()
{
	_view = glm::translate(Mat4Identity, _position) * glm::mat4_cast(_rotation);
	_inverseView = glm::inverse(_view);
}

void Camera::Resize(
	uint32_t width, 
	uint32_t height
)
{
	if (_width == width && _height == height)
	{
		return;
	}

	_width = width;
	_height = height;

	RecalculateProjection();
}
