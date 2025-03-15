#include "Camera.h"

Camera* Camera_Create()
{
	Camera* camera = calloc(1, sizeof(Camera));
	if (!camera) return NULL;

	return camera;
}

void Camera_Update(Camera* camera,
	VectorF playerPos,
	Box** rooms,
	int roomsCursor,
	float elapsed)
{
	VectorF target = VectorF_Add(playerPos, VectorF_New(24.f, 24.f));

	for (int i = 0; i < roomsCursor; i++)
	{
		Box* room = rooms[i];

		if (playerPos.x + 24.f > (float)room->pos.x * 12.f &&
			playerPos.x + 24.f < (float)(room->pos.x + room->size.x) * 12.f &&
			playerPos.y + 47.f > (float)room->pos.y * 12.f &&
			playerPos.y + 47.f < (float)(room->pos.y + room->size.y) * 12.f)
		{
			target = VectorF_Scale(VectorF_FromVector(Vector_Add(room->pos, Vector_Div(room->size, 2))), 12.f);

			break;
		}
	}

	VectorF diff = VectorF_Sub(target, camera->pos);

	float factor = 1.f - expf(-elapsed * 7.f);
	camera->pos = VectorF_Add(camera->pos, VectorF_Scale(diff, factor));
}

Vector Camera_GetCentered(Camera* camera)
{
	Vector cameraPos = Vector_New((int)floorf(camera->pos.x), (int)floorf(camera->pos.y));
	Vector center = Vector_New(576, 384);

	return Vector_Sub(cameraPos, center);
}

void Camera_Free(Camera* camera)
{
	free(camera);
}
