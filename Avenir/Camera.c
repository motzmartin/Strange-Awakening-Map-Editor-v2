#include "Camera.h"

Camera* Camera_Create()
{
	Camera* camera = calloc(1, sizeof(Camera));
	if (!camera) return NULL;

	return camera;
}

void Camera_Update(Camera* camera, Vector playerPos, Uint64 elapsed)
{
	Vector target = playerPos;
	Vector diff = Vector_Sub(target, camera->pos);

	float distance = sqrtf(powf(diff.x, 2.f) + powf(diff.y, 2.f));

	camera->pos = Vector_Add(camera->pos, Vector_Scale(diff, distance * elapsed * 1E-10F));
}

Vector Camera_GetCentered(Camera* camera)
{
	Vector center = { 576.f - 24.f, 384.f - 24.f };

	return Vector_Sub(Vector_Floor(camera->pos), center);
}

void Camera_Free(Camera* camera)
{
	free(camera);
}
