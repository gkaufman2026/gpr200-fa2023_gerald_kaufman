#include "../ew/ewMath/vec3.h"
#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/ewMath.h"
#include "transformations.h"

namespace gk {
	struct Camera {
		ew::Vec3 position;
		ew::Vec3 target; 
		float fov; 
		float aspectRatio;
		float nearPlane; 
		float farPlane;
		bool orthographic; 
		float orthoSize; 
		ew::Mat4 ViewMatrix() { // World->View
			return LookAt(position, target, ew::Vec3(0, 1, 0));
		}
		ew::Mat4 ProjectionMatrix() { // View->Clip
			if (orthographic) { // orthographic
				return Orthographic(orthoSize, aspectRatio, nearPlane, farPlane);
			}
			else { // Perspective
				return Perspective(fov, aspectRatio, nearPlane, farPlane);
			}
		}
	};
}