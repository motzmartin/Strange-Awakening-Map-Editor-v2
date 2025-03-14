#include "Camera.h"

Camera* Camera_Create()
{
	Camera* camera = calloc(1, sizeof(Camera));
	if (!camera) return NULL;

	return camera;
}

void Camera_Update(Camera* camera, VectorF playerPos, Uint64 elapsed)
{
	VectorF target = playerPos;
	VectorF diff = VectorF_Sub(target, camera->pos);

	float distance = sqrtf(powf(diff.x, 2.f) + powf(diff.y, 2.f));
	if (distance > 8.f)
	{
		camera->pos = VectorF_Add(camera->pos, VectorF_Scale(diff, distance * elapsed * 1e-10f));
	}
}

Vector Camera_GetCentered(Camera* camera)
{
	Vector cameraPos = Vector_New((int)floorf(camera->pos.x), (int)floorf(camera->pos.y));
	Vector center = Vector_New(576 - 24, 384 - 24);

	return Vector_Sub(cameraPos, center);
}

void Camera_Free(Camera* camera)
{
	free(camera);
}
