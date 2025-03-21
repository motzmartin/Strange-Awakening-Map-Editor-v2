#include "Camera.h"

Camera* Camera_Create()
{
	Camera* camera = calloc(1, sizeof(Camera));
	if (!camera) return NULL;

	return camera;
}

void Camera_Update(Camera* camera, VectorF playerPos, DynamicArray* rooms, float elapsed)
{
	VectorF target = VectorF_New(0.f, 0.f);

	Box* playerRoom = Camera_GetRoomByPlayerPos(rooms, playerPos);

	if (playerRoom)
	{
		VectorF roomPos = VectorConversion_FromVector(playerRoom->pos);
		VectorF roomSize = VectorConversion_FromVector(playerRoom->size);

		VectorF roomCenter = VectorF_Add(roomPos, VectorF_Div(roomSize, 2.f));

		target = VectorF_Scale(roomCenter, 12.f);
	}
	else
	{
		target = VectorF_Add(playerPos, VectorF_New(24.f, 24.f));
	}

	VectorF diff = VectorF_Sub(target, camera->pos);

	float factor = 1.f - expf(-elapsed * 7.f);
	camera->pos = VectorF_Add(camera->pos, VectorF_Scale(diff, factor));
}

Vector Camera_GetCentered(Camera* camera)
{
	Vector cameraPos = VectorConversion_FromVectorF(camera->pos);
	Vector center = Vector_New(576, 384);

	return Vector_Sub(cameraPos, center);
}

Box* Camera_GetRoomByPlayerPos(DynamicArray* rooms, VectorF playerPos)
{
	for (int i = 0; i < DynamicArray_GetSize(rooms); i++)
	{
		Box* room = DynamicArray_Get(rooms, i);

		if (playerPos.x + 24.f > (float)room->pos.x * 12.f &&
			playerPos.x + 24.f < (float)(room->pos.x + room->size.x) * 12.f &&
			playerPos.y + 47.f > (float)room->pos.y * 12.f &&
			playerPos.y + 47.f < (float)(room->pos.y + room->size.y) * 12.f)
		{
			return room;
		}
	}

	return NULL;
}

void Camera_Free(Camera* camera)
{
	free(camera);
}
