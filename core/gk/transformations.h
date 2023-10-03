#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/vec3.h"

namespace transformationLib {

	ew::Mat4 matrix;

	//Identity matrix
	inline ew::Mat4 Identity() {
		return ew::IdentityMatrix();
	};
	//Scale on x,y,z axes
	inline ew::Mat4 Scale(ew::Vec3 s) {
		...
	};
	//Rotation around X axis (pitch) in radians
	inline ew::Mat4 RotateX(float rad) {
		...
	};
	//Rotation around Y axis (yaw) in radians
	inline ew::Mat4 RotateY(float rad) {
		...
	};
	//Rotation around Z axis (roll) in radians
	inline ew::Mat4 RotateZ(float rad) {
		...
	};
	//Translate x,y,z
	inline ew::Mat4 Translate(ew::Vec3 t) {
		...
	};

	struct Transform {
		ew::Vec3 position = ew::Vec3(0.0f, 0.0f, 0.0f);

		//Euler angles (degrees)
		ew::Vec3 rotation = ew::Vec3(0.0f, 0.0f, 0.0f);
		ew::Vec3 scale = ew::Vec3(1.0f, 1.0f, 1.0f);
		ew::Mat4 getModelMatrix() const {
			ew::Mat4 modelMatrix = Identity();
			modelMatrix = Scale(scale);
			RotateZ(rotation.z);
			RotateX(rotation.x);
			RotateY(rotation.y);
			Translate(position);
			return modelMatrix;
		}
	};
}